#pragma once

#include <QWidget>
#include <menu.h>
#include "ui_menu.h"


class menu : public QWidget
{
	Q_OBJECT

public:
	menu(QWidget *parent = Q_NULLPTR);
	~menu();


private:
	Ui::menu ui;

};
