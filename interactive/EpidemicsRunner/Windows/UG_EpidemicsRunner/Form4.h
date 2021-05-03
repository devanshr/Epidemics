#pragma once

#include "Form3.h"
#include "Form5.h"
#include "Form6.h"
#include "Form7.h"
#include "plotter.h"
#include<limits>
#include<vector>
#include <string>
#include "../../../../models/seird.h"
#include "../../../../models/writer.h"
#include "../../../../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../../../../ConstrainedOptimization/core/parameters.h"


namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form4
	/// </summary>
	public ref class Form4 : public System::Windows::Forms::Form
	{
	public:
		Form4(void)
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
		~Form4()
		{
			delete user_selected_optimization_path;
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

	protected:




	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::CheckBox^ pp_check;
	private: System::Windows::Forms::CheckBox^ alpha_check;
	private: System::Windows::Forms::CheckBox^ qq_check;
	private: System::Windows::Forms::CheckBox^ kappa_check;
	private: System::Windows::Forms::CheckBox^ theta_check;
	private: System::Windows::Forms::NumericUpDown^ pp_input;

	private: System::Windows::Forms::NumericUpDown^ qq_input;

	private: System::Windows::Forms::NumericUpDown^ theta_input;

	private: System::Windows::Forms::NumericUpDown^ kappa_input;

	private: System::Windows::Forms::NumericUpDown^ alpha_input;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ File_strip_menu;
	private: System::Windows::Forms::ToolStripMenuItem^ loadFileToolStripMenuItem;
	private: System::Windows::Forms::Button^ cancel_button;

	private: double alpha_upper_input;
	private: double alpha_lower_input;
	private: double kappa_upper_input;
	private: double kappa_lower_input;
	private: double theta_upper_input;
	private: double theta_lower_input;
	private: double qq_upper_input;
	private: double qq_lower_input;
	private: double pp_upper_input;
	private: double pp_lower_input;

	//PSO settings
	private: int max_iter = 20;
	private: int no_particles = 32;
	private: int no_groups = 4;

	//NEwton Settings
	private: double convergence_parameter;

	private: std::string* user_selected_optimization_path;

	private: System::Windows::Forms::Button^ Optimize_button;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ t_start_input;
	private: System::Windows::Forms::NumericUpDown^ t_end_input;

	private: System::Windows::Forms::NumericUpDown^ stepsize_input;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::NumericUpDown^ initial_exposed;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::NumericUpDown^ initial_infected;
	private: System::Windows::Forms::NumericUpDown^ initial_deaths;
	private: System::Windows::Forms::NumericUpDown^ initial_recovered;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ initial_susceptibles;
	public: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ pso_optimize_button;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsForPSOToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
private: System::Windows::Forms::ToolStripMenuItem^ settingForGaussNewtonToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ loadExperimentalDatatToolStripMenuItem;






	public:
	private:






	


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;



	private: System::Void InitializeComponent() {
		System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
		System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
		System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
		System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->pp_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->qq_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->theta_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->kappa_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->alpha_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->pp_check = (gcnew System::Windows::Forms::CheckBox());
		this->alpha_check = (gcnew System::Windows::Forms::CheckBox());
		this->qq_check = (gcnew System::Windows::Forms::CheckBox());
		this->kappa_check = (gcnew System::Windows::Forms::CheckBox());
		this->theta_check = (gcnew System::Windows::Forms::CheckBox());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->File_strip_menu = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->loadExperimentalDatatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->settingsForPSOToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->settingForGaussNewtonToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->cancel_button = (gcnew System::Windows::Forms::Button());
		this->Optimize_button = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->t_start_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->t_end_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->stepsize_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->initial_exposed = (gcnew System::Windows::Forms::NumericUpDown());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->initial_infected = (gcnew System::Windows::Forms::NumericUpDown());
		this->initial_deaths = (gcnew System::Windows::Forms::NumericUpDown());
		this->initial_recovered = (gcnew System::Windows::Forms::NumericUpDown());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->initial_susceptibles = (gcnew System::Windows::Forms::NumericUpDown());
		this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		this->pso_optimize_button = (gcnew System::Windows::Forms::Button());
		this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		this->groupBox1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->BeginInit();fsh
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->BeginInit();
		this->menuStrip1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->t_start_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->t_end_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepsize_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_exposed))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
		this->SuspendLayout();
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->pp_input);
		this->groupBox1->Controls->Add(this->qq_input);
		this->groupBox1->Controls->Add(this->theta_input);
		this->groupBox1->Controls->Add(this->kappa_input);
		this->groupBox1->Controls->Add(this->alpha_input);
		this->groupBox1->Controls->Add(this->pp_check);
		this->groupBox1->Controls->Add(this->alpha_check);
		this->groupBox1->Controls->Add(this->qq_check);
		this->groupBox1->Controls->Add(this->kappa_check);
		this->groupBox1->Controls->Add(this->theta_check);
		this->groupBox1->Location = System::Drawing::Point(12, 63);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(248, 246);
		this->groupBox1->TabIndex = 5;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Parameters";
		// 
		// pp_input
		// 
		this->pp_input->DecimalPlaces = 4;
		this->pp_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->pp_input->Location = System::Drawing::Point(104, 212);
		this->pp_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->pp_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->pp_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->pp_input->Name = L"pp_input";
		this->pp_input->Size = System::Drawing::Size(130, 20);
		this->pp_input->TabIndex = 15;
		this->pp_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->pp_input->ValueChanged += gcnew System::EventHandler(this, &Form4::pp_input_ValueChanged);
		// 
		// qq_input
		// 
		this->qq_input->DecimalPlaces = 4;
		this->qq_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->qq_input->Location = System::Drawing::Point(104, 171);
		this->qq_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->qq_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->qq_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->qq_input->Name = L"qq_input";
		this->qq_input->Size = System::Drawing::Size(130, 20);
		this->qq_input->TabIndex = 14;
		this->qq_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->qq_input->ValueChanged += gcnew System::EventHandler(this, &Form4::qq_input_ValueChanged);
		// 
		// theta_input
		// 
		this->theta_input->DecimalPlaces = 8;
		this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->theta_input->Location = System::Drawing::Point(104, 131);
		this->theta_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->theta_input->Name = L"theta_input";
		this->theta_input->Size = System::Drawing::Size(130, 20);
		this->theta_input->TabIndex = 13;
		this->theta_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form4::theta_input_ValueChanged);
		// 
		// kappa_input
		// 
		this->kappa_input->DecimalPlaces = 8;
		this->kappa_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->kappa_input->Location = System::Drawing::Point(104, 87);
		this->kappa_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->kappa_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->kappa_input->Name = L"kappa_input";
		this->kappa_input->Size = System::Drawing::Size(130, 20);
		this->kappa_input->TabIndex = 12;
		this->kappa_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form4::kappa_input_ValueChanged);
		// 
		// alpha_input
		// 
		this->alpha_input->DecimalPlaces = 9;
		this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->alpha_input->Location = System::Drawing::Point(104, 43);
		this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->alpha_input->Name = L"alpha_input";
		this->alpha_input->Size = System::Drawing::Size(130, 20);
		this->alpha_input->TabIndex = 11;
		this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form4::alpha_input_ValueChanged);
		// 
		// pp_check
		// 
		this->pp_check->AutoSize = true;
		this->pp_check->Location = System::Drawing::Point(6, 212);
		this->pp_check->Name = L"pp_check";
		this->pp_check->Size = System::Drawing::Size(38, 17);
		this->pp_check->TabIndex = 10;
		this->pp_check->Text = L"pp";
		this->pp_check->UseVisualStyleBackColor = true;
		this->pp_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::pp_check_CheckedChanged);
		// 
		// alpha_check
		// 
		this->alpha_check->AutoSize = true;
		this->alpha_check->Location = System::Drawing::Point(6, 43);
		this->alpha_check->Name = L"alpha_check";
		this->alpha_check->Size = System::Drawing::Size(52, 17);
		this->alpha_check->TabIndex = 6;
		this->alpha_check->Text = L"alpha";
		this->alpha_check->UseVisualStyleBackColor = true;
		this->alpha_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::alpha_check_CheckedChanged);
		// 
		// qq_check
		// 
		this->qq_check->AutoSize = true;
		this->qq_check->Location = System::Drawing::Point(6, 171);
		this->qq_check->Name = L"qq_check";
		this->qq_check->Size = System::Drawing::Size(38, 17);
		this->qq_check->TabIndex = 9;
		this->qq_check->Text = L"qq";
		this->qq_check->UseVisualStyleBackColor = true;
		this->qq_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::qq_check_CheckedChanged);
		// 
		// kappa_check
		// 
		this->kappa_check->AutoSize = true;
		this->kappa_check->Location = System::Drawing::Point(6, 87);
		this->kappa_check->Name = L"kappa_check";
		this->kappa_check->Size = System::Drawing::Size(56, 17);
		this->kappa_check->TabIndex = 7;
		this->kappa_check->Text = L"kappa";
		this->kappa_check->UseVisualStyleBackColor = true;
		this->kappa_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::kappa_check_CheckedChanged);
		// 
		// theta_check
		// 
		this->theta_check->AutoSize = true;
		this->theta_check->Location = System::Drawing::Point(6, 131);
		this->theta_check->Name = L"theta_check";
		this->theta_check->Size = System::Drawing::Size(50, 17);
		this->theta_check->TabIndex = 8;
		this->theta_check->Text = L"theta";
		this->theta_check->UseVisualStyleBackColor = true;
		this->theta_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::theta_check_CheckedChanged);
		// 
		// menuStrip1
		// 
		this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
			this->File_strip_menu,
				this->settingsForPSOToolStripMenuItem, this->settingForGaussNewtonToolStripMenuItem
		});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1298, 24);
		this->menuStrip1->TabIndex = 6;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// File_strip_menu
		// 
		this->File_strip_menu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->loadFileToolStripMenuItem,
				this->loadExperimentalDatatToolStripMenuItem
		});
		this->File_strip_menu->Name = L"File_strip_menu";
		this->File_strip_menu->Size = System::Drawing::Size(37, 20);
		this->File_strip_menu->Text = L"File";
		// 
		// loadFileToolStripMenuItem
		// 
		this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
		this->loadFileToolStripMenuItem->Size = System::Drawing::Size(254, 22);
		this->loadFileToolStripMenuItem->Text = L"Select Data Specification Directory";
		this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form4::loadFileToolStripMenuItem_Click);
		// 
		// loadExperimentalDatatToolStripMenuItem
		// 
		this->loadExperimentalDatatToolStripMenuItem->Name = L"loadExperimentalDatatToolStripMenuItem";
		this->loadExperimentalDatatToolStripMenuItem->Size = System::Drawing::Size(254, 22);
		this->loadExperimentalDatatToolStripMenuItem->Text = L"Load Experimental Data";
		this->loadExperimentalDatatToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form4::loadExperimentalDatatToolStripMenuItem_Click);
		// 
		// settingsForPSOToolStripMenuItem
		// 
		this->settingsForPSOToolStripMenuItem->Name = L"settingsForPSOToolStripMenuItem";
		this->settingsForPSOToolStripMenuItem->Size = System::Drawing::Size(106, 20);
		this->settingsForPSOToolStripMenuItem->Text = L"Settings For PSO";
		this->settingsForPSOToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form4::settingsForPSOToolStripMenuItem_Click);
		// 
		// settingForGaussNewtonToolStripMenuItem
		// 
		this->settingForGaussNewtonToolStripMenuItem->Name = L"settingForGaussNewtonToolStripMenuItem";
		this->settingForGaussNewtonToolStripMenuItem->Size = System::Drawing::Size(157, 20);
		this->settingForGaussNewtonToolStripMenuItem->Text = L"Setting For Gauss-Newton";
		this->settingForGaussNewtonToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form4::settingForGaussNewtonToolStripMenuItem_Click);
		// 
		// cancel_button
		// 
		this->cancel_button->Location = System::Drawing::Point(359, 592);
		this->cancel_button->Name = L"cancel_button";
		this->cancel_button->Size = System::Drawing::Size(108, 38);
		this->cancel_button->TabIndex = 7;
		this->cancel_button->Text = L"Cancel";
		this->cancel_button->UseVisualStyleBackColor = true;
		this->cancel_button->Click += gcnew System::EventHandler(this, &Form4::cancel_button_Click);
		// 
		// Optimize_button
		// 
		this->Optimize_button->Location = System::Drawing::Point(12, 590);
		this->Optimize_button->Name = L"Optimize_button";
		this->Optimize_button->Size = System::Drawing::Size(164, 38);
		this->Optimize_button->TabIndex = 8;
		this->Optimize_button->Text = L"Run Gauss-Newton";
		this->Optimize_button->UseVisualStyleBackColor = true;
		this->Optimize_button->Click += gcnew System::EventHandler(this, &Form4::Optimize_button_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(15, 335);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(36, 13);
		this->label1->TabIndex = 9;
		this->label1->Text = L"t_start";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(15, 361);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(34, 13);
		this->label2->TabIndex = 10;
		this->label2->Text = L"t_end";
		// 
		// t_start_input
		// 
		this->t_start_input->DecimalPlaces = 2;
		this->t_start_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_start_input->Location = System::Drawing::Point(116, 333);
		this->t_start_input->Name = L"t_start_input";
		this->t_start_input->Size = System::Drawing::Size(130, 20);
		this->t_start_input->TabIndex = 11;
		this->t_start_input->ValueChanged += gcnew System::EventHandler(this, &Form4::t_start_input_ValueChanged);
		// 
		// t_end_input
		// 
		this->t_end_input->DecimalPlaces = 2;
		this->t_end_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_end_input->Location = System::Drawing::Point(116, 359);
		this->t_end_input->Name = L"t_end_input";
		this->t_end_input->Size = System::Drawing::Size(130, 20);
		this->t_end_input->TabIndex = 12;
		this->t_end_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
		this->t_end_input->ValueChanged += gcnew System::EventHandler(this, &Form4::t_end_input_ValueChanged);
		// 
		// stepsize_input
		// 
		this->stepsize_input->DecimalPlaces = 6;
		this->stepsize_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->stepsize_input->Location = System::Drawing::Point(116, 554);
		this->stepsize_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->stepsize_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepsize_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->stepsize_input->Name = L"stepsize_input";
		this->stepsize_input->Size = System::Drawing::Size(130, 20);
		this->stepsize_input->TabIndex = 33;
		this->stepsize_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 131072 });
		this->stepsize_input->ValueChanged += gcnew System::EventHandler(this, &Form4::stepsize_input_ValueChanged);
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(15, 556);
		this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(71, 13);
		this->label11->TabIndex = 32;
		this->label11->Text = L"RK4 Stepsize";
		// 
		// initial_exposed
		// 
		this->initial_exposed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_exposed->Location = System::Drawing::Point(114, 441);
		this->initial_exposed->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_exposed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_exposed->Name = L"initial_exposed";
		this->initial_exposed->Size = System::Drawing::Size(130, 20);
		this->initial_exposed->TabIndex = 31;
		this->initial_exposed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
		this->initial_exposed->ValueChanged += gcnew System::EventHandler(this, &Form4::initial_exposed_ValueChanged);
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = System::Drawing::Point(12, 441);
		this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(78, 13);
		this->label10->TabIndex = 30;
		this->label10->Text = L"Initial_Exposed";
		// 
		// initial_infected
		// 
		this->initial_infected->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_infected->Location = System::Drawing::Point(114, 471);
		this->initial_infected->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_infected->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_infected->Name = L"initial_infected";
		this->initial_infected->Size = System::Drawing::Size(130, 20);
		this->initial_infected->TabIndex = 27;
		this->initial_infected->ValueChanged += gcnew System::EventHandler(this, &Form4::initial_infected_ValueChanged);
		// 
		// initial_deaths
		// 
		this->initial_deaths->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_deaths->Location = System::Drawing::Point(116, 529);
		this->initial_deaths->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_deaths->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_deaths->Name = L"initial_deaths";
		this->initial_deaths->Size = System::Drawing::Size(130, 20);
		this->initial_deaths->TabIndex = 29;
		this->initial_deaths->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 72, 0, 0, 0 });
		this->initial_deaths->ValueChanged += gcnew System::EventHandler(this, &Form4::initial_deaths_ValueChanged);
		// 
		// initial_recovered
		// 
		this->initial_recovered->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_recovered->Location = System::Drawing::Point(116, 501);
		this->initial_recovered->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_recovered->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_recovered->Name = L"initial_recovered";
		this->initial_recovered->Size = System::Drawing::Size(130, 20);
		this->initial_recovered->TabIndex = 28;
		this->initial_recovered->ValueChanged += gcnew System::EventHandler(this, &Form4::initial_recovered_ValueChanged);
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(15, 529);
		this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(68, 13);
		this->label7->TabIndex = 26;
		this->label7->Text = L"Initial Deaths";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(12, 411);
		this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(94, 13);
		this->label6->TabIndex = 25;
		this->label6->Text = L"Initial Susceptibles";
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(12, 501);
		this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(87, 13);
		this->label5->TabIndex = 24;
		this->label5->Text = L"Initial Recovered";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(12, 471);
		this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(73, 13);
		this->label4->TabIndex = 23;
		this->label4->Text = L"Initial Infected";
		// 
		// initial_susceptibles
		// 
		this->initial_susceptibles->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_susceptibles->Location = System::Drawing::Point(116, 411);
		this->initial_susceptibles->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_susceptibles->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7000000, 0, 0, 0 });
		this->initial_susceptibles->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->initial_susceptibles->Name = L"initial_susceptibles";
		this->initial_susceptibles->Size = System::Drawing::Size(130, 20);
		this->initial_susceptibles->TabIndex = 22;
		this->initial_susceptibles->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5800000, 0, 0, 0 });
		this->initial_susceptibles->ValueChanged += gcnew System::EventHandler(this, &Form4::initial_susceptibles_ValueChanged);
		// 
		// chart1
		// 
		chartArea1->AxisX->Title = L"Time";
		chartArea1->AxisY->Title = L"Amount";
		chartArea1->Name = L"ChartArea1";
		this->chart1->ChartAreas->Add(chartArea1);
		legend1->Name = L"Legend1";
		this->chart1->Legends->Add(legend1);
		this->chart1->Location = System::Drawing::Point(267, 70);
		this->chart1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
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
		series5->ChartArea = L"ChartArea1";
		series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		series5->Legend = L"Legend1";
		series5->Name = L"Exposed";
		this->chart1->Series->Add(series1);
		this->chart1->Series->Add(series2);
		this->chart1->Series->Add(series3);
		this->chart1->Series->Add(series4);
		this->chart1->Series->Add(series5);
		this->chart1->Size = System::Drawing::Size(546, 514);
		this->chart1->TabIndex = 34;
		this->chart1->Text = L"chart1";
		title1->Name = L"Result of SRI Model";
		this->chart1->Titles->Add(title1);
		this->chart1->Click += gcnew System::EventHandler(this, &Form4::chart1_Click);
		// 
		// pso_optimize_button
		// 
		this->pso_optimize_button->Location = System::Drawing::Point(192, 592);
		this->pso_optimize_button->Name = L"pso_optimize_button";
		this->pso_optimize_button->Size = System::Drawing::Size(149, 36);
		this->pso_optimize_button->TabIndex = 35;
		this->pso_optimize_button->Text = L"Run PSO";
		this->pso_optimize_button->UseVisualStyleBackColor = true;
		this->pso_optimize_button->Click += gcnew System::EventHandler(this, &Form4::pso_optimize_button_Click);
		// 
		// chart2
		// 
		chartArea2->AxisX->Title = L"Iteration";
		chartArea2->AxisY->Title = L"Squared Error";
		chartArea2->Name = L"ChartArea1";
		this->chart2->ChartAreas->Add(chartArea2);
		legend2->Enabled = false;
		legend2->Name = L"Legend1";
		this->chart2->Legends->Add(legend2);
		this->chart2->Location = System::Drawing::Point(820, 68);
		this->chart2->Name = L"chart2";
		series6->ChartArea = L"ChartArea1";
		series6->Legend = L"Legend1";
		series6->Name = L"Series1";
		this->chart2->Series->Add(series6);
		this->chart2->Size = System::Drawing::Size(466, 514);
		this->chart2->TabIndex = 36;
		this->chart2->Text = L"chart2";
		// 
		// Form4
		// 
		this->AutoSize = true;
		this->ClientSize = System::Drawing::Size(1298, 639);
		this->Controls->Add(this->chart2);
		this->Controls->Add(this->pso_optimize_button);
		this->Controls->Add(this->chart1);
		this->Controls->Add(this->stepsize_input);
		this->Controls->Add(this->label11);
		this->Controls->Add(this->initial_exposed);
		this->Controls->Add(this->label10);
		this->Controls->Add(this->initial_infected);
		this->Controls->Add(this->initial_deaths);
		this->Controls->Add(this->initial_recovered);
		this->Controls->Add(this->label7);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->initial_susceptibles);
		this->Controls->Add(this->t_end_input);
		this->Controls->Add(this->t_start_input);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->Optimize_button);
		this->Controls->Add(this->cancel_button);
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->menuStrip1);
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"Form4";
		this->Text = L"Parameter Estimation";
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form4::Form4_FormClosing);
		this->Load += gcnew System::EventHandler(this, &Form4::Form4_Load);
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->EndInit();
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->t_start_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->t_end_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepsize_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_exposed))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_infected))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_deaths))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_recovered))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initial_susceptibles))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	private: System::Void Form4_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
private: System::Void alpha_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (alpha_check->Checked) {
		Form5^ box = gcnew Form5;
		// set values 
		box->set_upper(0);
		box->set_lower(0);
		if (box->ShowDialog().Equals(System::Windows::Forms::DialogResult::OK))
		{
			// If it came back with OK, get the values
			alpha_upper_input = System::Decimal::ToDouble(box->get_upper());
			alpha_lower_input = System::Decimal::ToDouble(box->get_lower());
		}		
	}
}
private: System::Void kappa_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (kappa_check->Checked) {
		Form5^ box = gcnew Form5;
		// set values 
		box->set_upper(0);
		box->set_lower(0);
		if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// If it came back with OK, get the values
			kappa_upper_input = System::Decimal::ToDouble(box->get_upper());
			kappa_lower_input = System::Decimal::ToDouble(box->get_lower());
		}
	}
}
private: System::Void theta_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (theta_check->Checked) {
		Form5^ box = gcnew Form5;
		// set values 
		box->set_upper(0);
		box->set_lower(0);
		if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// If it came back with OK, get the values
			theta_upper_input = System::Decimal::ToDouble(box->get_upper());
			theta_lower_input = System::Decimal::ToDouble(box->get_lower());
		}
	}
}
private: System::Void qq_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (qq_check->Checked) {
		Form5^ box = gcnew Form5;
		// set values 
		box->set_upper(0);
		box->set_lower(0);
		if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// If it came back with OK, get the values
			qq_upper_input = System::Decimal::ToDouble(box->get_upper());
			qq_lower_input = System::Decimal::ToDouble(box->get_lower());
		}
	}
}
private: System::Void pp_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (pp_check->Checked) {
		Form5^ box = gcnew Form5;
		// set values 
		box->set_upper(0);
		box->set_lower(0);
		if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// If it came back with OK, get the values
			pp_upper_input = System::Decimal::ToDouble(box->get_upper());
			pp_lower_input = System::Decimal::ToDouble(box->get_lower());
		}
	}
}
private: System::Void alpha_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	 plot_on_keypress();	
}
private: System::Void kappa_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void theta_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void qq_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void pp_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	 plot_on_keypress();
}
private: System::Void cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}

	// Collects the values for the parameters, creates the evaluate.lua and starts the Gauss Newton - optimization.
	void main_newton() { 	

		   double alpha= System::Decimal::ToDouble(this->alpha_input->Value);
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);

		   std::vector<std::string > names_of_constants;
		   std::vector<double> values_of_constants;
		   std::vector<std::string> names_of_variables;

		   std::vector<std::string > names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
		   std::vector<double> values_of_inits;

		   co::EVar64Manager initial_vars;

		   if (this->alpha_check->Checked) {
			   names_of_variables.push_back("alpha");

			   co::EVar64 v_alpha=co::EVar64(co::EFloat64(alpha), co::EFloat64(alpha_lower_input), co::EFloat64(alpha_upper_input));
			   initial_vars.add("alpha", v_alpha);
		   }
		   else {
			   names_of_constants.push_back("alpha");
			   values_of_constants.push_back(alpha);
		   }

		   if (this->kappa_check->Checked) {
			   names_of_variables.push_back("kappa");
			   //EFloats for bounds aswelll!!
			   co::EVar64 v_kappa= co::EVar64(co::EFloat64(kappa), co::EFloat64(kappa_lower_input), co::EFloat64(kappa_upper_input));
			   initial_vars.add("kappa", v_kappa);
		   }
		   else {
			   names_of_constants.push_back("kappa");
			   values_of_constants.push_back(kappa);
		   }

		   if (this->theta_check->Checked) {
			   names_of_variables.push_back("theta");
			   co::EVar64 v_theta = co::EVar64(co::EFloat64(theta), co::EFloat64(theta_lower_input), co::EFloat64(theta_upper_input));
			   initial_vars.add("theta", v_theta);
		   }
		   else {
			   names_of_constants.push_back("theta");
			   values_of_constants.push_back(theta);
		   }

		   if (this->qq_check->Checked) {
			   names_of_variables.push_back("qq");
			   co::EVar64 v_qq = co::EVar64(co::EFloat64(qq), co::EFloat64(qq_lower_input), co::EFloat64(qq_upper_input));
			   initial_vars.add("qq", v_qq);
		   }
		   else {
			   names_of_constants.push_back("qq");
			   values_of_constants.push_back(qq);
		   }

		   if (this->pp_check->Checked) {
			   names_of_variables.push_back("pp");
			   co::EVar64 v_pp = co::EVar64(co::EFloat64(pp), co::EFloat64(pp_lower_input), co::EFloat64(pp_upper_input));
			   initial_vars.add("pp", v_pp);
		   }
		   else {
			   names_of_constants.push_back("pp");
			   values_of_constants.push_back(pp);
		   }


		   values_of_inits = { System::Decimal::ToDouble(this->t_start_input->Value),System::Decimal::ToDouble(this->t_end_input->Value),System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_exposed->Value),System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };
		   
		   std::string textbody = R"(

seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
							)";
		   
		   if (user_selected_optimization_path == nullptr) {
			   MessageBox::Show(L"Please specify the directory for the experimental data");
		   }
		   else{
			   ug::epi::create_evaluate_lua(*user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits, System::Decimal::ToDouble(this->stepsize_input->Value));

			   co::NewtonOptions options;
			   options.set_stepsize_alpha(1);
			  
			   co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(*user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
			   co::EVarManager<co::EFloat64> estimated_vars;
			   co::NewtonOptimizer<decltype(evaluator)> solver(options, evaluator);
			   //	MessageBox::Show(gcnew String(user_selected_optimization_path->c_str())); //display path

			   solver.set_convergence_threshold(convergence_parameter);

			   auto result = solver.run(initial_vars, estimated_vars);

			   if (result == co::ErrorCode::OptimizationError) { MessageBox::Show(L"Optimization Error"); }
			   else if (result == co::ErrorCode::PathError) { MessageBox::Show(L"Path Error"); }
			   else if (result == co::ErrorCode::ComputationError) { MessageBox::Show(L"ComputationError"); }
			   else if (result == co::ErrorCode::ParseError) { MessageBox::Show(L"Parse Error!"); }
			   else if (result == co::ErrorCode::NoError) {
				   for (int i = 0; i < estimated_vars.len(); i++) {
					   if (estimated_vars.get_name(i) == "alpha") {
						   this->alpha_input->Value = System::Decimal(estimated_vars.get_param(i).get_value_as_double());
					   }
					   if (estimated_vars.get_name(i) == "kappa") {
						   this->kappa_input->Value = System::Decimal(estimated_vars.get_param(i).get_value_as_double());
					   }
					   if (estimated_vars.get_name(i) == "theta") {
						   this->theta_input->Value = System::Decimal(estimated_vars.get_param(i).get_value_as_double());
					   }
					   if (estimated_vars.get_name(i) == "qq") {
						   this->qq_input->Value = System::Decimal(estimated_vars.get_param(i).get_value_as_double());
					   }
					   if (estimated_vars.get_name(i) == "pp") {
						   this->pp_input->Value = System::Decimal(estimated_vars.get_param(i).get_value_as_double());
					   }


					   MessageBox::Show(L"Optimization Complete!");
					   auto sq_error = solver.get_saved_losses_in_past_iteration_as_double();
					   auto converted_name = gcnew String(L"Series1");
					   this->chart2->Series[converted_name]->Points->Clear();
					   this->chart2->Refresh();
					   for (int i = 0; i < sq_error.size(); i++) {

							System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i,
							   sq_error[i]));

							this->chart2->Series[converted_name]->Points->Add(dataPoint1);
					   }
					   


				   }
			   }
			   else { MessageBox::Show(L"Please check the settings"); }
			   
		   }

	}

	   void main_pso() {
		   double alpha = System::Decimal::ToDouble(this->alpha_input->Value);
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);

		   std::vector<std::string > names_of_constants;
		   std::vector<double> values_of_constants;
		   std::vector<std::string> names_of_variables;

		   std::vector<std::string > names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
		   std::vector<double> values_of_inits;

		   std::vector<co::EFloat64> bounds;

		   if (this->alpha_check->Checked) {
			   names_of_variables.push_back("alpha");
			   bounds.push_back(co::EFloat64(alpha_lower_input)); 
			   bounds.push_back( co::EFloat64(alpha_upper_input));

		   }
		   else {
			   names_of_constants.push_back("alpha");
			   values_of_constants.push_back(alpha);
		   }

		   if (this->kappa_check->Checked) {
			   names_of_variables.push_back("kappa");
			   bounds.push_back(co::EFloat64(kappa_lower_input));
			   bounds.push_back(co::EFloat64(kappa_upper_input));

		   }
		   else {
			   names_of_constants.push_back("kappa");
			   values_of_constants.push_back(kappa);
		   }

		   if (this->theta_check->Checked) {
			   names_of_variables.push_back("theta");
			   bounds.push_back(co::EFloat64(theta_lower_input));
			   bounds.push_back(co::EFloat64(theta_upper_input));

		   }
		   else {
			   names_of_constants.push_back("theta");
			   values_of_constants.push_back(theta);
		   }

		   if (this->qq_check->Checked) {
			   names_of_variables.push_back("qq");
			   bounds.push_back(co::EFloat64(qq_lower_input));
			   bounds.push_back(co::EFloat64(qq_upper_input));

		   }
		   else {
			   names_of_constants.push_back("qq");
			   values_of_constants.push_back(qq);
		   }

		   if (this->pp_check->Checked) {
			   names_of_variables.push_back("pp");
			   bounds.push_back(co::EFloat64(pp_lower_input));
			   bounds.push_back(co::EFloat64(pp_upper_input));

		   }
		   else {
			   names_of_constants.push_back("pp");
			   values_of_constants.push_back(pp);
		   }


		   values_of_inits = { System::Decimal::ToDouble(this->t_start_input->Value),System::Decimal::ToDouble(this->t_end_input->Value),System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_exposed->Value),System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };

		   std::string textbody = R"(
seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
							)";

		   if (user_selected_optimization_path == nullptr) {
			   MessageBox::Show(L"Please specify the directory for the experimental data");
		   }
		   else {

			   ug::epi::create_evaluate_lua(*user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits, System::Decimal::ToDouble(this->stepsize_input->Value));

			   co::PSOOptions options;
			   options.set_max_iterations((this->max_iter));
			   options.set_n_groups(this->no_groups);
			   options.set_n_particles(this->no_particles);
			   co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(*user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
			   co::ParticleSwarmOptimizer<co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File>> pso(options, evaluator);
			   co::EVarManager<co::EFloat64> estimated_parameters;

			   
			   auto result = pso.run(estimated_parameters, names_of_variables, bounds);

			   
			   if (result == co::ErrorCode::OptimizationError) { MessageBox::Show(L"Optimization Error"); }
			   else if (result == co::ErrorCode::PathError) { MessageBox::Show(L"Path Error"); }
			   else if (result == co::ErrorCode::ComputationError) { MessageBox::Show(L"ComputationError"); }
			   else if (result == co::ErrorCode::ParseError) { MessageBox::Show(L"Parse Error!"); }
			   else if (result == co::ErrorCode::NoError) {	MessageBox::Show(L"Optimization Complete!"); 
			   
			   
			   auto sq_error = pso.get_saved_losses_in_past_iteration_as_double();
			   auto converted_name = gcnew String(L"Series1");
			   this->chart2->Series[converted_name]->Points->Clear();
			   this->chart2->Refresh();
			   for (int i = 0; i < sq_error.size(); i++) {

				   System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i,
					   sq_error[i]));

				   this->chart2->Series[converted_name]->Points->Add(dataPoint1);
			   }
			   }
			   else { MessageBox::Show(L"Please check the settings"); }

		   }
	}
	void plot_on_keypress() {
		   //MessageBox::Show(L"plotter called");
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double alpha = System::Decimal::ToDouble(this->alpha_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);

		   double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);
		   
		   ug::epi::SEIRD<std::vector<double>> seird_model(alpha, kappa, theta, qq, pp);

		   seird_model.change_step_size(stepsize);

		   std::vector<double> u0 = { System::Decimal::ToDouble(this->initial_susceptibles->Value) ,System::Decimal::ToDouble(this->initial_exposed->Value),System::Decimal::ToDouble(this->initial_infected->Value),System::Decimal::ToDouble(this->initial_recovered->Value),System::Decimal::ToDouble(this->initial_deaths->Value) };
		   double t_start = System::Decimal::ToDouble(this->t_start_input->Value);
		   double t_end = System::Decimal::ToDouble(this->t_end_input->Value);

		  // auto [timepoints, data] = seird_model.run(t_start, u0, t_end);

		   auto [timepoints, data] = seird_model.run_linear_implicit(t_start, u0, t_end);

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
		   if (user_datapoints != nullptr && user_names != nullptr && user_cols != nullptr) {
			   for (int i = 1; i < user_names->size(); i++) {
				   converted_name = gcnew String((*user_names)[i].c_str());
				   plotter.plot(this, user_datapoints, converted_name, user_names->size(), i);
			   }

		   }
	   }


private: System::Void Optimize_button_Click(System::Object^ sender, System::EventArgs^ e) {
	main_newton();

}
private: System::Void loadFileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {


	if (user_selected_optimization_path) {
		delete user_selected_optimization_path;

	}

	System::Windows::Forms::FolderBrowserDialog fileDialog;
	String^ filepath;
	if (fileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK) {
//		String^ files = System::IO::Directory.GetFiles(fileDialog.SelectedPath);
		filepath = fileDialog.SelectedPath;
	}

	user_selected_optimization_path=new std::string;
	*user_selected_optimization_path = msclr::interop::marshal_as<std::string>(filepath);

	//MessageBox::Show(filepath);
}
private: System::Void Form4_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	Application::Exit();
}



private: System::Void t_start_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void t_end_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_susceptibles_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void initial_exposed_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
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
private: System::Void stepsize_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	plot_on_keypress();
}
private: System::Void pso_optimize_button_Click(System::Object^ sender, System::EventArgs^ e) {
	main_pso();
}

private: System::Void maxIterationsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void settingsForPSOToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Form6^ form = gcnew Form6;
	if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		// If it came back with OK, get the values
		max_iter = System::Decimal::ToInt32(form->get_max_iterations());
		no_groups = System::Decimal::ToInt32(form->get_groups());
		no_particles = System::Decimal::ToInt32(form->get_particles());
	}
}

private: System::Void settingForGaussNewtonToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Form7^ form = gcnew Form7;
	if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		// If it came back with OK, get the values
		convergence_parameter = System::Decimal::ToDouble(form->get_convergence_factor());
	}

}
private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void loadExperimentalDatatToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	ug::epi::load_csv_data_on_click(this, 5); //5 represents the number of prior plotted lines
	plot_on_keypress();
}
};
}
