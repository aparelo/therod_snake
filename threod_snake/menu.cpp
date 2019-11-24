#include "menu.h"
#include "field.h"

menu::menu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(start_game()));
}

menu::~menu()
{
}

