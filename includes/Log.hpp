#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>

class Log
{
  public:
    Log(std::string const &pathToFile);
    ~Log();
    void writeToFile(std::string const &line);
  private:
    std::fstream _file;
};

#endif
