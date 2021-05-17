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
      }
   }

   double q(const vector<double>& x) const
   {
      switch(test_n)
      {
         case 0: return 1 - x[0] - x[1];
      }
   }

   double h(const vector<double>& x) const
   {
      switch(test_n)
      {
         case 0: return x[0] + x[1] - 2;
      }
   }
};