#include <iostream>
#include <fstream>
#include <regex>

enum Tok {Open=1,Close=2,Red=3,Digit=6};
const std::string regexPatternStr = "([\\[\\{])|([\\]\\}])|(\"red\")|((\"[^\"]*\")|([-]?\\d+))";

int
countGroup(std::sregex_iterator &i,std::sregex_iterator ittend,const char open)
{
  long total = 0;
  bool foundRed = false;
  for(i = ++i; i != ittend; ++i)
  {
    std::smatch m = *i;
    if(m[Tok::Digit].matched){
      int num = std::stoi(m[Tok::Digit].str());
      total += num;
    }else if(m[Tok::Open].matched){
      int num = countGroup(i,ittend,m[Tok::Open].str()[0]);
      total += num;
    }else if(m[Tok::Red].matched && open == '{'){
      foundRed = true;
    }else if(m[Tok::Close].matched){
      break;
    }
  }
  if(foundRed) return 0;
  else return total;
}

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  std::regex numberPattern(regexPatternStr);
  const auto input = std::string((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());

  auto itt = std::sregex_iterator(input.begin(), input.end(), numberPattern);
  auto ittend = std::sregex_iterator();
  long total = 0;
  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    if(m[Tok::Open].matched){
      int num = countGroup(i,ittend,m[Tok::Open].str()[0]);
      total += num;
    }else{
      throw std::runtime_error("Unexpected token: " + m.str());
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
