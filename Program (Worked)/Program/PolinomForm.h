#include "Polinom.h"
#pragma once
namespace Program {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для PolinomForm
	/// </summary>
	public ref class PolinomForm : public System::Windows::Forms::Form
	{
	public:
		PolinomForm(void)
		{
			InitializeComponent();
			InitialozationUzerComponent();
			//
			//TODO: добавьте код конструктора
			//
			
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~PolinomForm()
		{
			if (components)
			{
				delete components;
			}
		}
		//USER ELEMENTS
	protected: array<TextBox^>^ Grop;
		   Polinom^ polinom;
		   int TypeFunct;
		   String^ FileDirectory;
		   bool LagrangeVisile,
			   NewtonVisible;
			   

	private: System::Windows::Forms::SplitContainer^ splitContainer;
	protected:

	protected:

	private: System::Windows::Forms::Button^ ChooseFile;


	private: System::Windows::Forms::Button^ RandomFile;
	private: System::Windows::Forms::OpenFileDialog^ PolinomDialog;



	private: System::Windows::Forms::GroupBox^ GropNewton;
	private: System::Windows::Forms::TextBox^ YNewton;
	private: System::Windows::Forms::TextBox^ XNewton;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::GroupBox^ GropLagrange;
	private: System::Windows::Forms::TextBox^ YLagrange;
	private: System::Windows::Forms::TextBox^ XLagrange;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

	private: System::Windows::Forms::GroupBox^ GropXNow;
	private: System::Windows::Forms::TextBox^ XNow;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ ChooseFunction;

	private: System::Windows::Forms::RadioButton^ Exponent;


	private: System::Windows::Forms::RadioButton^ Sine;
	private: System::Windows::Forms::RadioButton^ Modul;
	private: System::Windows::Forms::Button^ RandomFunction;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::TextBox^ Deviation;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::CheckBox^ VisibleNewton;
	private: System::Windows::Forms::CheckBox^ VisibleLagrange;
	private: System::Windows::Forms::OpenFileDialog^ FunctionDialog;




	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint4 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				1));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint5 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				3));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint6 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(5,
				2));
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Deviation = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->GropXNow = (gcnew System::Windows::Forms::GroupBox());
			this->XNow = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->GropNewton = (gcnew System::Windows::Forms::GroupBox());
			this->VisibleNewton = (gcnew System::Windows::Forms::CheckBox());
			this->YNewton = (gcnew System::Windows::Forms::TextBox());
			this->XNewton = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->GropLagrange = (gcnew System::Windows::Forms::GroupBox());
			this->VisibleLagrange = (gcnew System::Windows::Forms::CheckBox());
			this->YLagrange = (gcnew System::Windows::Forms::TextBox());
			this->XLagrange = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->RandomFunction = (gcnew System::Windows::Forms::Button());
			this->Exponent = (gcnew System::Windows::Forms::RadioButton());
			this->Sine = (gcnew System::Windows::Forms::RadioButton());
			this->Modul = (gcnew System::Windows::Forms::RadioButton());
			this->ChooseFunction = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->ChooseFile = (gcnew System::Windows::Forms::Button());
			this->RandomFile = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->PolinomDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->FunctionDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->GropXNow->SuspendLayout();
			this->GropNewton->SuspendLayout();
			this->GropLagrange->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer
			// 
			this->splitContainer->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->splitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer->IsSplitterFixed = true;
			this->splitContainer->Location = System::Drawing::Point(0, 0);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->groupBox3);
			this->splitContainer->Panel1->Controls->Add(this->GropXNow);
			this->splitContainer->Panel1->Controls->Add(this->GropNewton);
			this->splitContainer->Panel1->Controls->Add(this->GropLagrange);
			this->splitContainer->Panel1->Controls->Add(this->groupBox2);
			this->splitContainer->Panel1->Controls->Add(this->groupBox1);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Controls->Add(this->chart1);
			this->splitContainer->Size = System::Drawing::Size(1123, 560);
			this->splitContainer->SplitterDistance = 219;
			this->splitContainer->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->Deviation);
			this->groupBox3->Controls->Add(this->textBox7);
			this->groupBox3->Location = System::Drawing::Point(3, 243);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(206, 70);
			this->groupBox3->TabIndex = 11;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Максимальное отклонение графика интерполяции от графика функции F(X)";
			// 
			// Deviation
			// 
			this->Deviation->Location = System::Drawing::Point(27, 44);
			this->Deviation->Name = L"Deviation";
			this->Deviation->ReadOnly = true;
			this->Deviation->Size = System::Drawing::Size(173, 20);
			this->Deviation->TabIndex = 10;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(7, 45);
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->Size = System::Drawing::Size(14, 20);
			this->textBox7->TabIndex = 9;
			this->textBox7->Text = L"Y";
			// 
			// GropXNow
			// 
			this->GropXNow->Controls->Add(this->XNow);
			this->GropXNow->Controls->Add(this->textBox4);
			this->GropXNow->Location = System::Drawing::Point(3, 198);
			this->GropXNow->Name = L"GropXNow";
			this->GropXNow->Size = System::Drawing::Size(206, 44);
			this->GropXNow->TabIndex = 10;
			this->GropXNow->TabStop = false;
			this->GropXNow->Text = L"Текущее значение X";
			// 
			// XNow
			// 
			this->XNow->Location = System::Drawing::Point(27, 19);
			this->XNow->Name = L"XNow";
			this->XNow->ReadOnly = true;
			this->XNow->Size = System::Drawing::Size(173, 20);
			this->XNow->TabIndex = 9;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(7, 19);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(14, 20);
			this->textBox4->TabIndex = 8;
			this->textBox4->Text = L"X";
			// 
			// GropNewton
			// 
			this->GropNewton->Controls->Add(this->VisibleNewton);
			this->GropNewton->Controls->Add(this->YNewton);
			this->GropNewton->Controls->Add(this->XNewton);
			this->GropNewton->Controls->Add(this->textBox5);
			this->GropNewton->Controls->Add(this->textBox6);
			this->GropNewton->Location = System::Drawing::Point(6, 438);
			this->GropNewton->Name = L"GropNewton";
			this->GropNewton->Size = System::Drawing::Size(206, 118);
			this->GropNewton->TabIndex = 9;
			this->GropNewton->TabStop = false;
			this->GropNewton->Text = L"Значения координат для Полинома Ньютона";
			// 
			// VisibleNewton
			// 
			this->VisibleNewton->AutoSize = true;
			this->VisibleNewton->Checked = true;
			this->VisibleNewton->CheckState = System::Windows::Forms::CheckState::Checked;
			this->VisibleNewton->Location = System::Drawing::Point(7, 32);
			this->VisibleNewton->Name = L"VisibleNewton";
			this->VisibleNewton->Size = System::Drawing::Size(141, 17);
			this->VisibleNewton->TabIndex = 9;
			this->VisibleNewton->Text = L"Отображение графика";
			this->VisibleNewton->UseVisualStyleBackColor = true;
			// 
			// YNewton
			// 
			this->YNewton->Location = System::Drawing::Point(27, 80);
			this->YNewton->Name = L"YNewton";
			this->YNewton->ReadOnly = true;
			this->YNewton->Size = System::Drawing::Size(173, 20);
			this->YNewton->TabIndex = 8;
			// 
			// XNewton
			// 
			this->XNewton->Location = System::Drawing::Point(27, 55);
			this->XNewton->Name = L"XNewton";
			this->XNewton->ReadOnly = true;
			this->XNewton->Size = System::Drawing::Size(173, 20);
			this->XNewton->TabIndex = 7;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(7, 55);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(14, 20);
			this->textBox5->TabIndex = 5;
			this->textBox5->Text = L"X";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(7, 81);
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(14, 20);
			this->textBox6->TabIndex = 6;
			this->textBox6->Text = L"Y";
			// 
			// GropLagrange
			// 
			this->GropLagrange->Controls->Add(this->VisibleLagrange);
			this->GropLagrange->Controls->Add(this->YLagrange);
			this->GropLagrange->Controls->Add(this->XLagrange);
			this->GropLagrange->Controls->Add(this->textBox1);
			this->GropLagrange->Controls->Add(this->textBox2);
			this->GropLagrange->Location = System::Drawing::Point(6, 319);
			this->GropLagrange->Name = L"GropLagrange";
			this->GropLagrange->Size = System::Drawing::Size(206, 113);
			this->GropLagrange->TabIndex = 8;
			this->GropLagrange->TabStop = false;
			this->GropLagrange->Text = L"Значения координат для Полинома Лагранжа";
			// 
			// VisibleLagrange
			// 
			this->VisibleLagrange->AutoSize = true;
			this->VisibleLagrange->Checked = true;
			this->VisibleLagrange->CheckState = System::Windows::Forms::CheckState::Checked;
			this->VisibleLagrange->Location = System::Drawing::Point(5, 34);
			this->VisibleLagrange->Name = L"VisibleLagrange";
			this->VisibleLagrange->Size = System::Drawing::Size(141, 17);
			this->VisibleLagrange->TabIndex = 9;
			this->VisibleLagrange->Text = L"Отображение графика";
			this->VisibleLagrange->UseVisualStyleBackColor = true;
			// 
			// YLagrange
			// 
			this->YLagrange->Location = System::Drawing::Point(25, 82);
			this->YLagrange->Name = L"YLagrange";
			this->YLagrange->ReadOnly = true;
			this->YLagrange->Size = System::Drawing::Size(173, 20);
			this->YLagrange->TabIndex = 8;
			// 
			// XLagrange
			// 
			this->XLagrange->Location = System::Drawing::Point(25, 57);
			this->XLagrange->Name = L"XLagrange";
			this->XLagrange->ReadOnly = true;
			this->XLagrange->Size = System::Drawing::Size(173, 20);
			this->XLagrange->TabIndex = 7;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(5, 57);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(14, 20);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = L"X";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(5, 83);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(14, 20);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"Y";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->RandomFunction);
			this->groupBox2->Controls->Add(this->Exponent);
			this->groupBox2->Controls->Add(this->Sine);
			this->groupBox2->Controls->Add(this->Modul);
			this->groupBox2->Controls->Add(this->ChooseFunction);
			this->groupBox2->Location = System::Drawing::Point(3, 85);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(206, 107);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Построение полинома по заданной функции";
			// 
			// RandomFunction
			// 
			this->RandomFunction->Location = System::Drawing::Point(110, 57);
			this->RandomFunction->Margin = System::Windows::Forms::Padding(2);
			this->RandomFunction->Name = L"RandomFunction";
			this->RandomFunction->Size = System::Drawing::Size(88, 38);
			this->RandomFunction->TabIndex = 5;
			this->RandomFunction->Text = L"Рандомная генерация";
			this->RandomFunction->UseVisualStyleBackColor = true;
			this->RandomFunction->Click += gcnew System::EventHandler(this, &PolinomForm::RandFunction);
			// 
			// Exponent
			// 
			this->Exponent->AutoSize = true;
			this->Exponent->Location = System::Drawing::Point(6, 78);
			this->Exponent->Margin = System::Windows::Forms::Padding(2);
			this->Exponent->Name = L"Exponent";
			this->Exponent->Size = System::Drawing::Size(101, 17);
			this->Exponent->TabIndex = 4;
			this->Exponent->Text = L"Экспонента eX";
			this->Exponent->UseVisualStyleBackColor = true;
			this->Exponent->CheckedChanged += gcnew System::EventHandler(this, &PolinomForm::ChangedExp);
			// 
			// Sine
			// 
			this->Sine->AutoSize = true;
			this->Sine->Location = System::Drawing::Point(7, 57);
			this->Sine->Margin = System::Windows::Forms::Padding(2);
			this->Sine->Name = L"Sine";
			this->Sine->Size = System::Drawing::Size(84, 17);
			this->Sine->TabIndex = 2;
			this->Sine->TabStop = true;
			this->Sine->Text = L"Синус sin(X)";
			this->Sine->UseVisualStyleBackColor = true;
			this->Sine->CheckedChanged += gcnew System::EventHandler(this, &PolinomForm::ChangedSine);
			// 
			// Modul
			// 
			this->Modul->AutoSize = true;
			this->Modul->Checked = true;
			this->Modul->Location = System::Drawing::Point(7, 36);
			this->Modul->Margin = System::Windows::Forms::Padding(2);
			this->Modul->Name = L"Modul";
			this->Modul->Size = System::Drawing::Size(77, 17);
			this->Modul->TabIndex = 1;
			this->Modul->TabStop = true;
			this->Modul->Text = L"Модуль |X|";
			this->Modul->UseVisualStyleBackColor = true;
			this->Modul->CheckedChanged += gcnew System::EventHandler(this, &PolinomForm::ChackedModule);
			// 
			// ChooseFunction
			// 
			this->ChooseFunction->Location = System::Drawing::Point(110, 33);
			this->ChooseFunction->Margin = System::Windows::Forms::Padding(2);
			this->ChooseFunction->Name = L"ChooseFunction";
			this->ChooseFunction->Size = System::Drawing::Size(88, 19);
			this->ChooseFunction->TabIndex = 0;
			this->ChooseFunction->Text = L"Выбор файла";
			this->ChooseFunction->UseVisualStyleBackColor = true;
			this->ChooseFunction->Click += gcnew System::EventHandler(this, &PolinomForm::FilesFunct);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->ChooseFile);
			this->groupBox1->Controls->Add(this->RandomFile);
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(206, 76);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Построение полинома по заданным узлам интеполяции";
			// 
			// ChooseFile
			// 
			this->ChooseFile->Location = System::Drawing::Point(6, 32);
			this->ChooseFile->Name = L"ChooseFile";
			this->ChooseFile->Size = System::Drawing::Size(89, 37);
			this->ChooseFile->TabIndex = 0;
			this->ChooseFile->Text = L"Выбор файла";
			this->ChooseFile->UseVisualStyleBackColor = true;
			this->ChooseFile->Click += gcnew System::EventHandler(this, &PolinomForm::FilesPolinom);
			// 
			// RandomFile
			// 
			this->RandomFile->Location = System::Drawing::Point(103, 32);
			this->RandomFile->Name = L"RandomFile";
			this->RandomFile->Size = System::Drawing::Size(97, 37);
			this->RandomFile->TabIndex = 2;
			this->RandomFile->Text = L"Рандомная генерация";
			this->RandomFile->UseVisualStyleBackColor = true;
			this->RandomFile->Click += gcnew System::EventHandler(this, &PolinomForm::RandPolinom);
			// 
			// chart1
			// 
			chartArea2->CursorX->Interval = 0;
			chartArea2->CursorX->IsUserEnabled = true;
			chartArea2->CursorY->Interval = 0;
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->Enabled = false;
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			series2->BorderWidth = 4;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			dataPoint4->IsValueShownAsLabel = false;
			dataPoint4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Square;
			series2->Points->Add(dataPoint4);
			series2->Points->Add(dataPoint5);
			series2->Points->Add(dataPoint6);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(896, 556);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Visible = false;
			// 
			// PolinomDialog
			// 
			this->PolinomDialog->FileName = L"openFileDialog";
			this->PolinomDialog->Filter = L"Узлы интерполяции (Без функции): RD*.txt|RD*.txt";
			// 
			// FunctionDialog
			// 
			this->FunctionDialog->FileName = L"openFileDialog1";
			this->FunctionDialog->Filter = L"Узлы интерполяции sin(X): RS*.txt|RS*.txt|Узлы интерполяции fabs(X): RM*.txt|RM*."
				L"txt|Узлы интерполяции exp(X): RE*.txt|RE*.txt";
			// 
			// PolinomForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1123, 560);
			this->Controls->Add(this->splitContainer);
			this->MaximumSize = System::Drawing::Size(1139, 599);
			this->MinimumSize = System::Drawing::Size(1139, 599);
			this->Name = L"PolinomForm";
			this->Text = L"PolinomForm";
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->GropXNow->ResumeLayout(false);
			this->GropXNow->PerformLayout();
			this->GropNewton->ResumeLayout(false);
			this->GropNewton->PerformLayout();
			this->GropLagrange->ResumeLayout(false);
			this->GropLagrange->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
//ИНИЦИАЛИЗАЦИЯ ПОЛЬЗОВАТЕЛЬСКИХ ОБЪЕКТОВ		
private: void InitialozationUzerComponent() {
	Grop = gcnew array<TextBox^>(6){ XNow, Deviation, XLagrange, YLagrange, XNewton, YNewton };
	polinom = gcnew Polinom(Grop);
	splitContainer->Panel2->Controls->Add(polinom->GetChart());
	TypeFunct = Polinom::Type::Module;
	FileDirectory = nullptr;
	LagrangeVisile = true;
	NewtonVisible = true;
}

//ВЫБОР ФАЙЛА С УЗЛАМИ ИНТЕРПОЛЯЦИИ
private: System::Void FilesPolinom(System::Object^ sender, System::EventArgs^ e) {
	if (PolinomDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		polinom->PolinomNodes(PolinomDialog->FileName, Polinom::Type::DotPolinom);
		polinom->FunctPolinom(Polinom::Type::DotPolinom);
	}
}

//СОЗДАНИЕ ФАЙЛА С РАНДОМНЫМИ УЗЛАМИ ИНТЕРПОЛЯЦИИ
private: System::Void RandPolinom(System::Object^ sender, System::EventArgs^ e) {
	std::random_device Seed;
	String^ Filename = Polinom::RandFunction(Seed(), 4, Polinom::Type::DotPolinom);
	polinom->PolinomNodes(Filename, Polinom::Type::DotPolinom);
	polinom->FunctPolinom(Polinom::Type::DotPolinom);
}

//ВЫБОР ФАЙЛА С X КООРДИНАТАМИ УЗЛОВ ИНТЕРПОЛЯЦИИ НА ФУНКЦИИ F(X) 
private: System::Void FilesFunct(System::Object^ sender, System::EventArgs^ e) {
	if (FunctionDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		FileDirectory = FunctionDialog->FileName;
		polinom->PolinomNodes(FileDirectory, TypeFunct);
		polinom->FunctPolinom(TypeFunct);
	}
}

//СОЗДАНИЕ РАНДОМНОГО ФАЙЛА С X КООРДИНАТАМИ УЗЛОВ ИНТЕРПОЛЯЦИИ НА ФУНКЦИИ F(X)
private: System::Void RandFunction(System::Object^ sender, System::EventArgs^ e) {
	std::random_device Seed;
	String^ Filename = Polinom::RandFunction(Seed(), 4, TypeFunct);
	polinom->PolinomNodes(Filename, TypeFunct);
	polinom->FunctPolinom(TypeFunct);

}

//ВЫБОР ОТОБРАЖАЮЩЕГОСЯ ГРАФИКА (RADIOBUTTON)
private: System::Void ChackedModule(System::Object^ sender, System::EventArgs^ e) {
	if (TypeFunct != Polinom::Type::Module)
	{
		TypeFunct = Polinom::Type::Module;
		if (FileDirectory != nullptr)
		{
			polinom->PolinomNodes(FileDirectory, TypeFunct);
			polinom->FunctPolinom(TypeFunct);
		}
	}

}
private: System::Void ChangedSine(System::Object^ sender, System::EventArgs^ e) {
	if (TypeFunct != Polinom::Type::Sine)
	{
		TypeFunct = Polinom::Type::Sine;
		if (FileDirectory != nullptr)
		{
			polinom->PolinomNodes(FileDirectory, TypeFunct);
			polinom->FunctPolinom(TypeFunct);
		}
	}

}
private: System::Void ChangedExp(System::Object^ sender, System::EventArgs^ e) {
	if (TypeFunct != Polinom::Type::Expansion)
	{
		TypeFunct = Polinom::Type::Expansion;
		if (FileDirectory != nullptr)
		{
			polinom->PolinomNodes(FileDirectory, TypeFunct);
			polinom->FunctPolinom(TypeFunct);
		}
	}

}
private: System::Void LagrangeVisibleChanged(System::Object^ sender, System::EventArgs^ e) {

}
};
}
