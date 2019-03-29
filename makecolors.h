#ifndef MAKECOLORS_H
#define MAKECOLORS_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDirIterator>
#include <QImage>
#include <QDebug>
#include <QMutex>
#include <QColor>
#include <QRgb>
#include <QDateTime>

class MakeColors : public QThread
{
    Q_OBJECT
public:
    explicit MakeColors(const QString &nodesTxt, const QString &colorsTxt, const QStringList &searchPaths, QObject *parent);
    explicit MakeColors();
    ~MakeColors() override;
    void startProcess();
    void setFileNodesTxt(const QString &value);

    void setFileColorsTxt(const QString &value);

    void setTextureSearchDirectorys(const QStringList &value);

    enum LogLevel {
        None,
        Verbose,
        Info,
        Warning,
        Error
    };
    Q_ENUM(LogLevel)

    void setLogLevel(const LogLevel &value);

signals:
    void outputLog(const QString &message, int level);
    void progressChanged(int);
    void maxProgressChanged(int);

public slots:
    void stopProcess();

protected:
    void run() override;
private slots:
    QColor processImage(const QString &path);
    bool parseNodesTxt(const QString &nodesTxt);
    bool searchAndProgressTextures(const QString &path);
private:
    bool abort;
    int numberOfNodes = 0;
    int numberOfColors = 0;
    QString fileNodesTxt;
    QString fileColorsTxt;
    QStringList textureSearchDirectorys;
    QStringList textureFileFilter;
    LogLevel logLevel = Info;

    QHash<QString, QColor> requiredColors;
    QMap<QString, QString> nodeList;
    bool writeColorsTxt(const QString &file);
    void output(const QString &message, LogLevel level = None);
    QMutex mutex;
};

#endif // MAKECOLORS_H
