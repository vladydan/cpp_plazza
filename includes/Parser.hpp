#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/regex.hpp>
# include <utility>
# include <string>
# include <list>
# include <map>

typedef std::list<std::pair<std::list<std::string>,
                            std::string>> ListOfCommands;

class                      Parser
{
  std::string              _str;
  std::string              _expr;
  boost::regex             _regex;
  std::list<std::string>   _rslt;

 public:
  Parser(std::string const& str = std::string(""),
         std::string const& expr = std::string("(.*?)"));
  ~Parser();

  void                  setExpr(std::string const& expr);
  void                  setStr(std::string const& str);
  const std::string&    getExpr() const;
  const std::string&    getStr() const;
  const std::list<std::string>&  getRslt() const;

  bool                  match();
  void                  clearRslt();
  ListOfCommands        *convertStringToList(std::string strintToConvert);
};

#endif /* PARSER_HPP_ */
