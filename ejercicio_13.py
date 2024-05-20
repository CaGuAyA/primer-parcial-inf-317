import multiprocessing
from multiprocessing import Queue

def fibonacci_worker(start_index, count, queue):
    result = []
    a, b = 0, 1
    for i in range(start_index):
        a, b = b, a + b
    for i in range(count):
        result.append(a)
        a, b = b, a + b
    queue.put(result)

def calcular_fibonacci(n, num_processes):
    queue = Queue()
    processes = []
    terms_per_process = n // num_processes
    remaining_terms = n % num_processes

    start_index = 0
    for i in range(num_processes):
        count = terms_per_process + (1 if i < remaining_terms else 0)
        process = multiprocessing.Process(target=fibonacci_worker, args=(start_index, count, queue))
        processes.append(process)
        process.start()
        start_index += count

    fibonacci_series = []
    for _ in range(num_processes):
        fibonacci_series.extend(queue.get())

    for process in processes:
        process.join()

    return fibonacci_series

if __name__ == "__main__":
    n = 1000
    num_processes = multiprocessing.cpu_count()
    
    fibonacci_series = calcular_fibonacci(n, num_processes)
    
    print(f"Fibonacci series up to {n} terms:")
    print(fibonacci_series)
    
    # Save the result to a text file
    with open("fibonacci_series.txt", "w") as f:
        for number in fibonacci_series:
            f.write(f"{number}\n")
