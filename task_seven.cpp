#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>

void cast(int i, long long sum, long long target, const std::vector<int>& vec, bool& pass, bool do_concatenate) {
	if (i == (int)vec.size()) {
		if (sum == target) {
			pass = true;
		}
		return;
	}

	cast(i + 1, sum + vec[i], target, vec, pass, do_concatenate);
	cast(i + 1, sum * vec[i], target, vec, pass, do_concatenate);
	if (do_concatenate) {
		cast(i + 1, std::stoll(std::to_string(sum) + std::to_string(vec[i])), target, vec, pass, do_concatenate);
	}
}

int main() {
	long long res;
	long long answer_v1 = 0;
	long long answer_v2 = 0;

	while (scanf("%lld: ", &res) != EOF) {
		std::vector<int> vec;

		// Read the vector elements
		while (true) {
			int x;
			scanf("%d", &x);
			vec.push_back(x);
			char c;
			scanf("%c", &c);
			if (c == ' ') {
				continue;
			}
			else {
				break;
			}
		}

		bool pass_v1 = false;
		cast(1, vec[0], res, vec, pass_v1, false);
		if (pass_v1) {
			answer_v1 += res;
		}

		bool pass_v2 = false;
		cast(1, vec[0], res, vec, pass_v2, true); 
		if (pass_v2) {
			answer_v2 += res;
		}
	}

	std::cout << "part1 " << answer_v1 << std::endl;
	std::cout << "part2 " << answer_v2 << std::endl;

	return 0;
}
