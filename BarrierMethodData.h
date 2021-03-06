#pragma once
#include<vector>
#include "Test.h"
#include "Function.h"

using namespace std;

class BarrierMethodData : public Function
{
public:
   Test test;
   int funct_n = 0;

   double rg = 0;

   BarrierMethodData(const Test& t_test, int t_funct_n) :
      test(t_test), funct_n(t_funct_n) { }

   BarrierMethodData(const Test& t_test) : test(t_test) { }

   double G(const vector<double>& x) const
   {
      switch(funct_n)
      {
         case 0: return - 1.0 / test.g(x);
         case 1: return -1.0 * log(-1.0 * test.g(x));
         default: return 0;
      }
   }

   double GetValue(const vector<double>& x) const override
   {
      return test.f(x) + rg * G(x);
   }
};