#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double len(vector <int> w, vector <double> x, vector <double> y, long long V) {
	double ans = 0;
	for (int i = 0; i < V - 1; i++) {
		int j = w[i + 1];
		ans += sqrt((x[w[i]] - x[j]) * (x[w[i]] - x[j]) + (y[w[i]] - y[j]) * (y[w[i]] - y[j]));
	}
	ans += sqrt((x[w[V - 1]] - x[w[0]]) * (x[w[V - 1]] - x[w[0]]) + (y[w[V - 1]] - y[w[0]]) * (y[w[V - 1]] - y[w[0]]));
	return ans;
}

int main(int argc, char** argv) {
	char* filename = argv[1];
	ifstream fin(filename);
	long long V, i, j, k;
	double ans = 0, ans_cur = 0, t = 1;
	fin >> V;
	vector <double> x(V);
	vector <double> y(V);
	vector <int> trek(V), way(V);
	for (i = 0; i < V; i++) {
		fin >> x[i] >> y[i];
		trek[i] = i;
	}
	fin.close();
	ans = len(trek, x, y, V);
	for (i = 0; i < 1000000; i++) {
		way = trek;
		swap(way[rand() % V], way[rand() % V]);
		ans_cur = len(way, x, y, V);
		if (ans_cur < ans) {
			trek = way;
			ans = ans_cur;
		}
		else {
			if (double(rand()) / RAND_MAX < exp(ans_cur - ans) / t) {
				trek = way;
				ans = ans_cur;
			}
		}
		t *= 0.99;
	}
	cout << endl;
	cout << ans;
	return 0;
}