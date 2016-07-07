#ifndef PROCESSDATA_HPP_
# define PROCESSDATA_HPP_

# include "NamedPipe.hpp"

class ProcessData
{
  public:
    ProcessData(int processNumber = 0, int threadStatus = 0);
    ~ProcessData();
    int getProcessNumber() const;
    void setProcessNumber(int processNumber);
    int getThreadStatus() const;
    int getRetRead() const;
    void setRetRead(int retRead);
    void setThreadStatus(int threadStatus);
    void setFile(char const *file);
    const char *getFile() const;
    void setInfoToFind(const char *info);
    const char *getInfoToFind() const;
    int getExitStatus() const;
    void setExitStatus(int status);
    const char *getRslt() const;
    void setRslt(const char *rslt);
    char getReturn() const;
    void setReturn(char);
  private:
    int _processNumber;
    int _threadStatus;
    char _file[500];
    char _infoToFind[20];
    char _rslt[500];
    int _retRead;
    int _exitProcess;
    char _return;
};

NamedPipe &operator<<(NamedPipe& pipe, ProcessData const &obj);
NamedPipe &operator>>(NamedPipe& pipe, ProcessData *obj);

#endif /* PROCESSDATA_HPP_ */
