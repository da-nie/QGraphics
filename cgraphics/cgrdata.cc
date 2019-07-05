//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cgrdata.h"

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CGrData::CGrData(void)
{
 vector_CGrPoint.clear();
 Enable=false;
}
//----------------------------------------------------------------------------------------------------
//конструктор копий
//----------------------------------------------------------------------------------------------------
CGrData::CGrData(const CGrData& cGrDataPtr)
{
 Enable=cGrDataPtr.Enable;
 cGrLineStyle=cGrDataPtr.cGrLineStyle;
 cGrColor=cGrDataPtr.cGrColor;
 SetName(cGrDataPtr.Name);
 //копируем массивы
 vector_CGrPoint=cGrDataPtr.vector_CGrPoint;
}

//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CGrData::~CGrData()
{  
 DeletePoints();	
}
//****************************************************************************************************
//операторы
//****************************************************************************************************

//операция присваивания
CGrData& CGrData::operator=(const CGrData& cGrDataPtr)
{
 if (this==&cGrDataPtr) return (*this);//проверка на присваивание себе
 Enable=cGrDataPtr.Enable;
 cGrLineStyle=cGrDataPtr.cGrLineStyle;
 cGrColor=cGrDataPtr.cGrColor;
 SetName(cGrDataPtr.Name); 
 //копируем массивы
 vector_CGrPoint=cGrDataPtr.vector_CGrPoint;
 return(*this);
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//установить разрешения отображения
//----------------------------------------------------------------------------------------------------
void CGrData::SetEnable(bool enable)
{
 Enable=enable;
}
//----------------------------------------------------------------------------------------------------
//установить название графика
//----------------------------------------------------------------------------------------------------
void CGrData::SetName(const std::string &name)
{ 
 Name=name;	
}
//----------------------------------------------------------------------------------------------------
//установить цвет графика
//----------------------------------------------------------------------------------------------------
void CGrData::SetGrColor(const CGrColor &cGrColor_Set)
{
 cGrColor=cGrColor_Set;
}
//----------------------------------------------------------------------------------------------------
//установить стиль линий графика
//----------------------------------------------------------------------------------------------------
void CGrData::SetGrLineStyle(const CGrLineStyle &cGrLineStyle_Set)
{
 cGrLineStyle=cGrLineStyle_Set;
}
//----------------------------------------------------------------------------------------------------
//получить разрешение на отображение
//----------------------------------------------------------------------------------------------------
bool CGrData::GetEnable(void) const
{
 return(Enable);
}
//----------------------------------------------------------------------------------------------------
//получить название графика
//----------------------------------------------------------------------------------------------------
void CGrData::GetName(std::string &name) const
{
 name=Name;	
}
//----------------------------------------------------------------------------------------------------
//получить цвет графика
//----------------------------------------------------------------------------------------------------
void CGrData::GetGrColor(CGrColor &cGrColor_Get) const
{
 cGrColor_Get=cGrColor;	
}
//----------------------------------------------------------------------------------------------------
//получить стиль линий графика
//----------------------------------------------------------------------------------------------------
void CGrData::GetGrLineStyle(CGrLineStyle &cGrLineStyle_Get) const
{
 cGrLineStyle_Get=cGrLineStyle;
}
//----------------------------------------------------------------------------------------------------
//получить количество исходных точек графика
//----------------------------------------------------------------------------------------------------
size_t CGrData::GetPointAmount(void) const
{
 return(vector_CGrPoint.size());
}
//----------------------------------------------------------------------------------------------------
//удалить все исходные точки графика
//----------------------------------------------------------------------------------------------------
void CGrData::DeletePoints(void)
{
 vector_CGrPoint.clear();
}
//----------------------------------------------------------------------------------------------------
//получить X точки графика
//----------------------------------------------------------------------------------------------------
double CGrData::GetX(size_t index) const
{
 return(vector_CGrPoint[index].X);
}
//----------------------------------------------------------------------------------------------------
//получить Y точки графика
//----------------------------------------------------------------------------------------------------
double CGrData::GetY(size_t index) const
{	
 return(vector_CGrPoint[index].Y);
}
//----------------------------------------------------------------------------------------------------
//установить X точки графика
//----------------------------------------------------------------------------------------------------
void CGrData::SetX(size_t index,double value)
{
 vector_CGrPoint[index].X=value;
}
//----------------------------------------------------------------------------------------------------
//установить Y точки графика
//----------------------------------------------------------------------------------------------------
void CGrData::SetY(size_t index,double value)
{
 vector_CGrPoint[index].Y=value;
}
//----------------------------------------------------------------------------------------------------
//добавить точку в конец графика
//----------------------------------------------------------------------------------------------------
void CGrData::AddPoint(double x,double y)
{
 vector_CGrPoint.push_back(CGrPoint(x,y));
}
//----------------------------------------------------------------------------------------------------
//получить ссылку на вектор данных графиков
//----------------------------------------------------------------------------------------------------
std::vector<CGrPoint>& CGrData::GetGrPointVector(void)
{
 return(vector_CGrPoint);
}