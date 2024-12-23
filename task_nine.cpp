#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Block {
    int id, size, pos;
};

long long first_part(const std::string& s) {
    int n = s.length();
    int pos = 0;
    std::vector<Block> blocks;

    for (int i = 0; i < n; i++) {
        int dig = s[i] - '0';
        if (i % 2 == 0) {
            for (int rep = 0; rep < dig; rep++) {
                blocks.push_back(Block{ i / 2, 1, pos + rep });
            }
        }
        pos += dig;
    }

    while (true) {
        Block current = blocks.back();
        blocks.pop_back();
        bool inserted = false;
        for (int i = 0; i < (int)blocks.size() - 1; i++) {
            int A = blocks[i].pos + blocks[i].size;
            int B = blocks[i + 1].pos;
            if (B - A >= current.size) {
                inserted = true;
                current.pos = A;
                blocks.insert(blocks.begin() + i + 1, current);
                break;
            }
        }
        if (!inserted) {
            current.pos = blocks.back().pos + blocks.back().size;
            blocks.push_back(current);
            break;
        }
    }

    long long answer1 = 0;
    for (Block block : blocks) {
        answer1 += block.pos * block.id;
    }

    return answer1;
}


long long second_part(const std::string& s) {
    int n = s.length();
    int pos = 0;
    std::vector<Block> blocks;

    for (int i = 0; i < n; i++) {
        int dig = s[i] - '0';
        if (i % 2 == 0) {
            blocks.push_back(Block{ i / 2, dig, pos });
        }
        pos += dig;
    }

    long long answer2 = 0;
    while ((int)blocks.size() >= 2) {
        Block current = blocks.back();
        bool inserted = false;
        for (int i = 0; i < (int)blocks.size() - 1; i++) {
            int A = blocks[i].pos + blocks[i].size;
            int B = blocks[i + 1].pos;
            if (B - A >= current.size) {
                inserted = true;
                current.pos = A;
                blocks.pop_back();
                blocks.insert(blocks.begin() + i + 1, current);
                break;
            }
        }
        if (!inserted) {
            blocks.pop_back();
            for (int j = 0; j < current.size; j++) {
                answer2 += (current.pos + j) * current.id;
            }
        }
    }

    return answer2;
}

int main() {
    std::ifstream fin("input.txt");

    std::string s;
    std::getline(fin, s);

    long long answer1 = first_part(s);
    long long answer2 = second_part(s);

    std::cout << "Answer 1: " << answer1 << '\n';
    std::cout << "Answer 2: " << answer2 << '\n';

    fin.close();
    return 0;
}
