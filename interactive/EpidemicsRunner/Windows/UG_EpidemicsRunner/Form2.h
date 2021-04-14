#pragma once

#include "../../../../models/sir.h"
#include "../../../../models/writer.h"
#include "plotter.h"

//https://www.visualcplusdotnet.com/visualcplusdotnet21d.html

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Zusammenfassung für Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::NumericUpDown^ alpha_input;


	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Label^ label4;
	public:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ initial_susceptibles;

	private: System::Windows::Forms::NumericUpDown^ tau_input;

	private: System::Windows::Forms::NumericUpDown^ theta_input;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ initial_deaths;

	private: System::Windows::Forms::NumericUpDown^ initial_recovered;

	private: System::Windows::Forms::NumericUpDown^ initial_infected;

	private: System::Windows::Forms::Label^ label7;



	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->initial_deaths = (gcnew System::Windows::Forms::NumericUpDown());
			this->initial_recovered = (gcnew System::Windows::Forms::NumericUpDown());
			this->initial_infected = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->initial_susceptibles = (gcnew System::Windows::Forms::NumericUpDown());
			this->tau_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->theta_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->alpha_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tau_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 279);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(175, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
			this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form2::button1_MouseClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(206, 279);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form2::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->initial_deaths);
			this->groupBox1->Controls->Add(this->initial_recovered);
			this->groupBox1->Controls->Add(this->initial_infected);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->initial_susceptibles);
			this->groupBox1->Controls->Add(this->tau_input);
			this->groupBox1->Controls->Add(this->theta_input);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->alpha_input);
			this->groupBox1->Location = System::Drawing::Point(31, 44);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(297, 229);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Parameters";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form2::groupBox1_Enter);
			// 
			// initial_deaths
			// 
			this->initial_deaths->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_deaths->Location = System::Drawing::Point(106, 209);
			this->initial_deaths->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_deaths->Name = L"initial_deaths";
			this->initial_deaths->Size = System::Drawing::Size(120, 20);
			this->initial_deaths->TabIndex = 13;
			this->initial_deaths->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 72, 0, 0, 0 });
			this->initial_deaths->ValueChanged += gcnew System::EventHandler(this, &Form2::initial_deaths_ValueChanged);
			// 
			// initial_recovered
			// 
			this->initial_recovered->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_recovered->Location = System::Drawing::Point(106, 182);
			this->initial_recovered->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_recovered->Name = L"initial_recovered";
			this->initial_recovered->Size = System::Drawing::Size(120, 20);
			this->initial_recovered->TabIndex = 12;
			this->initial_recovered->ValueChanged += gcnew System::EventHandler(this, &Form2::initial_recovered_ValueChanged);
			// 
			// initial_infected
			// 
			this->initial_infected->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_infected->Location = System::Drawing::Point(106, 156);
			this->initial_infected->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_infected->Name = L"initial_infected";
			this->initial_infected->Size = System::Drawing::Size(120, 20);
			this->initial_infected->TabIndex = 11;
			this->initial_infected->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2714, 0, 0, 0 });
			this->initial_infected->ValueChanged += gcnew System::EventHandler(this, &Form2::initial_infected_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 211);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(68, 13);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Initial Deaths";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 129);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(94, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Initial Susceptibles";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 184);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(87, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Initial Recovered";
			this->label5->Click += gcnew System::EventHandler(this, &Form2::label5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 158);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(73, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Initial Infected";
			this->label4->Click += gcnew System::EventHandler(this, &Form2::label4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 73);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"tau";
			this->label3->Click += gcnew System::EventHandler(this, &Form2::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 47);
			this->label2->Name = L"label2";
			this->label2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label2->Size = System::Drawing::Size(31, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"theta";
			// 
			// initial_susceptibles
			// 
			this->initial_susceptibles->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_susceptibles->Location = System::Drawing::Point(106, 127);
			this->initial_susceptibles->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7000000, 0, 0, 0 });
			this->initial_susceptibles->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->initial_susceptibles->Name = L"initial_susceptibles";
			this->initial_susceptibles->Size = System::Drawing::Size(120, 20);
			this->initial_susceptibles->TabIndex = 4;
			this->initial_susceptibles->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 753056, 0, 0, 0 });
			this->initial_susceptibles->ValueChanged += gcnew System::EventHandler(this, &Form2::initial_susceptibles_ValueChanged);
			// 
			// tau_input
			// 
			this->tau_input->DecimalPlaces = 8;
			this->tau_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->tau_input->Location = System::Drawing::Point(106, 71);
			this->tau_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->tau_input->Name = L"tau_input";
			this->tau_input->Size = System::Drawing::Size(120, 20);
			this->tau_input->TabIndex = 3;
			this->tau_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1720495929, 115473, 0, 1376256 });
			this->tau_input->ValueChanged += gcnew System::EventHandler(this, &Form2::tau_input_ValueChanged);
			// 
			// theta_input
			// 
			this->theta_input->DecimalPlaces = 8;
			this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->theta_input->Location = System::Drawing::Point(106, 45);
			this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->theta_input->Name = L"theta_input";
			this->theta_input->Size = System::Drawing::Size(120, 20);
			this->theta_input->TabIndex = 2;
			this->theta_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { -495194266, 96608, 0, 1376256 });
			this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form2::theta_input_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"alpha";
			// 
			// alpha_input
			// 
			this->alpha_input->DecimalPlaces = 8;
			this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->alpha_input->Location = System::Drawing::Point(106, 19);
			this->alpha_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->alpha_input->Name = L"alpha_input";
			this->alpha_input->Size = System::Drawing::Size(120, 20);
			this->alpha_input->TabIndex = 0;
			this->alpha_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1720495929, 115473, 0, 1376256 });
			this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form2::numericUpDown1_ValueChanged);
			// 
			// chart1
			// 
			chartArea1->AxisX->Title = L"Time";
			chartArea1->AxisY->Title = L"Amount";
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(349, 44);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Susceptibles";
			series1->ShadowColor = System::Drawing::Color::Blue;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend1";
			series2->Name = L"Infected";
			series2->ShadowColor = System::Drawing::Color::Red;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Legend = L"Legend1";
			series3->Name = L"Deaths";
			series3->ShadowColor = System::Drawing::Color::Black;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Legend = L"Legend1";
			series4->Name = L"Recovered";
			series4->ShadowColor = System::Drawing::Color::Maroon;
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Size = System::Drawing::Size(900, 546);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			title1->Name = L"Result of SRI Model";
			this->chart1->Titles->Add(title1);
			this->chart1->Click += gcnew System::EventHandler(this, &Form2::chart1_Click);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1247, 639);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"Form2";
			this->Text = L"UG Epidemics: SIR Model";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form2::Form2_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tau_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form2_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		//MessageBox::Show(L"You clicked the Cancel button! It worked!");
		Application::Exit();
	}
	private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {


	}
	private: System::Void Deutsch_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}


private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		plot_on_keypress();
		/*
		double tau = System::Decimal::ToDouble(this->tau_input->Value);
		double theta = System::Decimal::ToDouble(this->theta_input->Value);
		double alpha = System::Decimal::ToDouble(this->alpha_input->Value);

		ug::epi::SIR<std::vector<double>> sir_model(tau, alpha, theta);

		std::vector<double> u0 = { System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };
		double t_start = 0;
		double t_end = 42;

		auto [timepoints, data] = sir_model.run(t_start, u0, t_end);

		auto names = sir_model.names;
		

		System::String^ converted_name;
		int iter = 0;
		ug::epi::Plotter<decltype(this), std::vector<double>> plotter;
		
		for (auto& x : names) {
			converted_name = gcnew String(names[iter].c_str());
			this->chart1->Series[converted_name]->Points->Clear();
			iter++;
		}
		this->chart1->Refresh();
		iter = 0;
		for (auto& x : names) {
			converted_name=gcnew String(names[iter].c_str());
			plotter.plot(this, timepoints, data, converted_name, 4, iter);
			iter++;
		}
		*/
		//auto g1=this->CreateGraphics();		
		
		//


		//	g1->DrawEllipse(Pens::Black, 150, 20, 50, 50);




			/*DataPointCollection^ datapoints;
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				15));
				*/

				//	this->chart1->Series["Series1"]->Points->DataBindXY(datapoints,datapoints);

				//	this->chart1->Series["Series1"]->Points->Add(dataPoint1);
				//	this->chart1->Series["Series1"]->Points->Add(dataPoint2);
				//	ug::epi::write_data("../", "temp.txt", timepoints, data, sir_model.names,"#","");
				//	system("python creategraph");

		//plotter.plot(g1, timepoints, data,4,0);

	}
private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}



	   void plot_on_keypress() {
		   double tau = System::Decimal::ToDouble(this->tau_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double alpha = System::Decimal::ToDouble(this->alpha_input->Value);

		   ug::epi::SIR<std::vector<double>> sir_model(alpha, tau, theta);
		   sir_model.change_step_size(0.25);

		   std::vector<double> u0 = { System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };
		   double t_start = 0;
		   double t_end = 42;

		   auto [timepoints, data] = sir_model.run(t_start, u0, t_end);

		   auto names = sir_model.names;


		   System::String^ converted_name;
		   int iter = 0;
		   ug::epi::Plotter<decltype(this), std::vector<double>> plotter;
		   
		   for (auto& x : names) {
			   converted_name = gcnew String(names[iter].c_str());
			   this->chart1->Series[converted_name]->Points->Clear();
			   iter++;
		   }
		   this->chart1->Refresh();
		   iter = 0;
		   for (auto& x : names) {
			   converted_name = gcnew String(names[iter].c_str());
			   plotter.plot(this, timepoints, data, converted_name, 4, iter);
			   iter++;
		   }
		   ug::epi::write_data("../EpidemicsRunnerOutput", "sri_output.txt", timepoints, data, sir_model.names);
	   }

private: System::Void theta_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void tau_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_susceptibles_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_infected_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_recovered_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_deaths_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void Form2_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	Application::Exit();
}
};
}
