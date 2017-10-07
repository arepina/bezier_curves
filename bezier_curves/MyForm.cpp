#include "MyForm.h"
#include <Windows.h>
using namespace bezier_curves;
using namespace std;
#include <cmath>

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
	is_arbitrary = false;
	is_third = true;
	is_closed = false;
	cleanCanvas();
}

#pragma region Click events
System::Void bezier_curves::MyForm::canvas_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	for (int i = 0; i < dots->Count; i++)//try to understand whether the dot is a moving one
	{
		if (abs(dots[i]->getPoint()->X - e->X) <= 5 && abs(dots[i]->getPoint()->Y - e->Y) <= 5)
			moving_index = i;
	}
	if (moving_index == -1) {//not moving
		if (dots->Count % 3 == 0 && dots->Count >= 3)//connecting point
		{
			GPoint^ p = gcnew GPoint(e->X, e->Y, Color::Red, PointType::Connecting);
			dots->Add(p);
			im->FillRectangle(gcnew SolidBrush(Color::Red), e->X - 3, e->Y - 3, 6, 6);
		}
		else if (dots->Count % 3 == 1 && dots->Count >= 4)//moving point
		{
			moving_index = dots->Count;
			PointF^ point = gcnew PointF(e->X, e->Y);
			int x = lie_on_line(point);
			if (x != -1)//change the coordinates only if the dot lie on the line
			{
				GPoint^ p = gcnew GPoint(x, e->Y, Color::Yellow, PointType::Moving);
				dots->Add(p);
				im->FillRectangle(gcnew SolidBrush(Color::Yellow), e->X - 3, e->Y - 3, 6, 6);
			}
			moving_index = -1;
		}
		else {//usual point
			GPoint^ p = gcnew GPoint(e->X, e->Y, Color::Black, PointType::Usual);
			dots->Add(p);
			im->FillRectangle(gcnew SolidBrush(Color::Black), e->X - 3, e->Y - 3, 6, 6);
		}
		if (dots->Count >= 2)//draw the linking lines
		{
			for (int i = 1; i < dots->Count; i++)
			{
				im->DrawLine(gcnew Pen(Color::Black), *dots[i]->getPoint(), *dots[i - 1]->getPoint());
			}
		}
		if (dots->Count % 3 == 1 && dots->Count > 1)//redraw only having enough points
		{
			redraw();
			moving_index = dots->Count;
			draw_moving_line();
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
	if (moving_index != -1 && moving_index < dots->Count)
	{
		if (dots[moving_index]->getType() == PointType::Moving) {
			draw_moving_line();
			PointF^ point = dots[moving_index]->getPoint();
			int x = lie_on_line(point);
			if (x != -1)// change the coordinates only if the dot lie on the line
				dots[moving_index]->setPoint(x, e->Y);
		}
		else
			dots[moving_index]->setPoint(e->X, e->Y);
			//todo MOVE OTHER DOTS
		redraw();
	}
}

#pragma endregion Click events

#pragma region Menu
System::Void bezier_curves::MyForm::cleanToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	dots->Clear();
	is_closed = false;
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
		is_closed = true;
	else
		MessageBox::Show("Слишком мало точек", "Упс...");
	redraw();
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
	array<PointF>^ arr = gcnew array<PointF>(dots->Count);
	for (int i = 0; i < dots->Count; i++)
	{
		arr[i] = *dots[i]->getPoint();
		im->FillRectangle(gcnew SolidBrush(dots[i]->getColor()), arr[i].X - 3.0f, arr[i].Y - 3.0f, 6.0f, 6.0f);
	}
	if (dots->Count % 3 == 1 && dots->Count >= 4) {
		Bezier^ b = gcnew Bezier(*dots[dots->Count - 1]->getPoint(), dots->Count, dots);
		is_arbitrary ? b->draw_arbitrary_order(im) : b->draw_third_order(im);
	}
	if (is_closed)
		end_up_line();
	canvas->Refresh();
}

int bezier_curves::MyForm::lie_on_line(PointF^ point)
{
	PointF^ before = dots[moving_index - 1]->getPoint();
	PointF^ before_before = dots[moving_index - 2]->getPoint();
	float down = (before_before->Y - before->Y);
	float up = (point->Y - before_before->Y) * (before_before->X - before->X) + before_before->X*(before_before->Y - before->Y);
	int intersect_x = up / down;
	if (abs(intersect_x - point->X) <= 5)
		return intersect_x;
	else return -1;
}

System::Void bezier_curves::MyForm::draw_moving_line()
{
	if (dots->Count >= 4) {
		PointF^ last = dots[moving_index - 1]->getPoint();
		PointF^ before_last = dots[moving_index - 2]->getPoint();
		int new_x = 2 * last->X - before_last->X;
		int new_y = 2 * last->Y - before_last->Y;
		im->DrawLine(gcnew Pen(Color::Blue), *before_last, Point(new_x, new_y));
		canvas->Refresh();
	}
}

System::Void bezier_curves::MyForm::end_up_line()
{
	PointF^ first = dots[dots->Count - 1]->getPoint();
	PointF^ last = dots[0]->getPoint();
	PointF^ before_first = dots[dots->Count - 2]->getPoint();
	PointF^ before_last = dots[1]->getPoint();
	PointF^ second = gcnew PointF(2 * first->X - before_first->X, 2 * first->Y - before_first->Y);
	PointF^ third = gcnew PointF(2 * last->X - before_last->X, 2 * last->Y - before_last->Y);
	array<PointF>^ arr = gcnew array<PointF>(4);
	arr[0] = *first;
	arr[1] = *second;
	arr[2] = *third;
	arr[3] = *last;
	im->DrawBeziers(gcnew Pen(Color::Black, 2.0f), arr);
}

#pragma endregion Drawing



