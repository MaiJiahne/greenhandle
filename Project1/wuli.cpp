#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int main() 
{
	vector<double> time;
	vector<double> v;
	vector<double> result;
	const double length = 0.2;
	const double pyou = 1261.2;
	const double pball = 7800.0;
	const double D = 0.0225;
	const double d = 0.001015;
	const double g = 9.8;
	double temp;
	for (int i = 0; i < 5; i++) {
		cin >> temp;
		time.push_back(temp);
	}
	cout << "time:" << endl;
	for (auto& i : time) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) {
		v.push_back(0.2 / time[i]);
	}
	cout << "v:" << endl;
	for (auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) {
		result.push_back((( pball- pyou) * g * d * d) / (18 * v[i] * (1 + 2.4 * (d / D))));
	}
	cout << "result:" << endl;
	for (auto& i : result) {
		cout << i << " ";
	}
	cout << endl;
}