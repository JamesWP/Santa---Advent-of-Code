#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::regex;
using std::stoi;
using std::vector;
using std::bitset;

const bool bitSet(int var, int pos)
{
  return (var) & (1<<(pos));
}

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  vector<int> sizes;
  for (std::string line; std::getline(f, line);){
    sizes.push_back(stoi(line));
    std::cout << line << std::endl;
  }

  vector<bool> used(sizes.size(),false);
  int combinations = 0;
  int minContainers = sizes.size()+1;
  const int combs = 2 << (sizes.size()-1);
  for(int bits=0;bits<combs;bits++){
    int total = 0;
    int containers = 0;
    //std::cout << "Comb[";
    for(int i=0;i<sizes.size();i++){
      if(bitSet(bits,i)){
        //std::cout << sizes[i] << ",";
        total += sizes[i];
        containers++;
      };
    }
    if(total == 150 && minContainers >= containers) {
      //std::cout << "=25";
      combinations = (minContainers>containers)? 1:combinations+1;
      minContainers = containers;
    }
    //std::cout << "]" << std::endl;
  }

  std::cout << "Size combs: " << combs << std::endl;
  std::cout << "Total combs: " << combinations << std::endl;

  return 0;
}
