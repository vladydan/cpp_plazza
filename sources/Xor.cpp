#include <string>
#include "Xor.hpp"
#include "AEncryptionMethod.hpp"

Xor::Xor(std::string const& stringToDecrypt, unsigned short key) :
  AEncryptionMethod(stringToDecrypt, key)
{
}

Xor::~Xor()
{
}

const std::string& Xor::decrypt()
{
  u_split split;

  split._short = this->_key;
  this->_decryptedString = "";
  int i = 0;
  for (char &cipherchar : this->_stringToDecrypt)
  {
    this->_decryptedString += cipherchar ^ split._char[i % 2];
    i++;
  }
  return (this->_decryptedString);
}
