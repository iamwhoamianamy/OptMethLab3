#include "Function.h"

using namespace std;

/// <summary>
/// ����� ��� ������ ���������� ������� ������������ ���������
/// ������� ������
/// </summary>
class Gauss
{
public:
   size_t size = 0;            // ����������� �������
   vector<double> prev;        // ����������� �� ������� ����
   vector<double> curr;        // ����� �����������,
   double delta = 10;

   int max_iter_count = 5000;  // ������������ ���������� ��������

   ///<param name = "t_size">- ����������� ������� �������</param>
   Gauss(const size_t& t_size);

   /// <summary>
   /// ����� ���������� ������� ������� ������
   /// </summary>
   /// <param name="funct">- ������ ������-���������� ������ Function � ����������� � �������</param>
   /// <param name="x0">- ������ ���������� �����������</param>
   /// <param name="f_eps">- ������� �� ��������� �������</param>
   /// <param name="xs_eps">- �������� �� �����������</param>
   /// <param name="fout">- ����� ������</param>
   /// <returns>���������� ��������</returns>
   int FindExtremum(const Function& funct,
                    const vector<double>& x0,
                    const double& f_eps, const double& xs_eps);

   const double SQRT5 = sqrt(5);
   const double PI = 3.141592653589793238462;
   int f_calc_count = 0;            // ���������� ���������� �������

   /// <summary>
   /// ����� ������� � ��������� ������� ��� ������ ������
   /// </summary>
   /// <param name="funct">- ������ ������-���������� ������ Function � ����������� � �������</param>
   /// <param name="x">- ������ ���������</param>
   /// <param name="comp_n">- ����� ����������</param>
   /// <returns>���� ����� - ������� � ��������� �������</returns>
   pair<double, double> FindSegmentWithMin(const Function& funct,
                                           vector<double> x,
                                           const int& comp_n);

   /// <summary>
   /// ����� ��������� �������� ������� ��� ������ ������
   /// </summary>
   /// <param name="funct">- ������ ������-���������� ������ Function � ����������� � �������</param>
   /// <param name="x">- ������ ���������</param>
   /// <param name="comp_n">- ����� ����������</param>
   /// <param name="eps">- �������� ������</param>
   /// <returns>�������� �������� �������</returns>
   double FindMinArgGolden(const Function& funct,
                           vector<double> x,
                           const int& comp_n,
                           const double& eps);
};