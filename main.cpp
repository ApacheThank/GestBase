#include <QApplication>
#include "mainwindow.h"
#include "dialogconnect.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextCodec>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel label;
        //on donne l'image au label
        label.setPixmap(QPixmap("home/akhasanov/CorGestBase/sql.png"));
        label.show();


    QTranslator qtTranslator;

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    QString nomFichier="CorGestBase_"+QLocale::system().name()+".qm";
    qDebug()<<nomFichier;
    QString baseName;

    //defining paths to translations
    #ifdef Q_OS_LINUX
     baseName="/usr/share/applications/CorGestBase/translations/";
    #endif
    #ifdef Q_OS_MACOS
    baseName=QApplication::applicationDirPath()+QLatin1String("/../Resources/translations/"); // path defaults to app dir.
    #endif
    #ifdef Q_OS_DARWIN
    baseName=QApplication::applicationDirPath()+QLatin1String("/akhasanov/CorGestBase/"); // path defaults to app dir.
    #endif
    #ifdef Q_OS_WIN
    baseName=QApplication::applicationDirPath();
    #endif

    myappTranslator.load(baseName+nomFichier);
    a.installTranslator(&myappTranslator);
    qDebug()<<QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    DialogConnect dialogConnect;
    while(dialogConnect.exec()==QDialog::Accepted)
    {

    QString id=dialogConnect.getId();
    QString mdp=dialogConnect.getMdp();

    QSqlDatabase dbConnect=QSqlDatabase::addDatabase("QMYSQL");
    //grant all privileges on dbGestBase.* to akhasanov@'%' identified by 'jamas003';
    dbConnect.setHostName("localhost");
    dbConnect.setUserName(id);
    dbConnect.setPassword(mdp);

    if(dbConnect.open())
    {

        MainWindow w;
        w.show();
        return a.exec();
    }
    else
    {
        dialogConnect.setMessage();
    }
    }


}
