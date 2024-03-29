#ifndef I_INTERPOLATER_H
#define I_INTERPOLATER_H

//****************************************************************************************************
//интерфейсный класс интерполяции
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include <stdint.h>
#include <vector>
#include "./cgraphics/cgrpoint.h"

//****************************************************************************************************
//интерфейсный класс интерполяции
//****************************************************************************************************
class IInterpolater
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
 private:
  //-переменные-----------------------------------------------------------------------------------------
 public:
  //-конструктор----------------------------------------------------------------------------------------
  //-деструктор-----------------------------------------------------------------------------------------
  virtual ~IInterpolater() {}
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  virtual bool Execute(const std::vector<CGrPoint> &input,std::vector<CGrPoint> &output,long double step)=0;//выполнить интерполяцию
  //-статические функции--------------------------------------------------------------------------------
  static IInterpolater* CreateNewCubicSpline(void);//создать новый класс интерполяции кубическим сплайном
  static IInterpolater* CreateNewQuadricSpline(void);//создать новый класс интерполяции квадратичным сплайном
  static IInterpolater* CreateNewLinear(void);//создать новый класс интерполяции кусочно-линейной функцией
  static IInterpolater* CreateNewQuadric(void);//создать новый класс интерполяции кусочно-квадратичной функцией
};
#endif
