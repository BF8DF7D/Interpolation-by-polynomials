#include "Polinom.h"


Polinom::Polinom(array< System::Windows::Forms::TextBox^>^ Grop) {
	//��������� ������
	OutputX = Grop[0];
	Deviation = Grop[1];
	OutputLagrange = gcnew array<System::Windows::Forms::TextBox^>(2) { Grop[2], Grop[3] };
	OutputNewton = gcnew array<System::Windows::Forms::TextBox^>(2) { Grop[4], Grop[5] };

	//������ �����������
	ChartPolinom = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChartPolinom))->BeginInit();
	ChartPolinom->Dock = System::Windows::Forms::DockStyle::Fill;
	System::Windows::Forms::DataVisualization::Charting::Cursor^ XCursor = ChartPolinom->ChartAreas->Add("PolinomAreas")->CursorX;
	XCursor->Interval = 0;
	XCursor->IntervalOffset = 0;
	XCursor->IsUserEnabled = true;

	//��������� ������������ ����������
	System::Windows::Forms::DataVisualization::Charting::Axis^ X = ChartPolinom->ChartAreas[0]->AxisX,
		^ Y = ChartPolinom->ChartAreas[0]->AxisY;
	X->MinorGrid->Enabled = true;
	X->MinorGrid->LineColor = System::Drawing::Color::Silver;
	X->IsMarginVisible = false;
	Y->MinorGrid->Enabled = true;
	Y->MinorGrid->LineColor = System::Drawing::Color::Silver;
	Y->IsMarginVisible = false;

	//��������� ������� 
	ChartPolinom->Legends->Add("LegendChart");

	//��������� �������� ������� F(X)
	System::Windows::Forms::DataVisualization::Charting::Series^ SeriesFunction = ChartPolinom->Series->Add("SeriesFunction"),
		^ SeriesLagrange = ChartPolinom->Series->Add("SeriesLagrange"),
		^ SeriesNewton = ChartPolinom->Series->Add("SeriesNewton"),
		^ SeriesDeviation = ChartPolinom->Series->Add("SeriesDeviation");
	SeriesFunction->LegendText = "������� F(X)";
	SeriesFunction->Color = System::Drawing::Color::Black;
	SeriesLagrange->LegendText = "������� ��������";
	SeriesLagrange->Color = System::Drawing::Color::DarkRed;
	SeriesNewton->LegendText = "������� �������";
	SeriesNewton->Color = System::Drawing::Color::Orange;
	SeriesDeviation->LegendText = "����� ������������� ���������� �������� �� �������";
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

	//�������� ������� ����������� ����� ������������
	System::Windows::Forms::DataVisualization::Charting::Series^ Polinom = ChartPolinom->Series->Add("SeriesPolinom");
	Polinom->ChartArea = "PolinomAreas";
	Polinom->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
	Polinom->MarkerBorderColor = System::Drawing::Color::Red;
	Polinom->MarkerColor = System::Drawing::Color::Transparent;
	Polinom->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
	Polinom->MarkerSize = 6;
	Polinom->MarkerBorderWidth = 3;
	Polinom->LegendText = "���� ������������";
	ChartPolinom->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Polinom::OnMouseMove);
	ChartPolinom->Click += gcnew System::EventHandler(this, &Polinom::OnClick);

	//������������� �����������
	Nodes = new std::vector<std::array<double, 2>>;
	Difference_Newton = new std::vector<std::vector<double>>();
}

/* ���������� ����� ������������
* System::String^ FILENAME - ��� �����, ��� �������� ��������� ������
* int TypeFunction - ��� �������, ������ ��������� ������� �������� 
*/
void Polinom::PolinomNodes(System::String^ FILENAME, int TypeFunction) {
	//������� ����������� ����� ��������� ����������� 
	for (auto element = ChartPolinom->Series->GetEnumerator(); element->MoveNext();) {	//������� �������� �� �����
		element->Current->Points->Clear();
	}
	Nodes->clear();																		//������� ����� ������������
	Difference_Newton->clear();															//������� ���������� ���������

	//���������� �� ����� ����� ������������;
	System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::OpenOrCreate);				//�������� �����
	System::IO::StreamReader^ Stream = gcnew System::IO::StreamReader(File);												//�������� ����������� ����� ������ �� �����
	array<wchar_t>^ Separator = gcnew array<wchar_t>(1) {' '};																//������ ���������� ���������� ������
	for (double X, Y; !Stream->EndOfStream;)																				//����������, ���� �� ��������� ����� ������
	{
		array<System::String^>^ line = Stream->ReadLine()->Split(Separator, System::StringSplitOptions::RemoveEmptyEntries);	//������ ��������� ������ [������� ������->���������->������� ������] 
		X = System::Convert::ToDouble(line[Element::Argument]);																	//������������� �������� ������� �� String -> double
		//������ ��������� Y ���������� ���� ������������
		if (TypeFunction == Type::DotPolinom) {											//������ ����
			Y = System::Convert::ToDouble(line[Element::Function]);						//������������� ������ ��������� �������� � Y ����������
		}
		else if (TypeFunction == Type::Expansion) {										//���������������
			Y = std::exp(-X);															//��������� �� X
		}
		else if (TypeFunction == Type::Module) {										//������
			Y = std::fabs(X);															//��������� �� X
		}
		else if (TypeFunction == Type::Sine) {											//����������������
			Y = std::sin(X);															//��������� �� X
		}
		Nodes->push_back(std::array<double, 2>{X, Y});									//���������� ����� ������������� � ���������
		ChartPolinom->Series->FindByName("SeriesPolinom")->Points->AddXY(X, Y);			//���������� ����� ������������� �� ������
	}
	Stream->Close();																	//�������� ������ ����������
	delete[] Separator;																	//�������� ��������� ������ ��� �����������

	//���������� ��������� ��� �������� �������
	//��������� ��������� 
	int Size = Nodes->size();															//��������� �������
	Difference_Newton->push_back(std::vector<double>());								//���������� ������, ���������� Fk
	for (int Fx = 0; Fx < Size; Fx++) {													//��������� ���������� Fk
		(*Difference_Newton)[0].push_back((*Nodes)[Fx][Element::Function]);				//Fk - Y ���������� ����� ������������
	}
	//���������� ���������
	//��������� �� ������� � ���� ����������� �������
	//X[degree][defference]; 
	//X10 11 12 -> X20 21 -> X30 
	for (int Degree = 1; Degree < Size; Degree++) {										//Degree - ������� ���������� �������� 									
		(*Difference_Newton).push_back(std::vector<double>());							//������� ��������� �������������� ���������� ��������
		for (int Difference = 0; Difference + Degree < Size; Difference++) {			//Difference - ����� ��������. 
			//���������� ��������� � �����������
			//���������: ������� ������� ������ - ������� �������
			double Numerator = (*Difference_Newton)[Degree - 1][Difference + 1] - (*Difference_Newton)[Degree - 1][Difference], 
				//�����������: X[������� �������� + �����.��������] - X[����.��������]
				Denominator = (*Nodes)[Degree + Difference][Element::Argument] - (*Nodes)[Difference][Element::Argument];		 
			//��������� ��������
			(*Difference_Newton)[Degree].push_back(Numerator / Denominator);
		}
	}
}

/*������������ ����� �����������
* ������������� ������� �������� � ����������� �� ���� ������������ - ��� �������,
* �������������� � ������ �����. � ����������� �� �������, ������������� ������ 
* ���������� ������������ � �������� ����� � �������� �������. 
* 
* unsigned int Seed - ����� ������������
* int Size - ���-�� ���������� ����� ������������ (�� ����, ���������� �� 2)
* int TipeRandom - ��� ������������ ��� ��� ������� 
*/
System::String^ Polinom::RandFunction(unsigned int Seed, int Size, int TipeRandom) {
	System::String^ FILENAME = gcnew System::String("R");								//R - ������ �������� ���������������� �����
	std::mt19937 random(Seed);															//����: ����� ������� (�������� > �����)
	
	//������ ������������
	if (TipeRandom == Type::DotPolinom) {																								//������ ����� �����������
		FILENAME += "D";																												//D - Dot, ������
		FILENAME = System::String::Join("", FILENAME, System::Convert::ToString(Seed), "_", System::Convert::ToString(Size), ".txt");	//�������� ����� �����
		System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::Create);							//�������� �����
		System::IO::StreamWriter^ Stream = gcnew System::IO::StreamWriter(File);														//�������� ����������� ������ �� ������ ���������� �����
		std::uniform_int_distribution<> random_int(-(2 * Size), 2 * Size);																//������������ ����� ����� � ������ ��������������
		for (int row = -Size + 1; row < Size; row++) {																					//��������� ���������������� ��� [X,Y] �� ��������
			Stream->WriteLine("{0} {1}", row, random_int(random));																		//���� ����������� �� X
		}
		Stream->Close();																												//��������� ������
	}
	else {																				//������� ��� ��������
		std::uniform_real_distribution<> random_double;									//������������ �������������� ����� � ������ ��������������
		if (TipeRandom == Type::Expansion) {											//����������������						
			FILENAME += "E";															//E - Exponent, ������
			random_double = std::uniform_real_distribution<>( - 4.0, 4.0);				//��������� ��������
		}
		else if (TipeRandom == Type::Module) {											//������
			FILENAME += "M";															//M - Module, ������
			random_double = std::uniform_real_distribution<>(-1.0, 1.0);				//��������� ��������
		}
		else if (TipeRandom == Type::Sine) {											//�����
			FILENAME += "S";															//S - Sine, ������
			random_double = std::uniform_real_distribution<>(-M_PI, M_PI);				//��������� ��������
		}
		FILENAME = System::String::Join("", FILENAME, System::Convert::ToString(Seed), "_", System::Convert::ToString(Size), ".txt");	//�������� ����� �����
		System::IO::FileStream^ File = gcnew System::IO::FileStream(FILENAME, System::IO::FileMode::Create);							//�������� �����
		System::IO::StreamWriter^ Stream = gcnew System::IO::StreamWriter(File);														//�������� ����������� ������ �� ������ ���������� �����
		std::vector<double> FunctionArg;																								//��������� ��� X �������� F(X)
		for (int row = -Size + 1; row < Size; row++) {																					//��������� ���������������� ���� ��������� X
			FunctionArg.push_back(random_double(random));																				
		}
		std::sort(FunctionArg.begin(), FunctionArg.end());																				//���������� ����������� ����������
		for (int row = 0, Size = FunctionArg.size(); row < Size; row++) {																//������ ��������������� �������� � ����
			Stream->WriteLine("{0}",FunctionArg[row]);																					
		}
		Stream->Close();																												//�������� ������
	}
	return FILENAME;																	//������� ������������ �����
}

//�������
double Polinom::Lagrange(double X) {																	
	double Lagrange = 0;
	auto Node = *Nodes;
	for (int Summary = 0, Size = Nodes->size(); Summary < Size; Summary++) {
		double Numerator = 1,
			Denominator = 1;																			
		for (int Composition = 0; Composition < Size; Composition++) {									//			  m
			if (Summary != Composition)																	//Numerator = �(X - Xj)
				Numerator *= X - Node[Composition][Element::Argument];									//			  j=0,i!=k
		}
		for (int Composition = 0; Composition < Size; Composition++) {									//				m
			if (Summary != Composition)																	//Denominator = �(Xk - Xj)
				Denominator *= Node[Summary][Element::Argument] - Node[Composition][Element::Argument];	//				j=0,i!=k
		}																								//			 m
		Lagrange += Numerator / Denominator * Node[Summary][Element::Function];							//Lagrange = E((Numerator/Denominator) * F(Xk))
	}																									//			 k=0
	return Lagrange;	//������ �������� �������� ��������
}

//������
double Polinom::Newton(double X) {
	double Newton = 0;
	for (int Degree = 0, Size = Nodes->size(); Degree < Size; Degree++) {
		double Composition = 1;													//				i
		for (int Difference = 0; Difference < Degree; Difference++) {			//Composition = �(X - Xj)
			Composition *= X - (*Nodes)[Difference][Element::Argument];			//				j=0
		}																		//		   m
		Newton += Composition * (*Difference_Newton)[Degree][0];				//Newton = E(Composition * Fi0 (���������� �������� �������));
	}																			//		   i=0
	return Newton;		//������ �������� �������� �������
}

/*���������� �������� 
* �������� ������ ������� ������������ �������� � �������. � ��� �� � ����������� �� ����
* ������� ������ � ��� ������. ��� �� ������� ��������� �������������� ���������� �������
* ������������ ���������� �������� �� ������� F(X)
* int TypeFunction - ��� �������
*/
void Polinom::FunctPolinom(int TypeFunction) {
	double MaxDeviation = 0,					//������������ ���������� ������� �� F(X)
		MaxCordX,								//���������� X ������������� ���������� 
		MaxFunctionY,							//���������� Y  ������������� ���������� ��� F(X):
		MaxPolinomY;							//���������� Y  ������������� ���������� ��� ��������
	//���������� ������� �������
	//�������� ����������� �� �����������:
	for (double X = (*Nodes)[0][Element::Argument],					//��������� ������� - ����� ����������� ��������
		MaxX = (*Nodes)[Nodes->size() - 1][Element::Argument];		//�������� �������� ����� ������������ ��������
		X <= MaxX + 0.01; X += 0.01) {								//��� �������
		double PolinomY = Lagrange(X);								//������������ �������� �������� � �����
		//���� �������� �٨ � ������ 
		if (TypeFunction != Type::DotPolinom) {						
			double FunctionY,										//�������� ������� � �����
				Deviation;											//����������
			//���ר� �������� ������� � �����
			if (TypeFunction == Type::Expansion) {
				FunctionY = std::exp(-X);
			}
			else if (TypeFunction == Type::Module) {
				FunctionY = std::fabs(X);
			}
			else if (TypeFunction == Type::Sine) {
				FunctionY = std::sin(X);
			}
			//���������� ������������ ����������
			Deviation = std::fabs(std::fabs(PolinomY) - std::fabs(FunctionY));	//���������� ����������
			if (Deviation > MaxDeviation) {										//���������� > �������������
				MaxDeviation = Deviation;										//��������� ��� �����������
				MaxCordX = X;													//������� ��� �������������� ����������
				MaxFunctionY = FunctionY;
				MaxPolinomY = PolinomY;
			}
			ChartPolinom->Series->FindByName("SeriesFunction")->Points->AddXY(X, FunctionY);	//�������� ����� �������
		}
		ChartPolinom->Series->FindByName("SeriesLagrange")->Points->AddXY(X, PolinomY);			//�������� ����� �������� ��������
		ChartPolinom->Series->FindByName("SeriesNewton")->Points->AddXY(X, Newton(X));			//�������� ����� �������� �������
	}
	//����������� ������� ������������� ����������;
	if (MaxDeviation != 0) {
		Deviation->Text = System::Convert::ToString(MaxDeviation);								//����������� ���������� �� ������� ������
		System::Windows::Forms::DataVisualization::Charting::DataPointCollection^ 
			PointsDeviation = ChartPolinom->Series->FindByName("SeriesDeviation")->Points;		//�������� ����� ������� �������� [�������]
		PointsDeviation->AddXY(MaxCordX, MaxFunctionY);											//�������� ��������������� �������� ����� �� ������� F(X)
		PointsDeviation->AddXY(MaxCordX, MaxPolinomY);											//�������� ��������������� �������� ����� �� ��������
	}
}

//����� ��������
System::Windows::Forms::DataVisualization::Charting::Chart^ Polinom::GetChart() {
	return ChartPolinom;
}

//���������� ����������� ���� ������ ������� ��������� ��������
void Polinom::OnMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	//������ ������ ������������ ��������� ������ � ���� �����, ����������� Y. ������ �� ��������� �� ������� ���������
	ChartPolinom->ChartAreas["PolinomAreas"]->CursorX->SetCursorPixelPosition(System::Drawing::PointF(e->X, e->Y), true);	
	//���������� ������� X ����������� ������� ������������� �������� ������� ��������� [���������� ��������]
	double pX = ChartPolinom->ChartAreas["PolinomAreas"]->CursorX->Position;							
	//����� X ��������� ���������� � ������� ����������
	OutputX->Text = System::Convert::ToString(pX);
}

//���ר� �������� ��������� �� ������ ����
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
