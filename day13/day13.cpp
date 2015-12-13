#include <iostream>
#include <algorithm>
#include <fstream>
#include <regex>
#include <set>
#include <map>
#include <vector>

using person = std::string;
using table = std::vector<person>;

class PeopleGraph {
public:
  std::map<std::tuple<person,person>,int> happynes;
  std::set<person> people;
  void addLine(person p,person next2,int happy){
    people.insert(p);
    people.insert(next2);
    happynes[std::make_tuple(p,next2)] = happy;
  }
};

// from SO
template <typename T>
bool is_unique(std::vector<T> vec)
{
    std::sort(vec.begin(), vec.end());
    return std::unique(vec.begin(), vec.end()) == vec.end();
}

int score(table &t, const PeopleGraph &pg){
  if(!is_unique(t)) return INT_MIN;
  int score = 0;
  for(int index=0;index<t.size();index++){

    const person p = t[index];
    const person next = t[(index+1)%t.size()];
    int happy = pg.happynes.at(std::make_tuple(p,next));
    happy += pg.happynes.at(std::make_tuple(next,p));
    //std::cout << p << "("<< happy <<"),";
    score += happy;
  }
  //std::cout << t[0] << std::endl;
  return score;
}

int constructTable(table &t, int left, const PeopleGraph &pg){
  if (left == 0) return score(t,pg);
  int sc = INT_MIN;
  for(const auto &p:pg.people){
    if(std::find(t.begin(),t.end(),p)!=t.end()) continue;
    t.push_back(p);
    sc = std::max(sc,constructTable(t,left-1,pg));
    t.pop_back();
  }
  return sc;
}

int constructTable(const PeopleGraph &pg){
    table t;
    return constructTable(t,pg.people.size(),pg);
}

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  std::regex numberPattern("(\\w+) would ((gain)|(lose)) (\\d+) happiness units by sitting next to (\\w+)\\.");
  enum Pat{From=1,Gain=3,Loose=4,Amount=5,To=6};

  const auto input = std::string((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());

  PeopleGraph pg;

  auto itt = std::sregex_iterator(input.begin(), input.end(), numberPattern);
  auto ittend = std::sregex_iterator();

  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    pg.addLine(m[Pat::From].str(),
      m[Pat::To].str(),
      (m[Pat::Gain].matched?1:-1) * std::stoi(m[Pat::Amount].str()));
  }

  std::set<person> people = pg.people;
  for(auto &p:people){
    pg.addLine("Me",p,0);
    pg.addLine(p,"Me",0);
  }

  std::cout << "Max cost: " << constructTable(pg) << std::endl;

  return 0;
}
