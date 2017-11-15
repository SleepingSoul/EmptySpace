#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>
#include <QSettings>

class MyApplication : public QApplication
{
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv, const QString &strOrg, const QString &strAppName);
    static MyApplication *theApplication()
    {
        return dynamic_cast <MyApplication *>(qApp);
    }
    QSettings *theSettings() const;

private:
    QSettings *settings;
};

#endif // MYAPPLICATION_H
