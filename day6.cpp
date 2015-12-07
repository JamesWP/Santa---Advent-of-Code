#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

const int gridSize = 10;
using lightRow = std::bitset<gridSize>;
using lightRows = std::vector<lightRow>;

std::ostream& operator<<(std::ostream &strm, const lightRows &a) {
  for(auto &row:a){
    for(int index=0;index<gridSize;index++){
      bool light = row[index];
      strm << (light? "[]":"--");
    }
    strm << std::endl;
  }
  return strm;
}

lightRow
ones(int startIndex,int endIndex)
{
  lightRow r;
  for (int i=startIndex;i <= endIndex;i++)
    r[i] = true;
  return r;
}

lightRow
zeros(int startIndex,int endIndex)
{
  lightRow r;
  r.set();
  for (int i=startIndex;i <= endIndex;i++)
    r[i] = false;
  return r;
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);


  lightRows grid(gridSize);

  // set
  grid[0] |= ones(2,5);
  // flip
  grid[1] |= ones(0,gridSize-1);
  grid[1] ^= ones(1,1);
  grid[1] ^= ones(0,gridSize-1);
  // unset
  grid[5] |= ones(0,gridSize-1);
  grid[5] &= zeros(2,5);
  grid[5] &= zeros(0,3);
  std::cout << grid;

  int lightsOn = 0;

  for(auto &row:grid)
    lightsOn += row.count();

  std::cout << "Lights On: " << lightsOn;

  return 0;
}
