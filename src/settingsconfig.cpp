#include "include/settingsconfig.h"
#include <qcoreapplication.h>
#include <QTranslator>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <fstream>

SettingsConfig::SettingsConfig()
{
	Path configFilePath = QCoreApplication::applicationDirPath().toStdString() + "\\config.ini";
	bool newConfig = false;

	if(!std::experimental::filesystem::exists(configFilePath))
	{
		QMessageBox
		(QMessageBox::Information, QTranslator::tr("Configuration file not found"),
		QTranslator::tr("A configuration file was not found. A new one will be created.")).exec();
		
		newConfig = true;
	}

	setConfigFile(configFilePath, newConfig);
}

SettingsConfig::~SettingsConfig()
{

}

void SettingsConfig::setConfigFile(Path filepath, bool newFile)
{
	/*	NOTE: The file is opened just to be created and is immediately closed. Maybe there's a more... correct way of
	*	doing this.
	*/
	std::ofstream file(filepath, std::ios::out | std::ios::app);

	if(!file.is_open())
	{
		QMessageBox			// I'm the formatting master <3.
		(
		QMessageBox::Warning, QTranslator::tr("Could not create the configuration file"),
		QTranslator::tr("The configuration file couldn't be created or opened. Check the permissions and try again.")
		).exec();
	}
	else
	{
		configuration = new QSettings(QString::fromStdString(filepath.string()), QSettings::IniFormat);
		qDebug() << "Configuration file set.";

		if(newFile)
			setLocale();
	}

	file.close();
}

void SettingsConfig::setLocale(QString locale)
{
	configuration->setValue("LOCALE", locale);
}

QString SettingsConfig::getLocale()
{
	return configuration->value("LOCALE", "locale_en").toString();
}