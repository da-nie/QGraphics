#ifndef C_CUBIC_SPLINE_H
#define C_CUBIC_SPLINE_H

//****************************************************************************************************
//класс интерполяции кубическим сплайном
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include "iinterpolater.h"

//****************************************************************************************************
//класс интерполяции кубическим сплайном
//****************************************************************************************************

class CCubicSpline:public IInterpolater
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
 private:
  //-переменные-----------------------------------------------------------------------------------------
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CCubicSpline(void);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CCubicSpline();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  bool Execute(const std::vector<CGrPoint> &input,std::vector<CGrPoint> &output,long double step);//выполнить интерполяцию
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
};
#endif
