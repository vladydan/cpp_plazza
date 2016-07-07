#ifndef PROCESS_HPP_
# define PROCESS_HPP_

# include <thread>
# include <list>
# include <utility>
# include <functional>
# include "ThreadPool.hpp"
# include "NamedPipe.hpp"
# include "ProcessData.hpp"

class Process
{
  public:
    Process(int nbr);
    ~Process();
    NamedPipe &getNamedPipeRead();
    NamedPipe &getNamedPipeWrite();
    void launch(int nbrThread);
    void readInfo();
    void writeInfo();
    pid_t getPid() const;
    void scrap(ProcessData const& data);
    /*Process &operator=(Process const&);
    Process(Process const&);*/

  private:
    NamedPipe *_namedPipeRead;
    NamedPipe *_namedPipeWrite;
    ThreadPool<ProcessData> *_threadPool;
    std::mutex _mutex;
    std::list<std::pair<std::string, std::string>> _regex;
    int _processNumber;
    bool _finished;
    pid_t _pid;
};

#endif /* PROCESS_HPP_ */
