#include <iostream>
#include <fstream>


int
countMemoryChars(std::string line)
{
  int chars = 0;
  for(int index = 0; index<line.length(); index++){
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

  std::cout << "Mem chars for " << line << " = " << chars << std::endl;
  return chars;
}

int
countEncodedChars(std::string line)
{
  int chars = 2;
  for(int index=0; index<line.length(); index++){
    switch(line[index]){
      case '\"':
      case '\\':
        chars++;
      default:
        chars++;
    }
  }

  std::cout << "Enc chars for " << line << " = " << chars << std::endl;
  return chars;
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int memChars = 0, total = 0, encChars = 0;
  for (std::string line; std::getline(f, line);){
    memChars += countMemoryChars(line);
    encChars += countEncodedChars(line);
    total += line.length();
  }

  std::cout << "Diff in mem chars: " << total - memChars << std::endl;
  std::cout << "Diff in enc chars: " << encChars - total << std::endl;

  return 0;
}
