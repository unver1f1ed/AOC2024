#include <iostream>
#include <vector>
#include <sstream>  
#include <string>   

bool pass_check(std::vector<int>& a);
int first_part(std::vector<std::vector<int>>& reports);
int second_part(std::vector<std::vector<int>>& reports);

int main() {
    int N = 1000;

    std::vector<std::vector<int>> reports;

    // Read all reports
    for (int i = 0; i < N; i++) {
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        int x;
        std::vector<int> report;

        while (ss >> x) {
            report.push_back(x); 
        }

        reports.push_back(report);  
    }

    int answer1 = first_part(reports); 
    std::cout << answer1 << std::endl;

    int answer2 = second_part(reports);
    std::cout << answer2 << std::endl;

    return 0;
}

bool pass_check(std::vector<int>& a) {
    int k = (int)a.size();
    bool pass = true;
    bool only_increasing = true;
    bool only_decreasing = true;

    for (int j = 0; j < k - 1; j++) {
        int delta = a[j + 1] - a[j];
        if (delta > 0)
            only_decreasing = false;
        if (delta < 0)
            only_increasing = false;
        if (!(1 <= abs(delta) && abs(delta) <= 3)) {
            pass = false;
            break;
        }
    }
    return pass && (only_increasing || only_decreasing);
}

int first_part(std::vector<std::vector<int>>& reports) {
    int answer1 = 0;

    // Process each report and check if it's safe
    for (auto& report : reports) {
        if (pass_check(report)) {
            answer1++;
        }
    }

    return answer1;
}

int second_part(std::vector<std::vector<int>>& reports) {
    int answer2 = 0;

    for (auto& report : reports) {
        bool any_pass = false;

        auto consider = [&](int i) {
            std::vector<int> b = report;
            b.erase(b.begin() + i);  // Remove the element at index i
            if (pass_check(b)) {
                any_pass = true;
            }
            };

        int k = report.size();

        // Try removing the first element
        consider(0);

        // Check the conditions that might make the report unsafe
        for (int j = 0; j < k - 1; j++) {
            int delta = report[j + 1] - report[j];
            if (abs(delta) < 1 || abs(delta) > 3) {
                consider(j);
                consider(j + 1);
                break;
            }
            if (j + 2 < k) {
                int delta2 = report[j + 2] - report[j + 1];
                if ((delta > 0) != (delta2 > 0)) {
                    consider(j);
                    consider(j + 1);
                    consider(j + 2);
                    break;
                }
            }
        }
        if (any_pass) {
            answer2++;
        }
    }

    return answer2;
}
