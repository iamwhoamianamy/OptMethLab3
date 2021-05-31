#include <iostream>
#include <fstream>
#include "Gauss.h"
#include "PenaltyMethodData.h"
#include "PenaltyMethod.h"
#include "BarrierMethodData.h"
#include "BarrierMethod.h"
#include "Test.h"

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

   int rg_num = 6;
   vector<double> x0 = { -5, 2 };

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(7) << "rg_num";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f";
   fout << setw(14) << "df" << endl;

   for(double i = 1; i < 10; i+=0.5)
   {
      double r0 = i;
      fout << "----------------------------------------------------------";
      fout << "-------------------------------------------------" << endl;

      double f_eps = pow(10, -9);
      for(int funct_n = 0; funct_n < 4; funct_n++)
      {
         penalty_method.barrier_method_data.funct_n = funct_n;
         vector<double> x = penalty_method.FindExtremum(x0, r0, rg_num, 0, f_eps);

         // Блок вывода
         fout << setw(5) << penalty_method.barrier_method_data.funct_n << setw(6) << r0 << setw(7) << rg_num;
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

   int rh_num = 4;
   vector<double> x0 = { -5, 2 };

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(7) << "rh_num";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f";
   fout << setw(14) << "df" << endl;

   for(int i = 140; i < 260; i += 10)
   {
      double r0 = i;
      fout << "----------------------------------------------------------";
      fout << "-------------------------------------------------" << endl;

      double f_eps = pow(10, -9);
      for(int funct_n = 0; funct_n < 3; funct_n++)
      {
         penalty_method.barrier_method_data.funct_n = funct_n;
         vector<double> x = penalty_method.FindExtremum(x0, r0, 0, rh_num, f_eps);

         // Блок вывода
         fout << setw(5) << penalty_method.barrier_method_data.funct_n << setw(6) << r0 << setw(7) << rh_num;
         fout << setw(6) << x0[0] << setw(6) << x0[1];
         fout << setw(8) << f_eps << setw(12) << penalty_method.iterations_count;
         fout << setw(14) << penalty_method.f_calc_cout;
         fout << setw(10) << x[0] << setw(10) << x[1] << setw(10) << penalty_method_data.test.f(x) << scientific;
         fout << setw(14) << abs(penalty_method_data.test.f(x) - penalty_method_data.test.f_min2) << defaultfloat << endl;
      }
   }

   fout.close();
}

void BarrierGTest(const string& file_name)
{
   // Объект для хранения тестовых функций
   Test test = Test(0);

   // Объект с данными для метода барьерных функций
   BarrierMethodData barrier_method_data = BarrierMethodData(test);

   // Объект метода штрафных функций
   BarrierMethod penalty_method = BarrierMethod(barrier_method_data);

   // Поток вывода
   ofstream fout(file_name);

   int rg_num = 3;
   vector<double> x0 = { -0.5, 0.2 };

   fout << setw(5) << "funct" << setw(6) << "r0" << setw(7) << "rg_num";
   fout << setw(6) << "x0x" << setw(6) << "x0y";
   fout << setw(8) << "eps" << setw(12) << "iterations" << setw(14) << "f_calc_count";
   fout << setw(10) << "x" << setw(10) << "y" << setw(10) << "f";
   fout << setw(14) << "df" << endl;

   fout << setprecision(4);

   for(double i = 0.1; i < 5; i += 0.25)
   {
      double r0 = i;
      fout << "----------------------------------------------------------";
      fout << "-------------------------------------------------" << endl;

      double f_eps = pow(10, -9);
      for(int funct_n = 0; funct_n < 2; funct_n++)
      {
         penalty_method.barrier_method_data.funct_n = funct_n;
         vector<double> x = penalty_method.FindExtremum(x0, r0, rg_num, f_eps);

         // Блок вывода
         fout << setw(5) << penalty_method.barrier_method_data.funct_n << setw(6) << r0 << setw(7) << rg_num;
         fout << setw(6) << x0[0] << setw(6) << x0[1];
         fout << setw(8) << f_eps << setw(12) << penalty_method.iterations_count;
         fout << setw(14) << penalty_method.f_calc_cout;
         fout << setw(10) << x[0] << setw(10) << x[1] << setw(10) << barrier_method_data.test.f(x) << scientific;
         fout << setw(14) << abs(barrier_method_data.test.f(x) - barrier_method_data.test.f_min1) << defaultfloat << endl;
      }
   }

   fout.close();
}

int main()
{
   PenaltyGTest("results/penalty_g_test.txt");
   //PenaltyHTest("results/penalty_h_test.txt");
   //BarrierGTest("results/barrier_g_test.txt");
   cout << "Done!";
}