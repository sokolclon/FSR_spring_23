#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	char* filename = argv[1];
	ifstream fin(filename);
	long long N, W, pi, wi, i, j;
	fin >> N >> W;
	vector <long long> p(N);
	vector <long long> w(N);
	for (i = 0; i < N; i++) {
		fin >> pi >> wi;
		p[i] = pi;
		w[i] = wi;
	}
	vector < vector <long long>> sol(N, vector <long long> (W + 1, 0));
	for (i = 0; i < N; i++) {
		for (j = 0; j <= W; j++) {
			if (w[i] <= j) {
				if (i > 0) {
					sol[i][j] = max(sol[i - 1][j], sol[i - 1][j - w[i]] + p[i]);
				}
				else {
					sol[i][j] = p[i];
				}
			}
			else {
				if (i > 0) {
					sol[i][j] = sol[i - 1][j];
				}
			}
		}
	}
	vector <int> solution(N, 0);
	i = N - 1; j = W;
	while (sol[i][j]) {
		if (i >= 1) {
			if (sol[i][j] == sol[i - 1][j]) {
				i--;
			}
			else if (sol[i][j] == p[i] + sol[i - 1][j - w[i]]) {
				solution[i] = 1;
				j = j - w[i];
				i--;
			}
		}
		else {
			break;
		}
	}
	long long psum = 0, wsum = 0;
	for (i = 0; i < N; i++) {
	    if (solution[i] != 0) {
		    psum += p[i];
		    wsum += w[i];
	    }
	}
	cout << "Total value: " << psum << endl;
	cout << "Remaining weight: " << W - wsum << endl;
	for (i = 0; i < N; i++) {
	    cout << solution[i] << ' ';
	}
	cout << endl;
	fin.close();
	return 0;
}
