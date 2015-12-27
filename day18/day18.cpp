#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

const int size = 100;
using std::vector;
using board = std::bitset<size*size>;
using neighbours = vector<int>;

int
ind(int row,int col)
{
  if(row==size || row<0 || col==100 || col<0) return -1;
  return row*size + col;
}

neighbours
getNeighbours(int index)
{
  int col = index%size;
  int row = index/size;
  neighbours n(8);
  n[0] = ind(row-1,col-1);
  n[1] = ind(row-1,col  );
  n[2] = ind(row-1,col+1);

  n[3] = ind(row  ,col-1);
  n[4] = ind(row  ,col+1);

  n[5] = ind(row+1,col-1);
  n[6] = ind(row+1,col  );
  n[7] = ind(row+1,col+1);

  return n;
}

bool
itteration(const board b, int index)
{
  int total = 0;
  for(auto &n:getNeighbours(index)){
    if(n>=0 && b[n]) total++;
  }
  return b[index]? (total==2||total==3):(total==3);
}

board
itteration(const board b)
{
  board b2=0;

  for(int i=0;i<size*size;i++){
    if(i==ind(0,0) || i==ind(99,0) || i==ind(99,99) || i==ind(0,99))
      b2[i]=true;
    else b2[i] = itteration(b,i);
  }

  return b2;
}

int
main(int argc, char const *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  board b = 0;
  int lineNo = 0;
  for (std::string line; std::getline(f, line);){
    int colNo = 0;
    for(auto &c:line){
      b[ind(lineNo,colNo)] = (c=='#');
      colNo++;
    }
    lineNo++;
  }

  std::cout << "Start: " << b.count() << std::endl;

  for(int i=0;i<100;i++)
    b = itteration(b);

  std::cout << "Done: " << b.count() << std::endl;

  return 0;
}
