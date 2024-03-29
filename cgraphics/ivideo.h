#ifndef I_VIDEO_H
#define I_VIDEO_H

//****************************************************************************************************
//интерфейсный класс видеодисплея
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include <stdint.h>

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

class CGrRect;

//****************************************************************************************************
//интерфейсный класс видеодисплея
//****************************************************************************************************
class IVideo
{
 public:	
  //-перечисления---------------------------------------------------------------------------------------
  //тип линий
  enum LINE_TYPE
  {
   LINE_TYPE_SOLID,//сплошная линия
   LINE_TYPE_DOT//прерывистая линия
  };	
 public:
  //-деструктор-----------------------------------------------------------------------------------------
  virtual ~IVideo() {}//деструктор
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  virtual void Init(void)=0;//инициализизация видеорежима
  virtual void GetScreenSize(uint32_t &width,uint32_t &height) const =0;//получить размеры экрана
  virtual void SetScreenSize(uint32_t width,uint32_t height)=0;//задать размеры экрана
  virtual void GetVideoPointer(void* &vptr) const =0;//получить указатель на видеобуфер
  virtual void GetLineSize(uint32_t &linesize) const =0;//получить размер строки в пикселях
  virtual void PutSymbol(int64_t x,int64_t y,char symbol,uint32_t color)=0;//вывод символа в позицию
  virtual void PutString(int64_t x,int64_t y,const char *string,uint32_t color)=0;//вывод строчки в позицию
  virtual void DrawPoint(int64_t x,int64_t y,uint32_t color)=0;//рисование точки
  virtual void DrawLine(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color,uint32_t thickness,LINE_TYPE line_type)=0;//рисование линии  
  virtual void GetStringImageSize(const char *string,uint32_t &width,uint32_t &height)=0;//получить размер строки в пикселях
  virtual void FillRectangle(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color)=0;//нарисовать закрашеный прямоугольник
  virtual void SetCursorCross(void)=0;//сделать курсор внутри области графика крестиком
  virtual void SetCursorMagnify(void)=0;//сделать курсор внутри области графика лупой
  virtual void ShowCursor(void)=0;//показать курсор
  virtual void HideCursor(void)=0;//скрыть курсор
  virtual void UnClipCursor(void)=0;//отпустить курсор
  virtual void ClipCursor(const CGrRect &cGrRect)=0;//запереть курсор в области
  virtual void SetCursorPos(int32_t x,int32_t y)=0;//установить координаты курсора
  virtual void SaveScreen(void)=0;//сохранить изображение в память
  virtual void RestoreScreen(void)=0;//восстановить изображение из памяти
  //-статические функции--------------------------------------------------------------------------------
  static IVideo* CreateNewCVideoSoftware(uint32_t width,uint32_t height);//создать класс программной растеризации
  static IVideo* CreateNewCVideoQt(uint32_t width,uint32_t height);//создать класс растеризации с помощью Qt
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
};

#endif
