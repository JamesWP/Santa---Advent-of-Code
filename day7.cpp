#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <cctype>
#include <cstdint>

using identifier = std::string;
using valtype = uint16_t;

class Operand
{
public:
  enum Type {NUM,IDENT};
  Type t;
  valtype value;
  identifier ident;
  Operand(valtype value):t{Type::NUM},value{value}{}
  Operand(identifier ident):t{Type::IDENT},ident{ident}{}
  Operand(){}
};

std::ostream & operator<<(std::ostream &os, const Operand& o)
{
  os << "Operand(";
  if(o.t==Operand::Type::NUM)
    os << "val=" << o.value;
  else
    os << o.ident;
  return os << ")" ;
}

class Expression
{
public:
  enum Operation {EQ, NOT,OR,AND,LSHIFT,RSHIFT};
  Operation op;
  Operand a,b;
  Expression(Operation op,Operand a,Operand b):op{op},a{a},b{b}{}
  Expression(Operation op,Operand a):op{op},a{a}{}
  Expression(){}
};

std::ostream & operator<<(std::ostream &os, const Expression& e)
{
  static const std::string opnames[] = { "EQ", "NOT", "OR", "AND", "LSHIFT", "RSHIFT" };
  os << "Expression(";
  os << opnames[e.op] << ",";
  os << e.a;
  if(e.op!=Expression::Operation::NOT && e.op!=Expression::Operation::EQ)
    os << "," << e.b;
  return os << ")" ;
}

Operand
parseOperand(std::string operand)
{
  if(isdigit(operand[0]))
    return {(valtype)std::stoi(operand)};
  else
    return {operand};
}

void
parseExp(std::map<identifier,Expression> &values, std::string input)
{
  const std::regex inputRegex(std::string("(((NOT)|((\\d+|[a-z]{1,2}) (AND|OR|LSHIFT|RSHIFT))) |(\\d+)|([a-z]{1,2}))(\\d*|[a-z]{1,2}) -> ([a-z]{1,2})"));
  std::smatch inputMatch;
  if(std::regex_match(input, inputMatch, inputRegex)){
    Expression::Operation op = Expression::Operation::EQ;
    /**/ if (inputMatch[3].matched)        op = Expression::Operation::NOT;
    else if(inputMatch[6].str()==   "AND") op = Expression::Operation::AND;
    else if(inputMatch[6].str()==    "OR") op = Expression::Operation::OR;
    else if(inputMatch[6].str()=="LSHIFT") op = Expression::Operation::LSHIFT;
    else if(inputMatch[6].str()=="RSHIFT") op = Expression::Operation::RSHIFT;
    identifier id = inputMatch[10].str();

    if(op==Expression::Operation::NOT){
      values[id] = {op,parseOperand(inputMatch[9].str())};
    }else if(op==Expression::Operation::EQ){
      if(inputMatch[8].matched)
        values[id] = {op,parseOperand(inputMatch[8].str())};
      else
        values[id] = {op,parseOperand(inputMatch[7].str())};
    }else{
      values[id] = {op,parseOperand(inputMatch[5].str()),parseOperand(inputMatch[9].str())};
    }
    std::cout << id << "<-" << values[id] << std::endl;
  }
}

// ahead declaration
valtype
evaluate(std::map<identifier,Expression> &values,const identifier id);

valtype
evaluate(std::map<identifier,Expression> &values,Operand o)
{
  std::cout << "eval" << o << std::endl;
  if(o.t==Operand::Type::NUM)
    return o.value;
  else
    return evaluate(values,o.ident);
}

valtype
evaluate(std::map<identifier,Expression> &values,Expression e)
{
  std::cout << "eval" << e << std::endl;
  switch(e.op){
    case Expression::Operation::EQ:
      return evaluate(values,e.a);
    case Expression::Operation::NOT:
      return ~evaluate(values,e.a);
    case Expression::Operation::AND:
      return evaluate(values,e.a) & evaluate(values,e.b);
    case Expression::Operation::OR:
      return evaluate(values,e.a) | evaluate(values,e.b);
    case Expression::Operation::LSHIFT:
      return evaluate(values,e.a) << evaluate(values,e.b);
    case Expression::Operation::RSHIFT:
      return evaluate(values,e.a) >> evaluate(values,e.b);
  }
}

valtype
evaluate(std::map<identifier,Expression> &values,const identifier id)
{
  std::cout << "eval" << id << std::endl;
  valtype val = evaluate(values,values[id]);
  values[id] = {Expression::Operation::EQ,{val}};
  return val;
}

int
main(int argc, char const *argv[]) {
  std::fstream f;
  f.open(argv[1], std::fstream::in);


  std::map<identifier,Expression> values;
  for (std::string line; std::getline(f, line);)
    parseExp(values, line);

  // the below is needed for part 2
  valtype part1 = 956;
  values["b"] = {Expression::Operation::EQ,{part1}};

  std::cout << "a <-" << evaluate(values,"a") << std::endl;

  return 0;
}
