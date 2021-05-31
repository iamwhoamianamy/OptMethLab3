#pragma once
#include<vector>
#include "Test.h"
#include "Function.h"

using namespace std;

class PenaltyMethodData : public Function
{
public:
   Test test;
   int funct_n = 0;

   double rg = 0;
   double rh = 0;

   PenaltyMethodData(const Test& t_test, int t_funct_n) :
      test(t_test), funct_n(t_funct_n) { }

   PenaltyMethodData(const Test& t_test) : test(t_test) { }

   double G(const vector<double>& x) const
   {
      if(test.g(x) <= 0)
         return 0;
      else
      {
         switch(funct_n)
         {
            case 0: return 0.5 * (test.g(x) + abs(test.g(x)));
            case 1: return pow(0.5 * (test.g(x) + abs(test.g(x))), 2);
            case 2: return pow(0.5 * (test.g(x) + abs(test.g(x))), 4);
            case 3: return 1.0 / test.g(x);
            default: return 0;
         }
      }
   }

   double H(const vector<double>& x) const
   {
      switch(funct_n)
      {
         case 0: return abs(test.h(x));
         case 1: return pow(test.h(x), 2);
         case 2: return pow(test.h(x), 4);
         default: return 0;
      }
   }

   double GetValue(const vector<double>& x) const override
   {
      return test.f(x) + rg * G(x) + rh * H(x);
   }
};