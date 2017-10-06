#include "MyForm.h"
#include <Windows.h>
using namespace bezier_curves;
using namespace std;

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
	is_arbitrary = true;
	is_third = false;
	cleanCanvas();
}

#pragma region Click events
System::Void bezier_curves::MyForm::canvas_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	for (int i = 0; i < dots->Count; i++)
	{
		if (abs(dots[i]->getPoint()->X - e->X) <= 5 && abs(dots[i]->getPoint()->Y - e->Y) <= 5)
			moving_index = i;
	}
	if (moving_index == -1) {//not moving
		im->FillRectangle(gcnew SolidBrush(Color::Black), e->X - 3, e->Y - 3, 6, 6);
		PointType type = dots->Count % 3 == 1 && dots->Count >= 4 ? PointType::Moving : PointType::Usual;
		GPoint^ p = gcnew GPoint(e->X, e->Y, Color::Black, type);
		dots->Add(p);
		if (dots->Count % 3 == 1)
		{
			redraw();
			if (dots->Count >= 4) {
				Point^ last = dots[dots->Count - 1]->getPoint();
				Point^ before_last = dots[dots->Count - 2]->getPoint();
				int new_x, new_y;
				if (last->X < before_last->X)
					new_x = last->X - abs(last->X - before_last->X);
				else
					new_x = before_last->X + abs(last->X - before_last->X);
				if (last->Y < before_last->Y)
					new_y = last->Y - abs(last->Y - before_last->Y);
				else
					new_y = last->Y + abs(last->Y - before_last->Y);
				im->DrawLine(gcnew Pen(Color::Blue), *before_last, Point(new_x, new_y));
			}
		}
	}
	canvas->Refresh();
}

System::Void bezier_curves::MyForm::canvas_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	moving_index = -1;
}

System::Void bezier_curves::MyForm::canvas_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (moving_index != -1)
	{
		/*if(dots[moving_index]->getType() == PointType::Moving)

		else*/
			dots[moving_index]->setPoint(e->X, e->Y);
		redraw();
	}
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

System::Void bezier_curves::MyForm::endToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (dots->Count >= 4)
	{
		Point^ dot_one = gcnew Point(dots[dots->Count - 2]->getPoint()->Y, dots[dots->Count - 2]->getPoint()->X);
		Point^ dot_two = gcnew Point(dots[1]->getPoint()->Y, dots[1]->getPoint()->X);
		array<Point>^ arr = gcnew array<Point>(4);
		arr[0] = *dots[dots->Count - 1]->getPoint();
		arr[1] = *dot_one;
		arr[2] = *dot_two;
		arr[3] = *dots[0]->getPoint();
		im->DrawBeziers(gcnew Pen(Color::Black), arr);
	}
	else
		MessageBox::Show("Слишком мало точек", "Упс...");
}

System::Void bezier_curves::MyForm::arbitraryToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	is_arbitrary = true;
	is_third = false;
}

System::Void bezier_curves::MyForm::thirdToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	is_arbitrary = false;
	is_third = true;
}
#pragma endregion Menu

#pragma region Drawing
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
	if (dots->Count % 3 == 1 && dots->Count >= 4) {
		//im->DrawBeziers(gcnew Pen(Color::Black), arr);
		Bezier^ b = gcnew Bezier(*dots[dots->Count - 1]->getPoint(), dots->Count, dots);
		is_arbitrary ? b->draw_arbitrary_order(im) : b->draw_third_order(im);
	}
	canvas->Refresh();
}

#pragma endregion Drawing



