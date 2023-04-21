#define _USE_MATH_DEFINES

#include <vector>
#include <array>
#include <ostream>
#include <ostream>
#include <math.h>
#include <random>
#include <functional>
#include <cliext/vector>
#pragma once

ref class Polinom
{
private:
	//КОНТЕЙНЕРЫ ХРАНЕНИЯ ВЫЧИСЛЕНИЙ
	System::Windows::Forms::DataVisualization::Charting::Chart^ ChartPolinom;	//График
	std::vector<std::array<double, 2>>* Nodes;									//Узлы интерполяции: пара [X,Y]
	std::vector<std::vector<double>>* Difference_Newton;						//Разделённые разности Ньютона 

	//ССЫЛКИ НА КОНТЕЙНЕРЫ ДЛЯ ВЫВОДА
	System::Windows::Forms::TextBox^ OutputX,					//Текущее значение X(Куда указывает курсор)
		^Deviation;												//Максимальное отклонение графика иинтерполяции от F(X)
	array< System::Windows::Forms::TextBox^>^ OutputLagrange,	//Контейнеры вывода пары (X, Ln(X)) для метода Лагранжа
		^OutputNewton;											//Контейнеры вывода пары (X, Ln(X)) для метода Ньютона

	//ПЕРЕЧИСЛЕНИЕ ДЛЯ ДОСТУПА К ЭЛЕМЕНТАМ 
	ref class Element {											//Тип элемента
	public: static int Argument = 0,							//Индекс Аргумента
			Function = 1;										//Индекс Функции
	};

	//ВЫЧИСЛЕНИЕ ПОЛИНОМА В ТОЧКЕ
	double Lagrange(double X);									//Вычисление полинома Лагранжа
	double Newton(double X);									//Вычисление полинома Ньютона

	//ОБРАБОТЧКИ ДЕЙСТВИЙ
	void OnMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);	//Движение мыши внутри графика
	void OnClick(System::Object^ sender, System::EventArgs^ e);								//Нажатие мыши внутри графика

public:
	//ПЕРЕЧИСЛЕНИЕ ДЛЯ ВЫБОРА СПОСОБА ОБРАБОТКИ 
	ref class Type {											//Тип графика 
	public: static int DotPolinom = 0,							//Точки интерполяции (Без просроение графика)
			Module = 1,											//Модуль: Y = fabs(X)
			Expansion = 2,										//Экспоненциальная функция: Y = exp(X)
			Sine = 3;											//Синус: Y = sin(X)
	};
	Polinom(array<System::Windows::Forms::TextBox^>^ Grop);									//Конструктор [базовая настройка и инициализация полей]
	void PolinomNodes(System::String^ FILENAME, int TypeFynction);							//Полчение узлов интерполяции [считывание, заполнение]
	static System::String^ RandFunction(unsigned int Seed, int Size, int TypeRandom);		//Рандомизатор входных значений [Зависит от типа функции]
	void FunctPolinom(int TypeFunction);													//Построение графиков интерполяции [Все графики]

	System::Windows::Forms::DataVisualization::Charting::Chart^ GetChart();					//Гетер графика
};

