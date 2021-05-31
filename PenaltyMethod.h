#pragma once
#include <iomanip>
#include "PenaltyMethodData.h"

using namespace std;

class PenaltyMethod
{
public:
   PenaltyMethodData barrier_method_data;

   int max_iter_count = 100;  // Максимальное количество итераций
   int iterations_count = 0;
   int f_calc_cout = 0;

   double CalcNewR(const int& num, const double& r)
   {
      switch(num)
      {
         case 0: return 0.0;

         case 1: return r + 1.0;
         case 2: return r + 100;

         case 3: return r * 2;
         case 4: return r * 200;

         case 5: return r * r;
         case 6: return r * r * r;
      }
   }

   PenaltyMethod(const PenaltyMethodData& t_penalty_method_data):
      barrier_method_data(t_penalty_method_data) { }

   /// <summary>
   /// Поиск экстремума методом штрафных функций
   /// </summary>
   /// <param name="x0">- начальная точка</param>
   /// <param name="r0">- начальное значение коэффициента штрафа</param>
   /// <param name="rg_num">- номер функции для вычисления параметра штрафа для функции G</param>
   /// <param name="rh_num">- номер функции для вычисления параметра штрафа для функции H</param>
   /// <param name="f_eps">- точость по изменению функции</param>
   /// <returns>Точка с найденным экстремумом</returns>
   vector<double> FindExtremum(const vector<double>& x0,
                     const double& r0,
                     const int& rg_num,
                     const int& rh_num,
                     const double& f_eps)
   {
      barrier_method_data.rg = r0;
      barrier_method_data.rh = r0;

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
         barrier_method_data.rh = CalcNewR(rh_num, barrier_method_data.rh);

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