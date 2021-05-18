#include <iostream>
#include <fstream>
#include "Gauss.h"
#include "PenaltyMethodData.h"
#include "PenaltyMethod.h"

using namespace std;

void PenaltyGTest(const string& file_name)
{
   // Объект для хранения тестовых функций
   Test test = Test(0);

   // Объект с данными для метода штрафных функций
   PenaltyMethodData penalty_method_data = PenaltyMethodData(test);

   // Объект метода штрафных функций
   PenaltyMethod penalty_method = PenaltyMethod(penalty_method_data);

   // Поток вывода
   ofstream fout(file_name);
   //fout << fixed;

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(6) << "incr";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f" << endl;

   for(int i = 0; i < 4; i++)
   {
      penalty_method.penalty_method_data.funct_n = i;
      penalty_method.FindExtremum({ -5, 2 }, 0.0, 1.0, 1e-4, fout);
   }

   fout.close();
}

int main()
{
   PenaltyGTest("results/penalty_g_test.txt");
}