#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int nearist(vector<vector<int>> row, int first, int path[][5], int size);
int cross_out(vector<vector<int>>& a, int col,int size);
int print(vector<vector<int>> cost, int path[][5], int size);

int main() {
	int over_size = 9999;
	int size = 5;
	int path[5][5];
	

	vector<vector<int>> cost;
	vector<int> a, b, c, d, f;


	a.push_back(over_size);
	a.push_back(25);
	a.push_back(40);
	a.push_back(31);
	a.push_back(27);
	cost.push_back(a);

	b.push_back(5);
	b.push_back(over_size);
	b.push_back(17);
	b.push_back(30);
	b.push_back(25);
	cost.push_back(b);

	c.push_back(19);
	c.push_back(15);
	c.push_back(over_size);
	c.push_back(6);
	c.push_back(1);
	cost.push_back(c);

	d.push_back(9);
	d.push_back(50);
	d.push_back(24);
	d.push_back(over_size);
	d.push_back(6);
	cost.push_back(d);

	f.push_back(22);
	f.push_back(8);
	f.push_back(7);
	f.push_back(10);
	f.push_back(over_size);
	cost.push_back(f);

	print(cost, path, size);
}

int nearist(vector<vector<int>> cost,  int first, int path[][5], int size) {
	vector<vector<int>> temp(cost);
	
	int sum = 0;
	int count = 0;
	int row = first;
	int col = first;

	path[row][0] = row;
	cross_out(temp, col, size);

	while (count < size-1) {
		int k = *min_element(temp[row].begin(), temp[row].end());
		for (col = 0; col < size; col++) {
			if (k == temp[row][col]) {
				cross_out(temp, col, size);
				row = col;
				break;
			}
		}
		sum = sum + k;
		path[first][count + 1] = row;
		++count;
	}

	col = first;
	sum = sum + cost[row][col];

	return sum;
}

int cross_out(vector<vector<int>>& a, int col, int size) {
	for (int row = 0; row < size; row++) {
		a[row][col] = 9999;
	}
	return 0;
}
int print(vector<vector<int>> cost, int path[][5], int size) {
	int first = 0;
	int solution = nearist(cost, first, path, size);
	int s = first;

	for (first = 1; first < size; first++) {
		int k = nearist(cost, first, path, size);
		if (solution > k) {
			s = first;
			solution = k;
		}
	}
	cout << "최소비용의 순환로는 ";
	for (int i = 0; i < size; i++) {
		cout << path[s][i] + 1 << " ";
	}
	cout << s + 1 << "이고, 최소비용은 " << solution << "입니다." << endl;

	return 0;
}
