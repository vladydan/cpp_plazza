#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

# include <thread>
# include <mutex>
# include <queue>
# include <condition_variable>
# include <vector>
# include <functional>
# include <utility>

template<typename T>
class ThreadPool
{
  public:
    ThreadPool(int numberOfThreads);
    ~ThreadPool();
    void putTaskInQueue(std::function<void(ThreadPool &, T)> f,
                        T functionParameter);
    void shutDown();
    int getCurrentTasks() const;
  private:
    void task();
    std::vector<std::thread>            _threadList;
    std::vector<std::mutex>             *_functionMutexes;
    std::mutex                          _mutex;
    std::queue<std::pair<T, std::function<void(ThreadPool &, T)>>> _tasks;
    std::condition_variable              _cond;
    bool                                 _finished;
    bool                                 _shutDown;
    int                                  _currentTasks;
};

#endif /* THREADPOOL_HPP_ */
