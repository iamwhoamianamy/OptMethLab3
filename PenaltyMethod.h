#pragma once
#include <iomanip>
#include "PenaltyMethodData.h"

using namespace std;

class PenaltyMethod
{
public:
   PenaltyMethodData penalty_method_data;

   int max_iter_count = 100;  // ������������ ���������� ��������

   PenaltyMethod(const PenaltyMethodData& t_penalty_method_data):
      penalty_method_data(t_penalty_method_data) { }

   /// <summary>
   /// ����� ���������� ������� �������� �������
   /// </summary>
   /// <param name="x0">- ��������� �����</param>
   /// <param name="r0">- ��������� �������� ������������ ������</param>
   /// <param name="increment">- ��������� ������������ ������</param>
   /// <param name="f_eps">- ������� �� ��������� �������</param>
   /// <param name="fout">- ����� ��� ������</param>
   void FindExtremum(const vector<double>& x0,
                     const double& r0,
                     const double& increment,
                     const double& f_eps,
                     ofstream& fout)
   {
      int total_f_calc_cout = 0;
      penalty_method_data.rg = r0;

      // �������� ������� �� ���������� � ������� ���������
      double prev_f = penalty_method_data.test.f(x0);
      double curr_f;

      // ��������� �����
      vector<double> x(2);

      int iterations_count = 0;
      bool result_fit = false;
      do
      {
         Gauss gauss = Gauss(2);

         // ��������� ������������� ������
         penalty_method_data.rg += increment;
         penalty_method_data.rh = 0;

         // ����� ���������� ������� ������
         gauss.FindExtremum(penalty_method_data, x0, 1e-20, 1e-20);

         // ���������� �����
         x = gauss.curr;

         // ������� � ���� �����
         curr_f = penalty_method_data.test.f(gauss.curr);

         iterations_count++;
         total_f_calc_cout += gauss.f_calc_count;

         if(abs(prev_f - curr_f) < f_eps)
            result_fit = true;

         prev_f = curr_f;

      } while(!result_fit && iterations_count < max_iter_count);

      fout << setw(5) << penalty_method_data.funct_n  << setw(6) << r0 << setw(6) << increment;
      fout << setw(6) << x0[0]  << setw(6) << x0[1];
      fout << setw(8) << f_eps << setw(12) << iterations_count;
      fout << setw(14) << total_f_calc_cout;
      fout << setw(10) << x[0] << setw(10) << x[1] << setw(10) << curr_f << endl;
   }
};