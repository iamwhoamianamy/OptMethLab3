#pragma once
#include <iomanip>
#include "PenaltyMethodData.h"

using namespace std;

class PenaltyMethod
{
public:
   PenaltyMethodData penalty_method_data;

   int max_iter_count = 100;  // ������������ ���������� ��������
   int iterations_count = 0;
   int f_calc_cout = 0;

   PenaltyMethod(const PenaltyMethodData& t_penalty_method_data):
      penalty_method_data(t_penalty_method_data) { }

   /// <summary>
   /// ����� ���������� ������� �������� �������
   /// </summary>
   /// <param name="x0">- ��������� �����</param>
   /// <param name="r0">- ��������� �������� ������������ ������</param>
   /// <param name="g_increment">- ��������� ������������ ������ ��� ������� G</param>
   /// <param name="h_increment">- ��������� ������������ ������ ��� ������� H</param>
   /// <param name="f_eps">- ������� �� ��������� �������</param>
   /// <returns>����� � ��������� �����������</returns>
   vector<double> FindExtremum(const vector<double>& x0,
                     const double& r0,
                     const double& g_increment,
                     const double& h_increment,
                     const double& f_eps)
   {
      penalty_method_data.rg = r0;
      penalty_method_data.rh = r0;

      // �������� ������� �� ���������� � ������� ���������
      double prev_f = penalty_method_data.test.f(x0);
      double curr_f;

      // ��������� �����
      vector<double> x(2);

      f_calc_cout = 0;
      iterations_count = 0;

      bool result_fit = false;
      do
      {
         Gauss gauss = Gauss(2);

         // ��������� ������������� ������
         penalty_method_data.rg += g_increment;
         penalty_method_data.rh += h_increment;

         // ����� ���������� ������� ������
         gauss.FindExtremum(penalty_method_data, x0, 1e-20, 1e-20);

         // ���������� �����
         x = gauss.curr;

         // ������� � ���� �����
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