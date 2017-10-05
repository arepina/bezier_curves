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
	cleanCanvas();
}

#pragma region Menu
System::Void bezier_curves::MyForm::cleanToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	cleanCanvas();
}

System::Void bezier_curves::MyForm::infoToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MessageBox::Show("��������� ��������� ���������� ������ ���143(1)\n" +
		"������� ���������� ����������\n" +
		"����� ����������: Visual Studio 2015 Entherprise \n" +
		"�� Windows 10\n" +
		"���� 05.10.2017\n" +
		"������ �������:\n" +
		"��������� ������:\n", "� ���������");
}
System::Void bezier_curves::MyForm::canvas_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	/*bool is_found = false;
	for each (GPoint^ p in dots)
	{
		if ((p->getPoint()->X - e->X <= 3) && abs(p->getPoint()->Y - e->Y <= 3))
			is_found = true;
	}
	if (is_found) {
		//start moving
	}
	else {*/
		im->FillRectangle(gcnew SolidBrush(Color::Black), e->X - 3, e->Y - 3, 6, 6);
		GPoint^ p = gcnew GPoint(e->X, e->Y, Color::Black, PointType::Usual);
		dots->Add(p);
	/*}*/
	canvas->Refresh();
}
#pragma endregion Menu

System::Void bezier_curves::MyForm::cleanCanvas()
{
	im->Clear(Color::White);
	dots->Clear();
	canvas->Refresh();
}




