#include <iostream>
#include <string>
#include <vector>

int first_part(std::vector<std::string>& a, int N, int W);
int second_part(std::vector<std::string>& a, int N, int W);

int main() {

	int N = 140;

	std::vector<std::string> a(N);
	for (std::string& row : a) {
		std::cin >> row;
	}

	int W = (int)a[0].length();
	

	int answer1 = first_part(a, N, W);
	int answer2 = second_part(a, N, W);
	printf("answer1: %d\n", answer1);
	printf("answer2: %d\n", answer2);
}

int first_part(std::vector<std::string>& a, int N, int W){

	auto inside = [&](int row, int col) {
		return 0 <= row && row < N && 0 <= col && col < W;
		};

	const std::string TEMPLATE = "XMAS";

	int answer1 = 0;

	for (int row = 0; row < N; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == 'X') {
				for (int drow = -1; drow <= 1; drow++) {
					for (int dcol = -1; dcol <= 1; dcol++) {
						if (drow == 0 && dcol == 0) {
							continue;
						}
						bool pass = true;
						for (int i = 0; i < 4; i++) {
							int r2 = row + drow * i;
							int c2 = col + dcol * i;
							if (inside(r2, c2) && a[r2][c2] == TEMPLATE[i]) {
								//just pass
							}
							else {
								pass = false;
								break;
							}
						}
						answer1 += pass;
					}
				}
			}
		}
	}
	return answer1;
}

int second_part(std::vector<std::string>& a, int N, int W) {

	const std::vector<std::pair<int, int>> dirs = { {-1,-1},{-1,1},{1,1},{1,-1} };

	int answer2 = 0;

	for (int row = 1; row < N - 1; row++) {
		for (int col = 1; col < W - 1; col++) {
			if (a[row][col] == 'A') {
				std::string collection;
				for (std::pair<int, int> dir : dirs) {
					collection += a[row+dir.first][col+dir.second];
				}
				if (collection == "MMSS" || collection == "MSSM" || collection == "SSMM" || collection == "SMMS") {
					answer2++;
				}
			}
		}
	}
	return answer2;
}