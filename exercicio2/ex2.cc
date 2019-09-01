#include <bits/stdc++.h> 
#include <iostream>
#include <vector>

using namespace std;

struct Task{
	int instantOfStart;
	int executionTime;
	int priority;
};

struct AlgorithmResult{
	float averageExecutionTime;
	float averageWaitTime;
	int contextSwitches;
	int totalProcessingTime;
};

AlgorithmResult FCFS(vector<Task> tasks){
	sort(tasks.begin(), tasks.end(), [](Task t1, Task t2){ return t1.instantOfStart < t2.instantOfStart; });
	
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

std::ostream& operator << (std::ostream &o, const AlgorithmResult a){
  return o << a.averageExecutionTime << " " << a.averageWaitTime << " " << a.contextSwitches << " " << a.totalProcessingTime;
}


int main() {
	int nTasks = 0;
	cin >> nTasks;
	
	vector<Task> tasks(nTasks, Task());
	
	for(auto& task: tasks) cin >> task.instantOfStart;
	for(auto& task: tasks) cin >> task.executionTime;
	for(auto& task: tasks) cin >> task.priority;
	
	cout << FCFS(tasks) << endl;
	
}
