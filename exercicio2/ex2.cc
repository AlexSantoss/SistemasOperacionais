#include <bits/stdc++.h> 
#include <iostream>
#include <vector>

using namespace std;

struct Task{
	int pid;
	int instantOfStart;
	int executionTime;
	int priority;
	int elapsedTime;
	int lastEnd;
};

struct AlgorithmResult{
	float averageExecutionTime;
	float averageWaitTime;
	int contextSwitches;
	int totalProcessingTime;
};

std::ostream& operator << (std::ostream &o, const AlgorithmResult a){
    return o << a.averageExecutionTime << " " << a.averageWaitTime << " " << a.contextSwitches << " " << a.totalProcessingTime;
}

void printTasks(vector<Task> tasks){
	for(auto task: tasks) {
		cout << task.instantOfStart << " " << task.executionTime << " " << task.elapsedTime << " " << task.lastEnd << " | ";
	}
	cout << endl;
}


void clearVector(vector<Task>& tasks){
	int i = 0;
    for(auto& task: tasks) {
        task.elapsedTime = 0;
        task.lastEnd = task.instantOfStart;
        task.pid = i++;
    }
}


AlgorithmResult FCFS(vector<Task> tasks){
	
	int lastEnd = 0;
	AlgorithmResult result{0, 0, 0, 0};
	
	for(auto task: tasks) {
		result.averageExecutionTime += task.executionTime+lastEnd-task.instantOfStart;
		result.averageWaitTime += lastEnd - task.instantOfStart;
		
		lastEnd += task.executionTime;
	}
	
	result.averageExecutionTime /= tasks.size();
	result.averageWaitTime /= tasks.size();
	result.contextSwitches = tasks.size() - 1;
	result.totalProcessingTime = lastEnd;
	return result;
}

AlgorithmResult RR(vector<Task> tasks){
    AlgorithmResult result{0, 0, 0, 0};
    vector<Task> row;
    int i=0;

    for(long unsigned int idx = 0, quantum = 0; i == 0 || row.size() != 0; i++){

        while(tasks[idx].instantOfStart == i && tasks.size() > idx) row.push_back(tasks[idx++]);

        if(row.front().elapsedTime == row.front().executionTime){
            row.front().lastEnd = i;
            result.averageExecutionTime += i - row.front().instantOfStart;
            
            row.erase(row.begin());
            
            quantum = 0;
            result.averageWaitTime += i-row.front().lastEnd;
            
            result.contextSwitches++;
        }

        if(quantum == 2) {
			row.push_back(row.front());
			
			row.front().lastEnd = i;
            row.erase(row.begin());
            
            quantum = 0;
            result.averageWaitTime += i-row.front().lastEnd;
            
            result.contextSwitches++;
        }

        row.front().elapsedTime++;
        quantum++;
    }
    
    result.averageWaitTime /= tasks.size();
    result.averageExecutionTime /= tasks.size();
    result.totalProcessingTime = --i;
    result.contextSwitches--;
    return result;
}

AlgorithmResult SJF(vector<Task> tasks){
    AlgorithmResult result{0, 0, 0, 0};
    vector<Task> row;
    int i=0;

    for(long unsigned int idx = 0; i == 0 || row.size() != 0; i++){
        while(tasks[idx].instantOfStart <= i && tasks.size() > idx) row.push_back(tasks[idx++]);
        sort(row.begin(), row.end(), [](Task t1, Task t2){ return t1.executionTime < t2.executionTime; });
        
        result.averageWaitTime += i - row.front().lastEnd;
        result.averageExecutionTime += row.front().executionTime + i - row.front().instantOfStart;
        result.contextSwitches++;
        i += row.front().executionTime - 1;

        row.erase(row.begin());
    }
    
    result.averageWaitTime /= tasks.size();
    result.averageExecutionTime /= tasks.size();
    result.totalProcessingTime = i;
    result.contextSwitches--;
    return result;
}

AlgorithmResult SRTF(vector<Task> tasks){
    AlgorithmResult result{0, 0, 0, 0};
    vector<Task> row;
    int i=0;

    for(long unsigned int idx = 0; i == 0 || row.size() > 0; i++){
        while(tasks[idx].instantOfStart <= i && tasks.size() > idx)row.push_back(tasks[idx++]);
        
        auto lastFrontPid = row.front().pid;
        if(row.front().executionTime - row.front().elapsedTime <= 0) {
			result.averageExecutionTime += i - row.front().instantOfStart;
			row.erase(row.begin());
		}
        
        sort(row.begin(), row.end(), [](Task t1, Task t2){ return t1.executionTime-t1.elapsedTime < t2.executionTime-t2.elapsedTime; });
        if(i != 0 && lastFrontPid != row.front().pid) {
			for(auto& task: row) if(task.pid == lastFrontPid) task.lastEnd = i;
			result.averageWaitTime += i - row.front().lastEnd;
			result.contextSwitches++;
		}
		
		row.front().elapsedTime++;
    }
    
    result.averageWaitTime /= tasks.size();
    result.averageExecutionTime /= tasks.size();
    result.totalProcessingTime = i-1;
    return result;
}


int main() {
	int nTasks = 0;
	cin >> nTasks;
	
	vector<Task> tasks(nTasks, Task());
	
	for(auto& task: tasks) cin >> task.instantOfStart;
	for(auto& task: tasks) cin >> task.executionTime;
	for(auto& task: tasks) cin >> task.priority;

    sort(tasks.begin(), tasks.end(), [](Task t1, Task t2){ return t1.instantOfStart < t2.instantOfStart; });
    clearVector(tasks);

	cout << FCFS(tasks) << endl;
	cout << RR(tasks) << endl;
	cout << SJF(tasks) << endl;
	cout << SRTF(tasks) << endl;
}
