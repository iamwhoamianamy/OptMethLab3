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

   double r0 = 0.0;
   double g_increment = 1.0;
   vector<double> x0 = { -5, 2 };

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(6) << "incr";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f";
   fout << setw(14) << "df" << endl;

   for(int i = 0; i < 6; i++)
   {
      fout << "----------------------------------------------------------";
      fout << "-------------------------------------------------" << endl;

      double f_eps = pow(10, -i);
      for(int funct_n = 0; funct_n < 4; funct_n++)
      {
         penalty_method.penalty_method_data.funct_n = funct_n;
         vector<double> x = penalty_method.FindExtremum(x0, r0, g_increment, 0, f_eps);

         // Блок вывода
         fout << setw(5) << penalty_method.penalty_method_data.funct_n << setw(6) << r0 << setw(6) << g_increment;
         fout << setw(6) << x0[0] << setw(6) << x0[1];
         fout << setw(8) << f_eps << setw(12) << penalty_method.iterations_count;
         fout << setw(14) << penalty_method.f_calc_cout;
         fout << setw(10) << x[0] << setw(10) << x[1] << setw(10) << penalty_method_data.test.f(x) << scientific;
         fout << setw(14) << abs(penalty_method_data.test.f(x) - penalty_method_data.test.f_min1) << defaultfloat << endl;
      }
   }

   fout.close();
}

void PenaltyHTest(const string& file_name)
{
   // Объект для хранения тестовых функций
   Test test = Test(0);

   // Объект с данными для метода штрафных функций
   PenaltyMethodData penalty_method_data = PenaltyMethodData(test);

   // Объект метода штрафных функций
   PenaltyMethod penalty_method = PenaltyMethod(penalty_method_data);

   // Поток вывода
   ofstream fout(file_name);

   double r0 = 0.0;
   double h_increment = 100.0;
   vector<double> x0 = { 0.1, 0.5 };

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(6) << "incr";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f";
   fout << setw(14) << "df" << endl;

   for(int i = 0; i < 6; i++)
   {
      fout << "----------------------------------------------------------";
      fout << "-------------------------------------------------" << endl;

      double f_eps = pow(10, -i);
      for(int funct_n = 0; funct_n < 3; funct_n++)
      {
         penalty_method.penalty_method_data.funct_n = funct_n;
         vector<double> x = penalty_method.FindExtremum(x0, r0, 0.0, h_increment, f_eps);

         // Блок вывода
         fout << setw(5) << penalty_method.penalty_method_data.funct_n << setw(6) << r0 << setw(6) << h_increment;
         fout << setw(6) << x0[0] << setw(6) << x0[1];
         fout << setw(8) << f_eps << setw(12) << penalty_method.iterations_count;
         fout << setw(14) << penalty_method.f_calc_cout;
         fout << setw(10) << x[0] << setw(10) << x[1] << setw(10) << penalty_method_data.test.f(x) << scientific;
         fout << setw(14) << abs(penalty_method_data.test.f(x) - penalty_method_data.test.f_min2) << defaultfloat << endl;
      }
   }

   fout.close();
}

int main()
{
   //PenaltyGTest("results/penalty_g_test.txt");
   PenaltyHTest("results/penalty_h_test.txt");
}