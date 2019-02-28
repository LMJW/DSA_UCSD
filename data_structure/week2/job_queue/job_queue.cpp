#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;

struct my_task {
    int thread;
    long long task_time;
    my_task(int a, long long b) : thread(a), task_time(b) {}
    bool operator<(const my_task& t2) const {
        if (task_time == t2.task_time) {
            return thread > t2.thread;
        }
        return task_time > t2.task_time;
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

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

    void AssignJobs() {
        priority_queue<my_task> pq;
        for (int i = 0; i < num_workers_; ++i) {
            pq.push(my_task(i, 0));
        }
        for (int i = 0; i < jobs_.size(); ++i) {
            auto t = pq.top();
            int tid = t.thread;
            long long starttime = t.task_time;
            pq.pop();

            assigned_workers_.push_back(tid);
            start_times_.push_back(starttime);
            pq.push(my_task(tid, starttime + jobs_[i]));
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
    return 0;
}
