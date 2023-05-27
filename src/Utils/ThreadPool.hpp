/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ThreadPoll
*/

#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_
    #include <vector>
    #include <thread>
    #include <mutex>
    #include <iostream>
    #include <condition_variable>
    #include <functional>

namespace Plazza {
    /**
     * @brief Number of threads
     *
     * @tparam nbr
     */
    // template <typename T>
    class ThreadPool {
        public:
            // ThreadPool() {};
            ThreadPool(std::size_t nbrWorkers) {
                _nbrWorkers = nbrWorkers;
                _pollSpaceLeft = _nbrWorkers;
                runPool();
            }
            ~ThreadPool() {};

            std::size_t spaceLeft() {
                return _pollSpaceLeft;
            }

            template <typename F>
            void newTask(F&& f) {
                _task = std::forward<F>(f);
                cond.notify_one();
                _pollSpaceLeft--;
            };

        protected:
        private:

            void runPool() {
                for (int i = 0; i < _nbrWorkers; i++) {
                    _workers.emplace_back([&] {
                        while (_isRunning) {
                            std::unique_lock<std::mutex> lock(_mutex);
                            cond.wait(lock);
                            _task();
                        }
                    });
                }
            }


            std::function<void()> _task;
            std::size_t _nbrWorkers = 0;
            std::size_t _pollSpaceLeft = 0;
            bool _isRunning = true;
            std::vector<std::thread> _workers;
            std::mutex _mutex;
            std::condition_variable cond;
    };
}

#endif /* !THREADPOOL_HPP_ */
