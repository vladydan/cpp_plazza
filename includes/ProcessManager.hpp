#ifndef PROCESS_MANAGER_HPP_
# define PROCESS_MANAGER_HPP_

# include <thread>
# include <string>
# include <list>
# include <map>
# include <sys/types.h>
# include <sys/wait.h>
# include "Process.hpp"
# include "NamedPipe.hpp"
# include "Log.hpp"

class ProcessManager
{
  public:
    ProcessManager();
    ~ProcessManager();
    bool addOrder(std::list<std::string> &fileList, std::string const &info, int nbrThreads);
    NamedPipe &getNamedPipeRead();
    NamedPipe &getNamedPipeWrite();
    std::list<Process *> &getProcess();
    void readInfo();
    void writeInfo();
    void joinReadThread();
    void exitProcesses();
    const std::list<std::pair<int, int>> &getProcessData() const;
    const std::map<int, std::list<std::string>> &getResults() const;
    void clearResult();
  private:
    NamedPipe *_namedPipeRead;
    NamedPipe *_namedPipeWrite;
    std::list<Process *> _process;
    std::thread *_readThread;
    std::list<std::pair<int, int>> _processData;
    std::map<int, std::list<std::string>> _results;
    bool _endExecution;
    bool _isAlone;
    Log _log;
};

#endif /* PROCESS_MANAGER_HPP_ */
