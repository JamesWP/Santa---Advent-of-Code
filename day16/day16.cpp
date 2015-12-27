#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::regex;
using std::stoi;



bool
passes(string itemName,int itemCount)
{

  /**/ if(itemName == "children"    ) return itemCount == 3;
  else if(itemName == "cats"        ) return itemCount >  7;
  else if(itemName == "samoyeds"    ) return itemCount == 2;
  else if(itemName == "pomeranians" ) return itemCount <  3;
  else if(itemName == "akitas"      ) return itemCount == 0;
  else if(itemName == "vizslas"     ) return itemCount == 0;
  else if(itemName == "goldfish"    ) return itemCount <  5;
  else if(itemName == "trees"       ) return itemCount >  3;
  else if(itemName == "cars"        ) return itemCount == 2;
  else if(itemName == "perfumes"    ) return itemCount == 1;
  else return true;
}

void
parseSue(string sue)
{
  auto r = regex("Sue (\\d*): (\\w+): (\\d*), (\\w+): (\\d*), (\\w+): (\\d*)");
  std::smatch m;
  if(std::regex_match(sue,m,r)){
    int sueNo = stoi(m[1].str());
    string item1 = m[2].str();
    int item1tot = stoi(m[3]);
    string item2 = m[4].str();
    int item2tot = stoi(m[5]);
    string item3 = m[6].str();
    int item3tot = stoi(m[7]);
    if(passes(item1,item1tot)
      && passes(item2,item2tot)
      && passes(item3,item3tot)){
          std::cout << "Found Sue " << sueNo << "!" << std::endl;
      }
  }
}

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  for (std::string line; std::getline(f, line);)
    parseSue(line);

  return 0;
}
