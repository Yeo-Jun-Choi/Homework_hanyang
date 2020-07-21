#include <iostream>
#include <random>
#include<vector>
using namespace std;
int retail_1 = 12;
int wholesale_1 = 12;
int stock_1 = 12;
int supply_1 = 12;
int retail(int demand, int suppl);
int wholesale(int demand, int suppl);
int stock(int demand, int suppl);
int supply(int demand, int suppl);
int sum_1 = 0;
int sum_2 = 0;
int sum_3 = 0;
int sum_4 = 0;
int sum_11 = 0;
int sum_22 = 0;
int sum_33 = 0;
int sum_44 = 0;

int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> dis(4, 8);


	int demand, j = 1, k = 2, n = 3, m = 4, b = 5;
	//= dis(gen);
	vector<int> abc;
	for (int i = 0; i < 60; ++i) {

		demand = dis(gen);
		abc.push_back(demand);
		retail_1 = retail(demand, 0);
		if (j == i) {
			wholesale_1 = wholesale(abc[i - 1], 0);
			++j;
		}
		if (k == i) {
			retail_1 = retail(0, abc[i - 2]);
			stock_1 = stock(abc[i - 2], 0);
			k++;
		}
		if (n == i) {
			wholesale_1 = wholesale(0, abc[i - 3]);
			supply_1 = supply(abc[i - 3], 0);
			++n;
		}
		if (m == i) {
			stock_1 = stock(0, abc[i - 4]);
			++m;
		}
		if (b == i) {
			supply_1 = supply(0, abc[i - 5]);
			++b;
		}

		sum_1 += retail_1 * 5;

		sum_2 += wholesale_1 * 5;

		sum_3 += stock_1 * 5;

		sum_4 += supply_1 * 5;
		sum_11 += sum_1;
		sum_22 += sum_2;
		sum_33 += sum_3;
		sum_44 += sum_4;
		cout << "수요 : " << demand << endl;
		cout << abc[i] << endl;
		cout << i << "일자 재고량";
		cout << "소매 : " << retail_1 << " 도매 : " << wholesale_1 << " 창고 : " << stock_1 << " 공급 : " << supply_1 << endl;
		cout << i << "일자 비용" << endl;
		cout << "소매 : " << sum_1 << " 도매 : " << sum_2 << " 창고 : " << sum_3 << " 공급 : " << sum_4 << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
		sum_1 = 0;
		sum_2 = 0;
		sum_3 = 0;
		sum_4 = 0;

	}
	cout << "총 비용" << endl;
	cout << "소매 : " << sum_11 << " 도매 : " << sum_22 << " 창고 : " << sum_33 << " 공급 : " << sum_44 << endl;
	return 0;
}

int retail(int demand, int suppl) {
	int result = retail_1;
	if (retail_1 < demand && suppl == 0) {
		sum_1 += demand * 15;
		return result;
	}
	if (demand != 0 && suppl != 0)
		result = result - demand + suppl + 1;
	else if (demand != 0)
		result -= demand;
	else if (suppl != 0)
		result = suppl + 1;
	return result;
}

int wholesale(int demand, int suppl) {
	int result = wholesale_1;
	if (wholesale_1 < demand && suppl == 0) {
		sum_2 += demand * 15;
		return result;
	}
	if (demand != 0 && suppl != 0)
		result = result - demand + suppl + 1;
	else if (demand != 0)
		result -= demand;
	else if (suppl != 0)
		result = suppl + 1;

	return result;
}

int stock(int demand, int suppl) {
	int result = stock_1;
	if (stock_1 < demand && suppl == 0) {
		sum_3 += demand * 15;
		return result;
	}

	if (demand != 0 && suppl != 0)
		result = result - demand + suppl + 1;
	else if (demand != 0)
		result -= demand;
	else if (suppl != 0)
		result = suppl + 1;
	return result;
}

int supply(int demand, int suppl) {
	int result = supply_1;
	if (supply_1 < demand && suppl == 0) {
		sum_4 += demand * 15;
		return result;
	}
	if (demand != 0 && suppl != 0)
		result = result - demand + suppl + 1;
	else if (demand != 0)
		result -= demand;
	else if (suppl != 0)
		result = suppl + 1;
	return result;
}