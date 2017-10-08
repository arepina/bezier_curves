#pragma once
#include "GPoint.h"
#include "Bezier.h"
#include "BSpline.h"

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
		bool is_arbitrary, is_third_bezier, is_closed_bezier, is_third_bspline, is_closed_bspline;
		System::Windows::Forms::PictureBox^  canvas;
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  cleanToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  infoToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  Ù‡ÈÎToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  endBezierToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  arbitraryToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  thirdBezierToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  bÒÔÎ‡ÈÌToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  endBSplineToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  thirdBSplineToolStripMenuItem;
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
			this->Ù‡ÈÎToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->endBezierToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->arbitraryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thirdBezierToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bÒÔÎ‡ÈÌToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->endBSplineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thirdBSplineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cleanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->Ù‡ÈÎToolStripMenuItem,
					this->bÒÔÎ‡ÈÌToolStripMenuItem, this->cleanToolStripMenuItem, this->infoToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(754, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// Ù‡ÈÎToolStripMenuItem
			// 
			this->Ù‡ÈÎToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->endBezierToolStripMenuItem,
					this->arbitraryToolStripMenuItem, this->thirdBezierToolStripMenuItem
			});
			this->Ù‡ÈÎToolStripMenuItem->Name = L"Ù‡ÈÎToolStripMenuItem";
			this->Ù‡ÈÎToolStripMenuItem->Size = System::Drawing::Size(49, 20);
			this->Ù‡ÈÎToolStripMenuItem->Text = L"¡ÂÁ¸Â";
			// 
			// endBezierToolStripMenuItem
			// 
			this->endBezierToolStripMenuItem->Name = L"endBezierToolStripMenuItem";
			this->endBezierToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->endBezierToolStripMenuItem->Text = L"«‡ÏÍÌÛÚ¸";
			this->endBezierToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::endToolStripMenuItem_Click);
			// 
			// arbitraryToolStripMenuItem
			// 
			this->arbitraryToolStripMenuItem->Name = L"arbitraryToolStripMenuItem";
			this->arbitraryToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->arbitraryToolStripMenuItem->Text = L"œÓËÁ‚ÓÎ¸ÌÓ„Ó ÔÓˇ‰Í‡";
			this->arbitraryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::arbitraryToolStripMenuItem_Click);
			// 
			// thirdBezierToolStripMenuItem
			// 
			this->thirdBezierToolStripMenuItem->Name = L"thirdBezierToolStripMenuItem";
			this->thirdBezierToolStripMenuItem->Size = System::Drawing::Size(209, 22);
			this->thirdBezierToolStripMenuItem->Text = L"“ÂÚ¸Â„Ó ÔÓˇ‰Í‡";
			this->thirdBezierToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::thirdToolStripMenuItem_Click);
			// 
			// bÒÔÎ‡ÈÌToolStripMenuItem
			// 
			this->bÒÔÎ‡ÈÌToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->endBSplineToolStripMenuItem,
					this->thirdBSplineToolStripMenuItem
			});
			this->bÒÔÎ‡ÈÌToolStripMenuItem->Name = L"bÒÔÎ‡ÈÌToolStripMenuItem";
			this->bÒÔÎ‡ÈÌToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->bÒÔÎ‡ÈÌToolStripMenuItem->Text = L"B-ÒÔÎ‡ÈÌ";
			// 
			// endBSplineToolStripMenuItem
			// 
			this->endBSplineToolStripMenuItem->Name = L"endBSplineToolStripMenuItem";
			this->endBSplineToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->endBSplineToolStripMenuItem->Text = L"«‡ÏÍÌÛÚ¸";
			this->endBSplineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::endBSplineToolStripMenuItem_Click);
			// 
			// thirdBSplineToolStripMenuItem
			// 
			this->thirdBSplineToolStripMenuItem->Name = L"thirdBSplineToolStripMenuItem";
			this->thirdBSplineToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->thirdBSplineToolStripMenuItem->Text = L"“ÂÚ¸Â„Ó ÔÓˇ‰Í‡";
			this->thirdBSplineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::thirdBSplineToolStripMenuItem_Click);
			// 
			// cleanToolStripMenuItem
			// 
			this->cleanToolStripMenuItem->Name = L"cleanToolStripMenuItem";
			this->cleanToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->cleanToolStripMenuItem->Text = L"Œ˜ËÒÚËÚ¸";
			this->cleanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cleanToolStripMenuItem_Click);
			// 
			// infoToolStripMenuItem
			// 
			this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			this->infoToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->infoToolStripMenuItem->Text = L"—Ô‡‚Í‡";
			this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::infoToolStripMenuItem_Click);
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
			 System::Void thirdBSplineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void endBSplineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
