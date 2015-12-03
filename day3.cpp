#include <iostream>
#include <fstream>
#include <set>

using house = std::pair<int,int>;

const int SANTA = 0;
const int ROBOSANTA = 1;

template<class T>
bool contains(std::set<T> ts,T t)
{
  return ts.find(t)!=ts.end();
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int houses = 1;
  int turn = SANTA;

  house curentHouse[2] = {{0,0},{0,0}};

  std::set<house> visited;

  visited.insert(curentHouse[SANTA]);

  char direction;
  do{
    f >> direction;

    if(f.eof()) break;

    switch(direction){
      case '^':
        curentHouse[turn].second++;
        break;
      case 'v':
        curentHouse[turn].second--;
        break;
      case '<':
        curentHouse[turn].first--;
        break;
      case '>':
        curentHouse[turn].first++;
        break;
      default:;
    }

    visited.insert(curentHouse[turn]);

    // comment this out to get part one solution
    turn = (turn==SANTA)? ROBOSANTA:SANTA;

    //std::cout << "[" << curentHouse.first << "," << curentHouse.second << "]" << std::endl;

  }while(!f.eof());

  std::cout << "Houses visited: " << visited.size() << std::endl;

  return 0;
}
