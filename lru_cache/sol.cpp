#include<bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    unordered_map<int, list<pair<int, int>>::iterator> keyToNode;
    list<pair<int, int>> cacheList;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto mapIterator = keyToNode.find(key);
        if(mapIterator == keyToNode.end()) {
            return -1;
        }
        auto listIterator = mapIterator->second;
        int value = listIterator->second;
        cacheList.splice(cacheList.begin(), cacheList, listIterator);
        return value;
    }

    void put(int key, int value) {
        auto mapIterator = keyToNode.find(key);
        if(mapIterator != keyToNode.end()) {
            auto listIterator = mapIterator->second;
            listIterator->second = value;
            cacheList.splice(cacheList.begin(), cacheList, listIterator);
            return;
        }
        cacheList.push_front({key, value});
        keyToNode[key] = cacheList.begin();

        if(cacheList.size() > capacity) {
            int leastRecentlyUsedKey = cacheList.back().first;
            keyToNode.erase(leastRecentlyUsedKey);
            cacheList.pop_back();
        }
    }
};


class Solution {
public:
    vector<string> solve(vector<string> &operationNames, vector<vector<int>> &operationInputs) {
        vector<string> results;
        LRUCache *cache = nullptr;
        for(int i=0; i<operationNames.size(); i++) {
            string &name = operationNames[i];
            vector<int> &input = operationInputs[i];
            if(name == "LRUCache") {
                if(cache) delete cache;
                int capacity = input[0];
                cache = new LRUCache(capacity);
                results.push_back("null");
            } else if(name == "put") {
                int key = input[0];
                int value = input[1];
                cache->put(key, value);
                results.push_back("null");
            } else if(name == "get") {
                int key = input[0];
                int value = cache->get(key);
                results.push_back(to_string(value));
            }
        }

        if(cache) {
            delete cache;
        }

        return results;
    }

    void printInputs(vector<string> &operationNames, vector<vector<int>> &operationInputs) {   
        for(int i=0; i<operationNames.size(); i++) {
            cout<<operationNames[i]<<" { ";
            for(auto &x: operationInputs[i]) cout<<x<<" ";
            cout<<"}\n";
        }
    }
};


vector<string> split(string &input, const string &delimeter) {
    vector<string> tokens;
    int start = 0;
    int end = input.find(delimeter);

    while(end != string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + delimeter.size();
        end = input.find(delimeter, start);
    }

    tokens.push_back(input.substr(start));
    return tokens;
}

int main()
{
    ios_base::sync_with_stdio(false);
    string input;
    getline(cin, input);
    input = input.substr(2, input.size() - 4);
    vector<string> operationNames = split(input, string("\",\""));
    getline(cin, input);
    input = input.substr(2, input.size() - 4);
    vector<vector<int>> operationInputs;
    for(auto &x: split(input, string("],["))) {
        vector<int> inputs;
        for(auto &i: split(x, string(","))) {
            inputs.push_back(stoi(i));
        }
        operationInputs.push_back(inputs);
    }
    Solution solution;
    vector<string> results = solution.solve(operationNames, operationInputs);
    cout<<"[";
    for(int i=0; i<results.size(); i++) {
        cout<<(i>0 ? ", ": "")<<results[i];
    }
    cout<<"]\n";
    return 0;
}