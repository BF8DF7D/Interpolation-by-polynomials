#include "Polinom.h"


Polinom::Polinom(array< System::Windows::Forms::TextBox^>^ Grop) {
	//НАСТРОЙКА ВЫВОДА
	OutputX = Grop[0];
	Deviation = Grop[1];
	OutputLagrange = gcnew array<System::Windows::Forms::TextBox^>(2) { Grop[2], Grop[3] };
	OutputNewton = gcnew array<System::Windows::Forms::TextBox^>(2) { Grop[4], Grop[5] };

	//ПАНЕЛИ ОТОБРАЖЕНИЯ
	ChartPolinom = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChartPolinom))->BeginInit();
	ChartPolinom->Dock = System::Windows::Forms::DockStyle::Fill;
	System::Windows::Forms::DataVisualization::Charting::Cursor^ XCursor = ChartPolinom->ChartAreas->Add("PolinomAreas")->CursorX;
	XCursor->Interval = 0;
	XCursor->IntervalOffset = 0;
	XCursor->IsUserEnabled = true;

	//НАСТРОЙКА КООРДИНАТНЫХ ПЛОСКОСТЕЙ
	System::Windows::Forms::DataVisualization::Charting::Axis^ X = ChartPolinom->ChartAreas[0]->AxisX,
		^ Y = ChartPolinom->ChartAreas[0]->AxisY;
	X->MinorGrid->Enabled = true;
	X->MinorGrid->LineColor = System::Drawing::Color::Silver;
	X->IsMarginVisible = false;
	Y->MinorGrid->Enabled = true;
	Y->MinorGrid->LineColor = System::Drawing::Color::Silver;
	Y->IsMarginVisible = false;

	//ДОБАВЕНИЕ ЛЕГЕНДЫ 
	ChartPolinom->Legends->Add("LegendChart");

	//НАСТРОЙКА ГРАФИКОВ ФУНКЦИЙ F(X)
	System::Windows::Forms::DataVisualization::Charting::Series^ SeriesFunction = ChartPolinom->Series->Add("SeriesFunction"),
		^ SeriesLagrange = ChartPolinom->Series->Add("SeriesLagrange"),
		^ SeriesNewton = ChartPolinom->Series->Add("SeriesNewton"),
		^ SeriesDeviation = ChartPolinom->Series->Add("SeriesDeviation");
	SeriesFunction->LegendText = "Функция F(X)";
	SeriesFunction->Color = System::Drawing::Color::Black;
	SeriesLagrange->LegendText = "Полином Лагранжа";
	SeriesLagrange->Color = System::Drawing::Color::DarkRed;
	SeriesNewton->LegendText = "Полином Ньютона";
	SeriesNewton->Color = System::Drawing::Color::Orange;
	SeriesDeviation->LegendText = "Место максимального отклонения полинома от функции";
	SeriesDeviation->Color = System::Drawing::Color::Blue;

	int rgb = 10;
	for (auto series = ChartPolinom->Series->GetEnumerator(); series->MoveNext(); rgb += 100) {
		series->Current->ChartArea = "PolinomAreas";
		series->Current->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		series->Current->YValuesPerPoint = 1;
		series->Current->BorderWidth = 3;
		series->Current->Legend = "LegendChart";
	}
	SeriesDeviation->BorderWidth = 2;

	//НАСТРОКА ГРАФИКА ОТОБРАЖЕНИЯ ТОЧЕК ИНТЕРПОЛЯЦИИ
	System::Windows::Forms::DataVisualization::Charting::Series^ Polinom = ChartPolinom->Series->Add("SeriesPolinom");
	Polinom->ChartArea = "PolinomAreas";
	Polinom->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
	Polinom->MarkerBorderColor = System::Drawing::Color::Red;
	Polinom->MarkerColor = System::Drawing::Color::Transparent;
	Polinom->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
	Polinom->MarkerSize = 6;
	Polinom->MarkerBorderWidth = 3;
	Polinom->LegendText = "Узлы интерполяции";
	ChartPolinom->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Polinom::OnMouseMove);
	ChartPolinom->Click += gcnew System::EventHandler(this, &Polinom::OnClick);

	//ИНИЦИАЛИЗАЦИЯ КОНТЕЙНЕРОВ
	Nodes = new std::vector<std::array<double, 2>>;
	Difference_Newton = new std::vector<std::vector<double>>();
}

/* СЧИТЫВАНИЕ ТОЧЕК ИНТЕРПОЛЯЦИИ
* System::String^ FILENAME - Имя файла, для открытия файлового потока
* int TypeFunction - Вид функции, способ обработки входных значений 
*/
void Polinom::PolinomNodes(System::String^ FILENAME, int TypeFunction) {
	//ОЧИСТКА ОКНЕТЙНЕРОВ ПЕРЕД ПОВТОРНЫМ ЗАПОЛНЕНИЕМ 
	for (auto element = ChartPolinom->Series->GetEnumerator(); element->MoveNext();) {	//Очистка графиков от точек
		element->Current->Points->Clear();
	}
	Nodes->clear();																		//Очистка узлов интерполяции
	Difference_Newton->clear();															//Очистка разделённых разностей

	//СЧИТЫВАНИЕ ИЗ ФАЙЛА УЗЛОВ ИНТЕРПОЛЯЦИИ;
	System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::OpenOrCreate);				//Открытие файла
	System::IO::StreamReader^ Stream = gcnew System::IO::StreamReader(File);												//Создание символьного птока чтения из файла
	array<wchar_t>^ Separator = gcnew array<wchar_t>(1) {' '};																//Массив разделитей символьной строки
	for (double X, Y; !Stream->EndOfStream;)																				//Считывание, пока не достигнут конец потока
	{
		array<System::String^>^ line = Stream->ReadLine()->Split(Separator, System::StringSplitOptions::RemoveEmptyEntries);	//Массив считанных данных [Считать строку->разделить->удалить пустые] 
		X = System::Convert::ToDouble(line[Element::Argument]);																	//Преобразовать аргумент функции из String -> double
		//СПОСОБ ПОЛУЧЕНИЯ Y КООРДИНАТЫ УЗЛА ИНТЕРПОЛЯЦИИ
		if (TypeFunction == Type::DotPolinom) {											//Только узлы
			Y = System::Convert::ToDouble(line[Element::Function]);						//Преобразовать второй считанный аргумент в Y координату
		}
		else if (TypeFunction == Type::Expansion) {										//Експаненциальна
			Y = std::exp(-X);															//Вычислить по X
		}
		else if (TypeFunction == Type::Module) {										//Модуль
			Y = std::fabs(X);															//Вычислить по X
		}
		else if (TypeFunction == Type::Sine) {											//Экспоненциальная
			Y = std::sin(X);															//Вычислить по X
		}
		Nodes->push_back(std::array<double, 2>{X, Y});									//Добавление точки интерпритации в контейнер
		ChartPolinom->Series->FindByName("SeriesPolinom")->Points->AddXY(X, Y);			//Добавление точки интерпритации на график
	}
	Stream->Close();																	//Закрытие потока считывания
	delete[] Separator;																	//Удаление выделеной памети под разделитель

	//ВЫЧИСЛЕНИЕ РАЗНОСТЕЙ ДЛЯ ПОЛИНОМА НЬЮТОНА
	//Начальное вхождение 
	int Size = Nodes->size();															//Получение размера
	Difference_Newton->push_back(std::vector<double>());								//Добавление строки, содержащей Fk
	for (int Fx = 0; Fx < Size; Fx++) {													//Заполение элементами Fk
		(*Difference_Newton)[0].push_back((*Nodes)[Fx][Element::Function]);				//Fk - Y координата точен интерполяции
	}
	//Вычисление разностей
	//Храняться по строкам в виде триугольной матрицы
	//X[degree][defference]; 
	//X10 11 12 -> X20 21 -> X30 
	for (int Degree = 1; Degree < Size; Degree++) {										//Degree - степень разделённой разности 									
		(*Difference_Newton).push_back(std::vector<double>());							//Добавть контейнер соотвествующей разделённой разности
		for (int Difference = 0; Difference + Degree < Size; Difference++) {			//Difference - Номер разности. 
			//Вычисление числителя и знаменателя
			//Числитель: верхний элемент справа - верхний элемент
			double Numerator = (*Difference_Newton)[Degree - 1][Difference + 1] - (*Difference_Newton)[Degree - 1][Difference], 
				//Знаменатель: X[Степень разности + номер.разности] - X[Степ.разности]
				Denominator = (*Nodes)[Degree + Difference][Element::Argument] - (*Nodes)[Difference][Element::Argument];		 
			//Получение разности
			(*Difference_Newton)[Degree].push_back(Numerator / Denominator);
		}
	}
}

/*РАНДОМИЗАЦИЯ ТОЧЕК ИНТЕПОЛЯЦИИ
* Рандомизирует входные значения в зависимости от типа рандомизации - тип функции,
* предпологаемый в данном файле. В зависимости от функции, предусмотрены разные 
* промежутки рандомизации и нейминга файла с входными данными. 
* 
* unsigned int Seed - Зерно рандомизации
* int Size - Кол-во зеркальных точек интерполяции (От нуля, множеается на 2)
* int TipeRandom - Тип рандомизации или тип функции 
*/
System::String^ Polinom::RandFunction(unsigned int Seed, int Size, int TipeRandom) {
	System::String^ FILENAME = gcnew System::String("R");								//R - Маркер Рандомно сгенерированного файла
	std::mt19937 random(Seed);															//ГПСЧ: Фихрь Мерсера (качество > время)
	
	//СПОСОБ РАНДОМИЗАЦИИ
	if (TipeRandom == Type::DotPolinom) {																								//Только точки интрполяции
		FILENAME += "D";																												//D - Dot, маркер
		FILENAME = System::String::Join("", FILENAME, System::Convert::ToString(Seed), "_", System::Convert::ToString(Size), ".txt");	//Создание имени файла
		System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::Create);							//Создание файла
		System::IO::StreamWriter^ Stream = gcnew System::IO::StreamWriter(File);														//Открытие символьного потока на основе созданного файла
		std::uniform_int_distribution<> random_int(-(2 * Size), 2 * Size);																//Рандомизатор целых чисел с равным распределением
		for (int row = -Size + 1; row < Size; row++) {																					//Получение последовательных пар [X,Y] из дипозона
			Stream->WriteLine("{0} {1}", row, random_int(random));																		//Пары упорядочены по X
		}
		Stream->Close();																												//Закарытие потока
	}
	else {																				//СПОСОБЫ ДЛЯ ГРАФИКОВ
		std::uniform_real_distribution<> random_double;									//Рандомизатор действительных чисел с равным распределением
		if (TipeRandom == Type::Expansion) {											//Экспоненциальная						
			FILENAME += "E";															//E - Exponent, маркер
			random_double = std::uniform_real_distribution<>( - 4.0, 4.0);				//Установка дипозона
		}
		else if (TipeRandom == Type::Module) {											//Модуль
			FILENAME += "M";															//M - Module, маркер
			random_double = std::uniform_real_distribution<>(-1.0, 1.0);				//Установка дипозона
		}
		else if (TipeRandom == Type::Sine) {											//Синус
			FILENAME += "S";															//S - Sine, маркер
			random_double = std::uniform_real_distribution<>(-M_PI, M_PI);				//Установка дипозона
		}
		FILENAME = System::String::Join("", FILENAME, System::Convert::ToString(Seed), "_", System::Convert::ToString(Size), ".txt");	//Создание имени файла
		System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::Create);							//Создание файла
		System::IO::StreamWriter^ Stream = gcnew System::IO::StreamWriter(File);														//Открытие символьного потока на основе созданного файла
		std::vector<double> FunctionArg;																								//Контейнер для X значений F(X)
		for (int row = -Size + 1; row < Size; row++) {																					//Получение неупорядоченного ряда рандомных X
			FunctionArg.push_back(random_double(random));																				
		}
		std::sort(FunctionArg.begin(), FunctionArg.end());																				//Сортировка полученного контейнера
		for (int row = 0, Size = FunctionArg.size(); row < Size; row++) {																//Запись отсортированных значений в файл
			Stream->WriteLine("{0}",FunctionArg[row]);																					
		}
		Stream->Close();																												//Закрытие потока
	}
	return FILENAME;																	//ВОЗВРАТ НАИМЕНОВАНИЯ ФАЙЛА
}

//ЛАГРАНЖ
double Polinom::Lagrange(double X) {																	
	double Lagrange = 0;
	auto Node = *Nodes;
	for (int Summary = 0, Size = Nodes->size(); Summary < Size; Summary++) {
		double Numerator = 1,
			Denominator = 1;																			
		for (int Composition = 0; Composition < Size; Composition++) {									//			  m
			if (Summary != Composition)																	//Numerator = П(X - Xj)
				Numerator *= X - Node[Composition][Element::Argument];									//			  j=0,i!=k
		}
		for (int Composition = 0; Composition < Size; Composition++) {									//				m
			if (Summary != Composition)																	//Denominator = П(Xk - Xj)
				Denominator *= Node[Summary][Element::Argument] - Node[Composition][Element::Argument];	//				j=0,i!=k
		}																								//			 m
		Lagrange += Numerator / Denominator * Node[Summary][Element::Function];							//Lagrange = E((Numerator/Denominator) * F(Xk))
	}																									//			 k=0
	return Lagrange;	//ВОЗРАТ ЗНАЧЕНИЯ ПОЛИНОМА ЛАГРАНЖА
}

//НЬЮТОН
double Polinom::Newton(double X) {
	double Newton = 0;
	for (int Degree = 0, Size = Nodes->size(); Degree < Size; Degree++) {
		double Composition = 1;													//				i
		for (int Difference = 0; Difference < Degree; Difference++) {			//Composition = П(X - Xj)
			Composition *= X - (*Nodes)[Difference][Element::Argument];			//				j=0
		}																		//		   m
		Newton += Composition * (*Difference_Newton)[Degree][0];				//Newton = E(Composition * Fi0 (Разденённая разность Ньютона));
	}																			//		   i=0
	return Newton;		//ВОЗРАТ ЗНАЧЕНИЯ ПОЛИНОМА НЬЮТОНА
}

/*ПОСТРОЕНИЕ ГРАФИКОВ 
* Функциия строит графики интерполяции Лагранжа и Ньютона. А так же в зависимости от типа
* функции строит и его график. Так же функция благодоря одновременному построению находит
* максимальное отклонение полинома от графика F(X)
* int TypeFunction - Вид Функции
*/
void Polinom::FunctPolinom(int TypeFunction) {
	double MaxDeviation = 0,					//МАксимальное отклонение полнома от F(X)
		MaxCordX,								//Координата X максимального отклонения 
		MaxFunctionY,							//Координата Y  максимального отклонения для F(X):
		MaxPolinomY;							//Координата Y  максимального отклонения для полинома
	//ПОСТРОЕНИЕ ГРАФИКА ФУНКЦИИ
	//Элементы упорядочены по возрастанию:
	for (double X = (*Nodes)[0][Element::Argument],					//Начальный элемент - самый минемальный аргумент
		MaxX = (*Nodes)[Nodes->size() - 1][Element::Argument];		//Конечный аргумент самый максимальный аргумент
		X <= MaxX + 0.01; X += 0.01) {								//Шаг графика
		double PolinomY = Lagrange(X);								//Высчитывание значения полинома в точке
		//ЕСЛИ РИСУЕТСЯ ЕЩЁ И ГРАФИК 
		if (TypeFunction != Type::DotPolinom) {						
			double FunctionY,										//Значение функции в точке
				Deviation;											//Отклонение
			//РАСЧЁТ ЗНАЧЕНИЯ ФУНКЦИИ В ТОЧКЕ
			if (TypeFunction == Type::Expansion) {
				FunctionY = std::exp(-X);
			}
			else if (TypeFunction == Type::Module) {
				FunctionY = std::fabs(X);
			}
			else if (TypeFunction == Type::Sine) {
				FunctionY = std::sin(X);
			}
			//НАХОЖДЕНИЕ МАКСИМАЬНОГО ОТКЛОНЕНИЯ
			Deviation = std::fabs(std::fabs(PolinomY) - std::fabs(FunctionY));	//Вычисление отклонения
			if (Deviation > MaxDeviation) {										//Отклонение > максимального
				MaxDeviation = Deviation;										//Сохранить как максимально
				MaxCordX = X;													//Сохрань все соотвествующие координаты
				MaxFunctionY = FunctionY;
				MaxPolinomY = PolinomY;
			}
			ChartPolinom->Series->FindByName("SeriesFunction")->Points->AddXY(X, FunctionY);	//Добавить точку функции
		}
		ChartPolinom->Series->FindByName("SeriesLagrange")->Points->AddXY(X, PolinomY);			//Добавить точку полинома Лагранжа
		ChartPolinom->Series->FindByName("SeriesNewton")->Points->AddXY(X, Newton(X));			//Добавить точку полинома Ньютона
	}
	//ОБОЗНАЧЕНИЕ ОТРЕЗКА МАКСИМАЛЬНОГО ОТКЛОНЕНИЯ;
	if (MaxDeviation != 0) {
		Deviation->Text = System::Convert::ToString(MaxDeviation);								//Отображение отклонения на главном экране
		System::Windows::Forms::DataVisualization::Charting::DataPointCollection^ 
			PointsDeviation = ChartPolinom->Series->FindByName("SeriesDeviation")->Points;		//Колекция точек графика смещения [Отрезок]
		PointsDeviation->AddXY(MaxCordX, MaxFunctionY);											//Добавить соответствующую смещению точку на функции F(X)
		PointsDeviation->AddXY(MaxCordX, MaxPolinomY);											//Добавить соответствующую смещению точку на полиноме
	}
}

//ГЕТЕР ГРАФИКОВ
System::Windows::Forms::DataVisualization::Charting::Chart^ Polinom::GetChart() {
	return ChartPolinom;
}

//ОБРАБОТЧИК ПЕРЕМЕЩЕНИЯ МЫШИ ВНУТРИ ОБЛАСТИ ОТРИСОВКИ ГРАФИКОВ
void Polinom::OnMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	//Рисует внутри координатной плоскости курсок в виде линни, паралельной Y. Курсор не выходящий за пределы плоскости
	ChartPolinom->ChartAreas["PolinomAreas"]->CursorX->SetCursorPixelPosition(System::Drawing::PointF(e->X, e->Y), true);	
	//Определяет позицию X внутреннего курсора относительной внутрней системы координат [Координаты графиков]
	double pX = ChartPolinom->ChartAreas["PolinomAreas"]->CursorX->Position;							
	//Вывод X внутреней координаты в элемент управления
	OutputX->Text = System::Convert::ToString(pX);
}

//РАСЧЁТ ЗНАЧЕНИЙ ПОЛИНОМОВ ПО ЩЕЛЧКУ МЫШИ
void Polinom::OnClick(System::Object^ sender, System::EventArgs^ e)
{

	System::Windows::Forms::DataVisualization::Charting::ChartArea^ Area = ChartPolinom->ChartAreas["PolinomAreas"];
	double pX = Area->CursorX->Position;
	OutputLagrange[Element::Argument]->Text = System::Convert::ToString(pX);
	OutputNewton[Element::Argument]->Text = System::Convert::ToString(pX);
	double LpY = Lagrange(pX),
		NpY = Newton(pX);
	OutputLagrange[Element::Function]->Text = System::Convert::ToString(LpY);
	OutputNewton[Element::Function]->Text = System::Convert::ToString(NpY);
}
