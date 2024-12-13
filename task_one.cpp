#include <iostream>
#include <vector>//array
#include <map>//map obj at second part
#include <algorithm>//sort

std::vector<int> right, left;

int first_part();
int second_part();

int main() {

    for (size_t i = 0; i < 1000; i++) {
        int x, y;
        std::cin >> x >> y;
        right.push_back(x);
        left.push_back(y);
    }//fill input

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    first_part();
    second_part();
    return 0;
}

int first_part() {

    long long sum1 = 0;

    for (size_t i = 0; i < 1000; i++)
        sum1 += abs(right[i]-left[i]);

    std::cout << sum1 << "\n";
    return sum1;
}

int second_part() {

    //left side check
    std::map<int, int> frequency;
    for (int x : left)
        frequency[x]++;

    long long sum2 = 0;

    //right side + sum
    for (size_t i = 0; i < 1000; i++)
        sum2 += (long long)right[i] * frequency[right[i]];

    std::cout << sum2 << "\n";
    return sum2;
}