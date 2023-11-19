import threading
import os

# Global variables
memo = {}  # Memoization cache
print_lock = threading.Lock()

def calculate_collatz(n):
    if n == 1:
        return [1], True

    if n in memo:
        return memo[n], True

    sequence, cached = calculate_collatz(n // 2 if n % 2 == 0 else 3 * n + 1)
    sequence.insert(0, n)
    memo[n] = sequence

    return sequence, False

def worker(start):
    while True:
        with print_lock:
            if start in memo:
                sequence = memo[start]
                print(f"Iteration: {start}")
                print("Retrieved from memoization cache.")
                print(f"Sequence: {sequence}\n")
            else:
                sequence, cached = calculate_collatz(start)
                if not cached:
                    memo[start] = sequence
                print(f"Iteration: {start}")
                print("Calculated sequence.")
                print(f"Sequence: {sequence}\n")
            clear_output()
        start += 1

def clear_output():
    if os.name == 'nt':
        os.system('cls')
    else:
        os.system('clear')

def main():
    start_number = 1
    num_threads = 12  # Update the number of threads here

    threads = []

    for i in range(num_threads):
        thread = threading.Thread(target=worker, args=(start_number,))
        threads.append(thread)
        thread.start()
        start_number += 1

    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()
