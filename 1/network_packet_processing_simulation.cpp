// network_packet_processing_simulation.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <queue>
#include <vector>
//#include <deque>

using namespace std;

struct Request 
{
	Request(int arrival_time, int process_time) :
		arrival_time(arrival_time),
		process_time(process_time)
	{}

	int arrival_time;
	int process_time;
};

struct Response 
{
	Response(bool dropped, int start_time) :
		dropped(dropped),
		start_time(start_time)
	{}

	bool dropped;
	int start_time;
};

class Buffer
{
public:
	Buffer(int size) :
		size_(size),
		finish_time_()
	{}

	Response Process(const Request &request) 
	{
		// write your code here
		int FinishTime;
		int StartTime;
		if (finish_time_.empty() == 1|| finish_time_.back() < request.arrival_time)
		{
			FinishTime = request.arrival_time + request.process_time;
		}
		else
		{
			FinishTime = finish_time_.back() + request.process_time;
		}
		//cout << "finishtime:"<<FinishTime << endl;
		//finish_time_.push(FinishTime);
		//cout << finish_time_.front()<<endl;
		//cout << "finishtime:" << finish_time_.front() <<" "<< finish_time_.back() << endl;
		//cout << finish_time_.size()<<endl;
		//finish_time_.pop();
		//cout << finish_time_.size() << endl;
		//cout << size_ << endl;
		//cout << finish_time_.empty();
		if (finish_time_.empty() == 1||request.arrival_time >= finish_time_.front())
		{
			if (finish_time_.empty() != 1)
			{
				if (request.arrival_time<finish_time_.back())
				{
					StartTime = finish_time_.back();
				}
				else
				{
					StartTime = request.arrival_time;
				}
				finish_time_.pop();
				finish_time_.push(FinishTime);
				return Response(0, StartTime);
			}
			else if (finish_time_.empty() == 1)
			{
				finish_time_.push(FinishTime);
				return Response(0, request.arrival_time);
			}
		
		}
		else if(finish_time_.size()>=size_)
		{
			return Response(1, request.arrival_time);
		}
		else
		{
			if(request.arrival_time<finish_time_.back())
			{
				StartTime = finish_time_.back();
			}
			else
			{
				StartTime = request.arrival_time;
			}
			finish_time_.push(FinishTime);
			return Response(0, StartTime);
		}
		
		/*
		if (finish_time_.empty() != 1)
		{
			if (request.arrival_time >= finish_time_.front())
			{
				cout << "finish_time_.front():" << finish_time_.front() << endl;
				finish_time_.pop();
			}
			if (finish_time_.empty() != 1)
			{
				if (finish_time_.size() < size_)
				{
					if (request.arrival_time >= finish_time_.back())
					{
						finish_time_.push(FinishTime);
						cout << "Response(0, request.arrival_time).dropped:" << Response(0, request.arrival_time).dropped << endl;
						cout << "(responses[i].dropped ? -1 : responses[i].start_time):" << (Response(0, request.arrival_time).dropped ? -1 : request.arrival_time) << endl;
						return Response(0, request.arrival_time);
					}
					return Response(1, request.arrival_time);
				}
				else
					return Response(1, request.arrival_time);
			}

		}
		else if (finish_time_.size() < size_)
		{
			finish_time_.push(FinishTime);
			return Response(0, request.arrival_time);
		}
		else 
			return Response(1, request.arrival_time);
		cout << "finish_time_.size()" << finish_time_.size() << endl;
		*/
		
	}
private:
	int size_;
	queue <int> finish_time_;
};

vector <Request> ReadRequests()
{
	vector <Request> requests;
	int count;
	cin >> count;
	for (int i = 0; i < count; ++i)
	{
		int arrival_time, process_time;
		cin >> arrival_time >> process_time;
		requests.push_back(Request(arrival_time, process_time));
	}
	return requests;
}

vector <Response> ProcessRequests(const vector <Request> &requests, Buffer *buffer) 
{
	vector <Response> responses;
	for (int i = 0; i < requests.size(); ++i)
		responses.push_back(buffer->Process(requests[i]));
	return responses;
}

void PrintResponses(const std::vector <Response> &responses) 
{
	for (int i = 0; i < responses.size(); ++i)
		cout << (responses[i].dropped ? -1 : responses[i].start_time) << endl;
}

int main()
{
	int size;
	cin >> size;
	vector <Request> requests = ReadRequests();

	Buffer buffer(size);
	vector <Response> responses = ProcessRequests(requests, &buffer);

	PrintResponses(responses);

	//system("pause");
	return 0;
}
