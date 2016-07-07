#ifndef AENCRYPTIONMETHOD_HPP_
# define AENCRYPTIONMETHOD_HPP_

# include <string>

class AEncryptionMethod
{
  public:
    AEncryptionMethod(std::string const& stringToDecrypt = "",
                      unsigned short key = 0);
    AEncryptionMethod(AEncryptionMethod const &);
    AEncryptionMethod &operator=(AEncryptionMethod const &);
    virtual ~AEncryptionMethod();
    virtual void setKey(unsigned short key);
    virtual unsigned short getKey() const;
    virtual void setStringToDecrypt(std::string const& stringToDecrypt);
    virtual const std::string& getStringToDecrypt() const;
    virtual const std::string& getDecryptedString() const;
    virtual const std::string& decrypt() = 0;
  protected:
    unsigned short _key;
    std::string _stringToDecrypt;
    std::string _decryptedString;
};

#endif /* AENCRYPTIONMETHOD_HPP_ */
