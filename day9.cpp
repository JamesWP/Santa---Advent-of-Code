#include <iostream>
#include <fstream>
#include <regex>
#import <cstdint>
#import <map>
#import <set>
#import <climits>

template<class F,class S>
using tuple = std::pair<F,S>;
using edge = tuple<std::string,int>;
using edgeset = std::set<edge>;
using ttable = std::map<std::string,edgeset>;
using patht = std::vector<std::string>;
using nodeset = std::set<std::string>;
using road = tuple<std::string,std::string>;
using dmap = std::map<road,int>;

// from SO
template <typename T>
bool is_unique(std::vector<T> vec)
{
    std::sort(vec.begin(), vec.end());
    return std::unique(vec.begin(), vec.end()) == vec.end();
}

// calculate distance of a link
int distance(const dmap &dm,std::string from,std::string to)
{
  const auto &it = dm.find({from,to});
  int d = it->second;
  if(d==0 || it==dm.end()) throw std::runtime_error{"Err:" + from + "->" + to};
  return d;
}

int min(int a,int b){return a<b?a:b;}

int max(int a,int b){return a<b?b:a;}

// calculate path length
int
distance(ttable &ts,const dmap &dm,patht &path)
{
  if(!is_unique(path)) return INT_MIN;
  int d = 0;
  for(int index = 0;index<path.size()-1;index++)
    d +=distance(dm,path[index],path[index+1]);
  return d;
}

// recursive complete path
int
minDist(ttable &ts,const dmap &dm,patht &path,int size,int index)
{
  //std::cout << "Populating index" << index << std::endl;
  if(index == size) return distance(ts,dm,path);
  int md = INT_MIN;
  for(auto &n:ts[path[index-1]]){
    path[index] = n.first;
    int dist = minDist(ts,dm,path,size,index+1);
    md = max(md,dist);
  }
  return md;
}

// for each start node
int
minDist(ttable &ts,const nodeset &all,const dmap &dm,patht &path,int size)
{
  int md = INT_MIN;
  for(auto &n:all){
    //std::cout << "Starting at " << n << std::endl;
    path[0] = n;
    int dist = minDist(ts,dm,path,size,1);
    md = max(md,dist);
  }
  return md;
}

// bootstrap
int
minDist(ttable &ts,const dmap &dm,const nodeset &all)
{
  patht path{all.size()};
  return minDist(ts,all,dm,path,all.size());
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  ttable ts;
  nodeset all;
  dmap dm;

  const std::regex linePattern(std::string("([a-zA-Z]*) to ([a-zA-Z]*) = (\\d*)"));
  for (std::string line; std::getline(f, line);){
    std::smatch inputMatch;
    std::regex_match(line, inputMatch, linePattern);
    const std::string from = inputMatch[1].str();
    const std::string to = inputMatch[2].str();
    const int distance = std::stoi(inputMatch[3].str());
    ts[from].insert(edge{to,distance});
    ts[to].insert(edge{from,distance});
    dm[road{from,to}] = distance;
    dm[road{to,from}] = distance;
    all.insert(to);
    all.insert(from);
  }

  int md = minDist(ts,dm,all);
  std::cout << "Minimum Distance: " << md << std::endl;


  return 0;
}
