/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ThreadPool
*/

#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

class ThreadPool {
    public:
        ThreadPool();
        ~ThreadPool();

    protected:
    private:
        void ThreadLoop();

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> threads;
    // std::queue<std::function<void()>> jobs;
};

#endif /* !THREADPOOL_HPP_ */
