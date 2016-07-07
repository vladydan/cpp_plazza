#include <string>
#include "AEncryptionMethod.hpp"

AEncryptionMethod::AEncryptionMethod(std::string const& stringToDecrypt,
                                     unsigned short key) :
  _key(key), _stringToDecrypt(stringToDecrypt)
{
}

AEncryptionMethod::AEncryptionMethod(AEncryptionMethod const &cpy)
{
  this->_key = cpy._key;
  this->_stringToDecrypt = cpy._stringToDecrypt;
  this->_decryptedString = cpy._decryptedString;
}

AEncryptionMethod::~AEncryptionMethod()
{
}

AEncryptionMethod &AEncryptionMethod::operator=(AEncryptionMethod const &cpy)
{
  if (this != &cpy)
    {
      this->_key = cpy._key;
      this->_stringToDecrypt = cpy._stringToDecrypt;
      this->_decryptedString = cpy._decryptedString;
    }
  return *this;
}

void AEncryptionMethod::setKey(unsigned short key)
{
  this->_key = key;
}

unsigned short AEncryptionMethod::getKey() const
{
  return (this->_key);
}

void AEncryptionMethod::setStringToDecrypt(std::string const& stringToDecrypt)
{
  this->_stringToDecrypt = stringToDecrypt;
}

const std::string& AEncryptionMethod::getStringToDecrypt() const
{
  return (this->_stringToDecrypt);
}

const std::string& AEncryptionMethod::getDecryptedString() const
{
  return (this->_decryptedString);
}
