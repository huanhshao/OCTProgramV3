#pragma once
#include "stdafx.h"
#include "CLGL.h"
#include "ConfigrationForm.h"
#include "thread.h"
#include "AlazarInfo.h"
#include "AdvantInfo.h"
#include "MulThrdHds.h"
namespace OCTProgram {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// OCT Program Main Interface.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//initialize resources
			cgl = new OpenCLGLClass();
			alazar = new AlazarInfo();
			adv = new AdvInfo();
			dc = GetDC((HWND)(this->Handle.ToInt32()));
			int w = 0;
			int h = 0;
			alazar->GetImageSize(&w, &h);	//w=1024,h=records per buffer
			adv->SetSignal(1.0,0.0,h);
			cgl->Initialize(dc, w, h);
			cgl->SetViewPort(0, 0, this->ClientSize.Width, this->ClientSize.Height);
			cgl->RenderScene();
			save_count = 0;
			//create threads
			ap = new AcqParam;
			ap->alazar = alazar;
			ap->clgl = cgl;
			ap->adv=adv;
			ap->thread_handle = (HANDLE)_beginthreadex(NULL, 0, &ACQDATA, ap, 0, NULL);
			pp = new ProcessParam;
			pp->clgl = cgl;
			pp->thread_handle = (HANDLE)_beginthreadex(NULL, 0, &PROCESSDATA, pp, 0, NULL);
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MainForm()
		{            
			if (pp){
				pp->EndThread();
				delete pp;
				pp = nullptr;
			}
			if (ap){
				ap->EndThread();
				delete ap;
				ap = nullptr;
			}
			if (cgl){
				delete cgl;
				cgl = nullptr;
			}
			if (alazar){
				delete alazar;
				alazar = nullptr;
			}
			if (adv){
				delete adv;
				adv=nullptr;
			}
			if (components){
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  菜单ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ConfigrationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  StartAcqBotton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^  StopAcqBotton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  窗口ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  gradationToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBoxGradation;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::ToolStripMenuItem^  帮助ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		HDC dc;
		OpenCLGLClass* cgl;
		AlazarInfo* alazar;
		AdvInfo* adv;
		AcqParam* ap;
		ProcessParam* pp;
		int save_count;

	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStripButton^  CapScrButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  labelFPS;
	private: System::Windows::Forms::ToolStripButton^  SaveDataButton;
	private: System::Windows::Forms::ToolStripButton^  StopSaveButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  CalibButton;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label2;



	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 设计器支持所需的方法 - 不要
			 /// 使用代码编辑器修改此方法的内容。
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->菜单ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ConfigrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->窗口ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->gradationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->帮助ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->StartAcqBotton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->StopAcqBotton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->SaveDataButton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->StopSaveButton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->CapScrButton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->CalibButton = (gcnew System::Windows::Forms::ToolStripButton());
				 this->groupBoxGradation = (gcnew System::Windows::Forms::GroupBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
				 this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->labelFPS = (gcnew System::Windows::Forms::Label());
				 this->menuStrip1->SuspendLayout();
				 this->toolStrip1->SuspendLayout();
				 this->groupBoxGradation->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->菜单ToolStripMenuItem, 
					 this->窗口ToolStripMenuItem, this->帮助ToolStripMenuItem});
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(992, 24);
				 this->menuStrip1->TabIndex = 0;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // 菜单ToolStripMenuItem
				 // 
				 this->菜单ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->ConfigrationToolStripMenuItem, 
					 this->exitToolStripMenuItem});
				 this->菜单ToolStripMenuItem->Name = L"菜单ToolStripMenuItem";
				 this->菜单ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
				 this->菜单ToolStripMenuItem->Text = L"菜单";
				 // 
				 // ConfigrationToolStripMenuItem
				 // 
				 this->ConfigrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->newToolStripMenuItem, 
					 this->loadToolStripMenuItem});
				 this->ConfigrationToolStripMenuItem->Name = L"ConfigrationToolStripMenuItem";
				 this->ConfigrationToolStripMenuItem->Size = System::Drawing::Size(133, 22);
				 this->ConfigrationToolStripMenuItem->Text = L"Configration";
				 // 
				 // newToolStripMenuItem
				 // 
				 this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
				 this->newToolStripMenuItem->Size = System::Drawing::Size(97, 22);
				 this->newToolStripMenuItem->Text = L"New";
				 this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
				 // 
				 // loadToolStripMenuItem
				 // 
				 this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
				 this->loadToolStripMenuItem->Size = System::Drawing::Size(97, 22);
				 this->loadToolStripMenuItem->Text = L"Load";
				 this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadToolStripMenuItem_Click);
				 // 
				 // exitToolStripMenuItem
				 // 
				 this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
				 this->exitToolStripMenuItem->Size = System::Drawing::Size(133, 22);
				 this->exitToolStripMenuItem->Text = L"Exit";
				 this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
				 // 
				 // 窗口ToolStripMenuItem
				 // 
				 this->窗口ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->gradationToolStripMenuItem});
				 this->窗口ToolStripMenuItem->Name = L"窗口ToolStripMenuItem";
				 this->窗口ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
				 this->窗口ToolStripMenuItem->Text = L"窗口";
				 // 
				 // gradationToolStripMenuItem
				 // 
				 this->gradationToolStripMenuItem->CheckOnClick = true;
				 this->gradationToolStripMenuItem->Name = L"gradationToolStripMenuItem";
				 this->gradationToolStripMenuItem->Size = System::Drawing::Size(121, 22);
				 this->gradationToolStripMenuItem->Text = L"Gradation";
				 this->gradationToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::gradationToolStripMenuItem_CheckedChanged);
				 // 
				 // 帮助ToolStripMenuItem
				 // 
				 this->帮助ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->aboutToolStripMenuItem, 
					 this->helpToolStripMenuItem});
				 this->帮助ToolStripMenuItem->Name = L"帮助ToolStripMenuItem";
				 this->帮助ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
				 this->帮助ToolStripMenuItem->Text = L"帮助";
				 // 
				 // aboutToolStripMenuItem
				 // 
				 this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
				 this->aboutToolStripMenuItem->Size = System::Drawing::Size(103, 22);
				 this->aboutToolStripMenuItem->Text = L"About";
				 this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
				 // 
				 // helpToolStripMenuItem
				 // 
				 this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
				 this->helpToolStripMenuItem->Size = System::Drawing::Size(103, 22);
				 this->helpToolStripMenuItem->Text = L"Help";
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Location = System::Drawing::Point(0, 696);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(992, 22);
				 this->statusStrip1->TabIndex = 1;
				 this->statusStrip1->Text = L"statusStrip1";
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {this->StartAcqBotton, this->toolStripSeparator1, 
					 this->StopAcqBotton, this->toolStripSeparator2, this->SaveDataButton, this->toolStripSeparator3, this->StopSaveButton, this->toolStripSeparator4, 
					 this->CapScrButton, this->toolStripSeparator5, this->CalibButton});
				 this->toolStrip1->Location = System::Drawing::Point(0, 24);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(992, 25);
				 this->toolStrip1->TabIndex = 2;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // StartAcqBotton
				 // 
				 this->StartAcqBotton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->StartAcqBotton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->StartAcqBotton->Name = L"StartAcqBotton";
				 this->StartAcqBotton->Size = System::Drawing::Size(23, 22);
				 this->StartAcqBotton->Text = L"StartAcq";
				 this->StartAcqBotton->Click += gcnew System::EventHandler(this, &MainForm::StartAcqBotton_Click);
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
				 // 
				 // StopAcqBotton
				 // 
				 this->StopAcqBotton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->StopAcqBotton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->StopAcqBotton->Name = L"StopAcqBotton";
				 this->StopAcqBotton->Size = System::Drawing::Size(23, 22);
				 this->StopAcqBotton->Text = L"StopAcq";
				 this->StopAcqBotton->Click += gcnew System::EventHandler(this, &MainForm::StopAcqBotton_Click);
				 // 
				 // toolStripSeparator2
				 // 
				 this->toolStripSeparator2->Name = L"toolStripSeparator2";
				 this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
				 // 
				 // SaveDataButton
				 // 
				 this->SaveDataButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->SaveDataButton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->SaveDataButton->Name = L"SaveDataButton";
				 this->SaveDataButton->Size = System::Drawing::Size(23, 22);
				 this->SaveDataButton->Text = L"SaveData";
				 this->SaveDataButton->Click += gcnew System::EventHandler(this, &MainForm::SaveDataButton_Click);
				 // 
				 // toolStripSeparator3
				 // 
				 this->toolStripSeparator3->Name = L"toolStripSeparator3";
				 this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
				 // 
				 // StopSaveButton
				 // 
				 this->StopSaveButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->StopSaveButton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->StopSaveButton->Name = L"StopSaveButton";
				 this->StopSaveButton->Size = System::Drawing::Size(23, 22);
				 this->StopSaveButton->Text = L"StopSave";
				 this->StopSaveButton->Click += gcnew System::EventHandler(this, &MainForm::StopSaveButton_Click);
				 // 
				 // toolStripSeparator4
				 // 
				 this->toolStripSeparator4->Name = L"toolStripSeparator4";
				 this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
				 // 
				 // CapScrButton
				 // 
				 this->CapScrButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->CapScrButton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->CapScrButton->Name = L"CapScrButton";
				 this->CapScrButton->Size = System::Drawing::Size(23, 22);
				 this->CapScrButton->Text = L"CapScr";
				 this->CapScrButton->Click += gcnew System::EventHandler(this, &MainForm::toolStripCapScr_Click);
				 // 
				 // toolStripSeparator5
				 // 
				 this->toolStripSeparator5->Name = L"toolStripSeparator5";
				 this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
				 // 
				 // CalibButton
				 // 
				 this->CalibButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->CalibButton->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->CalibButton->Name = L"CalibButton";
				 this->CalibButton->Size = System::Drawing::Size(23, 22);
				 this->CalibButton->Text = L"CailbData";
				 this->CalibButton->Click += gcnew System::EventHandler(this, &MainForm::CalibButton_Click);
				 // 
				 // groupBoxGradation
				 // 
				 this->groupBoxGradation->BackColor = System::Drawing::SystemColors::Control;
				 this->groupBoxGradation->Controls->Add(this->label3);
				 this->groupBoxGradation->Controls->Add(this->label2);
				 this->groupBoxGradation->Controls->Add(this->chart1);
				 this->groupBoxGradation->Controls->Add(this->trackBar2);
				 this->groupBoxGradation->Controls->Add(this->trackBar1);
				 this->groupBoxGradation->Font = (gcnew System::Drawing::Font(L"宋体", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(134)));
				 this->groupBoxGradation->ForeColor = System::Drawing::SystemColors::ControlText;
				 this->groupBoxGradation->Location = System::Drawing::Point(760, 520);
				 this->groupBoxGradation->Name = L"groupBoxGradation";
				 this->groupBoxGradation->Size = System::Drawing::Size(220, 173);
				 this->groupBoxGradation->TabIndex = 3;
				 this->groupBoxGradation->TabStop = false;
				 this->groupBoxGradation->Text = L"色阶调整";
				 this->groupBoxGradation->Visible = false;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(120, 17);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(41, 12);
				 this->label3->TabIndex = 4;
				 this->label3->Text = L"label3";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(16, 17);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(41, 12);
				 this->label2->TabIndex = 3;
				 this->label2->Text = L"label2";
				 // 
				 // chart1
				 // 
				 chartArea1->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
				 chartArea1->AxisX2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
				 chartArea1->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
				 chartArea1->AxisY2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
				 chartArea1->Name = L"ChartArea1";
				 chartArea1->Position->Auto = false;
				 chartArea1->Position->Height = 100;
				 chartArea1->Position->Width = 100;
				 this->chart1->ChartAreas->Add(chartArea1);
				 this->chart1->Location = System::Drawing::Point(18, 32);
				 this->chart1->Name = L"chart1";
				 this->chart1->Size = System::Drawing::Size(182, 59);
				 this->chart1->TabIndex = 2;
				 this->chart1->Text = L"chart1";
				 // 
				 // trackBar2
				 // 
				 this->trackBar2->Location = System::Drawing::Point(0, 120);
				 this->trackBar2->Maximum = 50;
				 this->trackBar2->Name = L"trackBar2";
				 this->trackBar2->Size = System::Drawing::Size(208, 45);
				 this->trackBar2->TabIndex = 1;
				 this->trackBar2->Value = 10;
				 this->trackBar2->Scroll += gcnew System::EventHandler(this, &MainForm::trackBar2_Scroll);
				 // 
				 // trackBar1
				 // 
				 this->trackBar1->LargeChange = 10;
				 this->trackBar1->Location = System::Drawing::Point(0, 97);
				 this->trackBar1->Maximum = 200;
				 this->trackBar1->Name = L"trackBar1";
				 this->trackBar1->Size = System::Drawing::Size(208, 45);
				 this->trackBar1->TabIndex = 0;
				 this->trackBar1->Value = 110;
				 this->trackBar1->Scroll += gcnew System::EventHandler(this, &MainForm::trackBar1_Scroll);
				 // 
				 // timer1
				 // 
				 this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(37, 69);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(29, 12);
				 this->label1->TabIndex = 5;
				 this->label1->Text = L"FPS:";
				 this->label1->Visible = false;
				 // 
				 // labelFPS
				 // 
				 this->labelFPS->AutoSize = true;
				 this->labelFPS->Location = System::Drawing::Point(73, 69);
				 this->labelFPS->Name = L"labelFPS";
				 this->labelFPS->Size = System::Drawing::Size(11, 12);
				 this->labelFPS->TabIndex = 6;
				 this->labelFPS->Text = L"0";
				 this->labelFPS->Visible = false;
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(992, 718);
				 this->Controls->Add(this->labelFPS);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->groupBoxGradation);
				 this->Controls->Add(this->toolStrip1);
				 this->Controls->Add(this->statusStrip1);
				 this->Controls->Add(this->menuStrip1);
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"MainForm";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"            ";
				 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
				 this->ClientSizeChanged += gcnew System::EventHandler(this, &MainForm::MainForm_ClientSizeChanged);
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->groupBoxGradation->ResumeLayout(false);
				 this->groupBoxGradation->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 OCTProgram::FormConfigration1^ fmCfg = gcnew OCTProgram::FormConfigration1();
				 fmCfg->ShowDialog();
				 if (fmCfg->IsConfSaved()){
					 cout<<"Create new config file: "
						 <<(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fmCfg->GetFileName())
						 <<endl;
					 OCTProgram::LoadForm^ fmLd = gcnew OCTProgram::LoadForm(alazar, fmCfg->GetFileName());
					 fmLd->ShowDialog();
					 int n = 0;
					 int m = 0;
					 alazar->GetImageSize(&n, &m);
					 adv->SetSignal(1.0,0.0,m);
					 cgl->PrepareResources(n, m);
				 }
			 }
	private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 OCTProgram::LoadForm^ fmLd = gcnew OCTProgram::LoadForm(alazar);
				 fmLd->ShowDialog();
				 int n = 0;
				 int m = 0;
				 alazar->GetImageSize(&n, &m);
				 adv->SetSignal(1.0,0.0,m);
				 cgl->PrepareResources(n, m);
			 }
	private: System::Void MainForm_ClientSizeChanged(System::Object^  sender, System::EventArgs^  e) {
				 int width = this->ClientSize.Width;
				 int height = this->ClientSize.Height;
				 cgl->SetViewPort(0, 0, width, height);
				 this->groupBoxGradation->Location = System::Drawing::Point(width - 240, height - 260);
			 }
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->chart1->Series->Clear();
#ifdef __DEBUG__
				 this->labelFPS->Visible = true;
				 this->label1->Visible = true;
#endif
				 this->timer1->Enabled = true;
				 this->groupBoxGradation->Location = System::Drawing::Point(
					 this->ClientSize.Width - 240, this->ClientSize.Height - 260);
				 cout<<"OCT Processing Program. V1.0. Copyright @ Huan_OTDM3105."<<endl
					 <<"Initializing...OK"<<endl;
			 }
	private: System::Void StartAcqBotton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->SetColor();
				 WaitForSingleObject(_HMutex, INFINITE);
				 SetEvent(ap->begin_acquisition);
				 ReleaseMutex(_HMutex);
				 this->菜单ToolStripMenuItem->Enabled = false;
				 this->StartAcqBotton->Enabled = false;
			 }
	private: System::Void StopAcqBotton_Click(System::Object^  sender, System::EventArgs^  e) {
				 WaitForSingleObject(_HMutex, INFINITE);
				 ResetEvent(ap->begin_acquisition);
				 ReleaseMutex(_HMutex);

				 while (WaitForSingleObject(ap->acquisition_running, 0) == WAIT_OBJECT_0){
					 //wait for thread to stop acquisition
					 Sleep(20);
					 continue;
				 } 
				 RefreshHist();
				 this->菜单ToolStripMenuItem->Enabled = true;
				 this->StartAcqBotton->Enabled = true;
			 }
	private: System::Void toolStripCapScr_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (!cgl->CaptureScreen(save_count))
				 {
					 MessageBox::Show(L"Capture Screen Failure!");
					 return;
				 }
				 save_count++;
			 }
	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 this->SetColor();
			 }
	private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 this->SetColor();
			 }
	private: System::Void gradationToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (this->gradationToolStripMenuItem->Checked){
					 this->groupBoxGradation->Visible = true;
				 }
				 else{
					 this->groupBoxGradation->Visible = false;
				 }
			 }
	private:void RefreshHist(){
				int hst[256];
				bool tm1stat = this->timer1->Enabled;
				this->timer1->Enabled = false;
				cgl->CalHistogram(hst);
				this->chart1->Series->Clear();
				System::Windows::Forms::DataVisualization::Charting::Series^ series =
					gcnew System::Windows::Forms::DataVisualization::Charting::Series();
				this->chart1->Series->Add(series);
				for (int i = 0; i < 255; i++){
					series->Points->AddXY(i, hst[i]);
				}
				this->timer1->Enabled = tm1stat;
			}
	private:void SetColor(){
				double i1=static_cast<double>(trackBar1->Value)/10-5;
				double i2=static_cast<double>(trackBar2->Value)/10+0.1;
				cgl->SetColorLevels(i1,i2);
				this->label2->Text=System::Convert::ToString(i1);
				this->label3->Text=System::Convert::ToString(i2);
			}
	private: System::Void SaveDataButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 cgl->CaptureScreen(save_count++);
				 //adv->StartWaveOut();
				 //MessageBox::Show(L"This botton is not used now!!");
				 //WaitForSingleObject(_HMutex, INFINITE);
				 //alazar->acqMode = 1;
				 //ReleaseMutex(_HMutex);
			 }
	private: System::Void StopSaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //adv->StopWaveOut();
				 MessageBox::Show(L"This botton is not used now!!");
				 //WaitForSingleObject(_HMutex, INFINITE);
				 //alazar->acqMode = 0;
				 //ReleaseMutex(_HMutex);
			 }
	private: System::Void CalibButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show(L"This botton is not used now!!");
			 }
	private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show(L"This is a about form!", L"About");
			 }
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 //render screen by timer1 in mainform
				 labelFPS->Text = System::Convert::ToString(cgl->GetFPS());
				 cgl->RenderScene();
			 }
	};
}
