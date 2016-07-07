#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

# include <exception>
# include <string>

class baseException : public std::exception
{
  public:
    baseException(const std::string message) : _message(message) { };
    ~baseException(void) { };
    const char* what() { return this->_message.c_str(); };
  private:
    std::string _message;
};

#endif /* EXCEPTION_HPP_ */
