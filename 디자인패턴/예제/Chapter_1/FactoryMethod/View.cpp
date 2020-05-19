#include "View.h"

MyView::MyView()
{
	cout << "Create MyView" << endl;
}

MyView::~MyView()
{
	cout << "Destroy MyView" << endl;
}

void MyView::Render()
{
	cout << "Render MyView" << endl;
}
