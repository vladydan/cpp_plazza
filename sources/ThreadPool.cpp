#include <functional>
#include <vector>
#include <thread>
#include <utility>
#include "ThreadPool.hpp"
#include "Process.hpp"
#include "ProcessData.hpp"

template<typename T>
ThreadPool<T>::ThreadPool(int numberOfThreads)
{
  this->_finished = false;
  this->_shutDown = false;
  this->_functionMutexes = new std::vector<std::mutex>(numberOfThreads);
  this->_currentTasks = 0;
  for(int i = 0; i < numberOfThreads; ++i)
  {
    this->_threadList.emplace_back(std::thread(&ThreadPool::task, this));
  }
}

template<typename T>
ThreadPool<T>::~ThreadPool()
{
  if (!_finished)
  {
    this->shutDown();
  }
}

template<typename T>
void ThreadPool<T>::putTaskInQueue(std::function<void(ThreadPool &, T)> f,
                                   T parameter)
{
  {
    std::unique_lock<std::mutex> lock(this->_mutex);
    std::pair<T, std::function<void(ThreadPool &, T)>> pair(parameter, f);
    this->_tasks.push(pair);
    this->_currentTasks++;
  }
  this->_cond.notify_one();
}

template<typename T>
void ThreadPool<T>::shutDown()
{
  {
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_shutDown = true;
  }
  this->_cond.notify_all();
  for(std::thread &thread : this->_threadList)
  {
    thread.join();
  }
  this->_threadList.clear();
  this->_finished = true;
  delete this->_functionMutexes;
}

template<typename T>
void ThreadPool<T>::task()
{
  std::function<void(ThreadPool &, T)> currentTask;
  T parameter;

  while(1)
  {
    {
      std::unique_lock<std::mutex> lock(this->_mutex);
      this->_cond.wait(lock, [this]
      {
        return !this->_tasks.empty() || this->_shutDown;
      });
      if (this->_shutDown && this->_tasks.empty())
      {
        return;
      }
      currentTask = this->_tasks.front().second;
      parameter = this->_tasks.front().first;
      this->_tasks.pop();
    }
    currentTask(*this, parameter);
    {
      std::unique_lock<std::mutex> lock(this->_mutex);
      this->_currentTasks--;
    }
  }
}

template<typename T>
int ThreadPool<T>::getCurrentTasks() const
{
  return this->_currentTasks;
}

template ThreadPool<int>::~ThreadPool();
template void ThreadPool<int>::task();
template ThreadPool<int>::ThreadPool(int numberOfThreads);
template void ThreadPool<int>::putTaskInQueue(std::function<void
                                              (ThreadPool &, int)> f,
                                              int parameter);
template int ThreadPool<int>::getCurrentTasks() const;
template ThreadPool<Process*>::~ThreadPool();
template void ThreadPool<Process*>::task();
template ThreadPool<Process*>::ThreadPool(int numberOfThreads);
template void ThreadPool<Process*>::putTaskInQueue(std::function<void
                                                   (ThreadPool &, Process *)> f,
                                                   Process *parameter);
template int ThreadPool<Process*>::getCurrentTasks() const;
template ThreadPool<ProcessData>::~ThreadPool();
template void ThreadPool<ProcessData>::task();
template ThreadPool<ProcessData>::ThreadPool(int numberOfThreads);
template void ThreadPool<ProcessData>::putTaskInQueue(std::function<void
                                              (ThreadPool &, ProcessData)> f,
                                              ProcessData ProcessData);
template int ThreadPool<ProcessData>::getCurrentTasks() const;
