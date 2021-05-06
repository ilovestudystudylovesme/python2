#include <iostream>
#include <climits>
using namespace std;


int trunc(int x) {
	return x > 0 ? x : 0;
}

int nDays = 60;
int d[60], sumd[60], s = 480, c = 8, ic = 20;
double p[60], f[60][2000];
int trace[60][2000];

int main() {

	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 2000; j++) {
			f[i][j] = INT_MAX;
		}
	}
	for (int i = 0; i < nDays; i++) {
		cin >> p[i];
	}

	for (int i = 0; i < nDays; i++) {
		cin >> d[i];
	}
	sumd[0] = d[0];
	for (int i = 1; i < nDays; i++) {
		sumd[i] = sumd[i - 1] + d[i];
	}
	for (int j = 0; j < 2000; j++) {
		int ifBuy = (j > 0) ? 1 : 0;
		f[0][j] = ifBuy * s + j * p[0] + trunc(sumd[0] - j) * ic + (j + trunc(j - sumd[0])) * 0.5 * c;
	}
	for (int i = 1; i < nDays; i++) {
		for (int j = 0; j < 2000; j++) {
			for (int k = 0; k <= j; k++) {
				int ifBuy = (j > k) ? 1 : 0;
				double cost = ifBuy * s + (j - k) * p[i] + trunc(sumd[i] - j) * ic + (trunc(k - sumd[i - 1]) + j - k + trunc(j - sumd[i])) * 0.5 * c;
				double totalcost = f[i - 1][k] + cost;
				if (totalcost < f[i][j]) {
					f[i][j] = totalcost;
					trace[i][j] = k;
				}
			}
		}
	}
	double minCost = INT_MAX;
	int k;
	for (int j = sumd[50]; j < 2000; j++) {
		if (f[59][j] < minCost) {
			minCost = f[59][j];
			k = j;
		}
	}
	int seq[60];

	for (int j = 59; j >= 0; j--) {
		int lastk = trace[j][k];
		seq[j] = k - lastk;
		k = lastk;
	}
	cout << minCost << endl;
	for (int j = 0; j < 60; j++) {
		cout << seq[j] << " ";
	}
}
