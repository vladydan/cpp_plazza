#ifndef XOR_HPP_
# define XOR_HPP_

# include <string>
# include "AEncryptionMethod.hpp"

union u_split
{
  unsigned char _char[2];
  unsigned short _short;
};

class Xor : public AEncryptionMethod
{
  public:
    Xor(std::string const& stringToDecrypt = "", unsigned short key = 0);
    virtual ~Xor();
    virtual const std::string& decrypt();
};

#endif /* XOR_HPP_ */
