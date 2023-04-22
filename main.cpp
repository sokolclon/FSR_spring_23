#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	char* filename = argv[1];
	ifstream fin(filename);
	long long V, E, i, j, k, es, ee, flag;
	fin >> V >> E;
	vector < vector <long long> > graph(V, vector <long long> (V, 0));
	for (i = 0; i < E; i++) {
		fin >> es >> ee;
		graph[es][ee] = 1;
        graph[ee][es] = 1;
		graph[es][es] = 1;
		graph[ee][ee] = 1;
	}
	int c_color = 0;
    vector <int> used(V, 0);
    for (i = 0; i < V; i++) {
        if (used[i] != 0) continue;
        used[i] = 1;
        flag = 0;
        if (i != V - 1) {
            for (j = i + 1; j < V; j++) {
                if (!graph[i][j] && !used[j]) {
                    flag = 1;
                    break;
                }
            }
        }
        else {
            c_color++;
            break;
        }
        while (flag) {
            for (j = i + 1; j < V - 1; j++) {
                if (graph[i][j] == 0 && used[j] == 0) break;
            }
            if (j == V) break;
            used[j] = 1;
            for (k = 0; k < V; k++) {
                if (graph[i][k] + graph[j][k] != 0) graph[i][k] = 1;
            }
            flag = 0;
            for (j = i + 1; j < V; j++) {
                if (!graph[i][j] && !used[j]) {
                    flag = 1;
                    break;
                }
            }
        }
        c_color++;
    }
    cout << c_color << endl;
	fin.close();
	return 0;
}