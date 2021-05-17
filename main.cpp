#include <iostream>
#include <fstream>
#include "Gauss2d.h"

using namespace std;

int main()
{
   Gauss2d gauss;
   gauss.test.test_n = 1;

   ofstream fout("result.txt");
   cout << gauss.FindExtremum({ -6, 5 }, 1e-15, 1e-15, fout) << endl;
   cout << gauss.curr[0] << " " << gauss.curr[1];

   fout.close();
}