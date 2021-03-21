#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form5
	/// </summary>
	public ref class Form5 : public System::Windows::Forms::Form
	{
	public:
		Form5(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}


		System::Decimal get_upper() { return this->upper->Value; }
		void set_upper(int val) { this->upper->Value = val; }

		System::Decimal get_lower() { return this->lower->Value; }
		void set_lower(int val) { this->lower->Value = val; }
		

			


	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form5()
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
	private: System::Windows::Forms::NumericUpDown^ upper;
	private: System::Windows::Forms::NumericUpDown^ lower;


	protected:



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
			this->OK_button = (gcnew System::Windows::Forms::Button());
			this->Cancel_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->upper = (gcnew System::Windows::Forms::NumericUpDown());
			this->lower = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->upper))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lower))->BeginInit();
			this->SuspendLayout();
			// 
			// OK_button
			// 
			this->OK_button->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OK_button->Location = System::Drawing::Point(114, 178);
			this->OK_button->Name = L"OK_button";
			this->OK_button->Size = System::Drawing::Size(90, 40);
			this->OK_button->TabIndex = 0;
			this->OK_button->Text = L"Insert";
			this->OK_button->UseVisualStyleBackColor = true;
			this->OK_button->Click += gcnew System::EventHandler(this, &Form5::OK_button_Click);
			// 
			// Cancel_button
			// 
			this->Cancel_button->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Cancel_button->Location = System::Drawing::Point(218, 178);
			this->Cancel_button->Name = L"Cancel_button";
			this->Cancel_button->Size = System::Drawing::Size(90, 40);
			this->Cancel_button->TabIndex = 1;
			this->Cancel_button->Text = L"Cancel";
			this->Cancel_button->UseVisualStyleBackColor = true;
			this->Cancel_button->Click += gcnew System::EventHandler(this, &Form5::Cancel_button_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(104, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Upper Bound";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(51, 97);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Lower Bound";
			this->label2->Click += gcnew System::EventHandler(this, &Form5::label2_Click);
			// 
			// upper
			// 
			this->upper->DecimalPlaces = 9;
			this->upper->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 393216, 0, 0, 0 });
			this->upper->Location = System::Drawing::Point(218, 47);
			this->upper->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 131072, 0, 0, 0 });
			this->upper->Name = L"upper";
			this->upper->Size = System::Drawing::Size(161, 26);
			this->upper->TabIndex = 6;
			this->upper->ValueChanged += gcnew System::EventHandler(this, &Form5::numericUpDown1_ValueChanged);
			// 
			// lower
			// 
			this->lower->DecimalPlaces = 9;
			this->lower->Location = System::Drawing::Point(218, 97);
			this->lower->Name = L"lower";
			this->lower->Size = System::Drawing::Size(161, 26);
			this->lower->TabIndex = 7;
			this->lower->ValueChanged += gcnew System::EventHandler(this, &Form5::numericUpDown2_ValueChanged);
			// 
			// Form5
			// 
			this->AcceptButton = this->OK_button;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->Cancel_button;
			this->ClientSize = System::Drawing::Size(433, 232);
			this->Controls->Add(this->lower);
			this->Controls->Add(this->upper);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Cancel_button);
			this->Controls->Add(this->OK_button);
			this->Name = L"Form5";
			this->Text = L"Parameter Bounds";
			this->Load += gcnew System::EventHandler(this, &Form5::Form5_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->upper))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lower))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void Form5_Load(System::Object^ sender, System::EventArgs^ e) {
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
