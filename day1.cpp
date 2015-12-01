#include <iostream>
#include <fstream>

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);
  char bracket;
  int flr = 0;
  int position = 1;
  bool notPrintedBasement = true;
  f >> bracket;
  while(!f.eof())
  {
    switch(bracket)
    {
      case '(':
        flr++;
        break;
      case ')':
        flr--;
        break;
      default:
        break;
    }
    if(flr<0 && notPrintedBasement){
      std::cout << "Entered basement at position: " << position << std::endl;
      notPrintedBasement = false;
    }
    f >> bracket;
    position++;
  }
  f.close();

  std::cout << "Floor: " << flr;
  return 0;
}
