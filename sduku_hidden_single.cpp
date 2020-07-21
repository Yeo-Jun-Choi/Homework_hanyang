#include<iostream>
using namespace std;

struct cell {
	int candidate[9] = { 0, };
	int sol;
	int count;
};

struct hint {
	int cell;
	int row;
	int col;
	int box;
};
void stack_cross_out(cell sduku[][9], hint a[], int& top, int size);
void cross_out(cell sduku[][9], hint a[], int& top, int size,int row, int column);
void cross_out_box(cell sduku[][9], hint a[], int& top, int box);
void cross_out_row(cell sduku[][9], hint a[], int& top, int row, int size);
void cross_out_col(cell sduku[][9], hint a[], int& top, int col, int size);
int box_cal(int row, int col, int size);
void naked_single(cell sduku[][9], hint a[], int& top, int size);
void hidden_single(cell sduku[][9], hint a[], int& top, int size);
int hidden_row(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can);
int hidden_column(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can);
void hidden_box(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can);
void sduku_print(cell sduku[][9], int size);

int main() {
	int top = -1;

	cell sduku[9][9] = {
		{{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0},{{0},8,9},{{0},3,9},{{0},0,0},{{0},0,0},{{0},0,0}},
		{{{0},7,9},{{0},0,0},{{0},0,0},{{0},0,0},{{0},6,9},{{0},0,0},{{0},0,0},{{0},9,9},{{0},8,9}},
	{{{0},9,9},{{0},0,0},{{0},8,9},{{0},7,9},{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0}},
	{{{0},0,0},{{0},0,0},{{0},1,9},{{0},3,9},{{0},0,0},{{0},0,0},{{0},8,9},{{0},0,0},{{0},0,0}},
	{{{0},5,9},{{0},9,9},{{0},0,0},{{0},1,9},{{0},7,9},{{0},8,9},{{0},0,0},{{0},3,9},{{0},4,9}},
	{{{0},0,0},{{0},0,0},{{0},3,9},{{0},0,0},{{0},0,0},{{0},2,9},{{0},9,9},{{0},0,0},{{0},0,0}},
	{{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0},{{0},7,9},{{0},4,9},{{0},0,0},{{0},2,9}},
	{{{0},8,9},{{0},2,9},{{0},0,0},{{0},0,0},{{0},9,9},{{0},0,0},{{0},0,0},{{0},0,0},{{0},7,9}},
	{{{0},0,0},{{0},0,0},{{0},0,0},{{0},5,9},{{0},2,9},{{0},0,0},{{0},0,0},{{0},0,0},{{0},0,0}}
	};

	hint stack[81] = { 0, };
	stack_cross_out(sduku, stack, top, 9);

	while (top < 80) {
		int x = top;
		naked_single(sduku, stack, top, 9);
		hidden_single(sduku, stack, top, 9);
		if (x == top) {
			cout << "naked single, hidden single로는 스도쿠 결과를 낼 수 없습니다." << endl;
			sduku_print(sduku, 9);
			return 0;
		}
	}
	sduku_print(sduku, 9);
	return 0;
}

void stack_cross_out(cell sduku[][9], hint a[], int& top, int size) {
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			if (sduku[k][i].sol != 0) {
				top++;
				a[top].cell = sduku[k][i].sol;
				a[top].row = k;
				cross_out_row(sduku, a, top, a[top].row, size);
				a[top].col = i;
				cross_out_col(sduku, a, top, a[top].col, size);
				a[top].box = box_cal(k, i, size);
				cross_out_box(sduku, a, top, a[top].box);
			}
		}
	}
}

void cross_out(cell sduku[][9], hint a[], int& top, int size,int row,int column) {
				top++;
				a[top].cell = sduku[row][column].sol;
				a[top].row = row;
				cross_out_row(sduku, a, top, a[top].row, size);
				a[top].col = column;
				cross_out_col(sduku, a, top, a[top].col, size);
				a[top].box = box_cal(row, column, size);
				cross_out_box(sduku, a, top, a[top].box);
}

void cross_out_box(cell sduku[][9], hint a[], int& top, int box) {
	for (int i = (box / 3) * 3; i < (box / 3) * 3 + 3; i++) {
		for (int j = (box % 3) * 3; j < (box % 3) * 3 + 3; j++) {
			if (sduku[i][j].candidate[a[top].cell - 1] == 0 && sduku[i][j].sol == 0) {
				sduku[i][j].candidate[a[top].cell - 1] = a[top].cell;
				sduku[i][j].count++;
			}

		}
	}
}

void cross_out_row(cell sduku[][9], hint a[], int& top, int row, int size) {
	for (int i = 0; i < size; i++) {
		if (sduku[row][i].candidate[a[top].cell - 1] == 0 && sduku[row][i].sol == 0) {
			sduku[row][i].candidate[a[top].cell - 1] = a[top].cell;
			sduku[row][i].count++;
		}
	}
}

void cross_out_col(cell sduku[][9], hint a[], int& top, int col, int size) {
	for (int i = 0; i < size; i++) {
		if (sduku[i][col].candidate[a[top].cell - 1] == 0 && sduku[i][col].sol == 0) {
			sduku[i][col].candidate[a[top].cell - 1] = a[top].cell;
			sduku[i][col].count++;
		}
	}
}

int box_cal(int row, int col, int size) {
	int k = 0;
	while (k < size) {
		if (k == 3 * (row / 3) + (col / 3))
			return k;
		k++;
	};
	return 0;
}

void naked_single(cell sduku[][9], hint a[], int& top, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (sduku[i][j].count == 8) {
				for (int k = 0; k < size; k++) {
					if (sduku[i][j].candidate[k] == 0 && sduku[i][j].sol == 0) {
						sduku[i][j].sol = k + 1;
						sduku[i][j].candidate[k] = k + 1;
						sduku[i][j].count++;
						cross_out(sduku, a, top, size, i, j);
					}
				}
			}
		}
	}
}

void hidden_single(cell sduku[][9], hint a[], int& top, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				if (sduku[i][j].candidate[k] == 0 && sduku[i][j].sol == 0) {
					if (hidden_row(sduku, a, top, size, i, j, k) == 0) {
						if (hidden_column(sduku, a, top, size, i, j, k) == 0) {
							hidden_box(sduku, a, top, size, i, j, k);
						}
					}
				}
			}
		}
	}
}

int hidden_row(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can) {
	int temp = 0;
	while (temp < size) {
		if (temp != column) {
			if (sduku[row][temp].sol == 0 && sduku[row][temp].candidate[can] == 0)
				return 0;
		}
		temp++;
	}
	sduku[row][column].sol = can + 1;
	sduku[row][column].candidate[can] = can + 1;
	sduku[row][column].count = 9;
	cross_out(sduku, a, top, size, row, column);
	return 1;
}

int hidden_column(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can) {
	int temp = 0;
	while (temp < size) {
		if (temp != row) {
			if (sduku[temp][column].sol == 0 && sduku[temp][column].candidate[can] == 0)
				return 0;
		}
		temp++;
	}
	sduku[row][column].sol = can + 1;
	sduku[row][column].candidate[can] = can + 1;
	sduku[row][column].count = 9;
	cross_out(sduku, a, top, size, row, column);
	return 1;
}

void hidden_box(cell sduku[][9], hint a[], int& top, int size, int row, int column, int can) {
	int box = box_cal(row, column, size);
	for (int i = (box / 3) * 3; i < (box / 3) * 3 + 3; i++) {
		for (int j = (box % 3) * 3; j < (box % 3) * 3 + 3; j++) {
			if (i != row || j != column) {
				if (sduku[i][j].sol == 0 && sduku[i][j].candidate[can] == 0) {
					return;
				}
			}
		}
	}
	sduku[row][column].sol = can + 1;
	sduku[row][column].candidate[can] = can + 1;
	sduku[row][column].count = 9;
	cross_out(sduku, a, top, size, row, column);
}

void sduku_print(cell sduku[][9], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << sduku[i][j].sol << " ";
		}
		cout << endl;
	}
}