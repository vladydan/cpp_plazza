#ifndef NAMED_PIPE_HPP_
# define NAMED_PIPE_HPP_

# include <string>

class ProcessData;

# define READER 1
# define WRITER 0

class NamedPipe
{
  public:
    NamedPipe(std::string const& pathToPipe);
    ~NamedPipe();
    void writePipe(ProcessData const &data) const;
    int readPipe(ProcessData *data) const;
    void createMkfifo() const;
    void openPipe(int flag);
    void closePipe() const;
    void removePipe() const;

  private:
    NamedPipe(NamedPipe const&);
    NamedPipe &operator=(NamedPipe const&);
    int _fd;
    std::string _pathToPipe;
};

#endif /* NAMED_PIPE_HPP_ */
