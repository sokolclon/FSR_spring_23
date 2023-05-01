#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#define INT_MAX 2147483647

using namespace std;

class uno {
public:
	vector<int> gene;
	double suitability;
public:
	uno() {
		suitability = INT_MAX;
	}
	friend bool operator<(const uno &c1, const uno &c2);
	friend bool operator>(const uno &c1, const uno &c2);
};

bool operator<(const uno &c1, const uno &c2) {
	return c1.suitability < c2.suitability;
}

bool operator>(const uno &c1, const uno &c2) {
	return c1.suitability > c2.suitability;
}

bool repeat(vector <int> a, int x) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == x)
			return true;
	}
	return false;
}

vector <int> generate_gene(int V) {
	vector <int> gene(V, 0);
	int i = 1;
	while (i < V) {
		int temp = rand() % (V - 1) + 1;
		if (!repeat(gene, temp)) {
			gene[i] = temp;
			i++;
		}
	}
	return gene;
}

vector <int> mutate_gene(vector <int> gene, int V, int k) {
	int cnt = 0;
	while (cnt < k) {
		int r = rand() % (V - 1) + 1;
		int r1 = rand() % (V - 1) + 1;
		if (r1 != r) {
			int temp = gene[r];
			gene[r] = gene[r1];
			gene[r1] = temp;
			cnt++;
		}
	}
	return gene;
}

vector <int> change_ribs(vector <int> gene, int V) {
	int A, B;
	while (true) {
		A = rand() % (V - 2);
		B = rand() % (V - 2);
		if (B < A) swap(A, B);
		if (A + 1 < B) break;
	}
	vector<int> new_gene;
	new_gene = gene;
	new_gene[A + 1] = gene[B];
	int i = 1;
	while (B - i > A) {
		new_gene[A + 1 + i] = gene[B - i];
		i++;
	}
	return new_gene;
}

double find_suitability(vector<int> gene, vector <vector <double> > &graph) {
	double f = 0;
	for (int i = 0; i < gene.size() - 1; i++) {
		if (graph[gene[i]][gene[i + 1]] == INT_MAX) {
		    return INT_MAX;
		}
		f += graph[gene[i]][gene[i + 1]];
	}
	return f;
}

uno solver(vector <vector <double> > &graph, int V) {
	int gen = 1;
	vector <uno> pop;
	uno temp;
	temp.gene = generate_gene(V);
	temp.suitability = find_suitability(temp.gene, graph);
	pop.push_back(temp);
	while (gen <= 10000) {
		sort(pop.begin(), pop.end());
		while (pop.size() >= 5) {
			pop.erase(pop.begin() + (pop.size() / 2), pop.end());
		}
		for (int i = 0; i < pop.size(); i++) {
			uno p1 = pop[i];
			int cnt = 0;
			while (true) {
				vector <int> new_g;
				new_g = change_ribs(p1.gene, V);
				uno new_gene;
				new_gene.gene = new_g;
				new_gene.suitability = find_suitability(new_gene.gene, graph);
				if (new_gene.suitability <= pop[i].suitability) {
					pop[i] = new_gene;
					break;
				} 
				else if (cnt > 100) {
					temp.gene = mutate_gene(new_gene.gene, V, rand() % 100 + 5);
					temp.suitability = find_suitability(temp.gene, graph);
					pop.push_back(temp);
					break;
				}
				cnt++;
			}
		}
		gen++;
	}
	sort(pop.begin(), pop.end());
	return pop[0];
}

int main(int argc, char** argv) {
	char* filename = argv[1];
	ifstream fin(filename);
	int V, i, j; fin >> V;
	vector <double> x(V);
	vector <double> y(V);
	double xi, yi, ans = 0;
	for (i = 0; i < V; i++) {
		fin >> xi >> yi;
		x[i] = xi;
        y[i] = yi;
	}
	vector <vector <double> > graph(V, vector <double> (V, 0));
	for (i = 0; i < V; i++) {
	    for (j = i + 1; j < V; j++) {
			graph[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			graph[j][i] = graph[i][j];
		}
	}
	uno A;
	A = solver(graph, V);
	for (i = 0; i < V - 1; i++) {
		ans += graph[A.gene[i]][A.gene[i + 1]];
	}
	ans += graph[A.gene[V - 1]][A.gene[0]];
	cout << ans << endl;
	fin.close();
	return 0;
}
