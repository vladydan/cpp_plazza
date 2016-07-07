#include <string>
#include <map>
#include <list>
#include "BruteForcer.hpp"
#include "Parser.hpp"
#include "AEncryptionMethod.hpp"
#include "Cesar.hpp"
#include "Xor.hpp"

BruteForcer::BruteForcer(std::string const& raw, std::string const& expr) :
  _parser("", expr), _raw(raw), _crypter(new Cesar())
{
}

BruteForcer::~BruteForcer()
{
  delete this->_crypter;
}

const std::string&      BruteForcer::getRaw() const
{
  return (this->_raw);
}

void                    BruteForcer::setRaw(std::string const& raw)
{
  this->_raw = raw;
}

const std::string&      BruteForcer::getExpr() const
{
  return (this->_parser.getExpr());
}

void                    BruteForcer::setExpr(std::string const& expr)
{
  this->_parser.setExpr(expr);
}

const std::list<std::string>&    BruteForcer::forceRaw()
{
  this->_crypter->setStringToDecrypt(this->_raw);
  this->iterate(CESAR_MIN, CESAR_MAX);
  // if (this->_parser.getRslt().empty())
  //   {
  //     delete this->_crypter;
  //     this->_crypter = new Xor();
  //     this->_crypter->setStringToDecrypt(this->_raw);
  //     this->_crypter->setKey(XOR_MIN);
  //     this->iterate(XOR_MIN, XOR_MAX);
  //   }
  return (this->_parser.getRslt());
}

void                    BruteForcer::iterate(unsigned short i,
                                             unsigned short key)
{
  while (i <= key)
    {
      this->_crypter->setKey(i);
      this->_parser.setStr(this->_crypter->decrypt());
      this->_parser.match();
      if (!this->_parser.getRslt().empty() || i == key)
        return ;
      ++i;
    }
}
