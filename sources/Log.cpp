#include "Log.hpp"

Log::Log(std::string const &pathToFile) : _file(pathToFile, std::ios_base::app)
{

}

Log::~Log()
{
  this->_file.close();
}

void Log::writeToFile(std::string const &line)
{
  this->_file << line << std::endl;
}
