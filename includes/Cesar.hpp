#ifndef CESAR_HPP_
# define CESAR_HPP_

# include <string>
# include "AEncryptionMethod.hpp"

class Cesar : public AEncryptionMethod
{
  public:
    Cesar(std::string const& stringToDecrypt = "", unsigned short key = 0);
    virtual ~Cesar();
    virtual const std::string& decrypt();
};

#endif /* CESAR_HPP_ */
