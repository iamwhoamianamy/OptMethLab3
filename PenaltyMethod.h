#pragma once
#include <iomanip>
#include "PenaltyMethodData.h"

using namespace std;

class PenaltyMethod
{
public:
   PenaltyMethodData penalty_method_data;

   int max_iter_count = 100;  // Максимальное количество итераций
   int iterations_count = 0;
   int f_calc_cout = 0;

   PenaltyMethod(const PenaltyMethodData& t_penalty_method_data):
      penalty_method_data(t_penalty_method_data) { }

   /// <summary>
   /// Поиск экстремума методом штрафных функций
   /// </summary>
   /// <param name="x0">- начальная точка</param>
   /// <param name="r0">- начальное значение коэффициента штрафа</param>
   /// <param name="g_increment">- инкремент коэффициента штрафа для функции G</param>
   /// <param name="h_increment">- инкремент коэффициента штрафа для функции H</param>
   /// <param name="f_eps">- точость по изменению функции</param>
   /// <returns>Точка с найденным экстремумом</returns>
   vector<double> FindExtremum(const vector<double>& x0,
                     const double& r0,
                     const double& g_increment,
                     const double& h_increment,
                     const double& f_eps)
   {
      penalty_method_data.rg = r0;
      penalty_method_data.rh = r0;

      // Значения функции на предыдущей и текущей итерациях
      double prev_f = penalty_method_data.test.f(x0);
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
         penalty_method_data.rg += g_increment;
         penalty_method_data.rh += h_increment;

         // Поиск экстремума методом Гаусса
         gauss.FindExtremum(penalty_method_data, x0, 1e-20, 1e-20);

         // Полученная точка
         x = gauss.curr;

         // Функция в этой точке
         curr_f = penalty_method_data.test.f(gauss.curr);

         iterations_count++;
         f_calc_cout += gauss.f_calc_count;

         if(abs(prev_f - curr_f) < f_eps)
            result_fit = true;

         prev_f = curr_f;

      } while(!result_fit && iterations_count < max_iter_count);
      
      return x;
   }
};