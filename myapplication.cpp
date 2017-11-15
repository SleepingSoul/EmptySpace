#include "myapplication.h"

MyApplication::MyApplication(int &argc, char **argv, const QString &strOrg, const QString &strAppName)
    :QApplication(argc, argv), settings(nullptr)
{
    setOrganizationName(strOrg);
    setApplicationName(strAppName);
    settings = new QSettings(strOrg, strAppName, this);
}

QSettings *MyApplication::theSettings() const
{
    return settings;
}
