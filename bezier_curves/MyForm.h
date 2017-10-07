#pragma once
#include "GPoint.h"
#include "Bezier.h"

namespace bezier_curves {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		List<GPoint^>^ dots;
		Bitmap ^bm;
		Graphics ^im;
		int moving_index;
		bool is_arbitrary, is_third, is_closed;
		System::Windows::Forms::PictureBox^  canvas;
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  cleanToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  infoToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  endToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  arbitraryToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  thirdToolStripMenuItem;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->canvas = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->endToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cleanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->arbitraryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thirdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// canvas
			// 
			this->canvas->BackColor = System::Drawing::Color::White;
			this->canvas->Location = System::Drawing::Point(-178, 28);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(1683, 787);
			this->canvas->TabIndex = 0;
			this->canvas->TabStop = false;
			this->canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseDown);
			this->canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseMove);
			this->canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->����ToolStripMenuItem,
					this->cleanToolStripMenuItem, this->infoToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(754, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->endToolStripMenuItem,
					this->arbitraryToolStripMenuItem, this->thirdToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// endToolStripMenuItem
			// 
			this->endToolStripMenuItem->Name = L"endToolStripMenuItem";
			this->endToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->endToolStripMenuItem->Text = L"��������";
			this->endToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::endToolStripMenuItem_Click);
			// 
			// cleanToolStripMenuItem
			// 
			this->cleanToolStripMenuItem->Name = L"cleanToolStripMenuItem";
			this->cleanToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->cleanToolStripMenuItem->Text = L"��������";
			this->cleanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cleanToolStripMenuItem_Click);
			// 
			// infoToolStripMenuItem
			// 
			this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			this->infoToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->infoToolStripMenuItem->Text = L"�������";
			this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::infoToolStripMenuItem_Click);
			// 
			// arbitraryToolStripMenuItem
			// 
			this->arbitraryToolStripMenuItem->Name = L"arbitraryToolStripMenuItem";
			this->arbitraryToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->arbitraryToolStripMenuItem->Text = L"������������� �������";
			this->arbitraryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::arbitraryToolStripMenuItem_Click);
			// 
			// thirdToolStripMenuItem
			// 
			this->thirdToolStripMenuItem->Name = L"thirdToolStripMenuItem";
			this->thirdToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->thirdToolStripMenuItem->Text = L"�������� �������";
			this->thirdToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::thirdToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(754, 362);
			this->Controls->Add(this->canvas);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Repina Anastasia BSE143 Bezier curves";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void cleanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void cleanCanvas();
			 System::Void redraw();
			 int lie_on_line(PointF^ point);
			 System::Void draw_moving_line();
			 System::Void end_up_line();
			 System::Void infoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void canvas_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void canvas_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void canvas_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void endToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void arbitraryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void thirdToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
