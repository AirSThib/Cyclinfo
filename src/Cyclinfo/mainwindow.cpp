#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapeditor.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* PARAMÈTRES DE FENÊTRE */

    setWindowTitle("Cyclinfo");
    setWindowIcon(QIcon("Logo.png"));
    resize(640,384);

    /* AUTRES FENETRES */

    mapEditor = new MapEditor();

    /* MENUS */

        /* Menu Fenêtre */

        QMenu *menuFenetre = menuBar()->addMenu(tr("&Fenêtre"));

        QAction *actionNouveauFichier = new QAction(tr("Nouveau fichier"), this);
        actionNouveauFichier->setIcon(QIcon("Gnome-document-new.png"));
        actionNouveauFichier->setShortcut(QKeySequence(tr("Ctrl+N")));
        menuFenetre->addAction(actionNouveauFichier);
        QObject::connect(actionNouveauFichier, SIGNAL(triggered()), this, SLOT(nouveauFichier()));

        QAction *actionOuvrirFichier = new QAction(tr("Ouvrir"), this);
        actionOuvrirFichier->setIcon(QIcon("Gnome-document-open.png"));
        actionOuvrirFichier->setShortcut(QKeySequence(tr("Ctrl+O")));
        menuFenetre->addAction(actionOuvrirFichier);
        QObject::connect(actionOuvrirFichier, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));

        QAction *actionEnregistrerFichier = new QAction(tr("Enregistrer"), this);
        actionEnregistrerFichier->setIcon(QIcon("Gnome-document-save.png"));
        actionEnregistrerFichier->setShortcut(QKeySequence(tr("Ctrl+S")));
        menuFenetre->addAction(actionEnregistrerFichier);
        QObject::connect(actionEnregistrerFichier, SIGNAL(triggered()), this, SLOT(enregistrerFichier()));

        menuFenetre->addSeparator();

        QAction *actionQuitter = new QAction(tr("Quitter"), this);
        actionQuitter->setIcon(QIcon("Gnome-application-exit.png"));
        actionQuitter->setShortcut(QKeySequence(tr("Ctrl+Q")));
        menuFenetre->addAction(actionQuitter);
        QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        /* Menu Édition */

        QMenu *menuEdition = menuBar()->addMenu(tr("&Édition"));

        QAction *actionTracerParcours = new QAction(tr("Tracer un parcours"), this);
        actionTracerParcours->setIcon(QIcon("Map_icon.png"));
        actionTracerParcours->setShortcut(QKeySequence(tr("Ctrl+T")));
        menuEdition->addAction(actionTracerParcours);
        QObject::connect(actionTracerParcours, SIGNAL(triggered()), mapEditor, SLOT(show()));

        QAction *actionAfficherCarte = new QAction(tr("Afficher la carte"), this);
        actionAfficherCarte->setIcon(QIcon("Emblem-earth.png"));
        actionAfficherCarte->setShortcut(QKeySequence(tr("Ctrl+M")));
        menuEdition->addAction(actionAfficherCarte);

    /* BARRES D'OUTILS */

        /* Barre d'outils Fenêtre */

        QToolBar *barreDOutilsFenetre = addToolBar(tr("Fenêtre"));
        barreDOutilsFenetre->addAction(actionNouveauFichier);
        barreDOutilsFenetre->addAction(actionOuvrirFichier);
        barreDOutilsFenetre->addAction(actionEnregistrerFichier);
        barreDOutilsFenetre->addAction(actionQuitter);

        /* Barre d'outils Édition */

        QToolBar *barreDOutilsEdition = addToolBar(tr("Édition"));
        barreDOutilsEdition->addAction(actionTracerParcours);
        barreDOutilsEdition->addAction(actionAfficherCarte);

    /* SDI */

    QWidget *sdi = new QWidget();
    setCentralWidget(sdi);

    QHBoxLayout *sdiLayout = new QHBoxLayout();
    sdi->setLayout(sdiLayout);

    table = new QTableWidget();
    table->setColumnCount(6);
    table->setRowCount(1);

        /* Labels */

        QTableWidgetItem *label0 = new QTableWidgetItem(tr("Icône"));
        table->setHorizontalHeaderItem(0,label0);

        QTableWidgetItem *label1 = new QTableWidgetItem(tr("Nom"));
        table->setHorizontalHeaderItem(1,label1);

        QTableWidgetItem *label2 = new QTableWidgetItem(tr("Latitude"));
        table->setHorizontalHeaderItem(2,label2);

        QTableWidgetItem *label3 = new QTableWidgetItem(tr("Longitude"));
        table->setHorizontalHeaderItem(3,label3);

        QTableWidgetItem *label4 = new QTableWidgetItem(tr("Altitude"));
        table->setHorizontalHeaderItem(4,label4);

        QTableWidgetItem *label5 = new QTableWidgetItem(tr("Distance du départ"));
        table->setHorizontalHeaderItem(5,label5);

        /* Contenu */

    sdiLayout->addWidget(table);

        /* FORMULAIRE D'ÉDITION */

        QVBoxLayout *formulaireVBoxLayout = new QVBoxLayout();

        QGridLayout *layoutVisualisation = new QGridLayout();

        visualisationIcone = new QLabel();
        layoutVisualisation->addWidget(visualisationIcone,0,0);

        visualisationNom = new QLabel();
        layoutVisualisation->addWidget(visualisationNom,0,1,1,2);

        formulaireVBoxLayout->addLayout(layoutVisualisation);

        QFormLayout *formulaireLayout = new QFormLayout();

        comboBoxIcon = new QComboBox();
        comboBoxIcon->addItem(tr("Départ"));
        comboBoxIcon->addItem(tr("Arrivée"));
        comboBoxIcon->addItem(tr("Catégorie de montagne"));
        comboBoxIcon->addItem(tr("Sprint"));
        comboBoxIcon->addItem(tr("Ravitaillement"));
        comboBoxIcon->insertSeparator(5);
        comboBoxIcon->addItem(tr("Aucun"));
        comboBoxIcon->setCurrentIndex(6);

        formulaireLayout->addRow(tr("Icône"), comboBoxIcon);

        spinBoxCategorie = new QSpinBox();
        spinBoxCategorie->setMinimum(0);
        spinBoxCategorie->setMaximum(4);
        spinBoxCategorie->setEnabled(false);
        QObject::connect(comboBoxIcon, SIGNAL(currentIndexChanged(int)), this, SLOT(activerSpinBoxCategorie(int)));
        QObject::connect(comboBoxIcon, SIGNAL(currentIndexChanged(int)), this, SLOT(actualiserVisualisationIcone(int)));
        QObject::connect(spinBoxCategorie, SIGNAL(valueChanged(int)), this, SLOT(actualiserVisualisationIconeSpinBox(int)));

        formulaireLayout->addRow(tr("Numéro de catégorie (0 pour HC)"), spinBoxCategorie);

        lineEditName = new QLineEdit();
        formulaireLayout->addRow(tr("Nom"), lineEditName);
        QObject::connect(lineEditName, SIGNAL(textChanged(QString)), visualisationNom, SLOT(setText(QString)));

        spinBoxLatitude = new QDoubleSpinBox();
        spinBoxLatitude->setMinimum(-90);
        spinBoxLatitude->setMaximum(90);
        spinBoxLatitude->setDecimals(4);
        formulaireLayout->addRow(tr("Latitude (décimal)"), spinBoxLatitude);

        spinBoxLongitude = new QDoubleSpinBox();
        spinBoxLongitude->setMinimum(-180);
        spinBoxLongitude->setMaximum(180);
        spinBoxLongitude->setDecimals(4);
        formulaireLayout->addRow(tr("Longitude (décimal)"), spinBoxLongitude);

        spinBoxAltitude = new QDoubleSpinBox();
        spinBoxAltitude->setMinimum(-418);
        spinBoxAltitude->setMaximum(8848);
        spinBoxLongitude->setDecimals(1);
        formulaireLayout->addRow(tr("Altitude (mètres)"), spinBoxAltitude);

        spinBoxDistanceDepart = new QDoubleSpinBox();
        spinBoxDistanceDepart->setMinimum(0);
        spinBoxDistanceDepart->setDecimals(3);
        spinBoxDistanceDepart->setSingleStep(0.1);
        formulaireLayout->addRow(tr("Distance depuis le départ (kilomètres)"), spinBoxDistanceDepart);

        formulaireVBoxLayout->addLayout(formulaireLayout);

        QPushButton *boutonFormulaireValider = new QPushButton();
        boutonFormulaireValider->setText(tr("Valider"));
        boutonFormulaireValider->setIcon(QIcon("Dialog-apply.png"));
        formulaireVBoxLayout->addWidget(boutonFormulaireValider);

        sdiLayout->addLayout(formulaireVBoxLayout);
}

void MainWindow::nouveauFichier()
{

}

void MainWindow::ouvrirFichier()
{

}

void MainWindow::enregistrerFichier()
{

}

void MainWindow::activerDepart()
{

}

void MainWindow::activerFinish()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
