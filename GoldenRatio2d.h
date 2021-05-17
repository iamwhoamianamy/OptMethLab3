#pragma once
#include <vector>
#include "Vector.h"
#include "Test.h"

using namespace std;

class GoldenRatio2d
{
public:

   const double SQRT5 = 2.2360679775;
   const double PI = 3.14159265359;
   int f_calc_count = 0;            // Количество вычислений функции

   GoldenRatio2d() { }
   
   // Поиск отрезка с минимумом функции из объекта test
   // по компоненте comp_n
   // с шагом delta
   pair<double, double> FindSegmentWithMin(const Test& test,
                                           vector<double> x,
                                           const int& comp_n,
                                           const double& delta)
   {
      pair<double, double> result;
      double x0 = 0;
      double xk, xk1, xk_1, h = 1;

      x[comp_n] = x0;
      double f = test.f(x);
      f_calc_count += 1;

      x[comp_n] = x0 + delta;
      if(f == test.f(x))
      {
         result.first = x0;
         result.second = x0 + delta;
         f_calc_count = 2;

         return result;
      }
      else
      {
         x[comp_n] = x0 - delta;
         if(f == test.f(x))
         {
            result.first = x0 - delta;
            result.second = x0;
            f_calc_count = 3;

            return result;
         }
         else
         {
            x[comp_n] = x0 + delta;
            if(f > test.f(x))
            {
               xk = x0 + delta;
               h = delta;
               f_calc_count++;
            }
            else
            {
               x[comp_n] = x0 - delta;
               if(f > test.f(x))
               {
                  xk = x0 - delta;
                  h = -delta;
                  f_calc_count += 2;
               }
               else
               {
                  result.first = x0 - delta;
                  result.second = x0 + delta;
                  f_calc_count += 2;

                  return result;
               }
            }

            xk_1 = x0;

            bool exit = false;
            do
            {
               h *= 2;
               xk1 = xk + h;

               x[comp_n] = xk;
               double f1 = test.f(x);

               x[comp_n] = xk1;
               double f2 = test.f(x);

               if(f1 > f2)
               {
                  xk_1 = xk;
                  xk = xk1;
               }
               else
                  exit = true;

               f_calc_count += 2;
            } while(!exit);

            result.first = xk_1;
            result.second = xk;
         }
      }
      return result;
   }

   // Поиск аргумента минимума функции funct
   // по компоненте с номером comp_n
   // методом золотого сечения с точностью eps
   double FindMinArgGolden(const Test& test,
                           vector<double> x,
                           const int& comp_n,
                           const double& eps)
   {
      pair<double, double> segment = FindSegmentWithMin(test, x, comp_n, 1);
      double a = segment.first, b = segment.second;

      double x1 = a + (3 - SQRT5) / 2 * (b - a);
      double x2 = a + (SQRT5 - 1) / 2 * (b - a);

      x[comp_n] = x1;
      double f1 = test.f(x);
      f_calc_count += 1;

      x[comp_n] = x2;
      double f2 = test.f(x);
      f_calc_count += 1;

      double a1, b1;

      int iter_count = 0;
      for(; abs(b - a) > eps; iter_count++)
      {
         a1 = a, b1 = b;
         if(f1 < f2)
         {
            b = x2;
            x2 = x1;
            x1 = a + (3 - SQRT5) / 2 * (b - a);
            f2 = f1;

            x[comp_n] = x1;
            f1 = test.f(x);
            f_calc_count += 1;
         }
         else
         {
            a = x1;
            x1 = x2;
            x2 = a + (SQRT5 - 1) / 2 * (b - a);
            f1 = f2;

            x[comp_n] = x2;
            f2 = test.f(x);
            f_calc_count += 1;
         }
      }

      return a;
   }
};