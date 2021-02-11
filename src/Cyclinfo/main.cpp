#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QtXml>
#include <QtGui>
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	QString lang("en");
	
	QDomDocument dom("xml");
	QFile xml_doc("settings.xml");
	if(!(xml_doc.open(QIODevice::ReadOnly)))
	{
		QMessageBox::warning(NULL, "Erreur à l'ouverture du document XML","Le document XML de préférences n'a pas pu être ouvert.");
	}

	if (!(dom.setContent(&xml_doc)))
	{
		xml_doc.close();
		QMessageBox::warning(NULL, "Erreur à l'ouverture du document XML", "Le document XML de préférences n'a pas pu être attribué à l'objet QDomDocument.");
	}

	xml_doc.close();
	
	QDomElement settings = dom.documentElement();
	QDomNode nodeSetting = settings.firstChild();

	while(!nodeSetting.isNull())
	{
	    if(!nodeSetting.toElement().isNull())
	    {
	    	if(nodeSetting.toElement().attribute("name", "?") == "lang")
	    	{
	    		lang = nodeSetting.toElement().attribute("value", "fr");
	    	}
	    }
	}
	
	QTranslator translator;
	translator.load("Cyclinfo_" + lang);
	a.installTranslator(&translator);
	
	MainWindow w;
	w.show();
	
	return a.exec();
}
