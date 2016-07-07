#include <string>
#include "Cesar.hpp"

Cesar::Cesar(std::string const& stringToDecrypt, unsigned short key) :
  AEncryptionMethod(stringToDecrypt, key)
{
}

Cesar::~Cesar()
{
}

const std::string& Cesar::decrypt()
{
  this->_decryptedString = "";
  int tmp = 0;

  for (unsigned char cipherchar : this->_stringToDecrypt)
  {
    if (cipherchar - this->_key < 0)
    {
      tmp = cipherchar - this->_key;
      cipherchar = 256 + tmp;
      this->_decryptedString += cipherchar;
    }
    else
      this->_decryptedString += (cipherchar - this->_key);
  }
  return (this->_decryptedString);
}
