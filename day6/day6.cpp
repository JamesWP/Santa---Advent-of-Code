#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

const int gridSize = 1000;
using lightRow = std::bitset<gridSize>;
using lightRows = std::vector<lightRow>;

std::ostream& operator<<(std::ostream &strm, const lightRows &a) {
  for(auto &row:a){
    for(int index=0;index<gridSize;index++){
      bool light = row[index];
      strm << (light? "[]":"<>");
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

void
toggle(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    grid[lineNo] ^= ones(x,x2);
}

void
on(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    grid[lineNo] |= ones(x,x2);
}

void
off(lightRows &grid,const int x,const int y,const int x2,const int y2) {
  for(int lineNo = y;lineNo<=y2;lineNo++)
    grid[lineNo] &= zeros(x,x2);
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);


  lightRows grid(gridSize);

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
    //std::cout << command << ":" << subcommand << " (" << x << "," << y << ") -> (" << x1 << "," << y1 << ") " << std::endl;

    if(command=="turn")
      if(subcommand=="on")
        on(grid,x,y,x1,y1);
      else
        off(grid,x,y,x1,y1);
    else
      toggle(grid,x,y,x1,y1);
  }while(!f.eof());

  //std::cout << grid;




  int lightsOn = 0;

  for(auto &row:grid)
    lightsOn += row.count();

  std::cout << "Lights On: " << lightsOn;

  return 0;
}
