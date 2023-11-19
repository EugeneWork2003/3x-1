#include <iostream>
#include <unordered_map>
#include <thread>

// Global variables
std::unordered_map<int, std::vector<int>> memo;  // Memoization cache

//std::vector<int> calculate_collatz(int n) {
//    std::cout << "Hello, world!" << std::endl;
//    if (n == 1) {
//        return { 1 };
//    }
//
//    if (memo.find(n) != memo.end()) {
//        return memo[n];
//    }
//
//    std::vector<int> sequence = { n };
//
//    if (n % 2 == 0) {
//        sequence = calculate_collatz(n / 2);
//    }
//    else {
//        sequence = calculate_collatz(3 * n + 1);
//    }

    sequence.insert(sequence.begin(), n);
    memo[n] = sequence;  // Memoize the sequence

    return sequence;
}



void worker(int start, int end, std::vector<std::vector<int>>& results) {
    for (int i = start; i <= end; ++i) {
        results[i] = calculate_collatz(i);
    }
}

int main() {
    int start_number = 1;
    int end_number = INT_MAX;
    int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads(num_threads);
    std::vector<std::vector<int>> results(end_number + 1);

    int chunk_size = (end_number - start_number + 1) / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = start_number + i * chunk_size;
        int end = (i == num_threads - 1) ? end_number : start + chunk_size - 1;
        threads[i] = std::thread(worker, start, end, std::ref(results));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Total numbers processed: " << results.size() << std::endl;

    return 0;
}
