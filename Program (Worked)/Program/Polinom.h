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
	//���������� �������� ����������
	System::Windows::Forms::DataVisualization::Charting::Chart^ ChartPolinom;	//������
	std::vector<std::array<double, 2>>* Nodes;									//���� ������������: ���� [X,Y]
	std::vector<std::vector<double>>* Difference_Newton;						//���������� �������� ������� 

	//������ �� ���������� ��� ������
	System::Windows::Forms::TextBox^ OutputX,					//������� �������� X(���� ��������� ������)
		^Deviation;												//������������ ���������� ������� ������������� �� F(X)
	array< System::Windows::Forms::TextBox^>^ OutputLagrange,	//���������� ������ ���� (X, Ln(X)) ��� ������ ��������
		^OutputNewton;											//���������� ������ ���� (X, Ln(X)) ��� ������ �������

	//������������ ��� ������� � ��������� 
	ref class Element {											//��� ��������
	public: static int Argument = 0,							//������ ���������
			Function = 1;										//������ �������
	};

	//���������� �������� � �����
	double Lagrange(double X);									//���������� �������� ��������
	double Newton(double X);									//���������� �������� �������

	//���������� ��������
	void OnMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);	//�������� ���� ������ �������
	void OnClick(System::Object^ sender, System::EventArgs^ e);								//������� ���� ������ �������

public:
	//������������ ��� ������ ������� ��������� 
	ref class Type {											//��� ������� 
	public: static int DotPolinom = 0,							//����� ������������ (��� ���������� �������)
			Module = 1,											//������: Y = fabs(X)
			Expansion = 2,										//���������������� �������: Y = exp(X)
			Sine = 3;											//�����: Y = sin(X)
	};
	Polinom(array<System::Windows::Forms::TextBox^>^ Grop);									//����������� [������� ��������� � ������������� �����]
	void PolinomNodes(System::String^ FILENAME, int TypeFynction);							//�������� ����� ������������ [����������, ����������]
	static System::String^ RandFunction(unsigned int Seed, int Size, int TypeRandom);		//������������ ������� �������� [������� �� ���� �������]
	void FunctPolinom(int TypeFunction);													//���������� �������� ������������ [��� �������]

	System::Windows::Forms::DataVisualization::Charting::Chart^ GetChart();					//����� �������
};

