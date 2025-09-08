/*****************************************************************************
 *
 *  Author:           2143 Class
 *  Email:            none
 *  Label:            Lecture 03
 *  Title:            Game of Life
 *  Course:           2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        Array based implementation of a stack data structure written in class
 *        by all of us.
 *
 *  Usage:
 *        None (ask me in class)
 *
 *  Files:
 *        main.cpp    - main driver
 *        gol.hpp     - game of life implementation
 *        colors.h    - file to allow console colors to printed
 *        helper.hpp  - example include for possible functions that don't
 *                      necessarily belong in game of life, but can be useful
 *                      for other projects as well.
 *****************************************************************************/

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