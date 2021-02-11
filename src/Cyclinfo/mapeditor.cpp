#include "mapeditor.h"

#include <QtGui>
#include <QWidget>

MapEditor::MapEditor(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle(tr("Éditeur de carte - Cyclinfo"));
	resize(384,256);
	
	QWidget *widgetPrincipal = new QWidget();
	setCentralWidget(widgetPrincipal);
	
	QGridLayout *layoutPrincipal = new QGridLayout();
	widgetPrincipal->setLayout(layoutPrincipal);
	
	
	
	QPushButton *boutonValider = new QPushButton();
	boutonValider->setText(tr("Valider"));
	boutonValider->setIcon(QIcon("Dialog-apply.png"));
	layoutPrincipal->addWidget(boutonValider,1,0);
	
	QPushButton *boutonAnnuler = new QPushButton();
	boutonAnnuler->setText(tr("Annuler"));
	layoutPrincipal->addWidget(boutonAnnuler,1,1);
}

