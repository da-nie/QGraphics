//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "clabel_imagearea.h"
#include <stdint.h>


//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CLabel_ImageArea::CLabel_ImageArea(IVideo *iVideo_Ptr_Set,IGraphics *iGraphics_Ptr_Set,QWidget *parent):QLabel(parent)
{
 iVideo_Ptr=iVideo_Ptr_Set;
 iGraphics_Ptr=iGraphics_Ptr_Set;
 //создадим область графика
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 //зададим размеры окна
 setGeometry(0,0,width,height);
 setMaximumSize(width,height);
 setMinimumSize(width,height);

 qImage_Graphics=QImage(width,height,QImage::Format_RGBA8888);

 iGraphics_Ptr->SetName("Interpolation function");
 //потребуются два графика для исходных и для интерполированных значений, удалять их необязательно
 cGrData_Based_Ptr=iGraphics_Ptr->AddNewGraphic();
 cGrData_Based_Ptr->SetName("Source function");
 cGrData_Based_Ptr->SetGrColor(CGrColor(0,255,0));
 cGrData_Based_Ptr->SetEnable(true);
 cGrData_Based_Ptr->SetGrLineStyle(CGrLineStyle(IVideo::LINE_TYPE_SOLID,1,true,false));

 cGrData_Interpolated_Ptr=iGraphics_Ptr->AddNewGraphic();
 cGrData_Interpolated_Ptr->SetName("Interpolated function");
 cGrData_Interpolated_Ptr->SetGrColor(CGrColor(255,0,255));
 cGrData_Interpolated_Ptr->SetEnable(true);

 //настраиваем исходные состояния кнопок мышки
 MouseLButton=false;
 MouseRButton=false;
 MouseCButton=false;
 //подключим таймер обновления экрана
 TimerId=startTimer(TIMER_INTERVAL_MS);
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CLabel_ImageArea::~CLabel_ImageArea()
{
 killTimer(TimerId);
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//обработчик таймера
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::timerEvent(QTimerEvent *qTimerEvent_Ptr)
{
 //переводим координаты курсора в систему координат виджета
 QPoint qPoint=mapFromGlobal(cursor().pos());
 int32_t x=qPoint.x();
 int32_t y=qPoint.y();

 CGrMousePoint cGrMousePoint(x,y);

 iGraphics_Ptr->OnTimer(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
 update();
}

//----------------------------------------------------------------------------------------------------
//обработчик перемещения мышки
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y();

 CGrMousePoint cGrMousePoint(x,y);

 iGraphics_Ptr->OnMouseMove(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
}
//----------------------------------------------------------------------------------------------------
//обработчик нажатия на кнопку мышки
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::mousePressEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y();
 CGrMousePoint cGrMousePoint(x,y);

 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  if (MouseLButton==false)
  {
   MouseLButton=true;
   iGraphics_Ptr->OnLButtonDown(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
  }
 }
 if (qMouseEvent_Ptr->button()&Qt::RightButton)
 {
  if (MouseRButton==false)
  {
   MouseRButton=true;
   iGraphics_Ptr->OnRButtonDown(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
  }
 }
 if (qMouseEvent_Ptr->button()&Qt::MidButton)
 {
  if (MouseCButton==false)
  {
   MouseCButton=true;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//обработчик отпускания кнопки мышки
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y();
 CGrMousePoint cGrMousePoint(x,y);

 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  if (MouseLButton==true)
  {
   MouseLButton=false;
   iGraphics_Ptr->OnLButtonUp(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
  }
 }
 if (qMouseEvent_Ptr->button()&Qt::RightButton)
 {
  if (MouseRButton==true)
  {
   MouseRButton=false;
   iGraphics_Ptr->OnRButtonUp(cGrMousePoint,MouseLButton,MouseRButton,MouseCButton);
  }
 }
 if (qMouseEvent_Ptr->button()&Qt::MidButton)
 {
  if (MouseCButton==true)
  {
   MouseCButton=false;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//обработчик события перерисовки
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::paintEvent(QPaintEvent *qPaintEvent_Ptr)
{
 QLabel::paintEvent(qPaintEvent_Ptr);
 void *vptr;
 iVideo_Ptr->GetVideoPointer(vptr);
 if (vptr==NULL) return;
 Redraw();
 QPainter qPainter(this);
 //обеспечить совместимость интерфейсов проще всего так, чтобы классу CVideo_Software ничего не узнать про qt
 //возможное решение с шаблоном iVideo потребует шаблона у всех классов, использующих iVideo, что неудобно
 QPixmap *qPixmap_Ptr=reinterpret_cast<QPixmap*>(vptr);
 qPainter.drawPixmap(0,0,*qPixmap_Ptr);
}

//----------------------------------------------------------------------------------------------------
//перерисовать экран
//----------------------------------------------------------------------------------------------------
void CLabel_ImageArea::Redraw(void)
{
 iGraphics_Ptr->Redraw();
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//обновить графики
//----------------------------------------------------------------------------------------------------
bool CLabel_ImageArea::UpdateGraphics(IInterpolater *iInterpolater_Ptr,const std::vector<CGrPoint> &new_point,std::string name,long double step)
{
 if (iInterpolater_Ptr==NULL) return(false);
 cGrData_Based_Ptr->GetGrPointVector()=new_point;
 bool ret=true;
 if ((ret=iInterpolater_Ptr->Execute(cGrData_Based_Ptr->GetGrPointVector(),cGrData_Interpolated_Ptr->GetGrPointVector(),step))==false) cGrData_Interpolated_Ptr->SetName("Interpolation error");
                                                                                                                                  else cGrData_Interpolated_Ptr->SetName(name);
 //установим масштаб, чтобы все графики поместились в окне и отменим возможный режим выделения области
 CGrRect cGrRect;
 iGraphics_Ptr->FindViewRectangle(cGrRect);
 iGraphics_Ptr->SetOriginalScale(cGrRect);
 iGraphics_Ptr->CancelSelect();
 iGraphics_Ptr->OnOriginalScale();
 update();
 return(ret);
}
