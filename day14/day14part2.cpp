#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  const int totSeconds = 2503;
  //const int totSeconds = 1000;

  std::regex numberPattern("(\\w+) can fly (\\d+) km\\/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");
  enum Pat{Name=1,Speed=2,Stamina=3,Rest=4};

  const auto input = std::string((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());

  auto itt = std::sregex_iterator(input.begin(), input.end(), numberPattern);
  auto ittend = std::sregex_iterator();

  using reindeer = std::tuple<std::string,int,int,int>;
  // bool:running, int:secs_remainin, int:dist, point
  using deerState = std::tuple<bool,int,int,int>;
  std::map<reindeer,deerState> progress;

  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    std::string name = m[Pat::Name].str();
    int speed = std::stoi(m[Pat::Speed].str());
    int stamina = std::stoi(m[Pat::Stamina].str());
    int rest = std::stoi(m[Pat::Rest].str());

    progress[std::make_tuple(name,speed,stamina,rest)] = std::make_tuple(true,stamina,0,0);
  }
  for(int i=0;i<totSeconds;i++){
    int dist = 0;
    for(auto &d:progress){
      auto &deerState = d.second;
      const auto &deer = d.first;
      bool running = std::get<0>(deerState);

      // if we are running, run the distance
      if(running) std::get<2>(deerState) += std::get<1>(deer);
      // decrement the remaining time
      std::get<1>(deerState)--;
      if(std::get<1>(deerState)<1){
        // we have timed out, switch state
        std::get<0>(deerState) = !running;
        // reset the time
        std::get<1>(deerState) =
          (!running)?std::get<2>(deer):std::get<3>(deer);
      }
      dist = std::max(dist,std::get<2>(deerState));
    }
    // give the winning deer(s) a point
    for(auto &d:progress){
      auto &deerState = d.second;
      const auto &deer = d.first;
      if(std::get<2>(deerState) == dist)
        std::get<3>(deerState)++;
      //std::cout << i << " Deer:" << std::get<0>(deer) << " is " << (std::get<0>(deerState)?"running":"resting") << " for " << std::get<1>(deerState) << " Distance:" << std::get<2>(deerState) << std::endl;
    }
  }

  for(auto &d:progress){
    auto &deerState = d.second;
    const auto &deer = d.first;
    std::cout << std::get<0>(deer) << "\tDistance" << std::get<2>(deerState);
    std::cout << " Points:" << std::get<3>(deerState) << std::endl;
  }

  return 0;
}
