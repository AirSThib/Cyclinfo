#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mapeditor.h"
#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void nouveauFichier();
	void ouvrirFichier();
	void enregistrerFichier();
	void activerSpinBoxCategorie(int id);
	void activerDepart(bool active);
	void activerFinish(bool active);

private:
	Ui::MainWindow *ui;
	MapEditor *mapEditor;
	QTableWidget *table;
	QLabel *visualisationIcone;
	QLabel *visualisationNom;
	QCheckBox *comboBoxIcon;
	QSpinBox *spinBoxCategorie;
	QLineEdit *lineEditName;
	QDoubleSpinBox *spinBoxLatitude;
	QDoubleSpinBox *spinBoxLongitude;
	QDoubleSpinBox *spinBoxAltitude;
	QDoubleSpinBox *spinBoxDistanceDepart;
};

#endif // MAINWINDOW_H
