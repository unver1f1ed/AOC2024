#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int i = 0;
long long A, B, C;

//combo
long long combo(int x);

//instructions
void adv(int x) {A >>= combo(x);}                     // opcode 0
void bxl(int x) {B ^= x;}                             // opcode 1
void bst(int x) {B = combo(x) % 8;}                   // opcode 2
void jnz(int x) { if (A == 0) {return;} i = x; i--;}  // opcode 3
void bxc(int x) {B ^= C;}                             // opcode 4
std::vector<int> cus;                                 // custom o
void out(int x) {cus.push_back(combo(x) % 8);}        // opcode 5
void bdv(int x) {B = A >> combo(x);}                  // opcode 6
void cdv(int x) {C = A >> combo(x);}                  // opcode 7


std::vector<std::pair<int, int>> vec;


std::vector<int> sim(long long dA); 

int main() {
	char inp[105];
	scanf(" %s", inp);
	scanf(" %s", inp);
	scanf(" %lld", &A);
	for (int i = 0; i < 7; i++) {
		scanf(" %s", inp);
	}

	int x, y;
	while (scanf(" %d,%d", &x, &y) != EOF) {
		scanf(",");
		vec.emplace_back(x, y);
	}


	std::vector<int> tars;
	for (std::pair<int, int> pair : vec) {
		tars.push_back(pair.first);
		tars.push_back(pair.second);
	}

	std::vector<long long> con;
	for (int i = 0; i < 1024; i++) {
		con.push_back(i);
	}

	long long pw = 1024;
	for (int k = 0; k < (int)tars.size(); k++) {
		std::vector<long long> ncon;
		for (long long dA : con) {
			std::vector<int> out = sim(dA);

			bool pass = true;

			for (int j = k; j <= k; j++) {
				if (j >= (int)out.size() || out[j] != tars[j]) {
					pass = false;
					break;
				}
			}
			if (pass) {
				for (int j = 0; j < 8; j++) {
					ncon.push_back(dA + j * pw);
				}
			}
		}
		con = ncon;

		std::sort(con.begin(), con.end());
		printf("%d %lld %lld\n", (int) con.size(), con[0], con.back());

		pw *= 8;
	}
	
	return 0;
}

long long combo(int x) {
	if (x <= 3) {
		return x;
	}
	if (x == 4) return A;
	if (x == 5) return B;
	if (x == 6) return C;
	assert(false);
}

std::vector<int> sim(long long dA) {
	A = dA;
	i = 0;
	cus.clear();
	while (0 <= i && i < (int)vec.size()) {
		int a = vec[i].first;
		int x = vec[i].second;
		switch (a) {
		case 0: adv(x); break;
		case 1: bxl(x); break;
		case 2: bst(x); break;
		case 3: jnz(x); break;
		case 4: bxc(x); break;
		case 5: out(x); break;
		case 6: bdv(x); break;
		case 7: cdv(x); break;
		}
		i++;
	}
	return cus;
}