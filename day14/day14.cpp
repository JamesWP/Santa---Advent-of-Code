#include <iostream>
#include <fstream>
#include <regex>

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

  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    std::string name = m[Pat::Name].str();
    int speed = std::stoi(m[Pat::Speed].str());
    int stamina = std::stoi(m[Pat::Stamina].str());
    int rest = std::stoi(m[Pat::Rest].str());
    std::cout << "Name: " << name;
    // how long is each total period
    int period = stamina + rest;
    int periodDistance = speed  * stamina;
    // how many times can he complete a whole period?
    int numPeriods = totSeconds / period;
    // how long is that?
    int totalDistance = periodDistance * numPeriods;
    // how long has he got left?
    int remainingTime = totSeconds % period;
    // how long is that?
    std::cout << " rt: " << remainingTime << " st:" << stamina;
    int remainingDistance = std::min(remainingTime,stamina) * speed;
    std::cout << " Distance: " << totalDistance << "+" << remainingDistance << "=" << totalDistance + remainingDistance;
    std::cout << std::endl;
  }

  return 0;
}
