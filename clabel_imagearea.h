#ifndef C_LABEL_IMAGE_AREA_H
#define C_LABEL_IMAGE_AREA_H

//****************************************************************************************************
//класс отображения графиков
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <QtWidgets>
#include <vector>

#include "cgraphics/igraphics.h"
#include "cgraphics/ivideo.h"
#include "interpolation/iinterpolater.h"

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

//****************************************************************************************************
//класс отображения графиков
//****************************************************************************************************
class CLabel_ImageArea:public QLabel
{
 Q_OBJECT
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
 private:
  //-константы------------------------------------------------------------------------------------------
  static const uint32_t TIMER_INTERVAL_MS=50;//интервал срабатывания таймера, мс
 private:
  //-переменные-----------------------------------------------------------------------------------------
  IVideo *iVideo_Ptr;//указатель на класс рисования
  IGraphics *iGraphics_Ptr;//указатель на класс рисования графиков
  int32_t TimerId;//идентификатор таймера
  QImage qImage_Graphics;//изображение графика

  bool MouseLButton;//состояние левой кнопки мышки
  bool MouseRButton;//состояние правой кнопки мышки
  bool MouseCButton;//состояние центральной кнопки мышки

  CGrData *cGrData_Based_Ptr;//указатель на данные графика исходной функции
  CGrData *cGrData_Interpolated_Ptr;//указатель на данные графика интерполированной функции
 public:
  //-конструктор----------------------------------------------------------------------------------------
  explicit CLabel_ImageArea(IVideo *iVideo_Ptr_Set,IGraphics *iGraphics_Ptr_Set,QWidget *parent=NULL);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CLabel_ImageArea();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  bool UpdateGraphics(IInterpolater *iInterpolater_Ptr,const std::vector<CGrPoint> &new_point,std::string name,long double step);//обновить графики
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
  void timerEvent(QTimerEvent *qTimerEvent_Ptr);//обработчик таймера
  void mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик перемещения мышки
  void mousePressEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик нажатия на кнопку мышки
  void mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик отпускания кнопки мышки
  void paintEvent(QPaintEvent *qPaintEvent_Ptr);//обработчик события перерисовки
  void Redraw(void);//перерисовать экран
  //-слоты----------------------------------------------------------------------------------------------
 public slots:
};

#endif