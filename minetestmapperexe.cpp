#include "minetestmapperexe.h"

MinetestMapperExe::MinetestMapperExe(const QString &program, QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    setExecutableFile(program);

    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(errorOccured(QProcess::ProcessError)));
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)),
            this,    SLOT(finished(int,QProcess::ExitStatus)));
    connect(process, SIGNAL(readyReadStandardOutput()),
            this,    SLOT(readStandardOutput()));
    connect(process, SIGNAL(readyReadStandardError()),
            this,    SLOT(readStandardError()));
}
void MinetestMapperExe::setExecutableFile(const QString &program)
{
    if(!program.isEmpty()) {
        state = Uninitialized;
        minetestMapperExecutableFile = program;
        process->setProgram(program);
    } else {
        state = Error;
        valid = false;
        minetestMapper = false;
    }
}

QStringList MinetestMapperExe::getSupportedBackends() const
{
    static const QRegularExpression regexp("\\W+");
    QString backends = options.value("--backend", "<auto>");
    QStringList list = backends.split(regexp, QString::SkipEmptyParts);
    return list;
}

void MinetestMapperExe::run()
{
    switch (state) {
    case Uninitialized:
        state = InitVersion;
        process->setArguments(QStringList("--version"));
        process->start(QIODevice::ReadOnly);
        break;
    case InitVersion:
        state = InitHelp;
        process->setArguments(QStringList("--help"));
        process->start(QIODevice::ReadOnly);
        break;
    case Ready:
        state = MappingStart;
        process->start(QIODevice::ReadOnly);
        break;

    case MappingStart:
    case MappingProgress:
    case MappingEnd:
        qDebug() << "Cant run MinetestMapper: Still running";
        break;
    case Error:
    default:
        qDebug() << "Cant run MinetestMapper: Some Error";
        break;
    }
}

bool MinetestMapperExe::init(){
    if(state == Uninitialized)
    {
        emit busyStateChanged(true);
        emit progressRangeChanged(0, 0);

        state = InitVersion;
        emit stateChanged("Init Version...");
        process->setArguments(QStringList("--version"));
        process->start(QIODevice::ReadOnly);
        return true;
    }
    return false;
}

bool MinetestMapperExe::startMapping(const QStringList &arguments){
    if(state == Ready)
    {
        //state = Mapping;
        emit busyStateChanged(true);
        process->setArguments(arguments);
        run();
        return true;
    }
    return false;
}

void MinetestMapperExe::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug()<< exitCode << exitStatus;
    switch (state) {
    case InitVersion:
        if(initVersion())
        {
            state = InitHelp;
            emit stateChanged("Init Help...");
            process->setArguments(QStringList("--help"));
            process->start(QIODevice::ReadOnly);
        }
        break;
    case InitHelp:
        if(initHelp())
        {
            valid = true;
            minetestMapper = true;
            state = Ready;
            emit stateChanged("Ready");
            emit busyStateChanged(false);
            finishInitialization();
        }
        break;
    case MappingStart:
    case MappingProgress:
    case MappingEnd:
        state = Ready;
        emit mappingFinished(exitCode, exitStatus);
        emit stateChanged("Ready");
        emit busyStateChanged(false);
    default:
        break;
    }
}

bool MinetestMapperExe::initVersion()
{
    QByteArray dataRaw;
    QString data;
    dataRaw = process->readAllStandardError();
    data = QString(dataRaw).trimmed();
    if (data.contains("unrecognized option")) {
        return false;
    }
    dataRaw = process->readAllStandardOutput();
    data = QString(dataRaw).trimmed();
    if (!data.contains("Version-ID:")) {
        return false;
    }
    version = data.replace(QRegularExpression(".*Version-ID: *"),"");
    return true;
}

bool MinetestMapperExe::initHelp()
{
    static const QRegularExpression optionRegex("^(|-[a-zA-Z].*)(--[a-zA-Z0-9][a-zA-Z0-9-_]+)( *(.*[^ \t\r\n]))?[ \t\r\n]*$");
    //QMap<QString, QString> options;

    QByteArray helpTextRaw = process->readAllStandardOutput();
    QStringList helpText = QString(helpTextRaw).trimmed().split("\n");
    for (int i = 0; i < helpText.count(); i++) {
        QString helpLine = helpText[i].trimmed();
        if (helpLine.contains("Color format: '#000000'")) {
            tree = Minetest;
        }
        else if (helpLine.contains("X and Y coordinate formats:")) {
            tree = Rogier5;
        }
        QString option = helpLine;
        option.replace(optionRegex, "\\2");
        if (option[1] != '-' || option.contains(' ')) continue;
        QString arguments = helpLine;
        arguments.replace(optionRegex, "\\4");
        if (arguments == helpLine) arguments = "";
        options[option] = arguments;
    }
    //this->options = options;
    return true;
}
void MinetestMapperExe::readStandardOutput(void)
{
    static const QRegularExpression re("([0-9]{1,3})(\\%)");
    if(state == MappingStart || state == MappingProgress || state == MappingEnd) {
        QByteArray outData = process->readAllStandardOutput();
        QString out = QString(outData).trimmed();
        if(!out.isEmpty()) {
            QRegularExpressionMatch match = re.match(out);
            if(match.hasMatch()){
                if(state == MappingStart)
                {
                    state = MappingProgress;
                    emit progressRangeChanged(0, 100);
                }
                int percent = match.captured(1).toInt(); // percent == number
                emit progressChanged(percent);
            }
            else {
                if(state == MappingProgress)
                {

                    state = MappingEnd;
                    emit progressRangeChanged(0, 0);
                }
            }
            emit stateChanged(out);
            emit mappingStandardOutput(out);
        }
    }
}

void MinetestMapperExe::readStandardError()
{
    if(state == MappingStart || state == MappingProgress || state == MappingEnd) {
        const QByteArray outData = process->readAllStandardError();
        if(outData.length() >1) {
            const QString out = QString(outData).trimmed();
            emit mappingStandardError(out);
        }
    }
}

void MinetestMapperExe::finishInitialization()
{
    emit initialisationFinished(true);
}

QString MinetestMapperExe::getMinetestMapperExecutableFile() const
{
    return minetestMapperExecutableFile;
}

MinetestMapperExe::Tree MinetestMapperExe::getTree() const
{
    return tree;
}

QString MinetestMapperExe::getTreeString() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<MinetestMapperExe::Tree>();
    qDebug() << metaEnum.valueToKey(tree);
    return QString(metaEnum.valueToKey(tree));
}

QString MinetestMapperExe::getVersion() const
{
    return version;
}

bool MinetestMapperExe::isMinetestMapper() const
{
    return minetestMapper;
}

bool MinetestMapperExe::isValid() const
{
    return valid;
}

void MinetestMapperExe::cancel() const
{
    if(process->state() == QProcess::Running)
    {
        process->kill();
    }
}

void MinetestMapperExe::errorOccured(QProcess::ProcessError error)
{
    emit mappingStandardError(process->errorString());
    emit busyStateChanged(false);

    qDebug() <<"Error starting MinetestMapper:"<<error
            <<"Error code: "<<process->error()
           <<"Error string: "<<process->errorString();
    QMessageBox::critical((QWidget*)this->parent(), tr("Minetest Mapper failed"),
             tr("<h1>ERROR</h1> <h2>minetestmapper failed</h2>"
                "Error code: <i>%1</i> <br>"
                "Error Message: <pre>%2</pre><br>")
                          .arg(error)
                          .arg(process->errorString()));
}
