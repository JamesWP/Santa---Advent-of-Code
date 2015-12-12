#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <numeric>

const int gridSize = 1000;
using lightRow = std::vector<int>;
using lightRows = std::vector<lightRow>;

template<class V>
V max(V a, V b) {return (a>b)? a:b;}

void
add(std::vector<int> &row,const int x,const int x2,const int amt) {
  for(int index = x;index<=x2;index++)
    row[index] = max(row[index] + amt,0);
}

void
toggle(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    add(grid[lineNo],x,x2,2);
}

void
on(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    add(grid[lineNo],x,x2,1);
}

void
off(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    add(grid[lineNo],x,x2,-1);
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  lightRows grid(gridSize,lightRow(gridSize));

  do{
    std::string command,subcommand,ignore;
    int x,y,x1,y1;
    f >> command;
    if(command=="turn"){
      f >> subcommand;
    }else if(command=="toggle"){
      subcommand = "N/A";
    }
    f >> x;
    f.ignore();
    f >> y;
    f >> ignore;
    f >> x1;
    f.ignore();
    f >> y1;

    if(f.eof()) break;

    if(command=="turn")
      if(subcommand=="on")
        on(grid,x,y,x1,y1);
      else
        off(grid,x,y,x1,y1);
    else
      toggle(grid,x,y,x1,y1);
  }while(!f.eof());

  uint lightsOn = 0;

  for(auto &row:grid)
    lightsOn += std::accumulate(row.begin(), row.end(), 0);

  std::cout << "Lights On: " << lightsOn;

  return 0;
}
