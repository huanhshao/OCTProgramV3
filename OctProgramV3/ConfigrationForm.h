#pragma once
#include <fstream>
#include <string>
#include "ComponetsOfForm.h"
#include "LoadForm.h"

namespace OCTProgram {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// FormConfigration1 摘要
	/// </summary>
	public ref class FormConfigration1 : public System::Windows::Forms::Form{
	public:
		FormConfigration1(void){
			InitializeComponent();
			sFlNm=L"";
			isFlSd=false;
		}
		String^ GetFileName(){
			return sFlNm;
		}
		bool IsConfSaved(){
			return isFlSd;
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~FormConfigration1(){
			if (components){
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BNCfgSave;
	private: System::Windows::Forms::Button^  BNCfgCancle;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::ComboBox^  comboBox22;
	private: System::Windows::Forms::ComboBox^  comboBox20;
	private: System::Windows::Forms::ComboBox^  comboBox21;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::ComboBox^  comboBox19;
	private: System::Windows::Forms::ComboBox^  comboBox18;
	private: System::Windows::Forms::ComboBox^  comboBox17;
	private: System::Windows::Forms::ComboBox^  comboBox16;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ComboBox^  comboBox14;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ComboBox^  comboBox15;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ComboBox^  comboBox13;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ComboBox^  comboBox10;
	private: System::Windows::Forms::ComboBox^  comboBox11;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::ComboBox^  comboBox12;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::ComboBox^  comboBox9;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBox6;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  comboBox7;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  comboBox8;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabControl^  tabControl1;


	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::ComboBox^  comboBox24;
	private: System::Windows::Forms::ComboBox^  comboBox23;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;
		String^ sFlNm;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TabPage^  Calib;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox9;
private: System::Windows::Forms::TextBox^  textBox12;
private: System::Windows::Forms::TextBox^  textBox11;
private: System::Windows::Forms::ToolStrip^  toolStrip1;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  label34;

			 bool isFlSd;
#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 设计器支持所需的方法 - 不要
			 /// 使用代码编辑器修改此方法的内容。
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->BNCfgSave = (gcnew System::Windows::Forms::Button());
				 this->BNCfgCancle = (gcnew System::Windows::Forms::Button());
				 this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
				 this->label31 = (gcnew System::Windows::Forms::Label());
				 this->textBox7 = (gcnew System::Windows::Forms::TextBox());
				 this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
				 this->label29 = (gcnew System::Windows::Forms::Label());
				 this->textBox5 = (gcnew System::Windows::Forms::TextBox());
				 this->label28 = (gcnew System::Windows::Forms::Label());
				 this->textBox4 = (gcnew System::Windows::Forms::TextBox());
				 this->label27 = (gcnew System::Windows::Forms::Label());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->label30 = (gcnew System::Windows::Forms::Label());
				 this->textBox6 = (gcnew System::Windows::Forms::TextBox());
				 this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
				 this->comboBox22 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox20 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox21 = (gcnew System::Windows::Forms::ComboBox());
				 this->label21 = (gcnew System::Windows::Forms::Label());
				 this->label22 = (gcnew System::Windows::Forms::Label());
				 this->comboBox19 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox18 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox17 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox16 = (gcnew System::Windows::Forms::ComboBox());
				 this->label20 = (gcnew System::Windows::Forms::Label());
				 this->label19 = (gcnew System::Windows::Forms::Label());
				 this->label18 = (gcnew System::Windows::Forms::Label());
				 this->label17 = (gcnew System::Windows::Forms::Label());
				 this->label16 = (gcnew System::Windows::Forms::Label());
				 this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
				 this->comboBox24 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox23 = (gcnew System::Windows::Forms::ComboBox());
				 this->label26 = (gcnew System::Windows::Forms::Label());
				 this->label25 = (gcnew System::Windows::Forms::Label());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->label24 = (gcnew System::Windows::Forms::Label());
				 this->label23 = (gcnew System::Windows::Forms::Label());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->comboBox14 = (gcnew System::Windows::Forms::ComboBox());
				 this->label14 = (gcnew System::Windows::Forms::Label());
				 this->comboBox15 = (gcnew System::Windows::Forms::ComboBox());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->comboBox13 = (gcnew System::Windows::Forms::ComboBox());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->comboBox10 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox11 = (gcnew System::Windows::Forms::ComboBox());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->comboBox12 = (gcnew System::Windows::Forms::ComboBox());
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->comboBox9 = (gcnew System::Windows::Forms::ComboBox());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->Calib = (gcnew System::Windows::Forms::TabPage());
				 this->textBox10 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox9 = (gcnew System::Windows::Forms::TextBox());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->textBox8 = (gcnew System::Windows::Forms::TextBox());
				 this->label33 = (gcnew System::Windows::Forms::Label());
				 this->label32 = (gcnew System::Windows::Forms::Label());
				 this->label34 = (gcnew System::Windows::Forms::Label());
				 this->label35 = (gcnew System::Windows::Forms::Label());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->textBox11 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox12 = (gcnew System::Windows::Forms::TextBox());
				 this->tabPage5->SuspendLayout();
				 this->groupBox7->SuspendLayout();
				 this->tabPage3->SuspendLayout();
				 this->groupBox6->SuspendLayout();
				 this->groupBox5->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 this->groupBox4->SuspendLayout();
				 this->groupBox3->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 this->tabControl1->SuspendLayout();
				 this->Calib->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // BNCfgSave
				 // 
				 this->BNCfgSave->Location = System::Drawing::Point(194, 307);
				 this->BNCfgSave->Name = L"BNCfgSave";
				 this->BNCfgSave->Size = System::Drawing::Size(68, 28);
				 this->BNCfgSave->TabIndex = 0;
				 this->BNCfgSave->Text = L"Save";
				 this->BNCfgSave->UseVisualStyleBackColor = true;
				 this->BNCfgSave->Click += gcnew System::EventHandler(this, &FormConfigration1::BNCfgSave_Click);
				 // 
				 // BNCfgCancle
				 // 
				 this->BNCfgCancle->Location = System::Drawing::Point(282, 307);
				 this->BNCfgCancle->Name = L"BNCfgCancle";
				 this->BNCfgCancle->Size = System::Drawing::Size(68, 28);
				 this->BNCfgCancle->TabIndex = 1;
				 this->BNCfgCancle->Text = L"Cancle";
				 this->BNCfgCancle->UseVisualStyleBackColor = true;
				 this->BNCfgCancle->Click += gcnew System::EventHandler(this, &FormConfigration1::BNCfgCancle_Click);
				 // 
				 // tabPage5
				 // 
				 this->tabPage5->Controls->Add(this->groupBox7);
				 this->tabPage5->Controls->Add(this->checkBox1);
				 this->tabPage5->Controls->Add(this->label30);
				 this->tabPage5->Controls->Add(this->textBox6);
				 this->tabPage5->Location = System::Drawing::Point(4, 21);
				 this->tabPage5->Name = L"tabPage5";
				 this->tabPage5->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage5->Size = System::Drawing::Size(330, 264);
				 this->tabPage5->TabIndex = 4;
				 this->tabPage5->Text = L"采样";
				 this->tabPage5->UseVisualStyleBackColor = true;
				 // 
				 // groupBox7
				 // 
				 this->groupBox7->Controls->Add(this->label31);
				 this->groupBox7->Controls->Add(this->textBox7);
				 this->groupBox7->Controls->Add(this->checkBox2);
				 this->groupBox7->Controls->Add(this->label29);
				 this->groupBox7->Controls->Add(this->textBox5);
				 this->groupBox7->Controls->Add(this->label28);
				 this->groupBox7->Controls->Add(this->textBox4);
				 this->groupBox7->Controls->Add(this->label27);
				 this->groupBox7->Controls->Add(this->textBox3);
				 this->groupBox7->Location = System::Drawing::Point(22, 9);
				 this->groupBox7->Name = L"groupBox7";
				 this->groupBox7->Size = System::Drawing::Size(261, 156);
				 this->groupBox7->TabIndex = 9;
				 this->groupBox7->TabStop = false;
				 this->groupBox7->Text = L"Samples";
				 // 
				 // label31
				 // 
				 this->label31->AutoSize = true;
				 this->label31->Location = System::Drawing::Point(18, 130);
				 this->label31->Name = L"label31";
				 this->label31->Size = System::Drawing::Size(35, 12);
				 this->label31->TabIndex = 12;
				 this->label31->Text = L"Part:";
				 // 
				 // textBox7
				 // 
				 this->textBox7->Location = System::Drawing::Point(101, 127);
				 this->textBox7->Name = L"textBox7";
				 this->textBox7->ReadOnly = true;
				 this->textBox7->Size = System::Drawing::Size(124, 21);
				 this->textBox7->TabIndex = 11;
				 this->textBox7->Text = L"1";
				 // 
				 // checkBox2
				 // 
				 this->checkBox2->AutoSize = true;
				 this->checkBox2->Checked = true;
				 this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->checkBox2->Location = System::Drawing::Point(20, 20);
				 this->checkBox2->Name = L"checkBox2";
				 this->checkBox2->Size = System::Drawing::Size(66, 16);
				 this->checkBox2->TabIndex = 10;
				 this->checkBox2->Text = L"Defalut";
				 this->checkBox2->UseVisualStyleBackColor = true;
				 this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &FormConfigration1::checkBox2_CheckedChanged);
				 // 
				 // label29
				 // 
				 this->label29->AutoSize = true;
				 this->label29->Location = System::Drawing::Point(18, 103);
				 this->label29->Name = L"label29";
				 this->label29->Size = System::Drawing::Size(53, 12);
				 this->label29->TabIndex = 5;
				 this->label29->Text = L"Records:";
				 // 
				 // textBox5
				 // 
				 this->textBox5->Location = System::Drawing::Point(101, 100);
				 this->textBox5->Name = L"textBox5";
				 this->textBox5->ReadOnly = true;
				 this->textBox5->Size = System::Drawing::Size(124, 21);
				 this->textBox5->TabIndex = 4;
				 this->textBox5->Text = L"1000";
				 // 
				 // label28
				 // 
				 this->label28->AutoSize = true;
				 this->label28->Location = System::Drawing::Point(18, 76);
				 this->label28->Name = L"label28";
				 this->label28->Size = System::Drawing::Size(77, 12);
				 this->label28->TabIndex = 3;
				 this->label28->Text = L"PostTrigger:";
				 // 
				 // textBox4
				 // 
				 this->textBox4->Location = System::Drawing::Point(101, 73);
				 this->textBox4->Name = L"textBox4";
				 this->textBox4->ReadOnly = true;
				 this->textBox4->Size = System::Drawing::Size(124, 21);
				 this->textBox4->TabIndex = 2;
				 this->textBox4->Text = L"2048";
				 // 
				 // label27
				 // 
				 this->label27->AutoSize = true;
				 this->label27->Location = System::Drawing::Point(18, 49);
				 this->label27->Name = L"label27";
				 this->label27->Size = System::Drawing::Size(71, 12);
				 this->label27->TabIndex = 1;
				 this->label27->Text = L"PreTrigger:";
				 // 
				 // textBox3
				 // 
				 this->textBox3->BackColor = System::Drawing::SystemColors::Window;
				 this->textBox3->ForeColor = System::Drawing::SystemColors::WindowText;
				 this->textBox3->Location = System::Drawing::Point(101, 46);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->ReadOnly = true;
				 this->textBox3->Size = System::Drawing::Size(124, 21);
				 this->textBox3->TabIndex = 0;
				 this->textBox3->Text = L"0";
				 // 
				 // checkBox1
				 // 
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Checked = true;
				 this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->checkBox1->Location = System::Drawing::Point(42, 183);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(96, 16);
				 this->checkBox1->TabIndex = 8;
				 this->checkBox1->Text = L"Save As File";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &FormConfigration1::checkBox1_CheckedChanged);
				 // 
				 // label30
				 // 
				 this->label30->AutoSize = true;
				 this->label30->Location = System::Drawing::Point(40, 214);
				 this->label30->Name = L"label30";
				 this->label30->Size = System::Drawing::Size(59, 12);
				 this->label30->TabIndex = 7;
				 this->label30->Text = L"FileName:";
				 // 
				 // textBox6
				 // 
				 this->textBox6->Location = System::Drawing::Point(123, 211);
				 this->textBox6->Name = L"textBox6";
				 this->textBox6->Size = System::Drawing::Size(123, 21);
				 this->textBox6->TabIndex = 6;
				 this->textBox6->Text = L"data.bin";
				 // 
				 // tabPage3
				 // 
				 this->tabPage3->Controls->Add(this->groupBox6);
				 this->tabPage3->Controls->Add(this->groupBox5);
				 this->tabPage3->Controls->Add(this->textBox2);
				 this->tabPage3->Controls->Add(this->textBox1);
				 this->tabPage3->Controls->Add(this->label24);
				 this->tabPage3->Controls->Add(this->label23);
				 this->tabPage3->Location = System::Drawing::Point(4, 21);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage3->Size = System::Drawing::Size(330, 264);
				 this->tabPage3->TabIndex = 2;
				 this->tabPage3->Text = L"触发";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 // 
				 // groupBox6
				 // 
				 this->groupBox6->Controls->Add(this->comboBox22);
				 this->groupBox6->Controls->Add(this->comboBox20);
				 this->groupBox6->Controls->Add(this->comboBox21);
				 this->groupBox6->Controls->Add(this->label21);
				 this->groupBox6->Controls->Add(this->label22);
				 this->groupBox6->Controls->Add(this->comboBox19);
				 this->groupBox6->Controls->Add(this->comboBox18);
				 this->groupBox6->Controls->Add(this->comboBox17);
				 this->groupBox6->Controls->Add(this->comboBox16);
				 this->groupBox6->Controls->Add(this->label20);
				 this->groupBox6->Controls->Add(this->label19);
				 this->groupBox6->Controls->Add(this->label18);
				 this->groupBox6->Controls->Add(this->label17);
				 this->groupBox6->Controls->Add(this->label16);
				 this->groupBox6->Location = System::Drawing::Point(22, 6);
				 this->groupBox6->Name = L"groupBox6";
				 this->groupBox6->Size = System::Drawing::Size(269, 116);
				 this->groupBox6->TabIndex = 23;
				 this->groupBox6->TabStop = false;
				 this->groupBox6->Text = L"Local";
				 // 
				 // comboBox22
				 // 
				 this->comboBox22->FormattingEnabled = true;
				 this->comboBox22->Location = System::Drawing::Point(177, 90);
				 this->comboBox22->Name = L"comboBox22";
				 this->comboBox22->Size = System::Drawing::Size(59, 20);
				 this->comboBox22->TabIndex = 13;
				 // 
				 // comboBox20
				 // 
				 this->comboBox20->FormattingEnabled = true;
				 this->comboBox20->Location = System::Drawing::Point(177, 64);
				 this->comboBox20->Name = L"comboBox20";
				 this->comboBox20->Size = System::Drawing::Size(59, 20);
				 this->comboBox20->TabIndex = 12;
				 // 
				 // comboBox21
				 // 
				 this->comboBox21->FormattingEnabled = true;
				 this->comboBox21->Location = System::Drawing::Point(89, 90);
				 this->comboBox21->Name = L"comboBox21";
				 this->comboBox21->Size = System::Drawing::Size(59, 20);
				 this->comboBox21->TabIndex = 11;
				 // 
				 // label21
				 // 
				 this->label21->AutoSize = true;
				 this->label21->Location = System::Drawing::Point(154, 93);
				 this->label21->Name = L"label21";
				 this->label21->Size = System::Drawing::Size(17, 12);
				 this->label21->TabIndex = 10;
				 this->label21->Text = L"K:";
				 // 
				 // label22
				 // 
				 this->label22->AutoSize = true;
				 this->label22->Location = System::Drawing::Point(12, 93);
				 this->label22->Name = L"label22";
				 this->label22->Size = System::Drawing::Size(71, 12);
				 this->label22->TabIndex = 9;
				 this->label22->Text = L"Level:   J:";
				 // 
				 // comboBox19
				 // 
				 this->comboBox19->FormattingEnabled = true;
				 this->comboBox19->Location = System::Drawing::Point(89, 64);
				 this->comboBox19->Name = L"comboBox19";
				 this->comboBox19->Size = System::Drawing::Size(59, 20);
				 this->comboBox19->TabIndex = 8;
				 // 
				 // comboBox18
				 // 
				 this->comboBox18->FormattingEnabled = true;
				 this->comboBox18->Location = System::Drawing::Point(177, 38);
				 this->comboBox18->Name = L"comboBox18";
				 this->comboBox18->Size = System::Drawing::Size(59, 20);
				 this->comboBox18->TabIndex = 7;
				 // 
				 // comboBox17
				 // 
				 this->comboBox17->FormattingEnabled = true;
				 this->comboBox17->Location = System::Drawing::Point(89, 38);
				 this->comboBox17->Name = L"comboBox17";
				 this->comboBox17->Size = System::Drawing::Size(59, 20);
				 this->comboBox17->TabIndex = 6;
				 // 
				 // comboBox16
				 // 
				 this->comboBox16->FormattingEnabled = true;
				 this->comboBox16->Location = System::Drawing::Point(89, 13);
				 this->comboBox16->Name = L"comboBox16";
				 this->comboBox16->Size = System::Drawing::Size(88, 20);
				 this->comboBox16->TabIndex = 5;
				 // 
				 // label20
				 // 
				 this->label20->AutoSize = true;
				 this->label20->Location = System::Drawing::Point(154, 67);
				 this->label20->Name = L"label20";
				 this->label20->Size = System::Drawing::Size(17, 12);
				 this->label20->TabIndex = 4;
				 this->label20->Text = L"K:";
				 // 
				 // label19
				 // 
				 this->label19->AutoSize = true;
				 this->label19->Location = System::Drawing::Point(12, 67);
				 this->label19->Name = L"label19";
				 this->label19->Size = System::Drawing::Size(71, 12);
				 this->label19->TabIndex = 3;
				 this->label19->Text = L"Slope:   J:";
				 // 
				 // label18
				 // 
				 this->label18->AutoSize = true;
				 this->label18->Location = System::Drawing::Point(154, 41);
				 this->label18->Name = L"label18";
				 this->label18->Size = System::Drawing::Size(17, 12);
				 this->label18->TabIndex = 2;
				 this->label18->Text = L"K:";
				 // 
				 // label17
				 // 
				 this->label17->AutoSize = true;
				 this->label17->Location = System::Drawing::Point(12, 41);
				 this->label17->Name = L"label17";
				 this->label17->Size = System::Drawing::Size(71, 12);
				 this->label17->TabIndex = 1;
				 this->label17->Text = L"Source:  J:";
				 // 
				 // label16
				 // 
				 this->label16->AutoSize = true;
				 this->label16->Location = System::Drawing::Point(12, 16);
				 this->label16->Name = L"label16";
				 this->label16->Size = System::Drawing::Size(65, 12);
				 this->label16->TabIndex = 0;
				 this->label16->Text = L"Operation:";
				 // 
				 // groupBox5
				 // 
				 this->groupBox5->Controls->Add(this->comboBox24);
				 this->groupBox5->Controls->Add(this->comboBox23);
				 this->groupBox5->Controls->Add(this->label26);
				 this->groupBox5->Controls->Add(this->label25);
				 this->groupBox5->Location = System::Drawing::Point(22, 120);
				 this->groupBox5->Name = L"groupBox5";
				 this->groupBox5->Size = System::Drawing::Size(269, 80);
				 this->groupBox5->TabIndex = 22;
				 this->groupBox5->TabStop = false;
				 this->groupBox5->Text = L"Extern";
				 // 
				 // comboBox24
				 // 
				 this->comboBox24->FormattingEnabled = true;
				 this->comboBox24->Location = System::Drawing::Point(89, 46);
				 this->comboBox24->Name = L"comboBox24";
				 this->comboBox24->Size = System::Drawing::Size(121, 20);
				 this->comboBox24->TabIndex = 21;
				 // 
				 // comboBox23
				 // 
				 this->comboBox23->FormattingEnabled = true;
				 this->comboBox23->Location = System::Drawing::Point(89, 20);
				 this->comboBox23->Name = L"comboBox23";
				 this->comboBox23->Size = System::Drawing::Size(121, 20);
				 this->comboBox23->TabIndex = 20;
				 // 
				 // label26
				 // 
				 this->label26->AutoSize = true;
				 this->label26->Location = System::Drawing::Point(12, 49);
				 this->label26->Name = L"label26";
				 this->label26->Size = System::Drawing::Size(35, 12);
				 this->label26->TabIndex = 19;
				 this->label26->Text = L"Range";
				 // 
				 // label25
				 // 
				 this->label25->AutoSize = true;
				 this->label25->Location = System::Drawing::Point(12, 23);
				 this->label25->Name = L"label25";
				 this->label25->Size = System::Drawing::Size(53, 12);
				 this->label25->TabIndex = 18;
				 this->label25->Text = L"Coupling";
				 // 
				 // textBox2
				 // 
				 this->textBox2->Location = System::Drawing::Point(111, 233);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(100, 21);
				 this->textBox2->TabIndex = 17;
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(111, 206);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(100, 21);
				 this->textBox1->TabIndex = 15;
				 // 
				 // label24
				 // 
				 this->label24->AutoSize = true;
				 this->label24->Location = System::Drawing::Point(34, 236);
				 this->label24->Name = L"label24";
				 this->label24->Size = System::Drawing::Size(53, 12);
				 this->label24->TabIndex = 16;
				 this->label24->Text = L"TimeOut:";
				 // 
				 // label23
				 // 
				 this->label23->AutoSize = true;
				 this->label23->Location = System::Drawing::Point(34, 209);
				 this->label23->Name = L"label23";
				 this->label23->Size = System::Drawing::Size(41, 12);
				 this->label23->TabIndex = 14;
				 this->label23->Text = L"Delay:";
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->groupBox4);
				 this->tabPage2->Controls->Add(this->groupBox3);
				 this->tabPage2->Controls->Add(this->comboBox9);
				 this->tabPage2->Controls->Add(this->label9);
				 this->tabPage2->Location = System::Drawing::Point(4, 21);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(330, 264);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"输入";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // groupBox4
				 // 
				 this->groupBox4->Controls->Add(this->label10);
				 this->groupBox4->Controls->Add(this->comboBox14);
				 this->groupBox4->Controls->Add(this->label14);
				 this->groupBox4->Controls->Add(this->comboBox15);
				 this->groupBox4->Controls->Add(this->label15);
				 this->groupBox4->Controls->Add(this->comboBox13);
				 this->groupBox4->Location = System::Drawing::Point(6, 148);
				 this->groupBox4->Name = L"groupBox4";
				 this->groupBox4->Size = System::Drawing::Size(310, 99);
				 this->groupBox4->TabIndex = 11;
				 this->groupBox4->TabStop = false;
				 this->groupBox4->Text = L"ChannelB";
				 // 
				 // label10
				 // 
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(24, 70);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(65, 12);
				 this->label10->TabIndex = 5;
				 this->label10->Text = L"Impedance:";
				 // 
				 // comboBox14
				 // 
				 this->comboBox14->FormattingEnabled = true;
				 this->comboBox14->Location = System::Drawing::Point(113, 42);
				 this->comboBox14->Name = L"comboBox14";
				 this->comboBox14->Size = System::Drawing::Size(81, 20);
				 this->comboBox14->TabIndex = 4;
				 // 
				 // label14
				 // 
				 this->label14->AutoSize = true;
				 this->label14->Location = System::Drawing::Point(24, 45);
				 this->label14->Name = L"label14";
				 this->label14->Size = System::Drawing::Size(41, 12);
				 this->label14->TabIndex = 3;
				 this->label14->Text = L"Range:";
				 // 
				 // comboBox15
				 // 
				 this->comboBox15->FormattingEnabled = true;
				 this->comboBox15->Location = System::Drawing::Point(113, 67);
				 this->comboBox15->Name = L"comboBox15";
				 this->comboBox15->Size = System::Drawing::Size(81, 20);
				 this->comboBox15->TabIndex = 2;
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->Location = System::Drawing::Point(24, 19);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(59, 12);
				 this->label15->TabIndex = 1;
				 this->label15->Text = L"Coupling:";
				 // 
				 // comboBox13
				 // 
				 this->comboBox13->FormattingEnabled = true;
				 this->comboBox13->Location = System::Drawing::Point(113, 16);
				 this->comboBox13->Name = L"comboBox13";
				 this->comboBox13->Size = System::Drawing::Size(81, 20);
				 this->comboBox13->TabIndex = 2;
				 // 
				 // groupBox3
				 // 
				 this->groupBox3->Controls->Add(this->comboBox10);
				 this->groupBox3->Controls->Add(this->comboBox11);
				 this->groupBox3->Controls->Add(this->label11);
				 this->groupBox3->Controls->Add(this->comboBox12);
				 this->groupBox3->Controls->Add(this->label12);
				 this->groupBox3->Controls->Add(this->label13);
				 this->groupBox3->Location = System::Drawing::Point(6, 43);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(310, 99);
				 this->groupBox3->TabIndex = 10;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"ChannelA";
				 // 
				 // comboBox10
				 // 
				 this->comboBox10->FormattingEnabled = true;
				 this->comboBox10->Location = System::Drawing::Point(113, 16);
				 this->comboBox10->Name = L"comboBox10";
				 this->comboBox10->Size = System::Drawing::Size(81, 20);
				 this->comboBox10->TabIndex = 6;
				 // 
				 // comboBox11
				 // 
				 this->comboBox11->FormattingEnabled = true;
				 this->comboBox11->Location = System::Drawing::Point(113, 42);
				 this->comboBox11->Name = L"comboBox11";
				 this->comboBox11->Size = System::Drawing::Size(81, 20);
				 this->comboBox11->TabIndex = 6;
				 // 
				 // label11
				 // 
				 this->label11->AutoSize = true;
				 this->label11->Location = System::Drawing::Point(24, 70);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(65, 12);
				 this->label11->TabIndex = 5;
				 this->label11->Text = L"Impedance:";
				 // 
				 // comboBox12
				 // 
				 this->comboBox12->FormattingEnabled = true;
				 this->comboBox12->Location = System::Drawing::Point(113, 67);
				 this->comboBox12->Name = L"comboBox12";
				 this->comboBox12->Size = System::Drawing::Size(81, 20);
				 this->comboBox12->TabIndex = 4;
				 // 
				 // label12
				 // 
				 this->label12->AutoSize = true;
				 this->label12->Location = System::Drawing::Point(24, 45);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(41, 12);
				 this->label12->TabIndex = 3;
				 this->label12->Text = L"Range:";
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->Location = System::Drawing::Point(24, 19);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(59, 12);
				 this->label13->TabIndex = 1;
				 this->label13->Text = L"Coupling:";
				 // 
				 // comboBox9
				 // 
				 this->comboBox9->FormattingEnabled = true;
				 this->comboBox9->Location = System::Drawing::Point(132, 14);
				 this->comboBox9->Name = L"comboBox9";
				 this->comboBox9->Size = System::Drawing::Size(83, 20);
				 this->comboBox9->TabIndex = 1;
				 this->comboBox9->SelectedIndexChanged += gcnew System::EventHandler(this, &FormConfigration1::comboBox9_SelectedIndexChanged);
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(30, 18);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(89, 12);
				 this->label9->TabIndex = 0;
				 this->label9->Text = L"Input Channel:";
				 // 
				 // tabPage1
				 // 
				 this->tabPage1->Controls->Add(this->groupBox2);
				 this->tabPage1->Controls->Add(this->groupBox1);
				 this->tabPage1->Location = System::Drawing::Point(4, 21);
				 this->tabPage1->Name = L"tabPage1";
				 this->tabPage1->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage1->Size = System::Drawing::Size(330, 264);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Text = L"基本设定";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->comboBox5);
				 this->groupBox2->Controls->Add(this->label5);
				 this->groupBox2->Controls->Add(this->comboBox6);
				 this->groupBox2->Controls->Add(this->label6);
				 this->groupBox2->Controls->Add(this->comboBox7);
				 this->groupBox2->Controls->Add(this->label7);
				 this->groupBox2->Controls->Add(this->comboBox8);
				 this->groupBox2->Controls->Add(this->label8);
				 this->groupBox2->Location = System::Drawing::Point(6, 133);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(310, 121);
				 this->groupBox2->TabIndex = 10;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Clock";
				 // 
				 // comboBox5
				 // 
				 this->comboBox5->FormattingEnabled = true;
				 this->comboBox5->Location = System::Drawing::Point(113, 16);
				 this->comboBox5->Name = L"comboBox5";
				 this->comboBox5->Size = System::Drawing::Size(83, 20);
				 this->comboBox5->TabIndex = 8;
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(24, 96);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(71, 12);
				 this->label5->TabIndex = 7;
				 this->label5->Text = L"Decimation:";
				 // 
				 // comboBox6
				 // 
				 this->comboBox6->FormattingEnabled = true;
				 this->comboBox6->Location = System::Drawing::Point(113, 42);
				 this->comboBox6->Name = L"comboBox6";
				 this->comboBox6->Size = System::Drawing::Size(83, 20);
				 this->comboBox6->TabIndex = 6;
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(24, 70);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(35, 12);
				 this->label6->TabIndex = 5;
				 this->label6->Text = L"Edge:";
				 // 
				 // comboBox7
				 // 
				 this->comboBox7->FormattingEnabled = true;
				 this->comboBox7->Location = System::Drawing::Point(113, 67);
				 this->comboBox7->Name = L"comboBox7";
				 this->comboBox7->Size = System::Drawing::Size(83, 20);
				 this->comboBox7->TabIndex = 4;
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(24, 45);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(53, 12);
				 this->label7->TabIndex = 3;
				 this->label7->Text = L"Rate ID:";
				 // 
				 // comboBox8
				 // 
				 this->comboBox8->FormattingEnabled = true;
				 this->comboBox8->Location = System::Drawing::Point(113, 93);
				 this->comboBox8->Name = L"comboBox8";
				 this->comboBox8->Size = System::Drawing::Size(83, 20);
				 this->comboBox8->TabIndex = 2;
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(24, 19);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(47, 12);
				 this->label8->TabIndex = 1;
				 this->label8->Text = L"Source:";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->comboBox4);
				 this->groupBox1->Controls->Add(this->label4);
				 this->groupBox1->Controls->Add(this->comboBox3);
				 this->groupBox1->Controls->Add(this->label3);
				 this->groupBox1->Controls->Add(this->comboBox2);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->comboBox1);
				 this->groupBox1->Controls->Add(this->label1);
				 this->groupBox1->Location = System::Drawing::Point(6, 6);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(310, 121);
				 this->groupBox1->TabIndex = 9;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"System";
				 // 
				 // comboBox4
				 // 
				 this->comboBox4->FormattingEnabled = true;
				 this->comboBox4->Location = System::Drawing::Point(113, 93);
				 this->comboBox4->Name = L"comboBox4";
				 this->comboBox4->Size = System::Drawing::Size(83, 20);
				 this->comboBox4->TabIndex = 8;
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(24, 96);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(59, 12);
				 this->label4->TabIndex = 7;
				 this->label4->Text = L"Borad ID:";
				 // 
				 // comboBox3
				 // 
				 this->comboBox3->FormattingEnabled = true;
				 this->comboBox3->Location = System::Drawing::Point(113, 67);
				 this->comboBox3->Name = L"comboBox3";
				 this->comboBox3->Size = System::Drawing::Size(83, 20);
				 this->comboBox3->TabIndex = 6;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(24, 70);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(65, 12);
				 this->label3->TabIndex = 5;
				 this->label3->Text = L"System ID:";
				 // 
				 // comboBox2
				 // 
				 this->comboBox2->FormattingEnabled = true;
				 this->comboBox2->Location = System::Drawing::Point(113, 42);
				 this->comboBox2->Name = L"comboBox2";
				 this->comboBox2->Size = System::Drawing::Size(83, 20);
				 this->comboBox2->TabIndex = 4;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(24, 45);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(77, 12);
				 this->label2->TabIndex = 3;
				 this->label2->Text = L"Sample Rate:";
				 // 
				 // comboBox1
				 // 
				 this->comboBox1->FormattingEnabled = true;
				 this->comboBox1->Location = System::Drawing::Point(113, 16);
				 this->comboBox1->Name = L"comboBox1";
				 this->comboBox1->Size = System::Drawing::Size(83, 20);
				 this->comboBox1->TabIndex = 2;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(24, 19);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(83, 12);
				 this->label1->TabIndex = 1;
				 this->label1->Text = L"Buffer Count:";
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Controls->Add(this->tabPage3);
				 this->tabControl1->Controls->Add(this->tabPage5);
				 this->tabControl1->Controls->Add(this->Calib);
				 this->tabControl1->Location = System::Drawing::Point(12, 12);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(338, 289);
				 this->tabControl1->TabIndex = 2;
				 // 
				 // Calib
				 // 
				 this->Calib->Controls->Add(this->textBox12);
				 this->Calib->Controls->Add(this->textBox11);
				 this->Calib->Controls->Add(this->toolStrip1);
				 this->Calib->Controls->Add(this->label35);
				 this->Calib->Controls->Add(this->label34);
				 this->Calib->Controls->Add(this->textBox10);
				 this->Calib->Controls->Add(this->textBox9);
				 this->Calib->Controls->Add(this->radioButton2);
				 this->Calib->Controls->Add(this->radioButton1);
				 this->Calib->Controls->Add(this->textBox8);
				 this->Calib->Controls->Add(this->label33);
				 this->Calib->Controls->Add(this->label32);
				 this->Calib->Location = System::Drawing::Point(4, 21);
				 this->Calib->Name = L"Calib";
				 this->Calib->Padding = System::Windows::Forms::Padding(3);
				 this->Calib->Size = System::Drawing::Size(330, 264);
				 this->Calib->TabIndex = 5;
				 this->Calib->Text = L"Calib";
				 this->Calib->UseVisualStyleBackColor = true;
				 // 
				 // textBox10
				 // 
				 this->textBox10->Location = System::Drawing::Point(135, 166);
				 this->textBox10->Name = L"textBox10";
				 this->textBox10->Size = System::Drawing::Size(86, 21);
				 this->textBox10->TabIndex = 6;
				 // 
				 // textBox9
				 // 
				 this->textBox9->Location = System::Drawing::Point(135, 139);
				 this->textBox9->Name = L"textBox9";
				 this->textBox9->Size = System::Drawing::Size(86, 21);
				 this->textBox9->TabIndex = 5;
				 // 
				 // radioButton2
				 // 
				 this->radioButton2->AutoSize = true;
				 this->radioButton2->Location = System::Drawing::Point(80, 167);
				 this->radioButton2->Name = L"radioButton2";
				 this->radioButton2->Size = System::Drawing::Size(47, 16);
				 this->radioButton2->TabIndex = 4;
				 this->radioButton2->TabStop = true;
				 this->radioButton2->Text = L"长度";
				 this->radioButton2->UseVisualStyleBackColor = true;
				 // 
				 // radioButton1
				 // 
				 this->radioButton1->AutoSize = true;
				 this->radioButton1->Location = System::Drawing::Point(80, 140);
				 this->radioButton1->Name = L"radioButton1";
				 this->radioButton1->Size = System::Drawing::Size(47, 16);
				 this->radioButton1->TabIndex = 3;
				 this->radioButton1->TabStop = true;
				 this->radioButton1->Text = L"阈值";
				 this->radioButton1->UseVisualStyleBackColor = true;
				 // 
				 // textBox8
				 // 
				 this->textBox8->Location = System::Drawing::Point(135, 88);
				 this->textBox8->Name = L"textBox8";
				 this->textBox8->Size = System::Drawing::Size(86, 21);
				 this->textBox8->TabIndex = 2;
				 this->textBox8->Text = L"60";
				 // 
				 // label33
				 // 
				 this->label33->AutoSize = true;
				 this->label33->Location = System::Drawing::Point(54, 112);
				 this->label33->Name = L"label33";
				 this->label33->Size = System::Drawing::Size(95, 12);
				 this->label33->TabIndex = 1;
				 this->label33->Text = L"SelectFunction:";
				 // 
				 // label32
				 // 
				 this->label32->AutoSize = true;
				 this->label32->Location = System::Drawing::Point(54, 91);
				 this->label32->Name = L"label32";
				 this->label32->Size = System::Drawing::Size(77, 12);
				 this->label32->TabIndex = 0;
				 this->label32->Text = L"NumsOfAscan:";
				 // 
				 // label34
				 // 
				 this->label34->AutoSize = true;
				 this->label34->Location = System::Drawing::Point(54, 35);
				 this->label34->Name = L"label34";
				 this->label34->Size = System::Drawing::Size(41, 12);
				 this->label34->TabIndex = 7;
				 this->label34->Text = L"Start:";
				 // 
				 // label35
				 // 
				 this->label35->AutoSize = true;
				 this->label35->Location = System::Drawing::Point(54, 61);
				 this->label35->Name = L"label35";
				 this->label35->Size = System::Drawing::Size(29, 12);
				 this->label35->TabIndex = 8;
				 this->label35->Text = L"End:";
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Location = System::Drawing::Point(3, 3);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(324, 25);
				 this->toolStrip1->TabIndex = 9;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // textBox11
				 // 
				 this->textBox11->Location = System::Drawing::Point(135, 34);
				 this->textBox11->Name = L"textBox11";
				 this->textBox11->Size = System::Drawing::Size(86, 21);
				 this->textBox11->TabIndex = 10;
				 this->textBox11->Text = L"2400";
				 // 
				 // textBox12
				 // 
				 this->textBox12->Location = System::Drawing::Point(135, 61);
				 this->textBox12->Name = L"textBox12";
				 this->textBox12->Size = System::Drawing::Size(86, 21);
				 this->textBox12->TabIndex = 11;
				 this->textBox12->Text = L"5900";
				 // 
				 // FormConfigration1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(362, 347);
				 this->Controls->Add(this->tabControl1);
				 this->Controls->Add(this->BNCfgCancle);
				 this->Controls->Add(this->BNCfgSave);
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"FormConfigration1";
				 this->ShowIcon = false;
				 this->Text = L"Configuration";
				 this->Load += gcnew System::EventHandler(this, &FormConfigration1::FormConfigration1_Load);
				 this->tabPage5->ResumeLayout(false);
				 this->tabPage5->PerformLayout();
				 this->groupBox7->ResumeLayout(false);
				 this->groupBox7->PerformLayout();
				 this->tabPage3->ResumeLayout(false);
				 this->tabPage3->PerformLayout();
				 this->groupBox6->ResumeLayout(false);
				 this->groupBox6->PerformLayout();
				 this->groupBox5->ResumeLayout(false);
				 this->groupBox5->PerformLayout();
				 this->tabPage2->ResumeLayout(false);
				 this->tabPage2->PerformLayout();
				 this->groupBox4->ResumeLayout(false);
				 this->groupBox4->PerformLayout();
				 this->groupBox3->ResumeLayout(false);
				 this->groupBox3->PerformLayout();
				 this->tabPage1->ResumeLayout(false);
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->tabControl1->ResumeLayout(false);
				 this->Calib->ResumeLayout(false);
				 this->Calib->PerformLayout();
				 this->ResumeLayout(false);

			 }
#pragma endregion
	private: 
		System::Void BNCfgCancle_Click(System::Object^  sender, System::EventArgs^  e){
			isFlSd=false;
			this->Close();
		}
	private: 
		System::Void BNCfgSave_Click(System::Object^  sender, System::EventArgs^  e){
			System::IO::Stream^ fs;
			System::IO::StreamWriter^ sw;
			SaveFileDialog ^sfdBoradInfo=gcnew SaveFileDialog();
			sfdBoradInfo->InitialDirectory=System::IO::Directory::GetCurrentDirectory()+"/resources/config/";
			sfdBoradInfo->Filter=L"配置文件(*.ini)|*.ini|所有文件(*.*)|*.*";
			sfdBoradInfo->FilterIndex=1;
			sfdBoradInfo->RestoreDirectory=true;
			sfdBoradInfo->DefaultExt=L".ini";
			sfdBoradInfo->AddExtension=true;
			if (sfdBoradInfo->ShowDialog()==System::Windows::Forms::DialogResult::OK){
				if ((fs=sfdBoradInfo->OpenFile())!=nullptr){
					//begin write
					Json::Value root;
					Json::Value sys;
					sys["buffer_count"]=int::Parse(((ComboBoxItem^)(this->comboBox1->SelectedItem))->Value());
					sys["samples_per_second"]=double::Parse(((ComboBoxItem^)(this->comboBox2->SelectedItem))->Value());
					sys["system_id"]=int::Parse(((ComboBoxItem^)(this->comboBox3->SelectedItem))->Value());
					sys["board_id"]=int::Parse(((ComboBoxItem^)(this->comboBox4->SelectedItem))->Value());
					root["system"]=sys;
					Json::Value clk;
					clk["clock_source"]=int::Parse(((ComboBoxItem^)(this->comboBox5->SelectedItem))->Value());
					clk["sample_rate"]=int::Parse(((ComboBoxItem^)(this->comboBox6->SelectedItem))->Value());
					clk["clock_edge"]=int::Parse(((ComboBoxItem^)(this->comboBox7->SelectedItem))->Value());
					clk["clock_decimation"]=int::Parse(((ComboBoxItem^)(this->comboBox8->SelectedItem))->Value());
					root["clock"]=clk;
					Json::Value chnl;
					chnl["input_channel"]=int::Parse(((ComboBoxItem^)(this->comboBox9->SelectedItem))->Value());
					Json::Value chA;
					chA["input_coupling"]=int::Parse(((ComboBoxItem^)(this->comboBox10->SelectedItem))->Value());
					chA["input_range"]=int::Parse(((ComboBoxItem^)(this->comboBox11->SelectedItem))->Value());
					chA["input_impedance"]=int::Parse(((ComboBoxItem^)(this->comboBox12->SelectedItem))->Value());
					chnl["channel_A"]=chA;
					Json::Value chB;
					chB["input_coupling"]=int::Parse(((ComboBoxItem^)(this->comboBox13->SelectedItem))->Value());
					chB["input_range"]=int::Parse(((ComboBoxItem^)(this->comboBox14->SelectedItem))->Value());
					chB["input_impedance"]=int::Parse(((ComboBoxItem^)(this->comboBox15->SelectedItem))->Value());
					chnl["channel_B"]=chB;
					root["channel"]=chnl;
					Json::Value trg;
					trg["trigger_operation"]=int::Parse(((ComboBoxItem^)(this->comboBox16->SelectedItem))->Value());
					Json::Value engine_J,engine_K;
					engine_J["trigger_source"]=int::Parse(((ComboBoxItem^)(this->comboBox17->SelectedItem))->Value());
					engine_J["trigger_slope"]=int::Parse(((ComboBoxItem^)(this->comboBox19->SelectedItem))->Value());
					engine_J["trigger_level"]=int::Parse(((ComboBoxItem^)(this->comboBox21->SelectedItem))->Value());
					trg["trigger_engine_J"]=engine_J;
					engine_K["trigger_source"]=int::Parse(((ComboBoxItem^)(this->comboBox18->SelectedItem))->Value());
					engine_K["trigger_slope"]=int::Parse(((ComboBoxItem^)(this->comboBox20->SelectedItem))->Value());
					engine_K["trigger_level"]=int::Parse(((ComboBoxItem^)(this->comboBox22->SelectedItem))->Value());
					trg["trigger_engine_K"]=engine_K;
					trg["trigger_ex_coupling"]=int::Parse(((ComboBoxItem^)(this->comboBox23->SelectedItem))->Value());
					trg["trigger_ex_range"]=int::Parse(((ComboBoxItem^)(this->comboBox24->SelectedItem))->Value());
					trg["trigger_delay"]=double::Parse(this->textBox1->Text);
					trg["trigger_timeout"]=double::Parse(this->textBox2->Text);
					root["trigger"]=trg;
					Json::Value aux;
					aux["mode"]=0;
					aux["parameters"]=0;
					root["AUX"]=aux;
					Json::Value acq;
					acq["pre_trigger_samples"]=int::Parse(this->textBox3->Text);
					acq["post_trigger_samples"]=int::Parse(this->textBox4->Text);
					acq["record_per_buffer"]=int::Parse(this->textBox5->Text);
					acq["buffers_per_image"]=int::Parse(this->textBox7->Text);
					root["acqusition_params"]=acq;
					Json::Value clb;
					clb["start_index"]=int::Parse(this->textBox11->Text);
					clb["end_index"]=int::Parse(this->textBox12->Text);
					clb["record_num_in_use"]=int::Parse(this->textBox8->Text);
					root["calib_params"]=clb;
					Json::StyledWriter writer;
					std::string output=writer.write(root);
					sw=gcnew StreamWriter(fs);
					sw->Write(gcnew String(output.c_str()));
					sw->Flush();
					sw->Close();
					fs->Close();
				}
			}
			this->sFlNm=sfdBoradInfo->FileName;
			this->isFlSd=true;
			this->Close();
		}
	private: 
		System::Void FormConfigration1_Load(System::Object^  sender, System::EventArgs^  e){
			std::ifstream ifs("resources/cfgdata.dat",std::ios::in);
			if (!ifs){
				MessageBox::Show(L"System File Does NOT Exist!!",L"Error");
				this->Close();
				return;
			}
			int boxIndex=0,itemIndex=-1;
			std::string tText,tValue;
			System::Windows::Forms::ComboBox^ tCb;
			while (!ifs.eof()){
				if (ifs.good()){
					if (ifs.peek()=='#'){
						ifs.ignore(1);
						if (itemIndex>0)
							tCb->SelectedIndex=itemIndex-1;
						if (ifs.eof()||!ifs.good())
							break;
						ifs>>boxIndex>>itemIndex;
						ifs.ignore(1);
						switch (boxIndex){
						case 1: tCb=this->comboBox1;break;
						case 2: tCb=this->comboBox2;break;
						case 3: tCb=this->comboBox3;break;
						case 4: tCb=this->comboBox4;break;
						case 5: tCb=this->comboBox5;break;
						case 6: tCb=this->comboBox6;break;
						case 7: tCb=this->comboBox7;break;
						case 8: tCb=this->comboBox8;break;
						case 9: tCb=this->comboBox9;break;
						case 10: tCb=this->comboBox10;break;
						case 11: tCb=this->comboBox11;break;
						case 12: tCb=this->comboBox12;break;
						case 13: tCb=this->comboBox13;break;
						case 14: tCb=this->comboBox14;break;
						case 15: tCb=this->comboBox15;break;
						case 16: tCb=this->comboBox16;break;
						case 17: tCb=this->comboBox17;break;
						case 18: tCb=this->comboBox18;break;
						case 19: tCb=this->comboBox19;break;
						case 20: tCb=this->comboBox20;break;
						case 21: tCb=this->comboBox21;break;
						case 22: tCb=this->comboBox22;break;
						case 23: tCb=this->comboBox23;break;
						case 24: tCb=this->comboBox24;break;
						default: tCb=nullptr;break;
						}
						continue;
					}
					if(tCb==nullptr) 
						break;
					ifs>>tText>>tValue;
					ifs.ignore(1);
					tCb->Items->Add(gcnew ComboBoxItem(
						gcnew String(tText.c_str()),
						gcnew String(tValue.c_str())));
				}
			}
			ifs.close();
			this->textBox1->Text=L"0";
			this->textBox2->Text=L"0";
			this->groupBox3->Enabled=false;
			this->groupBox4->Enabled=true;
		}
	private:
		System::Void comboBox9_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			if ((this->comboBox9->SelectedIndex+1)&1){
				this->groupBox3->Enabled=true;
			}else{
				this->groupBox3->Enabled=false;
			}
			if ((this->comboBox9->SelectedIndex+1)&2){
				this->groupBox4->Enabled=true;
			}else{
				this->groupBox4->Enabled=false;
			}
		}
	private:
		System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (this->checkBox2->Checked){
				this->textBox3->ReadOnly=true;
				this->textBox4->ReadOnly=true;
				this->textBox5->ReadOnly=true;
				this->textBox3->Text=L"1024";
				this->textBox4->Text=L"1024";
				this->textBox5->Text=L"100";
			} 
			else{
				MessageBox::Show(L"请勿随意更改相关数据!",L"提示");
				this->textBox3->ReadOnly=false;
				this->textBox4->ReadOnly=false;
				this->textBox5->ReadOnly=false;
			}
		}
	private:
		System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (this->checkBox1->Checked){
				this->textBox6->ReadOnly=false;
			} 
			else{
				this->textBox6->ReadOnly=true;
			}
		}
	};
}
