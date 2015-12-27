#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>

struct Ingredient
{
  std::string name;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
};
using std::vector;
using std::pair;
using std::min;
using std::max;
using recipie = vector<pair<struct Ingredient,int>>;

bool
validRecipie(const recipie &r)
{
  int total = 0, totalCalories = 0;
  for(auto &e:r){
    total += e.second;
    totalCalories += e.first.calories*e.second;
  }
  return (total == 100) && (totalCalories == 500);
}

int
evaluate(const recipie &r)
{
  if(!validRecipie(r)) return 0;
  int capacity = 0;
  int durability = 0;
  int flavor = 0;
  int texture = 0;
  int calories = 0;
  for(auto &e:r){
    const auto &i = e.first;
    const auto &amt = e.second;
    capacity += amt*i.capacity;
    durability += amt*i.durability;
    flavor += amt*i.flavor;
    texture += amt*i.texture;
    calories += amt*i.calories;
  }
  int sc = max(0,capacity)
    * max(0,durability)
    * max(0,flavor)
    * max(0,texture);
  return sc;
}

int
calculateBestRecipie(vector<struct Ingredient> is,int part,recipie &r)
{
  if(part == is.size()) return evaluate(r);
  int bestScore = 0;
  r[part] = std::make_tuple(is[part],0);
  for(int i=0;i<=100;i++){
    r[part].second = i;
    bestScore = max(bestScore,calculateBestRecipie(is, part+1, r));
  }
  return bestScore;
}

int
calculateBestRecipie(vector<struct Ingredient> is)
{
  recipie r(is.size());
  return calculateBestRecipie(is,0,r);
}

int
main(int argc, char const *argv[]) {

  std::fstream f;
  f.open(argv[1], std::fstream::in);

  std::regex numberPattern("(\\w+): capacity ([-]?\\d+), durability ([-]?\\d+), flavor ([-]?\\d+), texture ([-]?\\d+), calories ([-]?\\d+)");
  enum Pat{Name=1,Capacity=2,Durability=3,Flavour=4,Texture=5,Calories=6};

  const auto input = std::string((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());

  auto itt = std::sregex_iterator(input.begin(), input.end(), numberPattern);
  auto ittend = std::sregex_iterator();

  vector<struct Ingredient> ingredients;

  for(std::sregex_iterator i = itt; i != ittend; ++i)
  {
    std::smatch m = *i;
    std::string name = m[Pat::Name].str();
    int capacity = std::stoi(m[Pat::Capacity].str());
    int durability = std::stoi(m[Pat::Durability].str());
    int flavor = std::stoi(m[Pat::Flavour].str());
    int texture = std::stoi(m[Pat::Texture].str());
    int calories = std::stoi(m[Pat::Calories].str());
    ingredients.push_back({name,capacity,durability,flavor,texture,calories});
  }

  int bestRecipie = calculateBestRecipie(ingredients);

  std::cout << "Best score: " << bestRecipie << std::endl;
  return 0;
}
