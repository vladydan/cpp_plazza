#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "NamedPipe.hpp"
#include "ProcessData.hpp"

NamedPipe::NamedPipe(std::string const& pathToPipe) :
  _pathToPipe(pathToPipe)
{
}

NamedPipe::~NamedPipe()
{
  if (fcntl(this->_fd, F_GETFD) != -1)
  {
    if((close(this->_fd)) == -1)
    {
      perror("close");
      exit(EXIT_FAILURE);
    }
  }
}

void NamedPipe::writePipe(ProcessData const &data) const
{
  int ret;

  ret = write(this->_fd, &data, sizeof(ProcessData));
  (void)ret;
}

void NamedPipe::createMkfifo() const
{
  if (mkfifo(this->_pathToPipe.c_str(), 0666) == -1)
  {
    if (unlink(this->_pathToPipe.c_str()) != 0)
    {
      perror("remove");
    }
    if (mkfifo(this->_pathToPipe.c_str(), 0666) == -1)
    {
      std::cerr << getpid() << ": Error in creation of named pipe" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

void NamedPipe::openPipe(int flag)
{
  if (flag == WRITER)
  {
    if ((this->_fd = open(this->_pathToPipe.c_str(), O_WRONLY)) == -1)
    {
      perror("open");
      exit(EXIT_FAILURE);
    }
  }
  else if (flag == READER)
  {
    if ((this->_fd = open(this->_pathToPipe.c_str(), O_RDONLY)) == -1)
    {
      perror("open");
      exit(EXIT_FAILURE);
    }
  }
}

void NamedPipe::removePipe() const
{
  if ((unlink(this->_pathToPipe.c_str())) == -1)
  {
    perror("unlink");
  }
}

void NamedPipe::closePipe() const
{
  if ((close(this->_fd)) == -1)
  {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

int NamedPipe::readPipe(ProcessData *data) const
{
  int ret = 0;
  fd_set set;
  struct timeval timeout;
  int falseRet;

  FD_ZERO(&set);
  FD_SET(this->_fd, &set);

  timeout.tv_sec = 0;
  timeout.tv_usec = 5000000;

  ret = select(this->_fd + 1, &set, NULL, NULL, &timeout);
  if (ret != 0)
    falseRet = read(this->_fd, data, sizeof(ProcessData));
  (void)falseRet;
  return (ret);
}
