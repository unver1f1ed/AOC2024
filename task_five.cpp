//probably the worst one yet to solve (at least with cpp)
//the abuse of sets and maps is insane xD what can you do lol
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <set>

std::map<int, std::vector<int>> edges;

void topo_sort(int a, std::vector<int>& order, std::map<int, int>& in, const std::set<int>& present) {
    order.push_back(a);
    for (int b : edges[a]) {
        if (present.count(b)) {
            if (--in[b] == 0) {
                topo_sort(b, order, in, present);
            }
        }
    }
}

int main() {
    std::string input;
    long long answer1 = 0;
    long long answer2 = 0;

    while (getline(std::cin, input)) {
        if (input.empty() || !isdigit(input[0])) {
            continue;
        }
        int len = (int)input.length();

        std::vector<int> v;
        bool previous_bar = false;

        for (int i = 0; i < len; i++) {
            if (isdigit(input[i])) {
                int x = 0;
                while (isdigit(input[i])) {
                    x = 10 * x + (input[i] - '0'); // Parse number
                    i++;
                }
                v.push_back(x);
                if (input[i] == '|') {
                    previous_bar = true;
                }

                assert(input[i] == ',' || input[i] == '|' || input[i] == '\n' || input[i] == 0);
            }
        }

        if (previous_bar) {
            edges[v[0]].push_back(v[1]);
        }
        else {
            std::set<int> earlier;
            bool pass = true;

            for (int i = 0; i < (int)v.size(); i++) {
                int x = v[i];
                for (int y : edges[x]) {
                    if (earlier.count(y)) {
                        pass = false;
                    }
                }
                earlier.insert(x);
            }

            if (pass) {
                answer1 += v[v.size() / 2];
            }
            else {
      
                std::set<int> present;
                std::map<int, int> in;

                for (int x : v) {
                    present.insert(x);
                }

                for (int i = 0; i < (int)v.size(); i++) {
                    int x = v[i];
                    for (int y : edges[x]) {
                        if (present.count(y)) {
                            ++in[y];
                        }
                    }
                }

                std::vector<int> order;
                std::vector<int> starting;

                for (int x : v) {
                    if (in[x] == 0) {
                        starting.push_back(x);
                    }
                }

                for (int x : starting) {
                    topo_sort(x, order, in, present);
                }

                answer2 += order[order.size() / 2];
            }
        }
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
