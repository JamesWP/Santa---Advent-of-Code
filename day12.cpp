
#include <iostream>
#include <fstream>
#include <regex>


int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  std::regex numberPattern("(\"[^\"]*\")|([-]?\\d+)");

  const auto input = std::string((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());


  auto itt = std::sregex_iterator(input.begin(), input.end(), numberPattern);
  auto ittend = std::sregex_iterator();
  long total = 0;
  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    if(m[2].matched){
      int i = std::stoi(m[2].str());
      total += i;
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
