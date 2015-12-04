#pragma once
#include "AlazarInfo.h"

namespace OCTProgram {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// FormLoad 摘要
	/// </summary>
	public ref class LoadForm : public System::Windows::Forms::Form
	{
	public:
		LoadForm(AlazarInfo* al)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			alazar=al;
		}
		LoadForm(AlazarInfo* al,System::String^ fileDir)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			this->textBox1->Text=fileDir;
			alazar=al;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~LoadForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;
		AlazarInfo* alazar;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(83, 22);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(182, 21);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(277, 22);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(76, 20);
			this->button1->TabIndex = 1;
			this->button1->Text = L"打开文件";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoadForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(277, 49);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(76, 20);
			this->button2->TabIndex = 3;
			this->button2->Text = L"打开文件";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &LoadForm::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(83, 49);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(182, 21);
			this->textBox2->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(19, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Config：";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 55);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Calibre：";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(198, 78);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(67, 30);
			this->button3->TabIndex = 6;
			this->button3->Text = L"确定";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &LoadForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(277, 79);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(76, 29);
			this->button4->TabIndex = 7;
			this->button4->Text = L"取消";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &LoadForm::button4_Click);
			// 
			// FormLoad
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(367, 111);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"FormLoad";
			this->Text = L"LoadConfigration";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			OpenFileDialog^ ofdconf=gcnew OpenFileDialog();
			ofdconf->InitialDirectory=System::IO::Directory::GetCurrentDirectory()+"/resources/config/";
			ofdconf->Filter=L"配置文件(*.ini)|*.ini|所有文件(*.*)|*.*";
			ofdconf->FilterIndex=1;
			ofdconf->RestoreDirectory=true;
			if (ofdconf->ShowDialog()==System::Windows::Forms::DialogResult::OK)
			{
				this->textBox1->Text=ofdconf->FileName;
			}
		}
	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			OpenFileDialog^ ofdconf=gcnew OpenFileDialog();
			ofdconf->InitialDirectory=System::IO::Directory::GetCurrentDirectory()+"/resources/config/";
			ofdconf->Filter=L"配置文件(*.ini)|*.ini|所有文件(*.*)|*.*";
			ofdconf->FilterIndex=1;
			ofdconf->RestoreDirectory=true;
			if (ofdconf->ShowDialog()==System::Windows::Forms::DialogResult::OK)
			{
				this->textBox2->Text=ofdconf->FileName;
			}
		}
	private: 
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			alazar->ConfigureBoard((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(
				this->textBox1->Text));
			//Do something for "Calibre"
			this->Close();
		}
	private:
		System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Close();
		}
	};
}
