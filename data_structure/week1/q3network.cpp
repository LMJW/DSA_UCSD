#include <iostream>
#include <queue>
#include <vector>

using std::vector;

struct Request {
    Request(int arrivetime, int processtime)
        : arrival_time(arrivetime), process_time(processtime){};

    int arrival_time, process_time;
};

struct Response {
    Response(bool dropped, int start_time)
        : dropped(dropped), start_time(start_time){};

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size) : size_(size){};

    inline Response Process(const Request& request) {
        if (finish_time.size() < size_) {
            if (finish_time.empty()) {
                finish_time.push(request.arrival_time + request.process_time);
                return Response(false, request.arrival_time);
            } else {
                int last_finish_time = finish_time.back();
                finish_time.push(last_finish_time + request.process_time);
                return Response(false, last_finish_time);
            }
        } else if (request.arrival_time < finish_time.front()) {
            return Response(true, 0);
        } else {
            int last_finish_time = finish_time.back();
            int t = std::max(last_finish_time, request.arrival_time);
            finish_time.push(t + request.process_time);
            finish_time.pop();
            return Response(false, t);
        }
    };

private:
    size_t size_;
    std::queue<int> finish_time;
};

vector<Request> ReadRequest() {
    vector<Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request{arrival_time, process_time});
    }
    return requests;
}

vector<Response> ProcessRequests(vector<Request>& requests, Buffer& buffer) {
    vector<Response> responses;
    for (size_t i = 0; i < requests.size(); ++i) {
        responses.push_back(buffer.Process(requests[i]));
    }
    return responses;
}

void PrintResponse(vector<Response> responses) {
    for (size_t i = 0; i < responses.size(); ++i) {
        if (responses[i].dropped) {
            std::cout << -1 << "\n";
        } else {
            std::cout << responses[i].start_time << "\n";
        }
    }
}

int main() {
    int bufsize;
    std::cin >> bufsize;
    Buffer buffer = Buffer(bufsize);

    vector<Request> requests = ReadRequest();
    vector<Response> responses = ProcessRequests(requests, buffer);
    PrintResponse(responses);
    return 0;
}