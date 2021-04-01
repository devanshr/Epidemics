#pragma once

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
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Zusammenfassung f�r Form8
	/// </summary>
	public ref class Form8 : public System::Windows::Forms::Form
	{
	public:
		Form8(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzuf�gen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form8()
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

	private: System::Windows::Forms::NumericUpDown^ initial_infected;
	private: System::Windows::Forms::NumericUpDown^ initial_deaths;
	private: System::Windows::Forms::NumericUpDown^ initial_recovered;




	private: System::Windows::Forms::NumericUpDown^ initial_susceptibles;

	private: System::Windows::Forms::Button^ pso_optimize_button;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsForPSOToolStripMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^ settingForGaussNewtonToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ loadExperimentalDatatToolStripMenuItem;
private: System::Data::DataSet^ dataSet1;
private: System::Data::DataTable^ dataTable1;
private: System::Data::DataColumn^ dataColumn1;
private: System::Data::DataColumn^ dataColumn2;




private: System::Windows::Forms::PictureBox^ pictureBox1;




private: System::Windows::Forms::Button^ button1;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::PictureBox^ pictureBox2;
private: System::Windows::Forms::PictureBox^ pictureBox3;
private: System::Windows::Forms::PictureBox^ pictureBox4;
private: System::Windows::Forms::PictureBox^ pictureBox5;
private: System::Windows::Forms::HScrollBar^ hScrollBar1;
private: System::Windows::Forms::Label^ label4;










private: System::ComponentModel::IContainer^ components;

































	public:
	private:






	


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>




	private: System::Void InitializeComponent() {
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
		this->initial_infected = (gcnew System::Windows::Forms::NumericUpDown());
		this->initial_deaths = (gcnew System::Windows::Forms::NumericUpDown());
		this->initial_recovered = (gcnew System::Windows::Forms::NumericUpDown());
		this->initial_susceptibles = (gcnew System::Windows::Forms::NumericUpDown());
		this->pso_optimize_button = (gcnew System::Windows::Forms::Button());
		this->dataSet1 = (gcnew System::Data::DataSet());
		this->dataTable1 = (gcnew System::Data::DataTable());
		this->dataColumn1 = (gcnew System::Data::DataColumn());
		this->dataColumn2 = (gcnew System::Data::DataColumn());
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
		this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->groupBox1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->BeginInit();
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
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
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
		this->groupBox1->Location = System::Drawing::Point(12, 49);
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
		this->pp_input->Size = System::Drawing::Size(130, 26);
		this->pp_input->TabIndex = 15;
		this->pp_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->pp_input->ValueChanged += gcnew System::EventHandler(this, &Form8::pp_input_ValueChanged);
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
		this->qq_input->Size = System::Drawing::Size(130, 26);
		this->qq_input->TabIndex = 14;
		this->qq_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->qq_input->ValueChanged += gcnew System::EventHandler(this, &Form8::qq_input_ValueChanged);
		// 
		// theta_input
		// 
		this->theta_input->DecimalPlaces = 8;
		this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->theta_input->Location = System::Drawing::Point(104, 131);
		this->theta_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->theta_input->Name = L"theta_input";
		this->theta_input->Size = System::Drawing::Size(130, 26);
		this->theta_input->TabIndex = 13;
		this->theta_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form8::theta_input_ValueChanged);
		// 
		// kappa_input
		// 
		this->kappa_input->DecimalPlaces = 8;
		this->kappa_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->kappa_input->Location = System::Drawing::Point(104, 87);
		this->kappa_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->kappa_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->kappa_input->Name = L"kappa_input";
		this->kappa_input->Size = System::Drawing::Size(130, 26);
		this->kappa_input->TabIndex = 12;
		this->kappa_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form8::kappa_input_ValueChanged);
		// 
		// alpha_input
		// 
		this->alpha_input->DecimalPlaces = 9;
		this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->alpha_input->Location = System::Drawing::Point(104, 43);
		this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->alpha_input->Name = L"alpha_input";
		this->alpha_input->Size = System::Drawing::Size(130, 26);
		this->alpha_input->TabIndex = 11;
		this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form8::alpha_input_ValueChanged);
		// 
		// pp_check
		// 
		this->pp_check->AutoSize = true;
		this->pp_check->Location = System::Drawing::Point(6, 212);
		this->pp_check->Name = L"pp_check";
		this->pp_check->Size = System::Drawing::Size(53, 24);
		this->pp_check->TabIndex = 10;
		this->pp_check->Text = L"pp";
		this->pp_check->UseVisualStyleBackColor = true;
		this->pp_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::pp_check_CheckedChanged);
		// 
		// alpha_check
		// 
		this->alpha_check->AutoSize = true;
		this->alpha_check->Location = System::Drawing::Point(6, 43);
		this->alpha_check->Name = L"alpha_check";
		this->alpha_check->Size = System::Drawing::Size(74, 24);
		this->alpha_check->TabIndex = 6;
		this->alpha_check->Text = L"alpha";
		this->alpha_check->UseVisualStyleBackColor = true;
		this->alpha_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::alpha_check_CheckedChanged);
		// 
		// qq_check
		// 
		this->qq_check->AutoSize = true;
		this->qq_check->Location = System::Drawing::Point(6, 171);
		this->qq_check->Name = L"qq_check";
		this->qq_check->Size = System::Drawing::Size(53, 24);
		this->qq_check->TabIndex = 9;
		this->qq_check->Text = L"qq";
		this->qq_check->UseVisualStyleBackColor = true;
		this->qq_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::qq_check_CheckedChanged);
		// 
		// kappa_check
		// 
		this->kappa_check->AutoSize = true;
		this->kappa_check->Location = System::Drawing::Point(6, 87);
		this->kappa_check->Name = L"kappa_check";
		this->kappa_check->Size = System::Drawing::Size(79, 24);
		this->kappa_check->TabIndex = 7;
		this->kappa_check->Text = L"kappa";
		this->kappa_check->UseVisualStyleBackColor = true;
		this->kappa_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::kappa_check_CheckedChanged);
		// 
		// theta_check
		// 
		this->theta_check->AutoSize = true;
		this->theta_check->Location = System::Drawing::Point(6, 131);
		this->theta_check->Name = L"theta_check";
		this->theta_check->Size = System::Drawing::Size(72, 24);
		this->theta_check->TabIndex = 8;
		this->theta_check->Text = L"theta";
		this->theta_check->UseVisualStyleBackColor = true;
		this->theta_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::theta_check_CheckedChanged);
		// 
		// menuStrip1
		// 
		this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
		this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
			this->File_strip_menu,
				this->settingsForPSOToolStripMenuItem, this->settingForGaussNewtonToolStripMenuItem
		});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1298, 33);
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
		this->File_strip_menu->Size = System::Drawing::Size(54, 29);
		this->File_strip_menu->Text = L"File";
		// 
		// loadFileToolStripMenuItem
		// 
		this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
		this->loadFileToolStripMenuItem->Size = System::Drawing::Size(384, 34);
		this->loadFileToolStripMenuItem->Text = L"Select Data Specification Directory";
		this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::loadFileToolStripMenuItem_Click);
		// 
		// loadExperimentalDatatToolStripMenuItem
		// 
		this->loadExperimentalDatatToolStripMenuItem->Name = L"loadExperimentalDatatToolStripMenuItem";
		this->loadExperimentalDatatToolStripMenuItem->Size = System::Drawing::Size(384, 34);
		this->loadExperimentalDatatToolStripMenuItem->Text = L"Load Experimental Data";
		this->loadExperimentalDatatToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::loadExperimentalDatatToolStripMenuItem_Click);
		// 
		// settingsForPSOToolStripMenuItem
		// 
		this->settingsForPSOToolStripMenuItem->Name = L"settingsForPSOToolStripMenuItem";
		this->settingsForPSOToolStripMenuItem->Size = System::Drawing::Size(162, 29);
		this->settingsForPSOToolStripMenuItem->Text = L"Settings For PSO";
		this->settingsForPSOToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::settingsForPSOToolStripMenuItem_Click);
		// 
		// settingForGaussNewtonToolStripMenuItem
		// 
		this->settingForGaussNewtonToolStripMenuItem->Name = L"settingForGaussNewtonToolStripMenuItem";
		this->settingForGaussNewtonToolStripMenuItem->Size = System::Drawing::Size(236, 29);
		this->settingForGaussNewtonToolStripMenuItem->Text = L"Setting For Gauss-Newton";
		this->settingForGaussNewtonToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::settingForGaussNewtonToolStripMenuItem_Click);
		// 
		// cancel_button
		// 
		this->cancel_button->Location = System::Drawing::Point(1168, 164);
		this->cancel_button->Name = L"cancel_button";
		this->cancel_button->Size = System::Drawing::Size(108, 38);
		this->cancel_button->TabIndex = 7;
		this->cancel_button->Text = L"Cancel";
		this->cancel_button->UseVisualStyleBackColor = true;
		this->cancel_button->Click += gcnew System::EventHandler(this, &Form8::cancel_button_Click);
		// 
		// Optimize_button
		// 
		this->Optimize_button->Location = System::Drawing::Point(608, 64);
		this->Optimize_button->Name = L"Optimize_button";
		this->Optimize_button->Size = System::Drawing::Size(164, 38);
		this->Optimize_button->TabIndex = 8;
		this->Optimize_button->Text = L"Run Gauss-Newton";
		this->Optimize_button->UseVisualStyleBackColor = true;
		this->Optimize_button->Click += gcnew System::EventHandler(this, &Form8::Optimize_button_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(1045, 60);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(55, 20);
		this->label1->TabIndex = 9;
		this->label1->Text = L"t_start";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(1045, 86);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(50, 20);
		this->label2->TabIndex = 10;
		this->label2->Text = L"t_end";
		// 
		// t_start_input
		// 
		this->t_start_input->DecimalPlaces = 2;
		this->t_start_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_start_input->Location = System::Drawing::Point(1146, 58);
		this->t_start_input->Name = L"t_start_input";
		this->t_start_input->Size = System::Drawing::Size(130, 26);
		this->t_start_input->TabIndex = 11;
		this->t_start_input->ValueChanged += gcnew System::EventHandler(this, &Form8::t_start_input_ValueChanged);
		// 
		// t_end_input
		// 
		this->t_end_input->DecimalPlaces = 2;
		this->t_end_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_end_input->Location = System::Drawing::Point(1146, 84);
		this->t_end_input->Name = L"t_end_input";
		this->t_end_input->Size = System::Drawing::Size(130, 26);
		this->t_end_input->TabIndex = 12;
		this->t_end_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
		this->t_end_input->ValueChanged += gcnew System::EventHandler(this, &Form8::t_end_input_ValueChanged);
		// 
		// stepsize_input
		// 
		this->stepsize_input->DecimalPlaces = 6;
		this->stepsize_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->stepsize_input->Location = System::Drawing::Point(436, 209);
		this->stepsize_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->stepsize_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepsize_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->stepsize_input->Name = L"stepsize_input";
		this->stepsize_input->Size = System::Drawing::Size(130, 26);
		this->stepsize_input->TabIndex = 33;
		this->stepsize_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 131072 });
		this->stepsize_input->ValueChanged += gcnew System::EventHandler(this, &Form8::stepsize_input_ValueChanged);
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(288, 209);
		this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(106, 20);
		this->label11->TabIndex = 32;
		this->label11->Text = L"RK4 Stepsize";
		// 
		// initial_exposed
		// 
		this->initial_exposed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_exposed->Location = System::Drawing::Point(436, 92);
		this->initial_exposed->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_exposed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_exposed->Name = L"initial_exposed";
		this->initial_exposed->Size = System::Drawing::Size(130, 26);
		this->initial_exposed->TabIndex = 31;
		this->initial_exposed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
		this->initial_exposed->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_exposed_ValueChanged);
		// 
		// initial_infected
		// 
		this->initial_infected->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_infected->Location = System::Drawing::Point(454, 128);
		this->initial_infected->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_infected->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_infected->Name = L"initial_infected";
		this->initial_infected->Size = System::Drawing::Size(130, 26);
		this->initial_infected->TabIndex = 27;
		this->initial_infected->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_infected_ValueChanged);
		// 
		// initial_deaths
		// 
		this->initial_deaths->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_deaths->Location = System::Drawing::Point(454, 171);
		this->initial_deaths->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_deaths->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_deaths->Name = L"initial_deaths";
		this->initial_deaths->Size = System::Drawing::Size(130, 26);
		this->initial_deaths->TabIndex = 29;
		this->initial_deaths->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 72, 0, 0, 0 });
		this->initial_deaths->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_deaths_ValueChanged);
		// 
		// initial_recovered
		// 
		this->initial_recovered->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_recovered->Location = System::Drawing::Point(454, 148);
		this->initial_recovered->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_recovered->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->initial_recovered->Name = L"initial_recovered";
		this->initial_recovered->Size = System::Drawing::Size(130, 26);
		this->initial_recovered->TabIndex = 28;
		this->initial_recovered->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_recovered_ValueChanged);
		// 
		// initial_susceptibles
		// 
		this->initial_susceptibles->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->initial_susceptibles->Location = System::Drawing::Point(436, 62);
		this->initial_susceptibles->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->initial_susceptibles->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7000000, 0, 0, 0 });
		this->initial_susceptibles->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->initial_susceptibles->Name = L"initial_susceptibles";
		this->initial_susceptibles->Size = System::Drawing::Size(130, 26);
		this->initial_susceptibles->TabIndex = 22;
		this->initial_susceptibles->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5800000, 0, 0, 0 });
		this->initial_susceptibles->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_susceptibles_ValueChanged);
		// 
		// pso_optimize_button
		// 
		this->pso_optimize_button->Location = System::Drawing::Point(608, 108);
		this->pso_optimize_button->Name = L"pso_optimize_button";
		this->pso_optimize_button->Size = System::Drawing::Size(164, 36);
		this->pso_optimize_button->TabIndex = 35;
		this->pso_optimize_button->Text = L"Run PSO";
		this->pso_optimize_button->UseVisualStyleBackColor = true;
		this->pso_optimize_button->Click += gcnew System::EventHandler(this, &Form8::pso_optimize_button_Click);
		// 
		// dataSet1
		// 
		this->dataSet1->DataSetName = L"NewDataSet";
		// 
		// pictureBox1
		// 
		this->pictureBox1->Location = System::Drawing::Point(37, 349);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(200, 200);
		this->pictureBox1->TabIndex = 38;
		this->pictureBox1->TabStop = false;
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(608, 154);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(157, 30);
		this->button1->TabIndex = 43;
		this->button1->Text = L"Render-Optimize";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &Form8::button1_Click);
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(287, 124);
		this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(109, 20);
		this->label3->TabIndex = 23;
		this->label3->Text = L"Initial Infected";
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = System::Drawing::Point(287, 154);
		this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(127, 20);
		this->label8->TabIndex = 24;
		this->label8->Text = L"Initial Recovered";
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = System::Drawing::Point(287, 64);
		this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(141, 20);
		this->label9->TabIndex = 25;
		this->label9->Text = L"Initial Susceptibles";
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Location = System::Drawing::Point(290, 182);
		this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(102, 20);
		this->label12->TabIndex = 26;
		this->label12->Text = L"Initial Deaths";
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Location = System::Drawing::Point(287, 94);
		this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(117, 20);
		this->label13->TabIndex = 30;
		this->label13->Text = L"Initial_Exposed";
		// 
		// pictureBox2
		// 
		this->pictureBox2->Location = System::Drawing::Point(1086, 349);
		this->pictureBox2->Name = L"pictureBox2";
		this->pictureBox2->Size = System::Drawing::Size(200, 200);
		this->pictureBox2->TabIndex = 44;
		this->pictureBox2->TabStop = false;
		// 
		// pictureBox3
		// 
		this->pictureBox3->Location = System::Drawing::Point(832, 349);
		this->pictureBox3->Name = L"pictureBox3";
		this->pictureBox3->Size = System::Drawing::Size(200, 200);
		this->pictureBox3->TabIndex = 45;
		this->pictureBox3->TabStop = false;
		// 
		// pictureBox4
		// 
		this->pictureBox4->Location = System::Drawing::Point(557, 349);
		this->pictureBox4->Name = L"pictureBox4";
		this->pictureBox4->Size = System::Drawing::Size(200, 200);
		this->pictureBox4->TabIndex = 46;
		this->pictureBox4->TabStop = false;
		// 
		// pictureBox5
		// 
		this->pictureBox5->Location = System::Drawing::Point(303, 349);
		this->pictureBox5->Name = L"pictureBox5";
		this->pictureBox5->Size = System::Drawing::Size(200, 200);
		this->pictureBox5->TabIndex = 47;
		this->pictureBox5->TabStop = false;
		// 
		// hScrollBar1
		// 
		this->hScrollBar1->Location = System::Drawing::Point(411, 579);
		this->hScrollBar1->Name = L"hScrollBar1";
		this->hScrollBar1->Size = System::Drawing::Size(454, 31);
		this->hScrollBar1->TabIndex = 48;
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(604, 636);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(43, 20);
		this->label4->TabIndex = 49;
		this->label4->Text = L"Time";
		// 
		// Form8
		// 
		this->AutoSize = true;
		this->ClientSize = System::Drawing::Size(1298, 674);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->hScrollBar1);
		this->Controls->Add(this->pictureBox5);
		this->Controls->Add(this->pictureBox4);
		this->Controls->Add(this->pictureBox3);
		this->Controls->Add(this->pictureBox2);
		this->Controls->Add(this->button1);
		this->Controls->Add(this->pictureBox1);
		this->Controls->Add(this->pso_optimize_button);
		this->Controls->Add(this->stepsize_input);
		this->Controls->Add(this->label11);
		this->Controls->Add(this->initial_exposed);
		this->Controls->Add(this->label13);
		this->Controls->Add(this->initial_infected);
		this->Controls->Add(this->initial_deaths);
		this->Controls->Add(this->initial_recovered);
		this->Controls->Add(this->label12);
		this->Controls->Add(this->label9);
		this->Controls->Add(this->label8);
		this->Controls->Add(this->label3);
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
		this->Name = L"Form8";
		this->Text = L"SEIRD PDE";
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form8::Form8_FormClosing);
		this->Load += gcnew System::EventHandler(this, &Form8::Form8_Load);
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
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	private: System::Void Form8_Load(System::Object^ sender, System::EventArgs^ e) {
		//AddRows();
		//Fill();
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

void main_newton() { 	
	/*
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
		   */

	}	
void main_pso() {
/*
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
		   */
	}	
void plot_on_keypress() {
	/*	   //MessageBox::Show(L"plotter called");
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

		   } */
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
private: System::Void Form8_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
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
	//ug::epi::load_csv_data_on_click(this, 5); //5 represents the number of prior plotted lines
	plot_on_keypress();
}
private: System::Void dataGridView1_RowsAdded(System::Object^ sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^ e) {
}	  

/*private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	//DataGridViewRow^ row = (DataGridViewRow^) this->dataGridView1->Rows[0]->Clone();
	//row->Cells[0]->Value = "test";
	
	//this->dataGridView1->Rows->Add(row);

	//BindingSource^ source = gcnew BindingSource();
	//auto list = gcnew IList{ "col1","col2" };
//	System::Collections::IList
	//list->Add("test");
	//source->DataSource = list;
	//dataGridView1->DataSource = source;
	//dataGridView1->Refresh();
	//PopulateDataGrid();
	CreateDataTable();
}


private: void PopulateDataGrid() {

	/*auto row0 = gcnew ArrayList{};
	row0->Add(gcnew String (L"val"));
	row0->Add(gcnew String(L"val"));
	row0->Add(gcnew String(L"val"));
	row0->Add(gcnew String(L"val"));
	row0->Add(gcnew String(L"val"));

	auto row1 = gcnew ArrayList{};
	row1->Add(1);
	row1->Add(2);
	row1->Add(3);
	row1->Add(4);
	row1->Add(5);

	//auto row2 = ;
	row2->Add("val");
	row2->Add("val");
	row2->Add("val");
	row2->Add("val");
	row2->Add("val");

	auto row3 = gcnew ArrayList{};
	row3->Add("val");
	row3->Add("val");
	row3->Add("val");
	row3->Add("val");
	row3->Add("val");

	//dataGridView1->Columns[0]->
		//for (int i = 0; i < dataGridView1->ColumnCount; i++) {
			
			//dataGridView1->Columns[i]->

		//}
	
	for (int i = 0; i < row0->Count; i++) {
		dataGridView1->Rows->Add(row0[i]);
	}
	for (int i = 0; i < row1->Count; i++) {
		dataGridView1->Rows->Add(row1[i]);
	}
	//dataGridView1->Rows->Add(row0);
	//dataGridView1->Rows->Add(row1);
	dataGridView1->Rows->Add(row2);
	dataGridView1->Rows->Add(row3);
	//dataGridView1->Rows->
	/*dataGridView1->Columns[0]->DisplayIndex = 3;
	dataGridView1->Columns[1]->DisplayIndex = 4;
	dataGridView1->Columns[2]->DisplayIndex = 0;
	dataGridView1->Columns[3]->DisplayIndex = 1;
	dataGridView1->Columns[4]->DisplayIndex = 2;


}

private: void LoadFiletotable() {
	//std::string[] data = FILE->ReadAllLines("C:\\Users\\devan\\Desktop\\Book1.csv");
}
private: void CreateDataTable() {
	//Datatable
	/*
	this->col->ColumnName = "test1";
	this->col2->ColumnName = "test2";

	this->datatable->Columns->Add(col);
	this->datatable->Columns->Add(col2);
	dataset->Tables->Add(datatable);
	for (int i = 0; i <= 2; i++)
	{
		row = datatable->NewRow();
		row["test1"] = i;
		row["test2"] = "ParentItem " + i;
		datatable->Rows->Add(row);
	}

	dataGridView1->DataSource = datatable; 
}
private: void AddRows() {
	DataColumn^ col;
	DataRow^ row;
	for (int c = 0; c<= 10; c++) {
		col->ColumnName = c.ToString();
		for (int r = 0; r <= 10; r++) {
			row = dataTable1->NewRow();
			row[c] = "(" + c + "," + r + ")";
			dataTable1->Rows->Add(row);
		}
		dataTable1->Columns->Add(col);
	}
	//dataGridView1->Columns_


	/*
	for (int i = 0; i <= 2; i++)
	{
		row = dataTable1->NewRow();
		
		row["Column1"] = i;
		row["Column2"] = "ParentItem " + i;
		dataTable1->Rows->Add(row);
	}

	for (int c = 0; c < dataTable1->Columns->Count; c++) {
		for (int i = 0; i < dataTable1->Rows->Count; i++) {
			if(c==1 &&i==2){ dataGridView1[c, i]->Style->BackColor = System::Drawing::Color::Blue; }
			
		} 
	}
	
}

private: void SetupDatagrid() {
	/*array<String^>^ colnames = { "1", "2", "3","4", "5", "6","7", "8", "9","10","11" };
	//System::Windows::Forms::DataGridCol
	dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {
		//this->col1DataGridViewTextBoxColumnl, 
	});
	dataGridView2->Rows->Add(10);

	for (auto val : colnames->) {
		DataGridViewColumn^ val = gcnew DataGridViewColumn;
		DataGridViewCell^ cell = gcnew DataGridViewTextBoxCell;
		val->CellTemplate = cell;
		dataGridView2->Columns->Add(val);
	}
	for (int i = 0; i <= 10; i++) {
		DataGridViewColumn^ colname[i] = gcnew DataGridViewColumn; 
		DataGridViewCell^ cell = gcnew DataGridViewTextBoxCell;
		i->CellTemplate = cell;
		//dataGridView2->Columns->Add(i);

	}


	Controls->Add(dataGridView2);
	
}

private: void Fill() {

	//Array^ data = Array::CreateInstance(Int32::typeid, 40,40);
	array<int,2> ^ data2 = gcnew array<int,2>(6,6){
		{ 550550, 1215080, 625550, 850450 ,43434423,232323343},
		{ 483045,  912834, 3285553, 600425,23242445,3345435345 },
		{ 483045,  912834, 100323230, 600425,23242445,3345435345 },
		{ 483045,  912834, 3285553, 10320000,23242445,3345435345 },
		{ 483045,  912834, 3285553, 600425,23242445,3345435345 },
		{ 100000,100000,100000,100000,100000,100000 }
	};
	int dim_x = 100;
	int dim_y = 100;
	std::vector<double> vec(dim_x* dim_y, 0);
	vec[56] = 100000;
	vec[45] = 12345000;
	vec[72] = 5432;
	vec[73] = 54300000;
	vec[70] = 54321;


	dataGridView2->RowHeadersVisible = false;
	dataGridView2->ColumnHeadersVisible = false;
	dataGridView2->AllowUserToAddRows = false;
	dataGridView2->AllowUserToOrderColumns = false;
	dataGridView2->AllowUserToResizeColumns = false;
	dataGridView2->AllowUserToResizeRows = false;
	dataGridView2->RowsDefaultCellStyle->SelectionBackColor = Color::White;

	//dataGridView2->CellBorderStyle = DataGridViewCellBorderStyle->None;
	//int maxRows = ;
	int rowHeight = dataGridView2->Height / (dim_x - 1);
	int colwidth = dataGridView2->Width / dim_x - 1;

	for (int c = 0; c < dim_x; c++) dataGridView2->Columns->Add(c.ToString(), "");
	for (int c = 0; c < dim_x; c++) dataGridView2->Columns[c]->Width = colwidth;
	dataGridView2->Rows->Add(dim_x);
	for (int r = 0; r < dim_x; r++) dataGridView2->Rows[r]->Height = rowHeight;
	/*
	List<Color> baseColors = gcnew List<Color>();  // create a color list
	baseColors.Add(Color->RoyalBlue);
	baseColors.Add(Color->LightSkyBlue);
	baseColors.Add(Color->LightGreen);
	baseColors.Add(Color->Yellow);
	baseColors.Add(Color->Orange);
	baseColors.Add(Color->Red);
	//List<Color> colors = interpolateColors(baseColors, 1000);
	
	for (int r = 0; r < dim_y; r++)
	{
		for (int c = 0; c <dim_x; c++)
		{
			
			if (vec[r*dim_x+c] == 100000)
				dataGridView2[r, c]->Style->BackColor = Color::BurlyWood;
			if (vec[r * dim_x + c] > 100000)
				dataGridView2[r, c]->Style->BackColor = Color::Blue;

			/*
			if ( data2->GetValue(r, c)->Equals(100000)){
				dataGridView2[r, c]->Style->BackColor = Color::BurlyWood;	
			}
			if ((int)data2->GetValue(r, c) > 2000000) {
				dataGridView2[r, c]->Style->BackColor = Color::AliceBlue;
			}
			

			//dataGridView2[r,c] = 

		}
	}

	
}
*/

/*
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		   int dimx = 200; //dimensions of picturebox
		   int dimy = 200; //dimensions of picturebox
		   Bitmap^ img = gcnew Bitmap(dimx, dimy);
		   std::vector<float> u0 = initial_values(1, 1, 0.1); //initial values should look like a circle on the grid
		   float maxdist = (0 - 100) *(0 - 100) + (0 - 100) *(0 - 100);
		   for (int i = 0; i < dimy; i++) {
			   for (int j = 0; j < dimx; j++) {
				   float dist = (i - 100)* (i - 100) + (j - 100) *(j - 100);
				   float val = 255 * (dist / maxdist);
				   System::Drawing::Color c = System::Drawing::Color::FromArgb(255 - val, 1, 0);
				   img->SetPixel(i, j, c);
			   }
		   }

		   this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(img));

}

void set_radial_values(std::vector<float>& u0, typename std::vector<float>::value_type x_points, typename std::vector<float>::value_type y_points, typename std::vector<float>::value_type dimX, typename std::vector<float>::value_type dimY, typename std::vector<float>::value_type hx, typename std::vector<float>::value_type radius, typename std::vector<float>::value_type val, int current_dimension) {
				  for (int i = 0; i < x_points; i++) {
					  for (int j = 0; j < y_points; j++) {
						  float worldX = ((i + 1.0) / x_points) * dimX;
						  float worldY = ((j + 1.0) / y_points) * dimY;
						  int offset = current_dimension * x_points * y_points;
						  float a = (worldX - 0.5 * dimX);
						  float b = (worldY - 0.5 * dimY);
						  float r = 0.1;
						  if ((a * a + b * b) <= r) {
							  u0[i * x_points + j + offset] = val;
						  }
						  else {
							  u0[i * x_points + j + offset] = 0;
						  }
					  }

				  }
}

std::vector<float> initial_values(typename std::vector<float>::value_type dimX, typename std::vector<float>::value_type dimY, typename std::vector<float>::value_type hx) {
				 
				  size_t x_points = (dimX / hx) + 1;
				  size_t y_points = (dimY / hx) + 1;

				  size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
				  std::vector<float> u0(nVars * 5, float(0)); //number of vertices in discretization

				  //Sets initial values for first dimension
				  float r1 = 0.1;
				  float v1 = 100;
				  set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1, 0);

				  //Sets initial values for second dimension
				  float r2 = 100;
				  float v2 = 20;
				  set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r2, v2, 1);


				  return u0;
}
*/	   
	  
void set_radial_values(std::vector<double>& u0, typename std::vector<double>::value_type x_points, typename std::vector<double>::value_type y_points, typename std::vector<double>::value_type dimX, typename std::vector<double>::value_type dimY, typename std::vector<double>::value_type hx, typename std::vector<double>::value_type radius, typename std::vector<double>::value_type val, int current_dimension) {
	using F = typename std::vector<double>::value_type;
	for (int i = 0; i < y_points; i++) {
		for (int j = 0; j < x_points; j++) {
			F worldX = dimY - ((i) / (y_points - 1.0)) * dimY;
			F worldY = ((j) / (x_points - 1.0)) * dimX;
			int offset = current_dimension * x_points * y_points;
			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F r = 0.2;
			if ((a * a + b * b) <= radius * radius) {
				float v = 1 - (a * a + b * b) / (radius * radius);
				u0[i * x_points + j + offset] = val * v;
			}
			else {
				u0[i * x_points + j + offset] = 0;
			}
		}

	}
}

std::vector<double> initial_values(typename std::vector<double>::value_type dimX, typename std::vector<double>::value_type dimY, typename std::vector<double>::value_type hx) {
	using F = typename std::vector<double>::value_type;

	size_t x_points = (dimX / hx) + 1;
	size_t y_points = (dimY / hx) + 1;

	size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
	std::vector<F> u0(nVars * 5, F(0)); //number of vertices in discretization
	MessageBox::Show(gcnew String(std::to_string(nVars).c_str()));
	//Sets initial values for first dimension
	F r1 = 0.3;
	F v1 = 100;
	set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1, 0);

	//Sets initial values for second dimension
	F r2 = 0.1;
	F v2 = 50;
	set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r2, v2, 1);

	//Sets initial values for fifth dimension
	F r4 = 100;
	F v4 = 100;
	//set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r4, v4, 4);


	return u0;
}

void print_initialvalues(const std::vector<float> u, float dimX, float dimY, float hx, int current_dimension) {
	size_t x_points = (dimX / hx) + 1;
	size_t y_points = (dimY / hx) + 1;
	int offset = current_dimension * x_points * y_points;
	for (int i = 0; i < x_points; i++) {

		for (int j = 0; j < y_points; j++) {
			//	std::cout << u[i * x_points + j + offset] << "\t";
		}
		//	std::cout << "\n";
	}
}



void image_to_grid(int index_image_i, int index_image_j, int image_width, int image_height, int grid_width, int grid_height, int& i_g, int& j_g) {
	float ratio_i = index_image_i / (image_width - 1.0);
	float ratio_j = index_image_j / (image_height - 1.0);

	i_g = ratio_i * (grid_width - 1);
	j_g = ratio_j * (grid_height - 1);
}

void determine_color(double val, double min_val, double max_val, int& r, int& g, int& b) {
	float ratio = (val - min_val) / (max_val - min_val);
	//std::cout<<"val:"<<val-min_val<<"\n";
	int start_r = 0;
	int start_g = 0;
	int start_b = 0;

	r = start_r + (255 - start_r) * ratio;
	g = start_g + (255 - start_g) * ratio;
	b = start_b + (255 - start_b) * ratio;
}


#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int img_x = 200; //dimensions of picturebox
		int img_y = 200; //dimensions of picturebox
		Bitmap^ img = gcnew Bitmap(img_x, img_y);
		double h = 0.001;
		double dimX = 1.0;
		double dimY = 1.0;
		size_t grid_x = (dimX / h) + 1;
		size_t grid_y = (dimY / h) + 1;
		std::vector<double> u0 = initial_values(1, 1, h);
		double min_val = *std::min_element(u0.begin(), u0.end());
		double max_val = *std::max_element(u0.begin(), u0.end());

		for (int i = 0; i < u0.size(); i++) {
			//	MessageBox::Show(gcnew String(std::to_string(u0[i]).c_str()));
			//MessageBox::Show ( gcnew String(std::to_string(u0.size()).c_str()));
		}

		for (int i = 0; i < img_y; i++) {
			for (int j = 0; j < img_x; j++) {
				int i_g;
				int j_g;
				image_to_grid(j, i, img_x, img_y, grid_x, grid_y, j_g, i_g);
				int r;
				int g;
				int b;
				//	MessageBox::Show(gcnew String(std::to_string(j_g).c_str()));
				determine_color(u0[i_g * grid_x + j_g], min_val, max_val, r, g, b);
				System::Drawing::Color c = System::Drawing::Color::FromArgb(r, g, b);
				img->SetPixel(j, i, c);
			}
		}
		img->SetPixel(0, 0, System::Drawing::Color::Blue);
		this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(img));

	}

};
}
