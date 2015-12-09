#include <iostream>
#include <fstream>


int
countMemoryChars(std::string line)
{
  int chars = 0;
  for(int index = 0;index < line.length();index++){
    if(index==0 || index==line.length()-1) continue;
    if(line[index]=='\\'){
      index++;
      switch(line[index]){
        case 'x':
          index += 2;
        case '\\':
        case '\"':
          chars++;
      }
    }else{
      chars++;
    }
  }

  std::cout << "Chars for " << line << " = " << chars << std::endl;
  return chars;
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int chars = 0,total = 0;
  for (std::string line; std::getline(f, line);)
    chars += countMemoryChars(line), total += line.length();

  std::cout << "Chars: " << total - chars << std::endl;

  return 0;
}
