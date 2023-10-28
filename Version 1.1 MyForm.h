#pragma once
#include<msclr\marshal_cppstd.h> // библиотека для преобразования строк типа String^ в std::string и обратно
#include"Source.h"
namespace Project42
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			Input_Filename = new string;
			Output_Filename = new string;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			delete Input_Filename;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ execute;
	string* Input_Filename;
	string* Output_Filename;
	private: System::Windows::Forms::RichTextBox^ input_file_info;


	private: System::Windows::Forms::Button^ choose_input_file;
	private: System::Windows::Forms::RichTextBox^ output_file_info;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ choose_output_file;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->execute = (gcnew System::Windows::Forms::Button());
			this->input_file_info = (gcnew System::Windows::Forms::RichTextBox());
			this->choose_input_file = (gcnew System::Windows::Forms::Button());
			this->output_file_info = (gcnew System::Windows::Forms::RichTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->choose_output_file = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(57, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Входной файл";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// execute
			// 
			this->execute->Location = System::Drawing::Point(281, 435);
			this->execute->Name = L"execute";
			this->execute->Size = System::Drawing::Size(119, 41);
			this->execute->TabIndex = 1;
			this->execute->Text = L"Выполнить";
			this->execute->UseVisualStyleBackColor = true;
			this->execute->Click += gcnew System::EventHandler(this, &MyForm::execute_Click);
			// 
			// input_file_info
			// 
			this->input_file_info->Location = System::Drawing::Point(60, 75);
			this->input_file_info->Name = L"input_file_info";
			this->input_file_info->Size = System::Drawing::Size(371, 37);
			this->input_file_info->TabIndex = 2;
			this->input_file_info->Text = L"";
			// 
			// choose_input_file
			// 
			this->choose_input_file->Location = System::Drawing::Point(437, 75);
			this->choose_input_file->Name = L"choose_input_file";
			this->choose_input_file->Size = System::Drawing::Size(108, 37);
			this->choose_input_file->TabIndex = 3;
			this->choose_input_file->Text = L"Выбрать";
			this->choose_input_file->UseVisualStyleBackColor = true;
			this->choose_input_file->Click += gcnew System::EventHandler(this, &MyForm::choose_input_file_Click);
			// 
			// output_file_info
			// 
			this->output_file_info->Location = System::Drawing::Point(60, 225);
			this->output_file_info->Name = L"output_file_info";
			this->output_file_info->Size = System::Drawing::Size(372, 37);
			this->output_file_info->TabIndex = 4;
			this->output_file_info->Text = L"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(57, 182);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(211, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Сохранить результаты работы";
			// 
			// choose_output_file
			// 
			this->choose_output_file->Location = System::Drawing::Point(437, 225);
			this->choose_output_file->Name = L"choose_output_file";
			this->choose_output_file->Size = System::Drawing::Size(108, 37);
			this->choose_output_file->TabIndex = 6;
			this->choose_output_file->Text = L"Выбрать";
			this->choose_output_file->UseVisualStyleBackColor = true;
			this->choose_output_file->Click += gcnew System::EventHandler(this, &MyForm::choose_output_file_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(669, 570);
			this->Controls->Add(this->choose_output_file);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->output_file_info);
			this->Controls->Add(this->choose_input_file);
			this->Controls->Add(this->input_file_info);
			this->Controls->Add(this->execute);
			this->Controls->Add(this->label1);
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Анализ текста на сказуемые";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
	System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {}
	System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}
	System::Void choose_input_file_Click(System::Object^ sender, System::EventArgs^ e);
	String^ get_current_directory(); // функция получения текущей папки с программой
	System::Void choose_output_file_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void execute_Click(System::Object^ sender, System::EventArgs^ e);
};
}
