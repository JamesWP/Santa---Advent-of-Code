#include <iostream>
#include <fstream>

int
min(int a,int b)
{
  return (a<b)? a:b;
}

int
main(int argc,char *argv[])
{
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int l,w,h;
  int sa,sl;
  int bow,ribbon;
  int totalPaper = 0, totalRibbon = 0;
  do{
    f >> l;
    f.ignore(1,'x');
    f >> w;
    f.ignore(1,'x');
    f >> h;
    f.ignore(1,'\n');

    if(f.eof()) break;

    sa = 2*l*w + 2*w*h + 2*h*l;
    sl = min(l*w,min(w*h,l*h));
    bow = l*w*h;
    ribbon = min(l*2+w*2,min(w*2+h*2,h*2+l*2));

    //std::cout << l << "x" << w << "x" << h;
    //std::cout << " wp[" << sa << "," << sl << "]=" << sa+sl;
    //std::cout << " r[" << bow << "," << ribbon << "]=" << bow+ribbon <<  std::endl;

    totalPaper += sa + sl;
    totalRibbon += ribbon + bow;
  }while(!f.eof());

  std::cout << "Total Wrapping paper: " << totalPaper << std::endl;
  std::cout << "Total Ribbon : " << totalRibbon << std::endl;

  return 0;
}
