#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

static int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

class solution_solver {
private:
    std::unique_ptr<std::unique_ptr<char[]>[]> input;
    int height, width;
    std::vector<std::vector<std::pair<int, int>>> positions;

public:
    solution_solver() : height(-1), width(-1) {
        input = std::make_unique<std::unique_ptr<char[]>[]>(100);
        for (int i = 0; i < 100; ++i) {
            input[i] = std::make_unique<char[]>(100);
        }

        positions.resize(256);
    }

    void read_input() {
        for (auto& vec : positions) {
            vec.clear();
        }

        for (int row = 0; scanf(" %s", input[row].get()) != EOF; row++) {
            height = row + 1;
            width = strlen(input[row].get());

            for (int col = 0; col < width; col++) {
                if (input[row][col] != '.') {
                    unsigned char ch = static_cast<unsigned char>(input[row][col]);
                    positions[ch].emplace_back(row, col);
                }
            }
        }
    }

    int solve_part_one() {
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
        int count = 0;

        for (const auto& vec : positions) {
            if (vec.empty()) continue;

            for (size_t i = 0; i < vec.size(); i++) {
                for (size_t j = 0; j < vec.size(); j++) {
                    if (i == j) continue;

                    int r1 = vec[i].first;
                    int c1 = vec[i].second;
                    int r2 = vec[j].first;
                    int c2 = vec[j].second;

                    int new_row = r2 + (r2 - r1);
                    int new_col = c2 + (c2 - c1);

                    if (0 <= new_row && new_row < height && 0 <= new_col && new_col < width) {
                        if (!visited[new_row][new_col]) {
                            visited[new_row][new_col] = true;
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }

    int solve_part_two() {
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
        int count = 0;

        for (const auto& vec : positions) {
            if (vec.empty()) continue;

            for (size_t i = 0; i < vec.size(); i++) {
                for (size_t j = 0; j < vec.size(); j++) {
                    if (i == j) continue;

                    int r1 = vec[i].first;
                    int c1 = vec[i].second;
                    int r2 = vec[j].first;
                    int c2 = vec[j].second;

                    int dx = r2 - r1;
                    int dy = c2 - c1;
                    int g = gcd(std::abs(dx), std::abs(dy));
                    dx /= g;
                    dy /= g;

                    for (int rep = 0; rep < 2; rep++) {
                        for (int m = 0; true; m++) {
                            int new_row = r1 + dx * m;
                            int new_col = c1 + dy * m;

                            if (0 <= new_row && new_row < height && 0 <= new_col && new_col < width) {
                                if (!visited[new_row][new_col]) {
                                    visited[new_row][new_col] = true;
                                    count++;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        dx *= -1;
                        dy *= -1;
                    }
                }
            }
        }
        return count;
    }

    int get_height() const { return height; }
    int get_width() const { return width; }
};

int main() {
    solution_solver solver;

    solver.read_input();

    int part_one_answer = solver.solve_part_one();
    std::cout << "Part 1 Answer: " << part_one_answer << std::endl;

    int part_two_answer = solver.solve_part_two();
    std::cout << "Part 2 Answer: " << part_two_answer << std::endl;

    return 0;
}