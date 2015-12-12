#include <stdio.h>
#include <string.h>
#include <sstream>
#include "libs/md5.hpp"

int main(int argc,char *argv[])
{
    std::string input = argv[1];
    //std::string prefix("00000");
    std::string prefix("000000");

    int answer = -1;

    for(int i=0;;i++){
      std::ostringstream oss;
      oss << input << i;
      std::string inputWithNumber = oss.str();

      std::string output = md5(inputWithNumber);
      if(output.substr(0, prefix.size()) == prefix){
        std::cout << output << std::endl;
        answer = i;
        break;
      }
    }

    std::cout << answer;

    return 0;
}
