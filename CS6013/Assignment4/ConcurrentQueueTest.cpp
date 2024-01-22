#include "ConcurrentQueue.hpp"
#include <thread>
#include <vector>

bool testQueue(int num_producers, int num_consumers, int num_ints);

bool testQueue(int num_producers, int num_consumers, int num_ints) {
    std::vector<std::thread> producer, consumer;

    // reserve space for all producer and consumer threads
    producer.reserve(num_producers);
    consumer.reserve(num_consumers);

    // create a ConcurrentQueue object statically
    ConcurrentQueue<int> concurrentQueue{};

    std::mutex m;
    int* ret = new int;

    // create num_producer producer threads that
    // enqueue num_ints ints into the ConcurrentQueue
    for (int i = 0; i < num_producers; i++) {
        producer.emplace_back([&]() {
            for (int j = 0; j < num_ints; j++) {
                concurrentQueue.enqueue(j);
            }
        });
    }

    // create num_consumer consumer threads that
    // dequeue num_ints ints from the ConcurrentQueue
    for (int i = 0; i < num_consumers; ++i) {
        consumer.emplace_back([&]() {
            for (int j = 0; j < num_ints; j++) {
                concurrentQueue.dequeue(ret);
            }
        });
    }

    // wait for all threads to join
    for (auto& p : producer) {
        p.join();
    }

    for (auto& c : consumer) {
        c.join();
    }

    delete ret;

    return concurrentQueue.size() ==
           (num_producers - num_consumers) * num_ints;
}

int main(int argc, char** argv) {
//    Have your program take in from the command line (using argv)
//    the numbers of producers (threads that enqueue ints),
//    the numbers of consumers (threads that dequeue ints),
//    and the number of ints that producers and consumers enqueue and dequeue.
//    An example of command line execution of your program would be:
//    ./ConcurrentQueueTest 3 3 10
//    This will create 3 producer threads and 3 consumer threads.
//    Each thread will enqueue 10 integers and dequeue 10 integers respectively.

    if (argc != 4) {
        std::cerr << "Invalid command." << std::endl;
        exit(1);
    }

    if (testQueue(std::stoi(argv[1]),
                  std::stoi(argv[2]),
                  std::stoi(argv[3]))) {
        std::cout << "Concurrent test passed!" << std::endl;
        return 0;
    }

    std::cout << "Concurrent test failed." << std::endl;
    return 1;
}
