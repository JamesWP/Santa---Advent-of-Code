#include <iostream>
#include <fstream>
#include <map>

template<class T,class V>
bool contains(std::map<T,V> ts,T t)
{
  return ts.find(t)!=ts.end();
}

template<class F,class S>
std::ostream& operator<<(std::ostream &strm, const std::pair<F,S> &a) {
  return strm << "Pair(" << a.first << "," << a.second << ")";
}

bool
rule1(std::string input)
{
  // It contains at least three vowels (aeiou only), like aei, xazegov, or
  //aeiouaeiouaeiou.
  int vowels = 0;
  for(auto &ch:input)
    switch(ch){
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        vowels++;
    }
  return vowels>=3;
}

bool
rule2(std::string input)
{
  // It contains at least one letter that appears twice in a row, like xx,
  //abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
  auto it = std::begin(input);
  char last = *it;
  // do your special stuff here with the first element
  ++it;
  for (auto end=std::end(input); it!=end; ++it) {
    if(last == *it)
      return true;
    last = *it;
  }
  return false;
}

bool
rule3(std::string input)
{
  // It does not contain the strings ab, cd, pq, or xy, even if they are part
  //of one of the other requirements.
  auto it = std::begin(input);
  char last = *it;
  ++it;
  for (auto end=std::end(input); it!=end; ++it) {
    if(last == 'a' && *it == 'b') return false;
    if(last == 'c' && *it == 'd') return false;
    if(last == 'p' && *it == 'q') return false;
    if(last == 'x' && *it == 'y') return false;
    last = *it;
  }
  return true;
}

bool
rule4(std::string input)
{
  // It contains a pair of any two letters that appears at least twice in the
  //string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like
  //aaa (aa, but it overlaps).
  using letters = std::pair<char,char>;
  using pairs = std::map<letters,int>;
  pairs seen;
  auto it = std::begin(input);
  char last = *it;
  int index = 0;
  ++it;
  for (auto end=std::end(input); it!=end; ++it,index++) {
    letters ls = {last,*it};
    if(contains(seen,ls)){
      int oPos = seen[ls];
      if ((index - oPos) > 1) {
        return true;
      }
    }else{
      seen[ls] = index;
    }
    last = *it;
  }
  return false;
}

bool
rule5(std::string input)
{
  // It contains at least one letter which repeats with exactly one letter
  //between them, like xyx, abcdefeghi (efe), or even aaa.
  char last = input[0],middle = input[1];
  for(int index = 2;index<input.length();index++) {
    char ch = input[index];
    if(ch == last)
      return true;
    last = middle;
    middle = ch;
  }
  return false;
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int niceStrings = 0;

  std::string line;
  do{
    f >> line;

    if(f.eof()) break;

    std::cout << line;
    std::cout << " rule4(" << (rule4(line)? "pass":"fail") << ")";
    std::cout << " rule5(" << (rule5(line)? "pass":"fail") << ")";
    std::cout << std::endl;

    if(rule4(line) && rule5(line)) niceStrings++;

  }while(!f.eof());

  std::cout << "Nice strings: " << niceStrings;

  return 0;
}
