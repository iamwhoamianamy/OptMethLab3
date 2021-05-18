#include "Function.h"

using namespace std;

/// <summary>
/// Класс для поиска экстремума функции многомерного параметра
/// методом Гаусса
/// </summary>
class Gauss
{
public:
   size_t size = 0;            // Размерность вектора
   vector<double> prev;        // Приближение на текущем шаге
   vector<double> curr;        // Новое приближение,
   double delta = 10;

   int max_iter_count = 5000;  // Максимальное количество итераций

   ///<param name = "t_size">- размерность вектора функции</param>
   Gauss(const size_t& t_size);

   /// <summary>
   /// Поиск экстремума функции методом Гаусса
   /// </summary>
   /// <param name="funct">- объект класса-наследника класса Function с информацией о функции</param>
   /// <param name="x0">- вектор начального приближения</param>
   /// <param name="f_eps">- точость по изменению функции</param>
   /// <param name="xs_eps">- точность по компонентам</param>
   /// <param name="fout">- поток вывода</param>
   /// <returns>Количество итераций</returns>
   int FindExtremum(const Function& funct,
                    const vector<double>& x0,
                    const double& f_eps, const double& xs_eps);

   const double SQRT5 = sqrt(5);
   const double PI = 3.141592653589793238462;
   int f_calc_count = 0;            // Количество вычислений функции

   /// <summary>
   /// Поиск отрезка с минимумом функции для метода Гаусса
   /// </summary>
   /// <param name="funct">- объект класса-наследника класса Function с информацией о функции</param>
   /// <param name="x">- вектор компонент</param>
   /// <param name="comp_n">- номер компоненты</param>
   /// <returns>Пара чисел - отрезок с минимумом функции</returns>
   pair<double, double> FindSegmentWithMin(const Function& funct,
                                           vector<double> x,
                                           const int& comp_n);

   /// <summary>
   /// Поиск аргумента минимума функции для метода Гаусса
   /// </summary>
   /// <param name="funct">- объект класса-наследника класса Function с информацией о функции</param>
   /// <param name="x">- вектор компонент</param>
   /// <param name="comp_n">- номер компоненты</param>
   /// <param name="eps">- точность поиска</param>
   /// <returns>Аргумент минимума функции</returns>
   double FindMinArgGolden(const Function& funct,
                           vector<double> x,
                           const int& comp_n,
                           const double& eps);
};