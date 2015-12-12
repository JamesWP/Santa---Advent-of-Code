#include <iostream>
#include <fstream>
#include <string>

std::string
increment(std::string input)
{
  for(int index = input.length()-1;index>=0;index--){
    char ch = input[index];
    if(ch != 'z'){
      input[index] = ch+1;
      break;
    }else{
      input[index] = 'a';
    }
  }
  return input;
}

bool
rule1(const std::string &input)
{
  //Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd doesn't count.
  char last = input[0];
  int count = 1;
  for(int index = 1;index<input.length();index++){
    if(input[index] == last+1)
      count++;
    else count = 1;
    if(count==3) return true;
    last = input[index];
  }
  return false;  
}

bool
rule2(const std::string &input)
{
  // cant contain i o l;
  for(int index = 0;index<input.length();index++){
    switch(input[index]){
      case 'i':
      case 'o':
      case 'l':
        return false;
    }
  }
  return true;  
}

bool
rule3(const std::string &input)
{
  int pairs = 0;
  char firstPair;
  char last = input[0];
  for(int index = 1;index<input.length();index++){
    if(input[index]==last){
      if(pairs==1 && firstPair!=last) pairs++;
      if(pairs==0){ 
        pairs++;
        firstPair = input[index];
      }
      if(pairs==2) return true;
      index++;
      if(index==input.length()) return false;
      last = input[index];
    }
    last = input[index];
  }//ghjaabcc
  return false;  
}

int
main(int argc, char const *argv[]) {

  std::string input = argv[1];

  if(input.length()!=8) return std::cerr << "Please enter 8 characters" << std::endl,0;
  
  std::cout << "Input: " << input;
  std::cout << " rule1(" << (rule1(input)?"true":"false") << ")" << std::endl;
  std::cout << " rule2(" << (rule2(input)?"true":"false") << ")" << std::endl;
  std::cout << " rule3(" << (rule3(input)?"true":"false") << ")" << std::endl;
  input = increment(input);
  while(!(rule1(input)&&rule2(input)&&rule3(input))){
    input = increment(input);
    //std::cout << "Increment: " <<  input << std::endl;
  }
  std::cout << "Output: " << input << std::endl;
  
  return 0;
}

