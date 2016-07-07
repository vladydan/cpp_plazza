#include <boost/regex.hpp>
#include <utility>
#include <string>
#include <list>
#include "Parser.hpp"

Parser::Parser(std::string const& str, std::string const& expr) :
  _str(str), _expr(expr), _regex(boost::regex(expr))
{
}

Parser::~Parser()
{
}

void                    Parser::setExpr(std::string const& expr)
{
  this->_expr = expr;
  this->_regex = boost::regex(this->_expr);
}

void                    Parser::setStr(std::string const& str)
{
  this->_str = str;
}

const std::string&      Parser::getStr() const
{
  return (this->_str);
}

const std::string&      Parser::getExpr() const
{
  return (this->_expr);
}

const std::list<std::string>& Parser::getRslt() const
{
  return (this->_rslt);
}

void                    Parser::clearRslt()
{
  this->_rslt.clear();
}

bool                    Parser::match()
{
  boost::sregex_iterator it(this->_str.begin(), this->_str.end(), this->_regex);
  boost::sregex_iterator end;

  if (it == end)
    return (false);
  while (it != end)
    {
      this->_rslt.push_back(it->str());
      ++it;
    }
  return (true);
}

#include <iostream>

ListOfCommands *Parser::convertStringToList(std::string stringToConvert)
{
  std::list<std::string> list;
  std::string buf;
  ListOfCommands *order = new ListOfCommands;
  std::stringstream ss(stringToConvert);
  std::list<std::string> listOfFile;
  std::pair<std::list<std::string>, std::string> pair;

  list.push_back("(PHONE_NUMBER)");
  list.push_back("(EMAIL_ADDRESS)");
  list.push_back("(IP_ADDRESS)");
  bool pushed = false;
  while (ss >> buf)
  {
    bool found = false;
    pushed = false;
    this->setStr(buf);
    for (std::string &expr : list)
    {
      this->setExpr(expr);
      if (this->match() == true)
      {
        std::string newExpr = expr;
        pair.second = *this->_rslt.begin();
        found = true;
        newExpr.insert(newExpr.size() - 1, "*;");
        this->setExpr(newExpr);
        if (this->match() == true)
        {
          pushed = true;
          order->push_back(pair);
          pair.first.clear();
          pair.second.clear();
        }
        this->clearRslt();
        break;
      }
    }
    if (buf == ";")
    {
      pushed = true;
      order->push_back(pair);
      pair.first.clear();
      pair.second.clear();
    }
    else if (found == false)
    {
      pushed = false;
      pair.first.push_back(buf);
    }
  }
  if (pushed == false)
  {
    order->push_back(pair);
  }
  return order;
}
