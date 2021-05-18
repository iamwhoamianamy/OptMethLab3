#include <vector>
#include <fstream>
#include "Gauss.h"

Gauss::Gauss(const size_t& t_size) : size(t_size)
{
   prev = vector<double>(t_size);
   curr = vector<double>(t_size);
}

int Gauss::FindExtremum(const Function& funct,
                 const vector<double>& x0,
                 const double& f_eps, const double& xs_eps)
{
   prev = x0;
   curr = x0;

   bool result_fit = false;
   int iter_count = 0;
   do
   {
      for(size_t i = 0; i < size; i++)
         curr[i] = FindMinArgGolden(funct, curr, i, 1e-15);

      iter_count++;
      // –асчет изменени€ решени€ на текущей итерации
      if(abs(funct.GetValue(prev) - funct.GetValue(curr)) < f_eps)
         result_fit = true;

      for(int i = 0; i < size && result_fit; i++)
         if(abs(prev[i] - curr[i]) > xs_eps)
            result_fit = false;

      prev = curr;
   } while(iter_count < max_iter_count && !result_fit);

   return iter_count;
}

pair<double, double> Gauss::FindSegmentWithMin(const Function& funct,
                                        vector<double> x,
                                        const int& comp_n)
{
   pair<double, double> result;
   double x0 = 0;
   double xk, xk1, xk_1, h = 1;

   x[comp_n] = x0;
   double f = funct.GetValue(x);
   f_calc_count += 1;

   x[comp_n] = x0 + delta;
   if(f == funct.GetValue(x))
   {
      result.first = x0;
      result.second = x0 + delta;
      f_calc_count = 2;

      return result;
   }
   else
   {
      x[comp_n] = x0 - delta;
      if(f == funct.GetValue(x))
      {
         result.first = x0 - delta;
         result.second = x0;
         f_calc_count = 3;

         return result;
      }
      else
      {
         x[comp_n] = x0 + delta;
         if(f > funct.GetValue(x))
         {
            xk = x0 + delta;
            h = delta;
            f_calc_count++;
         }
         else
         {
            x[comp_n] = x0 - delta;
            if(f > funct.GetValue(x))
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
            double f1 = funct.GetValue(x);

            x[comp_n] = xk1;
            double f2 = funct.GetValue(x);

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

double Gauss::FindMinArgGolden(const Function& funct,
                        vector<double> x,
                        const int& comp_n,
                        const double& eps)
{
   pair<double, double> segment = FindSegmentWithMin(funct, x, comp_n);
   double a = segment.first, b = segment.second;

   double x1 = a + (3 - SQRT5) / 2 * (b - a);
   double x2 = a + (SQRT5 - 1) / 2 * (b - a);

   x[comp_n] = x1;
   double f1 = funct.GetValue(x);
   f_calc_count += 1;

   x[comp_n] = x2;
   double f2 = funct.GetValue(x);
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
         f1 = funct.GetValue(x);
         f_calc_count += 1;
      }
      else
      {
         a = x1;
         x1 = x2;
         x2 = a + (SQRT5 - 1) / 2 * (b - a);
         f1 = f2;

         x[comp_n] = x2;
         f2 = funct.GetValue(x);
         f_calc_count += 1;
      }
   }

   return a;
}