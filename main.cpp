#include <iostream>
#include <fstream>
#include "Gauss.h"
#include "PenaltyMethod.h"

using namespace std;

void PenaltyGTest()
{
   // Объект для хранения тестовых функций
   Test test = Test(0);

   // Объект метода штрафныхф функций
   PenaltyMethod penalty_method = PenaltyMethod(test);

   // Поток вывода
   ofstream fout("result.txt");
   cout << scientific;

   for(int i = 0; i < 4; i++)
   {
      // Изменение штрафной функции
      penalty_method.funct_n = i;

      cout << "----------Penalty function " << i << "----------" << endl;

      for(int j = 0; j < 100; j++)
      {
         // Объект метода Гаусса
         Gauss gauss = Gauss(2);

         // Изменение коэффициентов щтрафа
         penalty_method.rg = j;
         penalty_method.rh = 0;

         cout << "-----Penalty factor " << j << "-----" << endl;

         cout << "iterations: " << gauss.FindExtremum(penalty_method, { 2, -5 }, 1e-20, 1e-20, fout) << endl;

         cout << "x: " << abs(gauss.curr[0] - test.x_min1) << endl;
         cout << "y: " << abs(gauss.curr[1] - test.y_min1) << endl;
         cout << "f: " << abs(test.f(gauss.curr) - test.f_min1) << endl;

         //cout << "x: " << gauss.curr[0] << endl;
         //cout << "y: " << gauss.curr[1] << endl;
         //cout << "f: " << test.f(gauss.curr) << endl;

         cout << "f_calc_count: " << gauss.f_calc_count << endl << endl;
         gauss.max_iter_count = 0;
      }

   }
   fout.close();
}

int main()
{
   PenaltyGTest();
}