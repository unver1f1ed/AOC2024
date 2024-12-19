#include <iostream>
#include <vector>
#include <string>
#include <set>

std::vector<std::pair<int, int>> dirs = { {-1,0}, {0,1}, {1,0}, {0, -1} };

int first_part(std::vector<std::string>& input, int H, int W);
int second_part(std::vector<std::string>& input, int H, int W);

int main() {

	int H = 130;
	std::vector<std::string> input(H);
	for (int i = 0; i < H; i++){
		std::cin >> input[i];
	}

	int W = input[0].length();

	int answer1 = first_part(input, H, W);
	int answer2 = second_part(input, H, W);
	
	std::cout << "part1 = " << answer1 << '\n' << "part2 = "  << answer2 << '\n';

	return 0;
}

int first_part(std::vector<std::string>& input, int H, int W) {

	std::vector<std::string> grid = input;

	std::pair<int, int> current_cell{ -1,-1 };
	int dir = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (grid[row][col] == '^') {
				current_cell = { row, col };
				grid[row][col] = '.';
			}
		}
	}

	std::set<std::pair<int, int>> visited1;
	while (true) {
		visited1.insert(current_cell);
		int r2 = current_cell.first + dirs[dir].first;
		int c2 = current_cell.second + dirs[dir].second;
		if (!(0 <= r2 && r2 < H && 0 <= c2 && c2 < W)) {
			break;
		}
		if (grid[r2][c2] == '.') {
			current_cell = { r2,c2 };
		}
		else {
			dir = (dir + 1) % 4;
		}
	}
	return visited1.size();
}

int second_part(std::vector<std::string>& input, int H, int W) {

	std::pair<int, int> start_current_cell{ -1,-1 };
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (input[row][col] == '^') {
				start_current_cell = { row, col };
				input[row][col] = '.';
			}
		}
	}

	auto solve = [&]() {

		std::pair<int, int> current_cell = start_current_cell;
		int dir = 0;

		//boolean matrix instead?

		 
		int turns = 0;
		while (true) {
			turns++;
			if (turns == H * W * 4) {
				return true;
			}
			//slow

			int r2 = current_cell.first + dirs[dir].first;
			int c2 = current_cell.second + dirs[dir].second;
			if (!(0 <= r2 && r2 < H && 0 <= c2 && c2 < W)) {
				return false;
			}
			if (input[r2][c2] == '.') {
				current_cell = { r2,c2 };
			}
			else {
				dir = (dir + 1) % 4;
			}
		}
	};

	int answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (input[row][col] == '.' && start_current_cell != std::make_pair(row, col)) {
				input[row][col] = '#';

				if (solve()) {
					answer++;
				}

				input[row][col] = '.';
			}
		}
	}
	return answer;
}