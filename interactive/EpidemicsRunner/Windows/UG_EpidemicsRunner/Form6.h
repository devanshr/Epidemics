#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form6
	/// </summary>
	public ref class Form6 : public System::Windows::Forms::Form
	{
	public:
		Form6(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}


		System::Decimal get_max_iterations() { return this->max_iteration_input->Value; }
		
		System::Decimal get_particles() { return this->particles_input->Value; }

		System::Decimal get_groups() { return this->groups_input->Value; }

		




	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form6()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ OK_button;
	private: System::Windows::Forms::Button^ Cancel_button;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ max_iteration_input;
	private: System::Windows::Forms::NumericUpDown^ particles_input;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::NumericUpDown^ groups_input;
	



	protected:



	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->OK_button = (gcnew System::Windows::Forms::Button());
			this->Cancel_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->max_iteration_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->particles_input = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groups_input = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_iteration_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->particles_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groups_input))->BeginInit();
			this->SuspendLayout();
			// 
			// OK_button
			// 
			this->OK_button->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OK_button->Location = System::Drawing::Point(113, 200);
			this->OK_button->Name = L"OK_button";
			this->OK_button->Size = System::Drawing::Size(90, 40);
			this->OK_button->TabIndex = 0;
			this->OK_button->Text = L"Insert";
			this->OK_button->UseVisualStyleBackColor = true;
			this->OK_button->Click += gcnew System::EventHandler(this, &Form6::OK_button_Click);
			// 
			// Cancel_button
			// 
			this->Cancel_button->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Cancel_button->Location = System::Drawing::Point(218, 200);
			this->Cancel_button->Name = L"Cancel_button";
			this->Cancel_button->Size = System::Drawing::Size(90, 40);
			this->Cancel_button->TabIndex = 1;
			this->Cancel_button->Text = L"Cancel";
			this->Cancel_button->UseVisualStyleBackColor = true;
			this->Cancel_button->Click += gcnew System::EventHandler(this, &Form6::Cancel_button_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(113, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Max: Iterations";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(51, 97);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(115, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"No. of Particles";
			this->label2->Click += gcnew System::EventHandler(this, &Form6::label2_Click);
			// 
			// max_iteration_input
			// 
			this->max_iteration_input->Location = System::Drawing::Point(218, 47);
			this->max_iteration_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 300, 0, 0, 0 });
			this->max_iteration_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->max_iteration_input->Name = L"max_iteration_input";
			this->max_iteration_input->Size = System::Drawing::Size(161, 26);
			this->max_iteration_input->TabIndex = 6;
			this->max_iteration_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->max_iteration_input->ValueChanged += gcnew System::EventHandler(this, &Form6::numericUpDown1_ValueChanged);
			// 
			// particles_input
			// 
			this->particles_input->Location = System::Drawing::Point(218, 97);
			this->particles_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->particles_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->particles_input->Name = L"particles_input";
			this->particles_input->Size = System::Drawing::Size(161, 26);
			this->particles_input->TabIndex = 7;
			this->particles_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32, 0, 0, 0 });
			this->particles_input->ValueChanged += gcnew System::EventHandler(this, &Form6::numericUpDown2_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(51, 150);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(108, 20);
			this->label3->TabIndex = 8;
			this->label3->Text = L"No. of Groups";
			// 
			// groups_input
			// 
			this->groups_input->Location = System::Drawing::Point(218, 144);
			this->groups_input->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->groups_input->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->groups_input->Name = L"groups_input";
			this->groups_input->Size = System::Drawing::Size(161, 26);
			this->groups_input->TabIndex = 9;
			this->groups_input->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			// 
			// Form6
			// 
			this->AcceptButton = this->OK_button;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->Cancel_button;
			this->ClientSize = System::Drawing::Size(433, 252);
			this->Controls->Add(this->groups_input);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->particles_input);
			this->Controls->Add(this->max_iteration_input);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Cancel_button);
			this->Controls->Add(this->OK_button);
			this->Name = L"Form6";
			this->Text = L"Settings for PSO";
			this->Load += gcnew System::EventHandler(this, &Form6::Form6_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_iteration_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->particles_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groups_input))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form6_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void OK_button_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		//Needed for main.cpp of CO
	}
	private: System::Void numericUpDown2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		//Needed for main.cpp of CO
	}
	};
}
