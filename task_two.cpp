#include <iostream>
#include <vector>
#include <sstream>  
#include <string>   

bool pass_check(std::vector<int>& a);
int first_part(std::vector<std::vector<int>>& reports);  // Update to accept a vector of reports
int second_part(std::vector<std::vector<int>>& reports);  // Update to accept a vector of reports

int main() {
    int N = 1000;  // Presumably the number of lines we want to process

    std::vector<std::vector<int>> reports;  // Vector to store all reports

    // Read all reports
    for (int i = 0; i < N; i++) {
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);
        int x;
        std::vector<int> report;

        while (ss >> x) {
            report.push_back(x);  // Add the integers to the current report
        }

        reports.push_back(report);  // Add the current report to the list of reports
    }

    int answer1 = first_part(reports);  // Pass the vector of reports
    std::cout << answer1 << std::endl;

    int answer2 = second_part(reports);  // Pass the vector of reports
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

    // Process each report
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






/*
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

bool pass_check(const std::vector<int>& a);
bool pass_check_with_removal(const std::vector<int>& a);

int first_part(const std::vector<std::vector<int>>& reports);
int second_part(const std::vector<std::vector<int>>& reports);

int main() {
	int N;  // Number of reports
	std::cin >> N;
	std::cin.ignore();  // Ignore the newline after the number of reports

	std::vector<std::vector<int>> reports;  // Vector to store each report (list of integers)

	// Read all reports
	for (int i = 0; i < N; i++) {
		std::string line;
		std::getline(std::cin, line);

		std::stringstream ss(line);
		int x;
		std::vector<int> report;

		while (ss >> x) {
			report.push_back(x);  // Add the integers to the report vector
		}

		reports.push_back(report);  // Add the report to the list of reports
	}

	// Solve both parts
	int answer1 = first_part(reports);
	std::cout << "First part answer: " << answer1 << std::endl;

	int answer2 = second_part(reports);
	std::cout << "Second part answer: " << answer2 << std::endl;

	return 0;
}

// Function to check if a report is safe (Part 1)
bool pass_check(const std::vector<int>& a) {
	int k = a.size();
	bool only_increasing = true;
	bool only_decreasing = true;

	for (int j = 0; j < k - 1; j++) {
		int delta = a[j + 1] - a[j];
		if (delta > 0) only_decreasing = false;
		if (delta < 0) only_increasing = false;
		if (!(1 <= abs(delta) && abs(delta) <= 3)) return false;  // Check if the difference is within [1, 3]
	}

	return only_increasing || only_decreasing;  // Check if the list is strictly increasing or decreasing
}

// Function to check if a report can become safe by removing one element (Part 2)
bool pass_check_with_removal(const std::vector<int>& a) {
	int k = a.size();

	// Try removing each element and check if the remaining report is safe
	for (int i = 0; i < k; ++i) {
		std::vector<int> new_a = a;
		new_a.erase(new_a.begin() + i);  // Remove the element at index i
		if (pass_check(new_a)) return true;  // Check if the modified report is safe
	}

	return false;
}

// First part: count the number of safe reports
int first_part(const std::vector<std::vector<int>>& reports) {
	int answer1 = 0;

	// For each report, check if it's safe using pass_check
	for (const auto& report : reports) {
		if (pass_check(report)) {
			answer1++;
		}
	}

	return answer1;
}

// Second part: count the number of safe reports with the Problem Dampener (one removal)
int second_part(const std::vector<std::vector<int>>& reports) {
	int answer2 = 0;

	// For each report, check if it can be safe with one removal
	for (const auto& report : reports) {
		if (pass_check(report) || pass_check_with_removal(report)) {
			answer2++;
		}
	}

	return answer2;
}
*/