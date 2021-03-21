#pragma once

#include "Form3.h"
#include "Form5.h"
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
			if (components)
			{
				delete components;
			}
		}

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
	


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;



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
		this->cancel_button = (gcnew System::Windows::Forms::Button());
		this->groupBox1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pp_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qq_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->theta_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kappa_input))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alpha_input))->BeginInit();
		this->menuStrip1->SuspendLayout();
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
		this->groupBox1->Location = System::Drawing::Point(30, 103);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(257, 265);
		this->groupBox1->TabIndex = 5;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Parameters";
		// 
		// pp_input
		//
		this->pp_input->DecimalPlaces = 4;
		this->pp_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->pp_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->pp_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->pp_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->pp_input->Location = System::Drawing::Point(104, 212);
		this->pp_input->Name = L"pp_input";
		this->pp_input->Size = System::Drawing::Size(120, 26);
		this->pp_input->TabIndex = 15;
		// 
		// qq_input
		// 
		this->qq_input->DecimalPlaces = 4;
		this->qq_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
		this->qq_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->qq_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->qq_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->qq_input->Location = System::Drawing::Point(104, 171);
		this->qq_input->Name = L"qq_input";
		this->qq_input->Size = System::Drawing::Size(120, 26);
		this->qq_input->TabIndex = 14;
		// 
		// theta_input
		// 
		this->theta_input->DecimalPlaces = 8;
		this->theta_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->theta_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->theta_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->theta_input->Location = System::Drawing::Point(104, 131);
		this->theta_input->Name = L"theta_input";
		this->theta_input->Size = System::Drawing::Size(120, 26);
		this->theta_input->TabIndex = 13;
		this->theta_input->ValueChanged += gcnew System::EventHandler(this, &Form4::numericUpDown3_ValueChanged);
		// 
		// kappa_input
		// 
		this->kappa_input->DecimalPlaces = 8;
		this->kappa_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->kappa_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->kappa_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->kappa_input->Location = System::Drawing::Point(104, 87);
		this->kappa_input->Name = L"kappa_input";
		this->kappa_input->Size = System::Drawing::Size(120, 26);
		this->kappa_input->TabIndex = 12;
		this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form4::numericUpDown2_ValueChanged);
		// 
		// alpha_input
		// 
		this->alpha_input->DecimalPlaces = 9;
		this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->alpha_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->alpha_input->Location = System::Drawing::Point(104, 41);
		this->alpha_input->Name = L"alpha_input";
		this->alpha_input->Size = System::Drawing::Size(120, 26);
		this->alpha_input->TabIndex = 11;
		this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form4::numericUpDown1_ValueChanged);
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
		this->pp_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::pp_check_CheckedChanged);
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
		this->alpha_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::alpha_check_CheckedChanged);
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
		this->qq_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::qq_check_CheckedChanged);
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
		this->kappa_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::kappa_check_CheckedChanged);
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
		this->theta_check->CheckedChanged += gcnew System::EventHandler(this, &Form4::theta_check_CheckedChanged);
		// 
		// menuStrip1
		// 
		this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
		this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->File_strip_menu });
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1078, 33);
		this->menuStrip1->TabIndex = 6;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// File_strip_menu
		// 
		this->File_strip_menu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadFileToolStripMenuItem });
		this->File_strip_menu->Name = L"File_strip_menu";
		this->File_strip_menu->Size = System::Drawing::Size(54, 29);
		this->File_strip_menu->Text = L"File";
		// 
		// loadFileToolStripMenuItem
		// 
		this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
		this->loadFileToolStripMenuItem->Size = System::Drawing::Size(181, 34);
		this->loadFileToolStripMenuItem->Text = L"Load file";
		// 
		// cancel_button
		// 
		this->cancel_button->Location = System::Drawing::Point(161, 546);
		this->cancel_button->Name = L"cancel_button";
		this->cancel_button->Size = System::Drawing::Size(108, 38);
		this->cancel_button->TabIndex = 7;
		this->cancel_button->Text = L"Cancel";
		this->cancel_button->UseVisualStyleBackColor = true;
		this->cancel_button->Click += gcnew System::EventHandler(this, &Form4::cancel_button_Click);
		// 
		// Form4
		// 
		this->ClientSize = System::Drawing::Size(1078, 698);
		this->Controls->Add(this->cancel_button);
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->menuStrip1);
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"Form4";
		this->Text = L"Parameter Estimation";
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
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	private: System::Void Form4_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
private: System::Void alpha_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (alpha_check->Checked) {

		Form5^ box = gcnew Form5;
		box->Show();
		alpha_upper_input = System::Decimal::ToDouble(box->get_upper());
		alpha_lower_input = System::Decimal::ToDouble(box->get_lower());
		// set values 
		box->set_upper(100);
		box->set_lower(1);
		
	}
	
}
private: System::Void kappa_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (kappa_check->Checked) {

		Form5^ box = gcnew Form5;
		box->Show();

	}
}
private: System::Void theta_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (theta_check->Checked) {

		Form5^ box = gcnew Form5;
		box->Show();

	}
}
private: System::Void qq_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (qq_check->Checked) {

		Form5^ box = gcnew Form5;
		box->Show();

	}
}
private: System::Void pp_check_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (pp_check->Checked) {

		Form5^ box = gcnew Form5;
		box->Show();

	}
}


private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		// Constant OR Initial Value of alpha
	if (alpha_check->Checked) {
		//Initial Value
		MessageBox::Show(L"Parameter is checked, so given input is inital val");

	}
	else {
		//Fixed Value
	}
}
private: System::Void numericUpDown2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	// Constant OR Initial Value of alpha
	if (kappa_check->Checked) {
		//Initial Value
	}
	else {
		//Fixed Value
		MessageBox::Show(L"Parameter is UN-checked, so given input should be the fixed val");
	}
}
private: System::Void numericUpDown3_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	// Constant OR Initial Value of alpha
	if (theta_check->Checked) {
		//Initial Value
	}
	else {
		//Fixed Value
	}
}
private: System::Void cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}

	   void main_newton() { // COLLET DATA SEPARTE OPTIMIZE	
		   /*
		   * int main(){
	co::EVar64Manager initial_vars;
	co::EVar64 theta1(co::EFloat64(1),co::EFloat64(0),co::EFloat64(30));
	co::EVar64 theta2(co::EFloat64(1),co::EFloat64(0),co::EFloat64(10));
	co::EVar64 theta3(co::EFloat64(1),co::EFloat64(0),co::EFloat64(30));

	initial_vars.add("v_theta1",theta1);
	initial_vars.add("v_theta2",theta2);
	initial_vars.add("v_theta3",theta3);

	co::NewtonOptions options;
	options.set_stepsize_alpha(1);
	std::string dir ="/home/server1/Programs/ug4/ug4/plugins/ConstrainedOptimization/examples/logistic_1/";
	co::BiogasEvaluation<co::EFloat64,co::ConfigComputation::Local,co::ConfigOutput::File> evaluator(dir, "subset_target.lua","subset_sim.lua");
	co::EVarManager<co::EFloat64> estimated_vars;
	co::NewtonOptimizer<decltype(evaluator)> solver(options,evaluator);

	solver.run(initial_vars,estimated_vars);
}
		   */
		   double alpha = System::Decimal::ToDouble(this->alpha_input->Value);
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);
		   

		   co::EVar64Manager initial_vars;
		   co::EVar64 v_alpha(co::EFloat64(alpha, alpha_upper_input, alpha_lower_input));
		   initial_vars.add("v_alpha", v_alpha);
	   }


};
}
