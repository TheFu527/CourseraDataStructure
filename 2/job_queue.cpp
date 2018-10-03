// job_queue.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class JobQueue {
private:
	int num_workers_;
	struct Worker
	{
		long long works;
		int num;
	};
	vector<int> jobs_;
	vector<int> assigned_workers_;
	vector<long long> start_times_;
	vector<Worker> workers;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	int parent(int i)
	{
		return (i - 1) / 2;
	}

	int left(int i)
	{
		return 2 * i + 1;
	}

	int right(int i)
	{
		return 2 * i + 2;
	}

	void MinHeapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = 0;
		if (l < workers.size() && workers[l].works < workers[i].works)
			smallest = l;
		else
			smallest = i;
		if (r < workers.size() && workers[r].works < workers[smallest].works)
		{
			smallest = r;
		}
		if (l < workers.size() && r < workers.size() && workers[l].works == workers[r].works && (smallest == l || smallest == r))
		{
			if (workers[l].num < workers[r].num)
				smallest = l;
			else
				smallest = r;
		}
		if (smallest != i)
		{
			swap(workers[i], workers[smallest]);
			MinHeapify(smallest);
		}
		else
		{
			if (l < workers.size() && workers[l].num < workers[i].num && workers[l].works == workers[i].works)
				smallest = l;
			else
				smallest = i;
			if (r < workers.size() && workers[r].num < workers[smallest].num && workers[r].works == workers[smallest].works)
				smallest = r;
			if (smallest != i)
			{
				swap(workers[i], workers[smallest]);
				MinHeapify(smallest);
			}
		}
	}

	void BuildMinHeap()
	{
		workers.resize(num_workers_);
		for (int i = 0; i < workers.size(); i++)
			workers[i].num = i;
	}

	long long HeapMiniNum()
	{
		return workers[0].works;
	}
	/*
	void HeapIncreaseKey(int key)
	{
		workers[1] += key;
		while (i > 1 && workers[parent(i)] > workers[i])
		{
			swap(workers[i], workers[parent(i)]);
			i = parent(i);
		}
	}
	*/

	void AssignJobs() {
		// TODO: replace this code with a faster algorithm.
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		//vector<long long> next_free_time(num_workers_, 0);
	/*
		for (int i = 0; i < jobs_.size(); ++i) {
			int duration = jobs_[i];
			int next_worker = 0;
			for (int j = 0; j < num_workers_; ++j) {
				if (next_free_time[j] < next_free_time[next_worker])
					next_worker = j;
			}
			assigned_workers_[i] = next_worker;
			start_times_[i] = next_free_time[next_worker];
			next_free_time[next_worker] += duration;
		}
	*/
		BuildMinHeap();
		for (int i = 0; i < jobs_.size(); ++i)
		{
			start_times_[i] = workers[0].works;
			assigned_workers_[i] = workers[0].num;
			workers[0].works += jobs_[i];
			MinHeapify(0);
		}


	}

public:
	void Solve() {
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	//system("pause");
	return 0;
}
