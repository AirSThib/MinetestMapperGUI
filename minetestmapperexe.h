#ifndef MINETESTMAPPEREXE_H
#define MINETESTMAPPEREXE_H

#include <QByteArray>
#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QMetaEnum>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QString>

/**
 * @brief The MinetestMapperExe class
 * This is a helper class to manage the minetestmapper executable.
 */
class MinetestMapperExe : public QObject
{
    Q_OBJECT
public:
    explicit MinetestMapperExe(const QString &program, QObject *parent = nullptr);

    enum Tree{
        Unknown,
        Rogier5,
        Minetest
    };
    Q_ENUM(Tree)

    enum State{
        Error,
        Uninitialized,
        InitVersion,
        InitHelp,
        Ready,
        MappingStart, // started with mapping: Scanning world (reading block list)...
        MappingProgress, // processing z-coordinates...
        MappingEnd // Writing image...
    };

    QStringList getSupportedBackends() const;

    bool init();
    bool startMapping(const QStringList &arguments);
    bool isValid() const;

    bool isMinetestMapper() const;

    QString getVersion() const;

    Tree getTree() const;
    QString getTreeString() const;

    void setExecutableFile(const QString &program);
    QString getMinetestMapperExecutableFile() const;

signals:
    void stateChanged(const QString &str);
    /**
     * @brief progressRangeChanged
     * Signal is sent if the range changes. usefull for use with progressbars.
     * @param min
     * @param max
     */
    void progressRangeChanged(int min, int max);
    /**
     * @brief progressChanged
     * Sent, if the Minetestmapper's progress changes.
     * @param value
     */
    void progressChanged(int value);
    /**
     * @brief busyStateChanged
     * Sent, if the minetestmapper switches between busy and ready.
     * @param newState
     */
    void busyStateChanged(bool newState);

    void mappingFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void mappingErrorOccurred(QProcess::ProcessError error);
    void initialisationFinished(bool success);
    void mappingStandardOutput(const QString &str);
    void mappingStandardError(const QString &str);

public slots:

    void cancel() const;
private slots:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void readStandardOutput();
    void readStandardError();
    void errorOccured(QProcess::ProcessError error);
private:
    void finishInitialization(void);
    QProcess *process;
    QString version;
    QString minetestMapperExecutableFile;
    State state = Uninitialized;
    Tree tree = Unknown;
    bool valid = false;
    bool minetestMapper = false;
    QMap<QString, QString> options;
    void run();

    bool initVersion();
    bool initHelp();
};

#endif // MINETESTMAPPEREXE_H
