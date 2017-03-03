#include "makecolors.h"
#include <QMetaEnum>

MakeColors::MakeColors(const QString nodesTxt, const QString colorsTxt, const QStringList searchPaths, QObject *parent)
                 : QThread(parent)
{
    textureFileFilter << "*.png";
    setFileNodesTxt(nodesTxt);
    setFileColorsTxt(colorsTxt);
    setTextureSearchDirectorys(searchPaths);

    abort = false;
}

MakeColors::MakeColors()
{
    textureFileFilter << "*.png";

    abort = false;
}

MakeColors::~MakeColors()
{
    mutex.lock();
    abort = true;
    mutex.unlock();

    wait();
}



QColor MakeColors::processImage(QString path)
{
    //create a new image and load from path
    QImage img(path);
    QColor color;
    //convert to RGB32 format
    img = img.convertToFormat(QImage::Format_ARGB32);
    const int width = img.width();
    const int height = img.height();
    long r = 0;
    long g = 0;
    long b = 0;

    int counter = 0;
    for (int i = 0; i<height; i++)
    {

        //Dont access rowData directly! it depends on platform. always use QRgb()
        const QRgb *rowData = reinterpret_cast<const QRgb *>(img.constScanLine(i));
        for (int j = 0; j < width; j++) {

            QRgb pixelData = rowData[j];
            if (qAlpha(pixelData) < 128)
                continue;
            r += qRed(pixelData);
            g += qGreen(pixelData);
            b += qBlue(pixelData);

            counter++;

        }
    }
    if(counter == 0)
    {
        output("could not generate color of " +path +" too much transparency", WARNING);
        color = QColor();//invalid color
    }
    else{
        color = QColor(r/counter,g/counter,b/counter);
    }

    return color;
}

bool MakeColors::parseNodesTxt(QString nodesTxt)
{
    output("Parsing "+nodesTxt, INFO);
    QFile inputFile(nodesTxt);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {

            QString line = in.readLine();
            if(line.isEmpty() || line.startsWith('#'))
                continue;
            else{
                //qDebug()<< line;
                QStringList lineS = line.split(' ');
                const QString textureName = lineS[1];//get the filename out of the line

                //Insert the texturename and a invalid Color. The color will be set by searchAndProgrssTextures
                requiredColors.insert(textureName,QColor());

                //Insert Nodename and texturename into QMap to be sorted in alphabetical order
                nodeList.insert(lineS[0],lineS[1]);
            }


        }
        inputFile.close();
        numberOfNodes = requiredColors.size();
    }
    else{
        output("Could not open "+nodesTxt+" for reading!", ERROR);
        return false;
    }
    return true;
}

bool MakeColors::searchAndProgressTextures(const QString path)
{
    QDirIterator it(path, textureFileFilter, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        const QString textureFilePath = it.next();
        const QString textureFileName = it.fileName();
        if(requiredColors.contains(textureFileName)){
            output("Processing "+textureFileName, VERBOSE);
            const QColor color = processImage(textureFilePath);


            //inserting over an existing item will override it. We set the color in this place.
            requiredColors.insert(textureFileName, color);
            //numberOfColors++;
            emit progressChanged(++numberOfColors);
        }
        else{
            output("Not required: "+textureFileName, VERBOSE);
        }
    }
    return true;
}

void MakeColors::setLogLevel(const LogLevel &value)
{
    logLevel = value;
}

void MakeColors::setTextureSearchDirectorys(const QStringList &value)
{
    textureSearchDirectorys = value;
}

void MakeColors::setFileColorsTxt(const QString &value)
{
    this->fileColorsTxt = value;
}

void MakeColors::setFileNodesTxt(const QString &value)
{
    fileNodesTxt = value;
}

bool MakeColors::writeColorsTxt(const QString file)
{
    QFile outputFile(file);
    output("Writing colors.txt file to "+file ,INFO);
    if (outputFile.open(QIODevice::WriteOnly| QIODevice::Truncate | QIODevice::Text)) {
        //QTextStream in(&inputFile);
        QMapIterator<QString,QString> mi(nodeList);
        QTextStream out(&outputFile);

        QString lastMod = "";//Used for some nicer formating
        out << "# Autogenerated colors.txt file from MinetestMapperGui"<<endl;
        out << "# Generated at " << QDateTime::currentDateTime().toString() <<endl;
        while (mi.hasNext())
        {
            mi.next();
            const QString fullNodeName = mi.key();
            const QString currentMod = fullNodeName.section(':',0,0,QString::SectionIncludeLeadingSep);

            //write a new paragraph
            if(currentMod != lastMod)
            {
                lastMod = currentMod;
                out<<endl<<"# "<<currentMod<<endl;
            }
            //read the color for texture out of requiredColors QHash
            QColor color = requiredColors.value(mi.value());
            if( color.isValid()){
                out<<fullNodeName<< QString(" %1 %2 %3").arg(color.red(),3).arg(color.green(),3).arg(color.blue(),3) <<endl;
            }
            else{
                output("No color found for " +fullNodeName, WARNING);
            }



        }

        outputFile.close();
    }
    return true;
}

void MakeColors::run(void)
{
    parseNodesTxt(fileNodesTxt);
    emit maxProgressChanged(requiredColors.size());
    emit progressChanged(0);
    output(tr("Found %Ln node(s)","",nodeList.size()), INFO);
    output(tr("Searching and parsing %Ln texture file(s)","",requiredColors.size()), INFO);
    for(int i = 0; i < textureSearchDirectorys.size(); i++)
    {
        //emit stateChanged("search and process textures "+ i +" of "+textureSearchDirectorys.size());
        searchAndProgressTextures(textureSearchDirectorys.at(i));

    }
    writeColorsTxt(fileColorsTxt);
    output("Done! :)",INFO);
}

void MakeColors::startProcess(void)
{
    output("Starting...",VERBOSE);

    // Set this to 0 and -1 makes the progressbar shows busy
    emit maxProgressChanged(0);
    emit progressChanged(-1);
    start();
}


void MakeColors::stopProcess()
{
    mutex.lock();
    abort = true;
    mutex.unlock();
}


void MakeColors::output(QString message, LogLevel level)
{
    if(logLevel <= level){
        emit outputLog(message,level);
    }
}
