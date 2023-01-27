#include <iostream>
#include "gol.hpp"
#include <unistd.h>

using namespace std;

int main()
{

  GOL G(20, 20);
  // G.addGlider()
  system("clear");

  G.rando();
  G.Run(100);
}