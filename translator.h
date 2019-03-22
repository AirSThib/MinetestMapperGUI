#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QLibraryInfo>
#include <QLocale>
#include <QString>
#include <QStringList>
#include <QTranslator>

class Translator
{
public:
	explicit Translator(const QLocale &locale = QLocale::system());

	const QString translationsPath = "./translations/";
	const QString systemTranslationPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

	QStringList getTranslations() const;
	QLocale getCurrentLocale() const { return currentLocale; }
	bool setLocale(const QLocale &newLocale);

private:
	void load(const QLocale &locale);

	QLocale currentLocale;
	QTranslator qtTranslator;
	QTranslator appTranslator;
};

#endif // TRANSLATOR_H
