#ifndef BRUTEFORCER_HPP_
# define BRUTEFORCER_HPP_

# include <string>
# include <map>
# include <list>
# include "AEncryptionMethod.hpp"
# include "Parser.hpp"

# define XOR_MIN        255
# define XOR_MAX        65535
# define CESAR_MIN      0
# define CESAR_MAX      255

class                   BruteForcer
{
  Parser                _parser;
  std::string           _raw;
  AEncryptionMethod     *_crypter;

  void                  iterate(unsigned short i, unsigned short key);

  public:
  BruteForcer(std::string const& raw = "",
              std::string const& expr = "(.*?)");
  ~BruteForcer();

  const std::string&    getRaw() const;
  const std::string&    getExpr() const;

  void                  setRaw(std::string const& raw);
  void                  setExpr(std::string const& expr);

  const std::list<std::string>&  forceRaw();
};

#endif /* BRUTEFORCER_HPP_ */
