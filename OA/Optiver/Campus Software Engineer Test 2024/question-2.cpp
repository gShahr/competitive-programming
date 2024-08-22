// BODY
#include <cstdint>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct ProcessSchedule {
    int startTime;
    int endTime;
};

struct Dependency {
    int pid1;
    int pid2;
};

class Scheduler {
public:
    Scheduler(const vector<ProcessSchedule>& processes, const vector<Dependency>& dependencies)
        : processes(processes), dependencies(dependencies) {
        BuildGraph();
        TopologicalSort();
        int n = processes.size();
        depAdj.resize(n+1);
        for (int i = 0; i < n; i++) {
            depAdj[dependencies[i].pid2].push_back(dependencies[i].pid1);
        }
    }

    void PrintSchedule() {
        bool bad = hasCycle;
        for (auto pid : sortedProcesses) {
            int start = -1;
            int end = 1e9;
            for (int pidDep: depAdj[pid]) {
                start = max(start, processes[pidDep-1].startTime);
                end = min(end, processes[pidDep-1].endTime);
            }
            if (start != -1 && end != -1) {
                int startTime = max(start+1, processes[pid-1].startTime);
                int endTime = min(processes[pid-1].endTime, end-1);
                if (start >= end 
                || endTime - startTime <= 0
                || !(startTime > start && endTime < end)) {
                    bad = true;
                    break;
                }
                processes[pid-1].startTime = startTime;
                processes[pid-1].endTime = endTime;
            }
        }
        if (bad) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        for (auto pid: processes) {
            cout << pid.startTime << ' ' << pid.endTime << endl;
        }
    }

private:
    vector<ProcessSchedule> processes;
    vector<Dependency> dependencies;
    unordered_map<int, vector<int>> adjList;
    vector<int> sortedProcesses;
    vector<vector<int>> depAdj;
    bool hasCycle = false;

    void BuildGraph() {
        for (const auto& dep : dependencies) {
            adjList[dep.pid1].push_back(dep.pid2);
        }
    }

    bool TopologicalSort() {
        unordered_map<int, int> inDegree;
        for (const auto& pair : adjList) {
            if (inDegree.find(pair.first) == inDegree.end()) {
                inDegree[pair.first] = 0;
            }
            for (int neighbor : pair.second) {
                inDegree[neighbor]++;
            }
        }

        queue<int> q;
        for (const auto& pair : inDegree) {
            if (pair.second == 0) {
                q.push(pair.first);
            }
        }

        int count = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            sortedProcesses.push_back(node);
            count++;

            for (int neighbor : adjList[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Check for nodes with no dependencies
        for (int i = 1; i <= processes.size(); ++i) {
            if (inDegree.find(i) == inDegree.end()) {
                sortedProcesses.push_back(i);
                count++;
            }
        }

        // If count does not match the number of processes, there is a cycle
        if (count != processes.size()) {
            hasCycle = true;
            return false;
        }

        return true;
    }
};

int main() {

    int T;
    std::cin >> T;

    while (T--)
    {
        int N, M;
        std::cin >> N >> M;

        std::vector<ProcessSchedule> processes(N);
        for (int i = 0; i < N; ++i)
        {
            std::cin >> processes[i].startTime >> processes[i].endTime;
        }

        std::vector<Dependency> dependencies(M);
        for (int i = 0; i < M; ++i)
        {
            std::cin >> dependencies[i].pid1 >> dependencies[i].pid2;
        }

        Scheduler scheduler(processes, dependencies);
        scheduler.PrintSchedule();
    }

    return 0;
}