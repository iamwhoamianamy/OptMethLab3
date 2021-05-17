#pragma once
#include <vector>
#include "Vector.h"
#include "GoldenRatio2d.h"
#include "Test.h"

class Gauss2d
{
public:
   int size = 2;               // Размерность вектора
   vector<double> prev;        // Приближение на текущем шаге
   vector<double> curr;        // Новое приближение

   GoldenRatio2d gr;           // Класс для поиска минимума по компонентам
   int max_iter_count = 1000;  // Максимальное количество итераций

   Test test;                  // Информация о тестовых функциях

   Gauss2d() : size(2)
   {
      prev = vector<double>(2);
      curr = vector<double>(2);
   }

   // Поиск экстремума методом Гаусса
   // из начального приближения х0
   // возвращает количество итераций
   int FindExtremum(const vector<double>& x0,
                    const double& f_eps, const double& xs_eps,
                    ofstream& fout)
   {
      /*fout << setw(3) << "k";
      fout << setw(14) << "x" << setw(14) << "y" << setw(14) << "f(x, y)";
      fout << setw(14) << "Sx" << setw(14) << "Sy" << setw(14) << "lambda";
      fout << setw(14) << "|xk - x(k-1)|" << setw(14) << "|yk - y(k-1)|" << setw(14) << "|fk - f(k-1)|";
      fout << setw(14) << "angle";
      fout << setw(14) << "H00" << setw(14) << "H01" << setw(14) << "H10" << setw(14) << "H11" << endl;*/

      prev = x0;
      curr = x0;

      bool result_fit = false;
      int iter_count = 0;
      do
      {
         double x = gr.FindMinArgGolden(test, curr, 0, 1e-15);
         curr[0] = x;
         double y = gr.FindMinArgGolden(test, curr, 1, 1e-15);
         curr[1] = y;
         
         //// Блок вывода
         //fout << fixed << setw(3) << iter_count + 1;
         //fout << scientific;
         //fout << setw(14) << xk1[0] << setw(14) << xk1[1] << setw(14) << funct(xk1);
         //fout << setw(14) << Sk[0] << setw(14) << Sk[1] << setw(14) << lambda;
         //fout << setw(14) << abs(xk1[0] - xk[0]) << setw(14) << abs(xk1[1] - xk[1]) << setw(14) << funct(xk1) - funct(xk);
         //fout << setw(14) << acos((xk1[0] * Sk[0] + xk1[1] * Sk[1]) / (Norm(xk1) * Norm(grad))) * 180 / PI;
         //fout << setw(14) << H[0][0] << setw(14) << H[0][1] << setw(14) << H[1][0] << setw(14) << H[1][1] << endl;

         iter_count++;
         // Расчет изменения решения на текущей итерации
         if(abs(test.f(prev) - test.f(curr)) < f_eps)
            result_fit = true;

         for(int i = 0; i < size && result_fit; i++)
            if(abs(prev[i] - curr[i]) > xs_eps)
               result_fit = false;

         prev = curr;
      } while(iter_count < max_iter_count && result_fit == false);

      fout << endl;
      return iter_count;
   }
};