#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
//overall time compexity O(n)

//was a lambda function at first but who cares))
auto get_number (int& i, const std::string& s) {
	int x = 0;
	while (x < 1000 && isdigit(s[i])) {
		x = 10 * x + (s[i] - '0');
		i++;
	}
	if (1 <= x && x <= 999) {
		return x;
	}
	return -1;
} //0(1) linear time 

int first_part(std::string s, int n);
int second_part(std::string s, int n);

int main() {

	std::string s;
	char c;
	while (scanf("%c", &c) != EOF) {
		s += c;
	}

	s += "######################################################";

	int n = (int)s.length();

	int answer1 = first_part(s, n);
	int answer2 = second_part(s, n);
	
	std::cout << answer1 << std::endl;
	std::cout << answer2 << std::endl;

	return 0;
}

int first_part(std::string s, int n) {

	int answer1 = 0;
	for (int i = 0; i < n - 3; i++) {
		if (s[i] == 'm') {
			if (s[i + 1] == 'u' && s[i + 2] == 'l' && s[i + 3] == '(') {
				i += 4;
				int x = get_number(i, s);
				if (s[i] == ',') {
					i += 1;
					int y = get_number(i, s);
					if (s[i] == ')') {
						if (x != -1 && y != -1) {
							answer1 += x * y;
						}
					}
				}
			}
		}
	}

	return answer1;
}

// lot easier the expected btw
int second_part(std::string s, int n) {

	bool on = true;
	int answer2 = 0;
	for (int i = 0; i < n - 7; i++) {
		if (s.substr(i, 4) == "do()") {
			on = true;
		}
		if (s.substr(i, 7) == "don\'t()") {
			on = false;
		}
		if (on && s[i] == 'm') {
			if (s[i + 1] == 'u' && s[i + 2] == 'l' && s[i + 3] == '(') {
				i += 4;
				int x = get_number(i, s);
				if (s[i] == ',') {
					i += 1;
					int y = get_number(i, s);
					if (s[i] == ')') {
						if (x != -1 && y != -1) {
							answer2 += x * y;
						}
					}
				}
			}
		}
	}

	return answer2;
}