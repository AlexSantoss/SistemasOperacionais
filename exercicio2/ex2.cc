#include <bits/stdc++.h> 
#include <iostream>
#include <vector>

using namespace std;

struct Task{
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
    for(auto& task: tasks) {
        task.elapsedTime = 0;
        task.lastEnd = task.instantOfStart;
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

    //i = tempo;
    //idx = index da lista de tasks
    for(int idx = 0, quantum = 0; i == 0 || row.size() != 0; i++){

        //Adicionar tasks na fila
        while(tasks[idx].instantOfStart == i) row.push_back(tasks[idx++]);

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

int main() {
	int nTasks = 0;
	cin >> nTasks;
	
	vector<Task> tasks(nTasks, Task());
	
	for(auto& task: tasks) cin >> task.instantOfStart;
	for(auto& task: tasks) cin >> task.executionTime;
	for(auto& task: tasks) cin >> task.priority;

    sort(tasks.begin(), tasks.end(), [](Task t1, Task t2){ return t1.instantOfStart < t2.instantOfStart; });

	cout << FCFS(tasks) << endl;
	clearVector(tasks);
	cout << RR(tasks) << endl;
}
