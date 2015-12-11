#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string
sayWhatYouSee(std::string input)
{
  std::stringstream output;
  char last = input[0];
  int repeat = 1;
  for(int index = 1; index < input.length();index++){
    const char &ch = input[index];
    if(last != ch){
      //std::cout << "Char: " << last  << " Repeated: " << repeat << std::endl;
      output << repeat << last;
      repeat = 1;
      last = ch;
    }else
      repeat++;
  }
  //std::cout << "Char: " << last  << " Repeated: " << repeat << std::endl;
  output << repeat << last;
  return output.str();
}

std::string
sayWhatYouSee(std::string input, int numTimes)
{
  for(int i=0;i<numTimes;i++)
    input = sayWhatYouSee(input);
  return input;
}

int
main(int argc, char const *argv[]) {

  std::string input = argv[1];

  std::cout << "Input: " << input << std::endl;
  std::cout << "Output Length: " << sayWhatYouSee(input,50).length() << std::endl;
  
  
  
  return 0;
}

