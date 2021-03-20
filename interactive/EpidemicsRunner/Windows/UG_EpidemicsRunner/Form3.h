#pragma once

#include "../../../../models/sir.h"
#include "../../../../models/seird.h"
#include "../../../../models/writer.h"
#include "plotter.h"
#include "../../../../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../../../../ConstrainedOptimization/core/parameters.h"
#include<limits>
#include<vector>
#include <string>
#include "utility.h"
#include "Form4.h"
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
	/// Zusammenfassung für Form3
	/// </summary>
	public ref class Form3 : public System::Windows::Forms::Form
	{
	public:
		Form3(void)
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
		~Form3()
		{
			delete user_datapoints;
			delete user_timepoints;
			delete user_rows;
			delete user_names;
			delete user_cols;
			if (components)
			{
				delete components;
			}
		}

	public: std::vector<double>* user_datapoints;
	public: std::vector<double>* user_timepoints;
	public: std::vector<std::string>* user_names;
	public: int* user_rows;
	public: int* user_cols;
	//private: System::Windows::Forms::DataVisualization::Charting::Series^ additional_series;

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
	private: System::Windows::Forms::NumericUpDown^ theta_input;


	private: System::Windows::Forms::NumericUpDown^ kappa_input;



	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ initial_deaths;

	private: System::Windows::Forms::NumericUpDown^ initial_recovered;

	private: System::Windows::Forms::NumericUpDown^ initial_infected;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::NumericUpDown^ initial_exposed;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::NumericUpDown^ pp_input;

	private: System::Windows::Forms::NumericUpDown^ qq_input;
	private: System::Windows::Forms::NumericUpDown^ stepsize_input;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Button^ SaveImageButton;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ featuresToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadcsvDataToolStripMenuItem;
	private: System::Windows::Forms::Button^ para_estimator_button;




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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->stepsize_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->initial_exposed = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->initial_infected = (gcnew System::Windows::Forms::NumericUpDown());
			this->pp_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->qq_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->initial_deaths = (gcnew System::Windows::Forms::NumericUpDown());
			this->initial_recovered = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->initial_susceptibles = (gcnew System::Windows::Forms::NumericUpDown());
			this->theta_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->kappa_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->alpha_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->SaveImageButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->featuresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadcsvDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->para_estimator_button = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepsize_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_exposed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(18, 666);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(262, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form3::button1_Click);
			this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form3::button1_MouseClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(309, 666);
			this->button2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(112, 35);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form3::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->stepsize_input);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->initial_exposed);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->initial_infected);
			this->groupBox1->Controls->Add(this->pp_input);
			this->groupBox1->Controls->Add(this->qq_input);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->initial_deaths);
			this->groupBox1->Controls->Add(this->initial_recovered);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->initial_susceptibles);
			this->groupBox1->Controls->Add(this->theta_input);
			this->groupBox1->Controls->Add(this->kappa_input);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->alpha_input);
			this->groupBox1->Location = System::Drawing::Point(46, 68);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupBox1->Size = System::Drawing::Size(446, 568);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Parameters";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form3::groupBox1_Enter);
			// 
			// stepsize_input
			// 
			this->stepsize_input->DecimalPlaces = 6;
			this->stepsize_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->stepsize_input->Location = System::Drawing::Point(159, 505);
			this->stepsize_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->stepsize_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->stepsize_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->stepsize_input->Name = L"stepsize_input";
			this->stepsize_input->Size = System::Drawing::Size(180, 26);
			this->stepsize_input->TabIndex = 21;
			this->stepsize_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 131072 });
			this->stepsize_input->ValueChanged += gcnew System::EventHandler(this, &Form3::stepsize_input_ValueChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(9, 508);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(106, 20);
			this->label11->TabIndex = 20;
			this->label11->Text = L"RK4 Stepsize";
			// 
			// initial_exposed
			// 
			this->initial_exposed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_exposed->Location = System::Drawing::Point(159, 291);
			this->initial_exposed->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initial_exposed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_exposed->Name = L"initial_exposed";
			this->initial_exposed->Size = System::Drawing::Size(180, 26);
			this->initial_exposed->TabIndex = 19;
			this->initial_exposed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2714, 0, 0, 0 });
			this->initial_exposed->ValueChanged += gcnew System::EventHandler(this, &Form3::initial_exposed_ValueChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(9, 294);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(117, 20);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Initial_Exposed";
			// 
			// initial_infected
			// 
			this->initial_infected->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_infected->Location = System::Drawing::Point(159, 338);
			this->initial_infected->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initial_infected->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_infected->Name = L"initial_infected";
			this->initial_infected->Size = System::Drawing::Size(180, 26);
			this->initial_infected->TabIndex = 11;
			this->initial_infected->ValueChanged += gcnew System::EventHandler(this, &Form3::initial_infected_ValueChanged);
			// 
			// pp_input
			// 
			this->pp_input->DecimalPlaces = 4;
			this->pp_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->pp_input->Location = System::Drawing::Point(159, 191);
			this->pp_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pp_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->pp_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
			this->pp_input->Name = L"pp_input";
			this->pp_input->Size = System::Drawing::Size(180, 26);
			this->pp_input->TabIndex = 17;
			this->pp_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 14, 0, 0, 0 });
			this->pp_input->ValueChanged += gcnew System::EventHandler(this, &Form3::pp_input_ValueChanged);
			// 
			// qq_input
			// 
			this->qq_input->DecimalPlaces = 4;
			this->qq_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->qq_input->Location = System::Drawing::Point(159, 149);
			this->qq_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->qq_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->qq_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
			this->qq_input->Name = L"qq_input";
			this->qq_input->Size = System::Drawing::Size(180, 26);
			this->qq_input->TabIndex = 16;
			this->qq_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->qq_input->ValueChanged += gcnew System::EventHandler(this, &Form3::qq_input_ValueChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(9, 191);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(27, 20);
			this->label9->TabIndex = 15;
			this->label9->Text = L"pp";
			this->label9->Click += gcnew System::EventHandler(this, &Form3::label9_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(9, 149);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(27, 20);
			this->label8->TabIndex = 14;
			this->label8->Text = L"qq";
			// 
			// initial_deaths
			// 
			this->initial_deaths->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_deaths->Location = System::Drawing::Point(159, 426);
			this->initial_deaths->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initial_deaths->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_deaths->Name = L"initial_deaths";
			this->initial_deaths->Size = System::Drawing::Size(180, 26);
			this->initial_deaths->TabIndex = 13;
			this->initial_deaths->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 72, 0, 0, 0 });
			this->initial_deaths->ValueChanged += gcnew System::EventHandler(this, &Form3::initial_deaths_ValueChanged);
			// 
			// initial_recovered
			// 
			this->initial_recovered->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_recovered->Location = System::Drawing::Point(159, 385);
			this->initial_recovered->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initial_recovered->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->initial_recovered->Name = L"initial_recovered";
			this->initial_recovered->Size = System::Drawing::Size(180, 26);
			this->initial_recovered->TabIndex = 12;
			this->initial_recovered->ValueChanged += gcnew System::EventHandler(this, &Form3::initial_recovered_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(9, 429);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(102, 20);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Initial Deaths";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 254);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(141, 20);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Initial Susceptibles";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 388);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(127, 20);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Initial Recovered";
			this->label5->Click += gcnew System::EventHandler(this, &Form3::label5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 342);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(109, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Initial Infected";
			this->label4->Click += gcnew System::EventHandler(this, &Form3::label4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 112);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"theta";
			this->label3->Click += gcnew System::EventHandler(this, &Form3::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 72);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label2->Size = System::Drawing::Size(53, 20);
			this->label2->TabIndex = 5;
			this->label2->Text = L"kappa";
			// 
			// initial_susceptibles
			// 
			this->initial_susceptibles->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->initial_susceptibles->Location = System::Drawing::Point(159, 251);
			this->initial_susceptibles->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initial_susceptibles->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7000000, 0, 0, 0 });
			this->initial_susceptibles->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->initial_susceptibles->Name = L"initial_susceptibles";
			this->initial_susceptibles->Size = System::Drawing::Size(180, 26);
			this->initial_susceptibles->TabIndex = 4;
			this->initial_susceptibles->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 753056, 0, 0, 0 });
			this->initial_susceptibles->ValueChanged += gcnew System::EventHandler(this, &Form3::initial_susceptibles_ValueChanged);
			// 
			// theta_input
			// 
			this->theta_input->DecimalPlaces = 8;
			this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->theta_input->Location = System::Drawing::Point(159, 109);
			this->theta_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->theta_input->Name = L"theta_input";
			this->theta_input->Size = System::Drawing::Size(180, 26);
			this->theta_input->TabIndex = 3;
			this->theta_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1720495929, 115473, 0, 1376256 });
			this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form3::tau_input_ValueChanged);
			// 
			// kappa_input
			// 
			this->kappa_input->DecimalPlaces = 8;
			this->kappa_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->kappa_input->Location = System::Drawing::Point(159, 69);
			this->kappa_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->kappa_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->kappa_input->Name = L"kappa_input";
			this->kappa_input->Size = System::Drawing::Size(180, 26);
			this->kappa_input->TabIndex = 2;
			this->kappa_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { -495194266, 96608, 0, 1376256 });
			this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form3::theta_input_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 32);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"alpha";
			// 
			// alpha_input
			// 
			this->alpha_input->DecimalPlaces = 9;
			this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->alpha_input->Location = System::Drawing::Point(159, 29);
			this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->alpha_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->alpha_input->Name = L"alpha_input";
			this->alpha_input->Size = System::Drawing::Size(180, 26);
			this->alpha_input->TabIndex = 0;
			this->alpha_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1720495929, 115473, 0, 1376256 });
			this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form3::numericUpDown1_ValueChanged);
			// 
			// chart1
			// 
			chartArea2->AxisX->Title = L"Time";
			chartArea2->AxisY->Title = L"Amount";
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(524, 68);
			this->chart1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series6->Legend = L"Legend1";
			series6->Name = L"Susceptibles";
			series6->ShadowColor = System::Drawing::Color::Blue;
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series7->Legend = L"Legend1";
			series7->Name = L"Infected";
			series7->ShadowColor = System::Drawing::Color::Red;
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series8->Legend = L"Legend1";
			series8->Name = L"Deaths";
			series8->ShadowColor = System::Drawing::Color::Black;
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Legend = L"Legend1";
			series9->Name = L"Recovered";
			series9->ShadowColor = System::Drawing::Color::Maroon;
			series10->ChartArea = L"ChartArea1";
			series10->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series10->Legend = L"Legend1";
			series10->Name = L"Exposed";
			this->chart1->Series->Add(series6);
			this->chart1->Series->Add(series7);
			this->chart1->Series->Add(series8);
			this->chart1->Series->Add(series9);
			this->chart1->Series->Add(series10);
			this->chart1->Size = System::Drawing::Size(1350, 840);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			title2->Name = L"Result of SRI Model";
			this->chart1->Titles->Add(title2);
			this->chart1->Click += gcnew System::EventHandler(this, &Form3::chart1_Click);
			// 
			// SaveImageButton
			// 
			this->SaveImageButton->Location = System::Drawing::Point(1740, 929);
			this->SaveImageButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->SaveImageButton->Name = L"SaveImageButton";
			this->SaveImageButton->Size = System::Drawing::Size(112, 35);
			this->SaveImageButton->TabIndex = 4;
			this->SaveImageButton->Text = L"Save Image";
			this->SaveImageButton->UseVisualStyleBackColor = true;
			this->SaveImageButton->Click += gcnew System::EventHandler(this, &Form3::SaveImageButton_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->featuresToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1870, 33);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// featuresToolStripMenuItem
			// 
			this->featuresToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadcsvDataToolStripMenuItem });
			this->featuresToolStripMenuItem->Name = L"featuresToolStripMenuItem";
			this->featuresToolStripMenuItem->Size = System::Drawing::Size(94, 29);
			this->featuresToolStripMenuItem->Text = L"Features";
			// 
			// loadcsvDataToolStripMenuItem
			// 
			this->loadcsvDataToolStripMenuItem->Name = L"loadcsvDataToolStripMenuItem";
			this->loadcsvDataToolStripMenuItem->Size = System::Drawing::Size(299, 34);
			this->loadcsvDataToolStripMenuItem->Text = L"Load experimental data";
			this->loadcsvDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form3::loadcsvDataToolStripMenuItem_Click);
			// 
			// para_estimator_button
			// 
			this->para_estimator_button->Location = System::Drawing::Point(18, 731);
			this->para_estimator_button->Name = L"para_estimator_button";
			this->para_estimator_button->Size = System::Drawing::Size(262, 40);
			this->para_estimator_button->TabIndex = 6;
			this->para_estimator_button->Text = L"Optimize";
			this->para_estimator_button->UseVisualStyleBackColor = true;
			this->para_estimator_button->Click += gcnew System::EventHandler(this, &Form3::para_estimator_button_Click_1);
			// 
			// Form3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1870, 983);
			this->Controls->Add(this->para_estimator_button);
			this->Controls->Add(this->SaveImageButton);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form3";
			this->Text = L"UG Epidemics: SEIRD Model";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form3::Form3_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form3::Form3_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepsize_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_exposed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form3_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		//MessageBox::Show(L"You clicked the Cancel button! It worked!");
		Application::Exit();
	}
	private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		plot_on_keypress();
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
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double alpha = System::Decimal::ToDouble(this->alpha_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);

		   double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);

		   ug::epi::SEIRD<std::vector<double>> seird_model(alpha, kappa, theta,qq,pp);
		   
		   seird_model.change_step_size(stepsize);

		   std::vector<double> u0 = { System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_exposed->Value),System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };
		   double t_start = 0;
		   double t_end = 42;

		   auto [timepoints, data] = seird_model.run(t_start, u0, t_end);

		   auto names = seird_model.names;


		   System::String^ converted_name;
		   int iter = 0;
		   ug::epi::Plotter<decltype(this), std::vector<double>> plotter;
		   
		   for (auto& x : names) {
			   converted_name = gcnew String(names[iter].c_str());
			   this->chart1->Series[converted_name]->Points->Clear();
			   iter++;
		   }
		   if (user_datapoints != nullptr && user_names != nullptr && user_cols != nullptr) {
			   for (int i = 1; i < user_names->size(); i++) {
				   converted_name = gcnew String((*user_names)[i].c_str());
				   this->chart1->Series[converted_name]->Points->Clear();
			   }
		   }

		   this->chart1->Refresh();
		   iter = 0;
		   for (auto& x : names) {
			   converted_name = gcnew String(names[iter].c_str());
			   plotter.plot(this, timepoints, data, converted_name, 5, iter);
			   iter++;
		   }
		   ug::epi::write_data("../EpidemicsRunnerOutput", "sri_output.txt", timepoints, data, seird_model.names);
		   if (user_datapoints!= nullptr && user_names!=nullptr && user_cols!= nullptr) {
			   for (int i = 1; i <user_names->size();i++) {
				   converted_name = gcnew String((*user_names)[i].c_str());
				   plotter.plot(this, user_datapoints, converted_name, user_names->size(), i);
			   }

		   }
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
private: System::Void label9_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void stepsize_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void qq_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void pp_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_exposed_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void SaveImageButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::SaveFileDialog saveFileDialog;
	saveFileDialog.Filter="emf files (*.emf)|*.emf|All files (*.*)|*.*";
	saveFileDialog.FilterIndex = 2;

	if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		auto stream = saveFileDialog.OpenFile();
		switch (saveFileDialog.FilterIndex)
		{
		case 1:
			this->chart1->SaveImage(stream, ChartImageFormat::Emf);
			break;
		}
		stream->Close();
	}
//	
	//this->chart1->SaveImage(System::IO::Path::GetFullPath("chart1.emf"), ChartImageFormat::Emf);
}


private: System::Void loadcsvDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	ug::epi::load_csv_data_on_click(this,5); //5 represents the number of prior plotted lines
	plot_on_keypress();

}
private: System::Void Form3_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	Application::Exit();
}
private: System::Void para_estimator_button_Click_1(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		Form4^ form = gcnew Form4;
		form->Show();
}
};
}
