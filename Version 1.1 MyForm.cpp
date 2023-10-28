#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms; // пространство имён, предоставляющее доступ к функциям работы с окнами
using namespace msclr::interop; // пространство имён для преобразования строк типа String^ в std::string и обратно
[STAThreadAttribute] // обязательное требование для обмена сообщениями с сервером сообщений Windows с компонентами COM - системные диалоги
void main(cli::array<String^>^ arguments)
{
	Application::EnableVisualStyles(); // включает визуальные стили для приложения
	Application::SetCompatibleTextRenderingDefault(false); // задаёт по умолчанию значения для свойств определённых компонентов управления
	Project42::MyForm Page;
	Application::Run(% Page); // запуск приложения
	Application::Exit();
	return;
}

String^ Project42::MyForm::get_current_directory() // получение папки с программой
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(256, buffer); // получение расположения текущего файла
	return marshal_as<String^>(string(buffer) + "\\");// преобразование типов строк
}
System::Void Project42::MyForm::choose_output_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	FolderBrowserDialog^ select_resulting_file = gcnew FolderBrowserDialog;
	this->DialogResult = select_resulting_file->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// обработка нажатия кнопки "ОК"
		*Output_Filename = marshal_as<string>(select_resulting_file->SelectedPath); // преобразование типов для формирования названия выходного файла
		*Output_Filename += create_filename();
		output_file_info->Text = marshal_as<String^>(*Output_Filename); // вывести в окошко путь, в котором будет выходной файл
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// обработка нажатия кнопки "Отмена"
	}
	delete select_resulting_file;
}
System::Void Project42::MyForm::execute_Click(System::Object^ sender, System::EventArgs^ e) // нажатие кнопки выполнить
{
	text_analysis_into_predicates(*Input_Filename); // функция анализа текста из файла
}
System::Void Project42::MyForm::choose_input_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	// функция выбора исходного файла
	Stream^ stream;
	OpenFileDialog^ Select_File = gcnew OpenFileDialog(); // открыть диалоговое окно для выбора исходного файла
	Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открытия окна для сохранения файла в папке с программой
	Select_File->Filter = "txt files (*.txt)|*.txt";  // выбор только текстовых файлов
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// обработки кнопки ок при выборе файла в проводнике
		if ((stream = Select_File->OpenFile()) != nullptr) // если файл открывается
		{
			input_file_info->Text = Select_File->FileName; // вывод названия файла пользователю
			*Input_Filename = marshal_as<string>(input_file_info->Text); // привести к строковому типу std::string название входного файла для передачи в сортировку 
			extract_appropriate_filename(*Input_Filename); // убрать из названия файла запрещённые Windows символы
			stream->Close();
		}
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// обработка кнопки выход при выборе файла в проводнике
	}
	delete Select_File;
}
