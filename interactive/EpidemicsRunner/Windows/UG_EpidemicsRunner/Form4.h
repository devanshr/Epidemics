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
	private: double kappa_upper_input;
	private: double kappa_lower_input;
	private: double theta_upper_input;
	private: double theta_lower_input;
	private: double qq_upper_input;
	private: double qq_lower_input;
	private: double pp_upper_input;
	private: double pp_lower_input;
	private: System::Windows::Forms::Button^ Optimize_button;
	private: System::Windows::Forms::ToolStripMenuItem^ loadSubsetSimToolStripMenuItem;

	


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
		this->Optimize_button = (gcnew System::Windows::Forms::Button());
		this->loadSubsetSimToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
		this->groupBox1->Location = System::Drawing::Point(29, 66);
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
		this->pp_input->Location = System::Drawing::Point(104, 212);
		this->pp_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->pp_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
		this->pp_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
		this->pp_input->Name = L"pp_input";
		this->pp_input->Size = System::Drawing::Size(120, 26);
		this->pp_input->TabIndex = 15;
		this->pp_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
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
		this->qq_input->Size = System::Drawing::Size(120, 26);
		this->qq_input->TabIndex = 14;
		this->qq_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
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
		this->theta_input->Size = System::Drawing::Size(120, 26);
		this->theta_input->TabIndex = 13;
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
		this->kappa_input->Size = System::Drawing::Size(120, 26);
		this->kappa_input->TabIndex = 12;
		this->kappa_input->ValueChanged += gcnew System::EventHandler(this, &Form4::kappa_input_ValueChanged);
		// 
		// alpha_input
		// 
		this->alpha_input->DecimalPlaces = 9;
		this->alpha_input->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
		this->alpha_input->Location = System::Drawing::Point(104, 41);
		this->alpha_input->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->alpha_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
		this->alpha_input->Name = L"alpha_input";
		this->alpha_input->Size = System::Drawing::Size(120, 26);
		this->alpha_input->TabIndex = 11;
		this->alpha_input->ValueChanged += gcnew System::EventHandler(this, &Form4::alpha_input_ValueChanged);
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
		this->File_strip_menu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->loadFileToolStripMenuItem,
				this->loadSubsetSimToolStripMenuItem
		});
		this->File_strip_menu->Name = L"File_strip_menu";
		this->File_strip_menu->Size = System::Drawing::Size(54, 29);
		this->File_strip_menu->Text = L"File";
		// 
		// loadFileToolStripMenuItem
		// 
		this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
		this->loadFileToolStripMenuItem->Size = System::Drawing::Size(270, 34);
		this->loadFileToolStripMenuItem->Text = L"Load Subset_Target";
		this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form4::loadFileToolStripMenuItem_Click);
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
		// Optimize_button
		// 
		this->Optimize_button->Location = System::Drawing::Point(14, 546);
		this->Optimize_button->Name = L"Optimize_button";
		this->Optimize_button->Size = System::Drawing::Size(111, 38);
		this->Optimize_button->TabIndex = 8;
		this->Optimize_button->Text = L"Optimize";
		this->Optimize_button->UseVisualStyleBackColor = true;
		this->Optimize_button->Click += gcnew System::EventHandler(this, &Form4::Optimize_button_Click);
		// 
		// loadSubsetSimToolStripMenuItem
		// 
		this->loadSubsetSimToolStripMenuItem->Name = L"loadSubsetSimToolStripMenuItem";
		this->loadSubsetSimToolStripMenuItem->Size = System::Drawing::Size(270, 34);
		this->loadSubsetSimToolStripMenuItem->Text = L"Load Subset_Sim";
		// 
		// Form4
		// 
		this->ClientSize = System::Drawing::Size(1078, 698);
		this->Controls->Add(this->Optimize_button);
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
		//box->Show();
		// set values 
		box->set_upper(100);
		box->set_lower(1);
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
		box->set_upper(100);
		box->set_lower(1);

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
		box->set_upper(100);
		box->set_lower(1);
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
		box->set_upper(100);
		box->set_lower(1);

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
		box->set_upper(100);
		box->set_lower(1);

		if (box->ShowDialog() == System::Windows::Forms::DialogResult::OK)

		{

			// If it came back with OK, get the values

			pp_upper_input = System::Decimal::ToDouble(box->get_upper());
			pp_lower_input = System::Decimal::ToDouble(box->get_lower());


		}


	}
}


private: System::Void alpha_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void kappa_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void theta_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void qq_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pp_input_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}

	void main_newton() { // COLLET DATA SEPARTE OPTIMIZE	

		   double alpha= System::Decimal::ToDouble(this->alpha_input->Value);
		   double kappa = System::Decimal::ToDouble(this->kappa_input->Value);
		   double theta = System::Decimal::ToDouble(this->theta_input->Value);
		   double qq = System::Decimal::ToDouble(this->qq_input->Value);
		   double pp = System::Decimal::ToDouble(this->pp_input->Value);

		   std::vector<std::string > names_of_constants;
		   std::vector<double> values_of_constants;
		   std::vector<std::string> names_of_variables;

		  // MessageBox::Show(gcnew String(std::to_string(alpha).c_str()));
		   std::vector<std::string > names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
		   std::vector<double> values_of_inits;

		   co::EVar64Manager initial_vars;

		   if (this->alpha_check->Checked) {
			   names_of_variables.push_back("alpha");

			   co::EVar64 v_alpha=co::EVar64(co::EFloat64(alpha), co::EFloat64(alpha_lower_input), co::EFloat64(alpha_upper_input));

			   
		   }
		   else {
			   names_of_constants.push_back("alpha");
			   values_of_constants.push_back(alpha);
		   }

		   if (this->kappa_check->Checked) {
			   names_of_variables.push_back("kappa");
			   //EFloats for bounds aswelll!!
			   co::EVar64 v_kappa(co::EFloat64(kappa, kappa_upper_input, kappa_lower_input));
			   initial_vars.add("kappa", v_kappa);
		   }
		   else {
			   names_of_constants.push_back("kappa");
			   values_of_constants.push_back(kappa);
		   }

		   if (this->theta_check->Checked) {
			   names_of_variables.push_back("theta");
			   co::EVar64 v_theta(co::EFloat64(theta, theta_upper_input, theta_lower_input));
			   initial_vars.add("theta", v_theta);
		   }
		   else {
			   names_of_constants.push_back("theta");
			   values_of_constants.push_back(theta);
		   }

		   if (this->qq_check->Checked) {
			   names_of_variables.push_back("qq");
			   co::EVar64 v_qq(co::EFloat64(qq, qq_upper_input, qq_lower_input));
			   initial_vars.add("qq", v_qq);
		   }
		   else {
			   names_of_constants.push_back("qq");
			   values_of_constants.push_back(qq);
		   }

		   if (this->pp_check->Checked) {
			   names_of_variables.push_back("pp");
			   co::EVar64 v_pp(co::EFloat64(pp, pp_upper_input, pp_lower_input));
			   initial_vars.add("pp", v_pp);
		   }
		   else {
			   names_of_constants.push_back("pp");
			   values_of_constants.push_back(pp);
		   }


		   values_of_inits = { 0,42,5800000,0,70,0,0 };
		   /*
		   MessageBox::Show(gcnew String(std::to_string(names_of_constants.size()).c_str()));
		   MessageBox::Show(gcnew String(std::to_string(values_of_constants.size()).c_str()));
		   MessageBox::Show(gcnew String(std::to_string(names_of_variables.size()).c_str()));
		   */
		   std::string textbody = R"(

seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end)
							)";

		   ug::epi::create_evaluate_lua("C:/Users/devan/ug4/apps/test/", textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits);

		   co::NewtonOptions options;
		   options.set_stepsize_alpha(1);
		   std::string dir = "C:/Users/devan/ug4/apps/test/";
		   co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(dir, "subset_target.lua", "subset_sim.lua");
		   co::EVarManager<co::EFloat64> estimated_vars;
		   co::NewtonOptimizer<decltype(evaluator)> solver(options, evaluator);

		//   solver.run(initial_vars, estimated_vars);


	   }


private: System::Void Optimize_button_Click(System::Object^ sender, System::EventArgs^ e) {
	main_newton();

}
private: System::Void loadFileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
