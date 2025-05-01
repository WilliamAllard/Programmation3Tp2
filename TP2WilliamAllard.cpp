#include <iostream>
#include "TP2.h"

int main()
{
   TP2 tp2;
   tp2.lireLabyrinthe("TestMaze.tp2");
   tp2.solution();
   tp2.afficherLiens();
   tp2.afficherSolution();
   tp2.ecrireSolution("Solution.tp2");
}
