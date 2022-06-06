#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

bool linear_search(int N, std::vector<int> &S)
{
    for(auto i: S) {
        if(i == N)
            return true;
    }

    return false;
}

bool binary_search(int N, std::vector<int> &S)
{
    auto first = S.begin();
    auto last = S.end();

    while (true) {
        auto range_length = std::distance(first, last);
        auto mid_element_index = std::floor(range_length / 2);
        auto mid_element = *(first + mid_element_index);

        if (mid_element == N)
            return true;
        else if (mid_element > N)
            std::advance(last, -mid_element_index);
        else
            std::advance(first, mid_element_index);

        if(range_length == 1) {
            return false;
        }
    }
}

void run_small_search_test()
{
    auto N = 2;
    std::vector<int> S {1, 3, 2, 4, 5, 7, 9, 8, 6};

    std::sort(S.begin(), S.end());

    if(linear_search(N, S))
        std::cout << "Found by linear_search" << std::endl;
    if(binary_search(N, S))
        std::cout << "Found by binary_search" << std::endl;
}

void run_large_search_test(int size, int N)
{
    std::vector<int> S;
    std::random_device rd;
    std::mt19937 rand(rd());

    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

    for(auto i = 0; i < size; i++) {
        S.push_back(uniform_dist(rand));
    }

    std::sort(S.begin(), S.end());

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool search_result = binary_search(N, S);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout << "binary_search time: " << diff.count() << std::endl;

    if(search_result)
        std::cout << "Found " << N << std::endl;
    else
        std::cout << "No " << N << std::endl;
}

int main() {
    run_small_search_test();
    run_large_search_test(100000, 36543);
    run_large_search_test(1000000, 36543);
    run_large_search_test(10000000, 36543);
}
