#pragma once

#include<limits>
#include<vector>
#include <string>
#include "../../../../models/seird_pde.h"
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
	/// Zusammenfassung für Form8
	/// </summary>
	public ref class Form8 : public System::Windows::Forms::Form
	{
	public:
		Form8(void)
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

	//Newton Settings
	private: double convergence_parameter;

	private: std::string* user_selected_optimization_path;

	private: System::Windows::Forms::Button^ Optimize_button;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ t_start_input;
	private: System::Windows::Forms::NumericUpDown^ t_end_input;
	private: System::Windows::Forms::NumericUpDown^ stepsize_input;
	private: System::Windows::Forms::Label^ label11;


	private: System::Windows::Forms::NumericUpDown^ diffusion_input;





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



private: System::Windows::Forms::Label^ label12;

private: System::Windows::Forms::PictureBox^ pictureBox2;
private: System::Windows::Forms::PictureBox^ pictureBox3;
private: System::Windows::Forms::PictureBox^ pictureBox4;
private: System::Windows::Forms::PictureBox^ pictureBox5;
private: System::Windows::Forms::HScrollBar^ hScrollBar1;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::NumericUpDown^ scroll_val;
private: System::Windows::Forms::Label^ max_label;
private: System::Windows::Forms::Label^ min_label;
private: System::Windows::Forms::PictureBox^ legend_box;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::Label^ label14;
private: System::Windows::Forms::GroupBox^ groupBox2;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::NumericUpDown^ v1_input;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::NumericUpDown^ r1_input;
private: System::Windows::Forms::Label^ label20;
private: System::Windows::Forms::NumericUpDown^ v5_input;
private: System::Windows::Forms::Label^ label21;
private: System::Windows::Forms::NumericUpDown^ r5_input;
private: System::Windows::Forms::Label^ label18;
private: System::Windows::Forms::NumericUpDown^ v4_input;
private: System::Windows::Forms::Label^ label19;
private: System::Windows::Forms::NumericUpDown^ r4_input;
private: System::Windows::Forms::Label^ label16;
private: System::Windows::Forms::NumericUpDown^ v3_input;
private: System::Windows::Forms::Label^ label17;
private: System::Windows::Forms::NumericUpDown^ r3_input;
private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::NumericUpDown^ v2_input;
private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::NumericUpDown^ r2_input;

private: System::ComponentModel::IContainer^ components;

//private: std::vector<double> generated;


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
		this->diffusion_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->pso_optimize_button = (gcnew System::Windows::Forms::Button());
		this->dataSet1 = (gcnew System::Data::DataSet());
		this->dataTable1 = (gcnew System::Data::DataTable());
		this->dataColumn1 = (gcnew System::Data::DataColumn());
		this->dataColumn2 = (gcnew System::Data::DataColumn());
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
		this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
		this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->scroll_val = (gcnew System::Windows::Forms::NumericUpDown());
		this->max_label = (gcnew System::Windows::Forms::Label());
		this->min_label = (gcnew System::Windows::Forms::Label());
		this->legend_box = (gcnew System::Windows::Forms::PictureBox());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
		this->label20 = (gcnew System::Windows::Forms::Label());
		this->v5_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label21 = (gcnew System::Windows::Forms::Label());
		this->r5_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label18 = (gcnew System::Windows::Forms::Label());
		this->v4_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label19 = (gcnew System::Windows::Forms::Label());
		this->r4_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label16 = (gcnew System::Windows::Forms::Label());
		this->v3_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label17 = (gcnew System::Windows::Forms::Label());
		this->r3_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->v2_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label15 = (gcnew System::Windows::Forms::Label());
		this->r2_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->v1_input = (gcnew System::Windows::Forms::NumericUpDown());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->r1_input = (gcnew System::Windows::Forms::NumericUpDown());
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
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->diffusion_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scroll_val))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->legend_box))->BeginInit();
		this->groupBox2->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v5_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r5_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v4_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r4_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v3_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r3_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v2_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r2_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v1_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r1_input))->BeginInit();
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
		this->groupBox1->Location = System::Drawing::Point(37, 50);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(1277, 62);
		this->groupBox1->TabIndex = 5;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Parameters";
		// 
		// pp_input
		// 
		this->pp_input->DecimalPlaces = 4;
		this->pp_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->pp_input->Location = System::Drawing::Point(1113, 20);
		this->pp_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->pp_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->pp_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->pp_input->Name = L"pp_input";
		this->pp_input->Size = System::Drawing::Size(130, 20);
		this->pp_input->TabIndex = 15;
		this->pp_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
		this->pp_input->ValueChanged += gcnew System::EventHandler(this, &Form8::pp_input_ValueChanged);
		// 
		// qq_input
		// 
		this->qq_input->DecimalPlaces = 4;
		this->qq_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->qq_input->Location = System::Drawing::Point(853, 23);
		this->qq_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->qq_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->qq_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->qq_input->Name = L"qq_input";
		this->qq_input->Size = System::Drawing::Size(121, 20);
		this->qq_input->TabIndex = 14;
		this->qq_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 14, 0, 0, 0 });
		this->qq_input->ValueChanged += gcnew System::EventHandler(this, &Form8::qq_input_ValueChanged);
		// 
		// theta_input
		// 
		this->theta_input->DecimalPlaces = 8;
		this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->theta_input->Location = System::Drawing::Point(589, 22);
		this->theta_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->theta_input->Name = L"theta_input";
		this->theta_input->Size = System::Drawing::Size(130, 20);
		this->theta_input->TabIndex = 13;
		this->theta_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form8::theta_input_ValueChanged);
		// 
		// kappa_input
		// 
		this->kappa_input->DecimalPlaces = 8;
		this->kappa_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->kappa_input->Location = System::Drawing::Point(354, 25);
		this->kappa_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->kappa_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->kappa_input->Name = L"kappa_input";
		this->kappa_input->Size = System::Drawing::Size(130, 20);
		this->kappa_input->TabIndex = 12;
		this->kappa_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form8::kappa_input_ValueChanged);
		// 
		// alpha_input
		// 
		this->alpha_input->DecimalPlaces = 9;
		this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->alpha_input->Location = System::Drawing::Point(94, 25);
		this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->alpha_input->Name = L"alpha_input";
		this->alpha_input->Size = System::Drawing::Size(130, 20);
		this->alpha_input->TabIndex = 11;
		this->alpha_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 78, 0, 0, 524288 });
		this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form8::alpha_input_ValueChanged);
		// 
		// pp_check
		// 
		this->pp_check->AutoSize = true;
		this->pp_check->Location = System::Drawing::Point(1022, 23);
		this->pp_check->Name = L"pp_check";
		this->pp_check->Size = System::Drawing::Size(38, 17);
		this->pp_check->TabIndex = 10;
		this->pp_check->Text = L"pp";
		this->pp_check->UseVisualStyleBackColor = true;
		this->pp_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::pp_check_CheckedChanged);
		// 
		// alpha_check
		// 
		this->alpha_check->AutoSize = true;
		this->alpha_check->Location = System::Drawing::Point(6, 27);
		this->alpha_check->Name = L"alpha_check";
		this->alpha_check->Size = System::Drawing::Size(52, 17);
		this->alpha_check->TabIndex = 6;
		this->alpha_check->Text = L"alpha";
		this->alpha_check->UseVisualStyleBackColor = true;
		this->alpha_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::alpha_check_CheckedChanged);
		// 
		// qq_check
		// 
		this->qq_check->AutoSize = true;
		this->qq_check->Location = System::Drawing::Point(765, 21);
		this->qq_check->Name = L"qq_check";
		this->qq_check->Size = System::Drawing::Size(38, 17);
		this->qq_check->TabIndex = 9;
		this->qq_check->Text = L"qq";
		this->qq_check->UseVisualStyleBackColor = true;
		this->qq_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::qq_check_CheckedChanged);
		// 
		// kappa_check
		// 
		this->kappa_check->AutoSize = true;
		this->kappa_check->Location = System::Drawing::Point(254, 25);
		this->kappa_check->Name = L"kappa_check";
		this->kappa_check->Size = System::Drawing::Size(56, 17);
		this->kappa_check->TabIndex = 7;
		this->kappa_check->Text = L"kappa";
		this->kappa_check->UseVisualStyleBackColor = true;
		this->kappa_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::kappa_check_CheckedChanged);
		// 
		// theta_check
		// 
		this->theta_check->AutoSize = true;
		this->theta_check->Location = System::Drawing::Point(510, 25);
		this->theta_check->Name = L"theta_check";
		this->theta_check->Size = System::Drawing::Size(50, 17);
		this->theta_check->TabIndex = 8;
		this->theta_check->Text = L"theta";
		this->theta_check->UseVisualStyleBackColor = true;
		this->theta_check->CheckedChanged += gcnew System::EventHandler(this, &Form8::theta_check_CheckedChanged);
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
		this->menuStrip1->Size = System::Drawing::Size(1393, 24);
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
		this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::loadFileToolStripMenuItem_Click);
		// 
		// loadExperimentalDatatToolStripMenuItem
		// 
		this->loadExperimentalDatatToolStripMenuItem->Name = L"loadExperimentalDatatToolStripMenuItem";
		this->loadExperimentalDatatToolStripMenuItem->Size = System::Drawing::Size(254, 22);
		this->loadExperimentalDatatToolStripMenuItem->Text = L"Load Experimental Data";
		this->loadExperimentalDatatToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::loadExperimentalDatatToolStripMenuItem_Click);
		// 
		// settingsForPSOToolStripMenuItem
		// 
		this->settingsForPSOToolStripMenuItem->Name = L"settingsForPSOToolStripMenuItem";
		this->settingsForPSOToolStripMenuItem->Size = System::Drawing::Size(106, 20);
		this->settingsForPSOToolStripMenuItem->Text = L"Settings For PSO";
		this->settingsForPSOToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::settingsForPSOToolStripMenuItem_Click);
		// 
		// settingForGaussNewtonToolStripMenuItem
		// 
		this->settingForGaussNewtonToolStripMenuItem->Name = L"settingForGaussNewtonToolStripMenuItem";
		this->settingForGaussNewtonToolStripMenuItem->Size = System::Drawing::Size(157, 20);
		this->settingForGaussNewtonToolStripMenuItem->Text = L"Setting For Gauss-Newton";
		this->settingForGaussNewtonToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form8::settingForGaussNewtonToolStripMenuItem_Click);
		// 
		// cancel_button
		// 
		this->cancel_button->Location = System::Drawing::Point(1273, 616);
		this->cancel_button->Name = L"cancel_button";
		this->cancel_button->Size = System::Drawing::Size(108, 38);
		this->cancel_button->TabIndex = 7;
		this->cancel_button->Text = L"Cancel";
		this->cancel_button->UseVisualStyleBackColor = true;
		this->cancel_button->Click += gcnew System::EventHandler(this, &Form8::cancel_button_Click);
		// 
		// Optimize_button
		// 
		this->Optimize_button->Location = System::Drawing::Point(727, 134);
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
		this->label1->Location = System::Drawing::Point(39, 148);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(36, 13);
		this->label1->TabIndex = 9;
		this->label1->Text = L"t_start";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(39, 174);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(34, 13);
		this->label2->TabIndex = 10;
		this->label2->Text = L"t_end";
		// 
		// t_start_input
		// 
		this->t_start_input->DecimalPlaces = 2;
		this->t_start_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_start_input->Location = System::Drawing::Point(140, 146);
		this->t_start_input->Name = L"t_start_input";
		this->t_start_input->Size = System::Drawing::Size(130, 20);
		this->t_start_input->TabIndex = 11;
		this->t_start_input->ValueChanged += gcnew System::EventHandler(this, &Form8::t_start_input_ValueChanged);
		// 
		// t_end_input
		// 
		this->t_end_input->DecimalPlaces = 4;
		this->t_end_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->t_end_input->Location = System::Drawing::Point(140, 172);
		this->t_end_input->Name = L"t_end_input";
		this->t_end_input->Size = System::Drawing::Size(130, 20);
		this->t_end_input->TabIndex = 12;
		this->t_end_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 65536 });
		this->t_end_input->ValueChanged += gcnew System::EventHandler(this, &Form8::t_end_input_ValueChanged);
		// 
		// stepsize_input
		// 
		this->stepsize_input->DecimalPlaces = 6;
		this->stepsize_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->stepsize_input->Location = System::Drawing::Point(503, 172);
		this->stepsize_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->stepsize_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepsize_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
		this->stepsize_input->Name = L"stepsize_input";
		this->stepsize_input->Size = System::Drawing::Size(130, 20);
		this->stepsize_input->TabIndex = 33;
		this->stepsize_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->stepsize_input->ValueChanged += gcnew System::EventHandler(this, &Form8::stepsize_input_ValueChanged);
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(310, 175);
		this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(153, 13);
		this->label11->TabIndex = 32;
		this->label11->Text = L"Stepsize: Saptial and Temporal";
		this->label11->Click += gcnew System::EventHandler(this, &Form8::label11_Click);
		// 
		// diffusion_input
		// 
		this->diffusion_input->DecimalPlaces = 9;
		this->diffusion_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->diffusion_input->Location = System::Drawing::Point(503, 141);
		this->diffusion_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->diffusion_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
		this->diffusion_input->Name = L"diffusion_input";
		this->diffusion_input->Size = System::Drawing::Size(130, 20);
		this->diffusion_input->TabIndex = 29;
		this->diffusion_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->diffusion_input->ValueChanged += gcnew System::EventHandler(this, &Form8::initial_deaths_ValueChanged);
		// 
		// pso_optimize_button
		// 
		this->pso_optimize_button->Location = System::Drawing::Point(727, 178);
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
		this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pictureBox1->Location = System::Drawing::Point(37, 349);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(200, 200);
		this->pictureBox1->TabIndex = 38;
		this->pictureBox1->TabStop = false;
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(897, 134);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(164, 38);
		this->button1->TabIndex = 43;
		this->button1->Text = L"Run Simulation";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &Form8::button1_Click);
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Location = System::Drawing::Point(415, 146);
		this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(48, 13);
		this->label12->TabIndex = 26;
		this->label12->Text = L"Diffusion";
		// 
		// pictureBox2
		// 
		this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pictureBox2->Location = System::Drawing::Point(291, 349);
		this->pictureBox2->Name = L"pictureBox2";
		this->pictureBox2->Size = System::Drawing::Size(200, 200);
		this->pictureBox2->TabIndex = 44;
		this->pictureBox2->TabStop = false;
		// 
		// pictureBox3
		// 
		this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pictureBox3->Location = System::Drawing::Point(547, 349);
		this->pictureBox3->Name = L"pictureBox3";
		this->pictureBox3->Size = System::Drawing::Size(200, 200);
		this->pictureBox3->TabIndex = 45;
		this->pictureBox3->TabStop = false;
		// 
		// pictureBox4
		// 
		this->pictureBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pictureBox4->Location = System::Drawing::Point(802, 349);
		this->pictureBox4->Name = L"pictureBox4";
		this->pictureBox4->Size = System::Drawing::Size(200, 200);
		this->pictureBox4->TabIndex = 46;
		this->pictureBox4->TabStop = false;
		// 
		// pictureBox5
		// 
		this->pictureBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->pictureBox5->Location = System::Drawing::Point(1059, 349);
		this->pictureBox5->Name = L"pictureBox5";
		this->pictureBox5->Size = System::Drawing::Size(200, 200);
		this->pictureBox5->TabIndex = 47;
		this->pictureBox5->TabStop = false;
		// 
		// hScrollBar1
		// 
		this->hScrollBar1->Location = System::Drawing::Point(425, 616);
		this->hScrollBar1->Name = L"hScrollBar1";
		this->hScrollBar1->RightToLeft = System::Windows::Forms::RightToLeft::No;
		this->hScrollBar1->Size = System::Drawing::Size(454, 26);
		this->hScrollBar1->TabIndex = 48;
		this->hScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form8::hScrollBar1_Scroll);
		this->hScrollBar1->ValueChanged += gcnew System::EventHandler(this, &Form8::hScrollBar1_ValueChanged);
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(959, 645);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(30, 13);
		this->label4->TabIndex = 49;
		this->label4->Text = L"Time";
		// 
		// scroll_val
		// 
		this->scroll_val->DecimalPlaces = 5;
		this->scroll_val->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->scroll_val->Location = System::Drawing::Point(932, 616);
		this->scroll_val->Name = L"scroll_val";
		this->scroll_val->Size = System::Drawing::Size(120, 20);
		this->scroll_val->TabIndex = 50;
		this->scroll_val->ValueChanged += gcnew System::EventHandler(this, &Form8::scroll_val_ValueChanged);
		// 
		// max_label
		// 
		this->max_label->AutoSize = true;
		this->max_label->Location = System::Drawing::Point(1326, 348);
		this->max_label->Name = L"max_label";
		this->max_label->Size = System::Drawing::Size(27, 13);
		this->max_label->TabIndex = 51;
		this->max_label->Text = L"Max";
		// 
		// min_label
		// 
		this->min_label->AutoSize = true;
		this->min_label->Location = System::Drawing::Point(1326, 529);
		this->min_label->Name = L"min_label";
		this->min_label->Size = System::Drawing::Size(24, 13);
		this->min_label->TabIndex = 52;
		this->min_label->Text = L"Min";
		// 
		// legend_box
		// 
		this->legend_box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->legend_box->Location = System::Drawing::Point(1292, 348);
		this->legend_box->Name = L"legend_box";
		this->legend_box->Size = System::Drawing::Size(22, 200);
		this->legend_box->TabIndex = 53;
		this->legend_box->TabStop = false;
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(105, 566);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(67, 13);
		this->label5->TabIndex = 54;
		this->label5->Text = L"Susceptibles";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(369, 566);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(48, 13);
		this->label6->TabIndex = 55;
		this->label6->Text = L"Exposed";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(623, 566);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(46, 13);
		this->label7->TabIndex = 56;
		this->label7->Text = L"Infected";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = System::Drawing::Point(878, 566);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(54, 13);
		this->label10->TabIndex = 57;
		this->label10->Text = L"Recoverd";
		// 
		// label14
		// 
		this->label14->AutoSize = true;
		this->label14->Location = System::Drawing::Point(1138, 566);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(56, 13);
		this->label14->TabIndex = 58;
		this->label14->Text = L"Deceased";
		// 
		// groupBox2
		// 
		this->groupBox2->Controls->Add(this->label20);
		this->groupBox2->Controls->Add(this->v5_input);
		this->groupBox2->Controls->Add(this->label21);
		this->groupBox2->Controls->Add(this->r5_input);
		this->groupBox2->Controls->Add(this->label18);
		this->groupBox2->Controls->Add(this->v4_input);
		this->groupBox2->Controls->Add(this->label19);
		this->groupBox2->Controls->Add(this->r4_input);
		this->groupBox2->Controls->Add(this->label16);
		this->groupBox2->Controls->Add(this->v3_input);
		this->groupBox2->Controls->Add(this->label17);
		this->groupBox2->Controls->Add(this->r3_input);
		this->groupBox2->Controls->Add(this->label13);
		this->groupBox2->Controls->Add(this->v2_input);
		this->groupBox2->Controls->Add(this->label15);
		this->groupBox2->Controls->Add(this->r2_input);
		this->groupBox2->Controls->Add(this->label9);
		this->groupBox2->Controls->Add(this->v1_input);
		this->groupBox2->Controls->Add(this->label3);
		this->groupBox2->Controls->Add(this->r1_input);
		this->groupBox2->Location = System::Drawing::Point(37, 232);
		this->groupBox2->Name = L"groupBox2";
		this->groupBox2->Size = System::Drawing::Size(1277, 100);
		this->groupBox2->TabIndex = 59;
		this->groupBox2->TabStop = false;
		this->groupBox2->Text = L"Initial Values";
		// 
		// label20
		// 
		this->label20->AutoSize = true;
		this->label20->Location = System::Drawing::Point(1043, 59);
		this->label20->Name = L"label20";
		this->label20->Size = System::Drawing::Size(19, 13);
		this->label20->TabIndex = 74;
		this->label20->Text = L"v5";
		// 
		// v5_input
		// 
		this->v5_input->DecimalPlaces = 2;
		this->v5_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->v5_input->Location = System::Drawing::Point(1090, 57);
		this->v5_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
		this->v5_input->Name = L"v5_input";
		this->v5_input->Size = System::Drawing::Size(120, 20);
		this->v5_input->TabIndex = 73;
		this->v5_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		// 
		// label21
		// 
		this->label21->AutoSize = true;
		this->label21->Location = System::Drawing::Point(1043, 25);
		this->label21->Name = L"label21";
		this->label21->Size = System::Drawing::Size(16, 13);
		this->label21->TabIndex = 72;
		this->label21->Text = L"r5";
		// 
		// r5_input
		// 
		this->r5_input->DecimalPlaces = 2;
		this->r5_input->Location = System::Drawing::Point(1090, 23);
		this->r5_input->Name = L"r5_input";
		this->r5_input->Size = System::Drawing::Size(120, 20);
		this->r5_input->TabIndex = 71;
		this->r5_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// label18
		// 
		this->label18->AutoSize = true;
		this->label18->Location = System::Drawing::Point(786, 56);
		this->label18->Name = L"label18";
		this->label18->Size = System::Drawing::Size(19, 13);
		this->label18->TabIndex = 70;
		this->label18->Text = L"v4";
		// 
		// v4_input
		// 
		this->v4_input->DecimalPlaces = 2;
		this->v4_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->v4_input->Location = System::Drawing::Point(833, 54);
		this->v4_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
		this->v4_input->Name = L"v4_input";
		this->v4_input->Size = System::Drawing::Size(120, 20);
		this->v4_input->TabIndex = 69;
		this->v4_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		// 
		// label19
		// 
		this->label19->AutoSize = true;
		this->label19->Location = System::Drawing::Point(786, 22);
		this->label19->Name = L"label19";
		this->label19->Size = System::Drawing::Size(16, 13);
		this->label19->TabIndex = 68;
		this->label19->Text = L"r4";
		// 
		// r4_input
		// 
		this->r4_input->DecimalPlaces = 2;
		this->r4_input->Location = System::Drawing::Point(833, 20);
		this->r4_input->Name = L"r4_input";
		this->r4_input->Size = System::Drawing::Size(120, 20);
		this->r4_input->TabIndex = 67;
		this->r4_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// label16
		// 
		this->label16->AutoSize = true;
		this->label16->Location = System::Drawing::Point(531, 56);
		this->label16->Name = L"label16";
		this->label16->Size = System::Drawing::Size(19, 13);
		this->label16->TabIndex = 66;
		this->label16->Text = L"v3";
		// 
		// v3_input
		// 
		this->v3_input->DecimalPlaces = 2;
		this->v3_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->v3_input->Location = System::Drawing::Point(578, 54);
		this->v3_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
		this->v3_input->Name = L"v3_input";
		this->v3_input->Size = System::Drawing::Size(120, 20);
		this->v3_input->TabIndex = 65;
		this->v3_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		// 
		// label17
		// 
		this->label17->AutoSize = true;
		this->label17->Location = System::Drawing::Point(531, 22);
		this->label17->Name = L"label17";
		this->label17->Size = System::Drawing::Size(16, 13);
		this->label17->TabIndex = 64;
		this->label17->Text = L"r3";
		// 
		// r3_input
		// 
		this->r3_input->DecimalPlaces = 2;
		this->r3_input->Location = System::Drawing::Point(578, 20);
		this->r3_input->Name = L"r3_input";
		this->r3_input->Size = System::Drawing::Size(120, 20);
		this->r3_input->TabIndex = 63;
		this->r3_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Location = System::Drawing::Point(275, 56);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(19, 13);
		this->label13->TabIndex = 62;
		this->label13->Text = L"v2";
		// 
		// v2_input
		// 
		this->v2_input->DecimalPlaces = 2;
		this->v2_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->v2_input->Location = System::Drawing::Point(322, 54);
		this->v2_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
		this->v2_input->Name = L"v2_input";
		this->v2_input->Size = System::Drawing::Size(120, 20);
		this->v2_input->TabIndex = 61;
		this->v2_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		// 
		// label15
		// 
		this->label15->AutoSize = true;
		this->label15->Location = System::Drawing::Point(275, 22);
		this->label15->Name = L"label15";
		this->label15->Size = System::Drawing::Size(16, 13);
		this->label15->TabIndex = 60;
		this->label15->Text = L"r2";
		// 
		// r2_input
		// 
		this->r2_input->DecimalPlaces = 2;
		this->r2_input->Location = System::Drawing::Point(322, 20);
		this->r2_input->Name = L"r2_input";
		this->r2_input->Size = System::Drawing::Size(120, 20);
		this->r2_input->TabIndex = 59;
		this->r2_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = System::Drawing::Point(57, 61);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(19, 13);
		this->label9->TabIndex = 58;
		this->label9->Text = L"v1";
		// 
		// v1_input
		// 
		this->v1_input->DecimalPlaces = 2;
		this->v1_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
		this->v1_input->Location = System::Drawing::Point(104, 59);
		this->v1_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
		this->v1_input->Name = L"v1_input";
		this->v1_input->Size = System::Drawing::Size(120, 20);
		this->v1_input->TabIndex = 57;
		this->v1_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(57, 27);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(16, 13);
		this->label3->TabIndex = 56;
		this->label3->Text = L"r1";
		// 
		// r1_input
		// 
		this->r1_input->DecimalPlaces = 2;
		this->r1_input->Location = System::Drawing::Point(104, 25);
		this->r1_input->Name = L"r1_input";
		this->r1_input->Size = System::Drawing::Size(120, 20);
		this->r1_input->TabIndex = 0;
		this->r1_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// Form8
		// 
		this->AutoSize = true;
		this->BackColor = System::Drawing::SystemColors::Control;
		this->ClientSize = System::Drawing::Size(1393, 674);
		this->Controls->Add(this->groupBox2);
		this->Controls->Add(this->label14);
		this->Controls->Add(this->label10);
		this->Controls->Add(this->label7);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->legend_box);
		this->Controls->Add(this->min_label);
		this->Controls->Add(this->max_label);
		this->Controls->Add(this->scroll_val);
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
		this->Controls->Add(this->diffusion_input);
		this->Controls->Add(this->label12);
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
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->diffusion_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTable1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scroll_val))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->legend_box))->EndInit();
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v5_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r5_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v4_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r4_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v3_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r3_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v2_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r2_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->v1_input))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r1_input))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	private: System::Void Form8_Load(System::Object^ sender, System::EventArgs^ e) {
		//AddRows();
		//Fill();
		user_datapoints =new std::vector<double>();
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
	Application::Exit();
	//Close();
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

/*
		// FOR DATAGRIDVIEW


private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

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

std::vector<double> initial_values(typename std::vector<double>::value_type dimX, typename std::vector<double>::value_type dimY, typename std::vector<double>::value_type hx, typename std::vector<double>::value_type r1,
	typename std::vector<double>::value_type r2, typename std::vector<double>::value_type r3, typename std::vector<double>::value_type r4, typename std::vector<double>::value_type r5,
	typename std::vector<double>::value_type v1, typename std::vector<double>::value_type v2, typename std::vector<double>::value_type v3, typename std::vector<double>::value_type v4,
	typename std::vector<double>::value_type v5 ) {
	using F = typename std::vector<double>::value_type;
	
	size_t x_points = (dimX / hx) + 1; //1001
	size_t y_points = (dimY / hx) + 1;

	size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
	std::vector<F> u0(nVars * 5, F(0)); //number of vertices in discretization
	
		//F r1 = 1;
		//F v1 = 100;
		set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1, 0);
	
		//F r2 = 3;
		//F v2 = 100;
		set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r2, v2, 1);
		
		//F r3 = 6;
		//F v3 = 100;
		set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r3, v3, 2);
		
		//F r4 = 9;
		//F v4 = 100;
		set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r4, v4, 3);
	
		//F r5 = 12;
		//F v5 = 100;
		set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r5, v5, 4);
	

	return u0;
}

void set_gaussian_values(std::vector<double>& u0, typename std::vector<double>::value_type x_points, typename std::vector<double>::value_type y_points, typename std::vector<double>::value_type dimX, typename std::vector<double>::value_type dimY, typename std::vector<double>::value_type hx, typename std::vector<double>::value_type radius, typename std::vector<double>::value_type val, int current_dimension) {
	using F = typename std::vector<double>::value_type;
	for (int i = 0; i < y_points; i++) {
		for (int j = 0; j < x_points; j++) {
			F worldX = dimY - ((i) / (y_points - 1.0)) * dimY;
			F worldY = ((j) / (x_points - 1.0)) * dimX;
			int offset = current_dimension * x_points * y_points;
			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F sigma = radius;
			F x = (a * a + b * b);
			//MessageBox::Show(gcnew String(std::to_string(x).c_str()));
			//MessageBox::Show(gcnew String(std::to_string(i * x_points + j + offset).c_str()));
			//MessageBox::Show(gcnew String(std::to_string(val * (std::exp(-sigma * x))).c_str()));
			u0[i * x_points + j + offset] = val * (std::exp(-sigma * x));

		}

	}
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

		Run_SERID_PDE();
		plot_heatmaps("/output0.txt");
		
}

void plot_heatmaps(std::string filenum) {
	double t_start = System::Decimal::ToDouble(this->t_start_input->Value);
	double t_end = System::Decimal::ToDouble(this->t_end_input->Value);
	double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);

	int img_x = 200; //dimensions of picturebox
	int img_y = 200; //dimensions of picturebox
	double dimX = 1.0;
	double dimY = 1.0;
	size_t grid_x = (dimX / stepsize) + 1;
	size_t grid_y = (dimY / stepsize) + 1;

	std::string delimiter = "\t";
	int gridx = (int)grid_x;

	if (user_datapoints == nullptr) {
		user_datapoints = new std::vector<double>();
	}
	else {
		delete user_datapoints;
		user_datapoints = new std::vector<double>();
	}

	if (user_selected_optimization_path == nullptr) {
		MessageBox::Show(L"Please specify the directory for Output generation");
	}
	else {

		co::ErrorCode err;
		try {
			std::string path = *user_selected_optimization_path + filenum;
			err = co::utility::parse_csv(path, *user_datapoints, delimiter, &gridx);

			//MessageBox::Show(gcnew String(path.c_str()));

		}
		catch (System::Exception^ e) {
			MessageBox::Show(L"Could not read file" + e);
		}
		//if (err != co::ErrorCode::NoError)MessageBox::Show(L"Error");
		if (err == co::ErrorCode::ParseError)MessageBox::Show(L" Parse Error - Could not locate file");


		//MessageBox::Show(gcnew String(std::to_string().c_str()));

		int offset = (*user_datapoints).size() / 5;

		double min_val = *std::min_element(user_datapoints->begin(), user_datapoints->end());
		double max_val = *std::max_element(user_datapoints->begin(), user_datapoints->end());

		max_label->Text = gcnew String(std::to_string(max_val).c_str());
		min_label->Text = gcnew String(std::to_string(min_val).c_str());

		Bitmap^ legend = gcnew Bitmap(22, 200);

		for (int i = 0; i < legend->Size.Height; i++) {
			for (int j = 0; j < legend->Size.Width; j++) {

				double aux = 1.0 - (static_cast<double>(i) / (legend->Size.Height - 1.0));

				System::Drawing::Color c = System::Drawing::Color::FromArgb(aux * 255, 0, 255 - aux * 255);
				legend->SetPixel(j, i, c);
			}
		}
		legend_box->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(legend));


		List<System::Windows::Forms::PictureBox^>^ list = gcnew List<System::Windows::Forms::PictureBox^>();
		list->Add(pictureBox1);
		list->Add(pictureBox2);
		list->Add(pictureBox3);
		list->Add(pictureBox4);
		list->Add(pictureBox5);

		for (int pic = 0; pic < list->Count; pic++) {
			//create img 
			Bitmap^ img = gcnew Bitmap(img_x, img_y);
			for (int i = 0; i < img_y; i++) {
				for (int j = 0; j < img_x; j++) {
					int i_g;
					int j_g;
					image_to_grid(j, i, img_x, img_y, grid_x, grid_y, j_g, i_g);
					int r;
					int g;
					int b;

					determine_color((*user_datapoints)[i_g * grid_x + j_g + static_cast<unsigned long long>(pic) * offset], min_val, max_val, r, g, b);

					//MessageBox::Show(gcnew String(std::to_string(heatvals[i_g * grid_x + j_g + static_cast<unsigned long long>(pic) * offset]).c_str()));
					//MessageBox::Show(gcnew String(std::to_string(min_val).c_str()));
					//MessageBox::Show(gcnew String(std::to_string(max_val).c_str()));

					System::Drawing::Color c = System::Drawing::Color::FromArgb(r, 0, 255 - b);
					img->SetPixel(j, i, c);
				}
			}

			img->SetPixel(0, 0, System::Drawing::Color::Blue);
			list[pic]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(img));

		}
	}
}

void Run_SERID_PDE() {
	
	//Parameters
	double alpha = System::Decimal::ToDouble(this->alpha_input->Value);
	double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
	double theta = System::Decimal::ToDouble(this->theta_input->Value);
	double pp = System::Decimal::ToDouble(this->pp_input->Value);
	double qq = System::Decimal::ToDouble(this->qq_input->Value);

	double diffusion = System::Decimal::ToDouble(this->diffusion_input->Value);
	//double rho = 0.1;
	
	//Time
	double t_start = System::Decimal::ToDouble(this->t_start_input->Value);
	double t_end = System::Decimal::ToDouble(this->t_end_input->Value);
	double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);

	//Initial Values
	double r1 = System::Decimal::ToDouble(this->r1_input->Value);
	double r2 = System::Decimal::ToDouble(this->r2_input->Value);
	double r3 = System::Decimal::ToDouble(this->r3_input->Value);
	double r4 = System::Decimal::ToDouble(this->r4_input->Value);
	double r5 = System::Decimal::ToDouble(this->r5_input->Value);

	double v1 = System::Decimal::ToDouble(this->v1_input->Value);
	double v2 = System::Decimal::ToDouble(this->v2_input->Value);
	double v3 = System::Decimal::ToDouble(this->v3_input->Value);
	double v4 = System::Decimal::ToDouble(this->v4_input->Value);
	double v5 = System::Decimal::ToDouble(this->v5_input->Value);

	 //MessageBox::Show(gcnew String(std::to_string(r1).c_str()));
	 //MessageBox::Show(gcnew String(std::to_string(v1).c_str()));

	auto seird_model= ug::epi::SEIRD_PDE<std::vector<double>, ug::epi::seird::Geometry::Plane>(alpha, kappa, theta, qq, pp, diffusion);
	
	seird_model.change_step_size_spatial(stepsize);
	seird_model.change_step_size_time(stepsize);

	
	std::vector<double> u0 = initial_values(1, 1, stepsize, r1, r2, r3, r4, r5, v1, v2, v3, v4, v5);
	//std::string filepath = "C:/Users/devan/Desktop/THESIS/Plugin/Output/";

	std::string filename = "/output";

	if (user_selected_optimization_path == nullptr) {
		MessageBox::Show(L"Please specify the directory for Output generation");	
	}
	else {
		//MessageBox::Show(gcnew String((*user_selected_optimization_path).c_str()));

		seird_model.set_store_to_file(true, *user_selected_optimization_path, filename);

		auto [timepoints, data] = seird_model.run(t_start, u0, t_end);
	}

}



private: System::Void hScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
	//after button click - output is generated 
	std::string filepath = "C:/Users/devan/Desktop/THESIS/Plugin/Output/";
	std::string filename = "output";

	double t_start = System::Decimal::ToDouble(this->t_start_input->Value);
	double t_end = System::Decimal::ToDouble(this->t_end_input->Value);
	double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);


	//hScrollBar1->Maximum =t_end;
	hScrollBar1->Minimum = t_start;
	hScrollBar1->SmallChange= (hScrollBar1->Size.Width) / ((t_end - t_start) / stepsize);
	hScrollBar1->LargeChange = (hScrollBar1->Size.Width) / ((t_end - t_start) / stepsize);

	hScrollBar1->Maximum = (t_end - t_start)/stepsize ;

	double change = 1/((t_end - t_start) / stepsize);
	//hScrollBar1->SmallChange = change;
	//hScrollBar1->LargeChange = change;



	/*int img_x = 200; //dimensions of picturebox
	int img_y = 200; //dimensions of picturebox
	double dimX = 1.0;
	double dimY = 1.0;
	size_t grid_x = (dimX / stepsize) + 1;
	size_t grid_y = (dimY / stepsize) + 1;


	//pass output selected by user 
	//double timepointUser = 0.0;
	std::vector<double> generated;
	std::string delimiter = "\t";
	int gridx = (int)grid_x;

	int filenum = ((hScrollBar1->Value) / (t_end)) *( 1 / change);
	int iterations = (t_end - t_start) / stepsize;

	scroll_val->Value = hScrollBar1->Value;


	co::ErrorCode err;
	try {
		for (int i = 0; i <= iterations - 1; i++) {
			err = co::utility::parse_csv(filepath + "/output" + std::to_string(i).c_str() + ".txt", generated, delimiter, &gridx);
			//MessageBox::Show(gcnew String(std::to_string(generated.size()).c_str()));
			//MessageBox::Show(gcnew String(std::to_string(change).c_str()));
			MessageBox::Show(gcnew String(std::to_string(i).c_str()));

			int offset = generated.size() / 5;

			double min_val = *std::min_element(generated.begin(), generated.end());
			double max_val = *std::max_element(generated.begin(), generated.end());


			List<System::Windows::Forms::PictureBox^>^ list = gcnew List<System::Windows::Forms::PictureBox^>();
			list->Add(pictureBox1);
			list->Add(pictureBox2);
			list->Add(pictureBox3);
			list->Add(pictureBox4);
			list->Add(pictureBox5);

			for (int pic = 0; pic < list->Count; pic++) {
				//create img 
				Bitmap^ img = gcnew Bitmap(img_x, img_y);
				for (int i = 0; i < img_y; i++) {
					for (int j = 0; j < img_x; j++) {
						int i_g;
						int j_g;
						image_to_grid(j, i, img_x, img_y, grid_x, grid_y, j_g, i_g);
						int r;
						int g;
						int b;

						determine_color(generated[i_g * grid_x + j_g + static_cast<unsigned long long>(pic) * offset], min_val, max_val, r, g, b);

						//MessageBox::Show(gcnew String(std::to_string(heatvals[i_g * grid_x + j_g + static_cast<unsigned long long>(pic) * offset]).c_str()));
						//MessageBox::Show(gcnew String(std::to_string(min_val).c_str()));
						//MessageBox::Show(gcnew String(std::to_string(max_val).c_str()));

						System::Drawing::Color c = System::Drawing::Color::FromArgb(r, 0, 255-b);
						img->SetPixel(j, i, c);
					}
				}

				img->SetPixel(0, 0, System::Drawing::Color::Blue);
				list[pic]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(img));

			}


		}

		
	}
	catch (System::Exception^ e) {
		MessageBox::Show(L"Could not read file" + e);
	}
	if (err != co::ErrorCode::NoError)MessageBox::Show(L"Error");
	if (err == co::ErrorCode::ParseError)MessageBox::Show(L" Parse Error");


	//MessageBox::Show(gcnew String(std::to_string().c_str()));
	*/
	

}
private: System::Void hScrollBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void scroll_val_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

	hScrollBar1->Value = System::Decimal::ToDouble(scroll_val->Value);

	double t_start = System::Decimal::ToDouble(this->t_start_input->Value);
	double t_end = System::Decimal::ToDouble(this->t_end_input->Value);
	double stepsize = System::Decimal::ToDouble(this->stepsize_input->Value);
	double change = 1 / ((t_end - t_start) / stepsize);


	scroll_val->Maximum = t_end_input->Value;
	scroll_val->Minimum = t_start_input->Value;
	scroll_val->Increment = stepsize_input->Value;

	int filenum = System::Decimal::ToDouble(scroll_val->Value) * (1 / stepsize);//((hScrollBar1->Value) / (t_end)) * (1 / change);

	std::string path = "/output" + std::to_string(filenum) + ".txt";


	if ((System::Decimal::ToDouble(scroll_val->Value)) == (System::Decimal::ToDouble(scroll_val->Maximum))) {
		MessageBox::Show(L"Max Value reached! ");
		return;
	}

	plot_heatmaps(path);

}



private: System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
/*

Lua bindings -Initial Managar class 

Gui -
Inital vals 
colours 
funtions ***




*/