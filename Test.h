#pragma once
#include <vector>

using namespace std;

// Класс с информацией о тестовых функциях и коэффициентах r
class Test
{
public:
   int test_n;

   Test() : test_n(0) {}

   Test(int t_test_n) : test_n(t_test_n) {}

   double f(const vector<double>& x) const
   {
      switch(test_n)
      {
         case 0: return 10 * (x[1] - x[0]) * (x[1] - x[0]) + x[1] * x[1];
         case 1: return (x[0] - 1) * (x[0] - 1) + (x[1] - 3) * (x[1] - 3);
         case 2: return x[0] * x[0] + x[1] * x[1];
         case 3: return 5 * (x[1] + x[0]) * (x[1] + x[0]) + (x[0] - 2) * (x[0] - 2);
      }
   }

   double h(const vector<double>& x) const
   {
      return x[0] + x[1] - 2;
   }

   double g(const vector<double>& x) const
   {
      return 1 - x[0] - x[1];
   }

   // Точные значения минимума задач и точек
   // в которых эти значения достигаются
   double f_min1 = 0.25;
   double x_min1 = 0.5;
   double y_min1 = 0.5;

   double f_min2 = 1;
   double x_min2 = 1;
   double y_min2 = 1;
};