#include "translator.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QDebug>
#include <QDir>

Translator::Translator(const QLocale &locale)
{
	load(locale);
}

void Translator::load(const QLocale &locale)
{
	qDebug() << "Loading Locale:" << locale;
	if (qtTranslator.load(locale, "qt", "_", systemTranslationPath)) {
		qApp->installTranslator(&qtTranslator);
		qDebug() << "Qt Translator installed from system path" << systemTranslationPath;
	}
	else {
		qtTranslator.load(locale, "qt", "_", translationsPath);
		qApp->installTranslator(&qtTranslator);
		qDebug() << "Qt Translator installed from standard path" << translationsPath;
	}

	if (appTranslator.load(locale, "gui", "_", translationsPath))
		qApp->installTranslator(&appTranslator);
}

QStringList Translator::getTranslations() const
{
	QDir dir(translationsPath);
	QStringList fileNames = dir.entryList(QStringList("qt_*.qm"));
	for (QString &s : fileNames) {
		s.truncate(s.lastIndexOf('.')); // "qt_de"
		s.remove(0, s.indexOf('_') + 1); // "de"
	}
	return fileNames;
}

bool Translator::setLocale(const QLocale & newLocale)
{
	if (currentLocale == newLocale)
		return false;

	QLocale::setDefault(newLocale);
	currentLocale = newLocale;
	load(newLocale);
	return true;
}
