#include "main.h"
#include <cmath>
#include "rc.h"

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, num);
	return true;
}

bool NumDialog::OnOK(){
	try {
		num = GetInt(IDC_EDIT1);
		if (num <= 0 || num > 10000)
			return false;
	}
	catch (XCtrl&) {
		return false;
	}
	return true;
}
void MainWindow::NewColor() {
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.lpCustColors = custCols;
	cc.rgbResult = myCol;
	if (ChooseColor(&cc) == IDOK) {
		myCol = cc.rgbResult;
		InvalidateRect(*this, NULL, true);
	}
}
void MainWindow::NewNumber() {
	NumDialog nd(brojKrugova);
	
	if (nd.DoModal(0, *this) == IDOK) {
		brojKrugova = nd.getNum();
		InvalidateRect(*this, NULL, true);
	}
}
void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);	
	int r = rect.bottom / 4;
	HBRUSH brush = CreateSolidBrush(myCol);
	HGDIOBJ holdBrush = SelectObject(hdc, brush);
	SelectPen(hdc, GetStockObject(NULL_PEN));
	SetROP2(hdc, R2_NOTXORPEN);
	for (int i = 0; i < brojKrugova; ++i) {
		double a = 2 * 3.14*i / brojKrugova;
		double x = rect.right/2 + r * cos(a);
		double y = rect.bottom/2 + r * sin(a);
		Ellipse(hdc, x + r, y + r, x - r, y - r);
	}
	DeleteObject(SelectObject(hdc, holdBrush));
}

void MainWindow::OnCommand(int id){
	switch(id){
	case ID_COLOR: 
		NewColor();	
		break;
	case ID_NUMBER: 
		NewNumber();	
		break;
	case ID_EXIT: 
		DestroyWindow(*this); 
		break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

