#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::string;
using std::unordered_map;
using std::vector;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;

    // using unordered map to store the name and phone number pair
    unordered_map<int, string> phone_book;
    string nf = "not found";

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            phone_book[queries[i].number] = queries[i].name;
        } else if (queries[i].type == "del") {
            phone_book.erase(queries[i].number);
        } else {
            auto iter = phone_book.find(queries[i].number);
            if (iter == phone_book.end()) {
                result.push_back(nf);
            } else {
                result.push_back(iter->second);
            }
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
