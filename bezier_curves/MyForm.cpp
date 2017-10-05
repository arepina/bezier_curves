#include "MyForm.h"
#include <Windows.h>
using namespace bezier_curves;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	return 0;
}

bezier_curves::MyForm::MyForm(void)
{
	InitializeComponent();
	bm = gcnew Bitmap(canvas->Width, canvas->Height);
	canvas->Image = bm;
	im = Graphics::FromImage(bm);
	dots = gcnew List<GPoint^>();
	moving_index = -1;
	cleanCanvas();
}

#pragma region Click events
System::Void bezier_curves::MyForm::canvas_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	for (int i = 0; i < dots->Count; i++)
	{
		if (abs(dots[i]->getPoint()->X - e->X) <= 3 && abs(dots[i]->getPoint()->Y - e->Y) <= 3)
			moving_index = i;
	}
	if (moving_index == -1) {//not moving
		im->FillRectangle(gcnew SolidBrush(Color::Black), e->X - 3, e->Y - 3, 6, 6);
		GPoint^ p = gcnew GPoint(e->X, e->Y, Color::Black, PointType::Usual);
		dots->Add(p);
		if (dots->Count % 4 == 0) //todo change the check to mod
			redraw();
	}
	canvas->Refresh();
}
System::Void bezier_curves::MyForm::canvas_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	moving_index = -1;
	canvas->Refresh();
}
System::Void bezier_curves::MyForm::canvas_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (moving_index != -1)
	{
		dots[moving_index]->setPoint(e->X, e->Y);
		redraw();
	}
	canvas->Refresh();
}
#pragma endregion Click events

#pragma region Menu
System::Void bezier_curves::MyForm::cleanToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dots->Clear();
	cleanCanvas();
}

System::Void bezier_curves::MyForm::infoToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MessageBox::Show("Программа выполнена студенткой группы БПИ143(1)\n" +
		"Репиной Анастасией Андреевной\n" +
		"Среда разработки: Visual Studio 2015 Entherprise \n" +
		"ОС Windows 10\n" +
		"Дата 05.10.2017\n" +
		"Состав проекта:\n" +
		"Выполнены пункты:\n", "О программе");
}
#pragma endregion Menu

System::Void bezier_curves::MyForm::cleanCanvas()
{
	im->Clear(Color::White);
	canvas->Refresh();
}

System::Void bezier_curves::MyForm::redraw()
{
	cleanCanvas();
	array<Point>^ arr = gcnew array<Point>(dots->Count);
	for (int i = 0; i < dots->Count; i++)
	{
		arr[i] = *dots[i]->getPoint();
		im->FillRectangle(gcnew SolidBrush(Color::Black), arr[i].X - 3, arr[i].Y - 3, 6, 6);		
	}
	if(dots->Count >= 4)//todo change the check to mod
		im->DrawBeziers(gcnew Pen(Color::Black), arr);
}




