//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include <algorithm>

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
CMainWindow::CMainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::CMainWindow)
{
 ui->setupUi(this);
 setWindowTitle(tr("Построение графика интерполяции табличной функции"));
 //используем фабричный метод для создания класса построения графика
 iVideo_Ptr.reset(IVideo::CreateNewCVideoQt(AREA_WIDTH,AREA_HEIGHT));
 iGraphics_Ptr.reset(IGraphics::CreateNewCGraphics(iVideo_Ptr.get()));
 cLabel_ImageArea_Ptr=new CLabel_ImageArea(iVideo_Ptr.get(),iGraphics_Ptr.get(),ui->qLabel_Map);
 //добавим список вариантов интерполяции
 InterpolaterList.push_back(std::make_pair<IInterpolater*,std::string>(IInterpolater::CreateNewLinear(),"Кусочно-линейная"));
 InterpolaterList.push_back(std::make_pair<IInterpolater*,std::string>(IInterpolater::CreateNewQuadric(),"Кусочно-квадратичная"));
 InterpolaterList.push_back(std::make_pair<IInterpolater*,std::string>(IInterpolater::CreateNewQuadricSpline(),"Квадратичный сплайн"));
 InterpolaterList.push_back(std::make_pair<IInterpolater*,std::string>(IInterpolater::CreateNewCubicSpline(),"Кубический сплайн"));
 //добавим варианты интерполяции в выпадающий список
 size_t size=InterpolaterList.size();
 for(size_t n=0;n<size;n++) ui->qComboBox_Interpolation->addItem(tr(InterpolaterList[n].second.c_str()));
 ui->qComboBox_Interpolation->setCurrentIndex(0);
 //зададим текст в полях редактирования
 ui->qlineEdit_X->setText("0");
 ui->qlineEdit_Y->setText("0");
 ui->qlineEdit_Step->setText("0.1");
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CMainWindow::~CMainWindow()
{
 delete(ui);
 //так как список интерполяторов создан обычными указателями, его нужно удалить
 size_t size=InterpolaterList.size();
 for(size_t n=0;n<size;n++) delete(InterpolaterList[n].first);
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//отсортировать массив точек
//----------------------------------------------------------------------------------------------------
void CMainWindow::Sort(std::vector<CGrPoint> &input_points) const
{
 auto sort_function=[](const CGrPoint &cGrPoint_A,const CGrPoint &cGrPoint_B)->bool
 {
  if (cGrPoint_A.X<cGrPoint_B.X) return(true);
  return(false);
 };
 std::sort(input_points.begin(),input_points.end(),sort_function);
}
//----------------------------------------------------------------------------------------------------
//убрать одинаковые последовательные элементы из массива точек
//----------------------------------------------------------------------------------------------------
void CMainWindow::Unique(std::vector<CGrPoint> &input_points) const
{
 auto compare_function=[](const CGrPoint &cGrPoint_A,const CGrPoint &cGrPoint_B)->bool
 {
  if (cGrPoint_A.X==cGrPoint_B.X) return(true);
  return(false);
 };
 input_points.resize(std::unique(input_points.begin(),input_points.end(),compare_function)-input_points.begin());
}
//----------------------------------------------------------------------------------------------------
//выполнить интерполяцию
//----------------------------------------------------------------------------------------------------
bool CMainWindow::Interpolate(std::vector<CGrPoint> &input_points,IInterpolater *iInterpolater_Ptr,const std::string &name,long double step)
{
 return(cLabel_ImageArea_Ptr->UpdateGraphics(iInterpolater_Ptr,input_points,name,step));
}

//****************************************************************************************************
//слоты
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//событие нажатия на кнопку "Применить вариант интерполяции"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_qPushButton_ApplyInterpolation_clicked()
{
 //считаем шаг интерполяции
 QString qString_Step=ui->qlineEdit_Step->text();
 bool step_ok;
 long double step=qString_Step.toDouble(&step_ok);
 if (step_ok==false)
 {
  QMessageBox::warning(this,tr("Ошибка"),tr("Значение шага интерполяции не является числом!"));
  return;
 }

 //во входных данных могут быть одинаковые координаты X и отсутствие сортировки, поэтому сортируем входные данные и убираем одинаковые элементы
 Sort(InputPoints);
 Unique(InputPoints);
 //узнаем выбранный интерполятор
 size_t index=ui->qComboBox_Interpolation->currentIndex();
 size_t size=InterpolaterList.size();
 if (index>=size)
 {
  QMessageBox::warning(this,tr("Ошибка"),tr("Отсутствует интерполятор!"));
  return;
 }
 bool res=Interpolate(InputPoints,InterpolaterList[index].first,"Interpolated function",step);
 if (res==false)
 {
  QMessageBox::warning(this,tr("Ошибка"),tr("Интерполяция невозможна!"));
 }
}

//----------------------------------------------------------------------------------------------------
//событие нажатия на кнопку "Добавить точку в список"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_qPushButton_AddPoint_clicked()
{
 QString qString_X=ui->qlineEdit_X->text();
 QString qString_Y=ui->qlineEdit_Y->text();
 bool x_ok;
 bool y_ok;
 double x=qString_X.toDouble(&x_ok);
 double y=qString_Y.toDouble(&y_ok);
 if (x_ok==false)
 {
  QMessageBox::warning(this,tr("Ошибка"),tr("Значение координаты по X не является числом!"));
  return;
 }
 if (y_ok==false)
 {
  QMessageBox::warning(this,tr("Ошибка"),tr("Значение координаты по Y не является числом!"));
  return;
 }
 //добавляем в список точку
 ui->qListWidget_Points->addItem("("+qString_X+";"+qString_Y+")");
 //чтобы не связываться со списком, сохраним координаты в отдельном массиве
 InputPoints.push_back(CGrPoint(x,y));
}
//----------------------------------------------------------------------------------------------------
//событие нажатия на кнопку "Очистить список точек"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_qPushButton_ClearPointList_clicked()
{
 std::vector<CGrPoint> empty;
 InputPoints.clear();
 InputPoints.swap(empty);
 ui->qListWidget_Points->clear();
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************



