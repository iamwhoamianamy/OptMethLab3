#pragma once
#include <iomanip>
#include "BarrierMethodData.h"

using namespace std;

class BarrierMethod
{
public:
   BarrierMethodData barrier_method_data;

   int max_iter_count = 100;  // Максимальное количество итераций
   int iterations_count = 0;
   int f_calc_cout = 0;

   double CalcNewR(const int& num, const double& rg)
   {
      switch(num)
      {
         case 0: return 0.0;

         case 1: return rg - 0.01;

         case 2: return rg / 2;
         case 3: return rg / 10;

         case 4: return pow(rg, 0.5);
         case 5: return pow(rg, 0.25);
      }
   }

   BarrierMethod(const BarrierMethodData& t_barrier_method_data) :
      barrier_method_data(t_barrier_method_data) { }

   /// <summary>
   /// Поиск экстремума методом барьерных функций
   /// </summary>
   /// <param name="x0">- начальная точка</param>
   /// <param name="r0">- начальное значение коэффициента штрафа</param>
   /// <param name="rg_num">- номер функции для вычисления параметра штрафа для функции G</param>
   /// <param name="f_eps">- точость по изменению функции</param>
   /// <returns>Точка с найденным экстремумом</returns>
   vector<double> FindExtremum(const vector<double>& x0,
                               const double& r0,
                               const int& rg_num,
                               const double& f_eps)
   {
      barrier_method_data.rg = r0;

      // Значения функции на предыдущей и текущей итерациях
      double prev_f = barrier_method_data.test.f(x0);
      double curr_f;

      // Найденная точка
      vector<double> x(2);

      f_calc_cout = 0;
      iterations_count = 0;

      bool result_fit = false;
      do
      {
         Gauss gauss = Gauss(2);

         // Изменение коэффициентов штрафа
         barrier_method_data.rg = CalcNewR(rg_num, barrier_method_data.rg);

         // Поиск экстремума методом Гаусса
         gauss.FindExtremum(barrier_method_data, x0, 1e-20, 1e-20);

         // Полученная точка
         x = gauss.curr;

         // Функция в этой точке
         curr_f = barrier_method_data.test.f(gauss.curr);

         iterations_count++;
         f_calc_cout += gauss.f_calc_count;

         if(abs(prev_f - curr_f) < f_eps)
            result_fit = true;

         prev_f = curr_f;

      } while(!result_fit && iterations_count < max_iter_count);

      return x;
   }
};