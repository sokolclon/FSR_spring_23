#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	char* filename = argv[1];
	ifstream fin(filename);
	ofstream data;
	data.open("data.dzn");
	long long N, W, pi, wi, i, j;
	fin >> N >> W;
	data << "N = " << N << ';' << endl;
	data << "W = " << W << ';' << endl;
	vector <long long> p(N);
	vector <long long> w(N);
	for (i = 0; i < N; i++) {
		fin >> pi >> wi;
		p[i] = pi;
		w[i] = wi;
	}
	data << "profit = [";
	for (i = 0; i < N; i++) {
		data << p[i] << ", ";
	}
	data << "];";
	data << endl;
	data << "size = [";
	for (i = 0; i < N; i++) {
		data << w[i] << ", ";
	}
	data << "];";
	data << endl;
	data.close();
	fin.close();
	system("minizinc --solver Gecode minizinc_ks.mzn data.dzn");
	return 0;
}
