#pragma once
#include <qsettings.h>
#include <experimental/filesystem>
#include <QString>

using Path = std::experimental::filesystem::path;

class SettingsConfig
{
public:
	SettingsConfig();
	~SettingsConfig();

	void setLocale(QString locale = "locale_en");
	QString getLocale();

private:
	QSettings *configuration;

	void setConfigFile(Path filepath, bool newFile);



};

