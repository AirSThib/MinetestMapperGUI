#include "geometry.h"


const QRegularExpression Geometry::corners = QRegularExpression("(-?\\d*),(-?\\d*):(-?\\d*),(-?\\d*)");
const QRegularExpression Geometry::centerDimension = QRegularExpression("(-?\\d*),(-?\\d*):(-?\\d*)x(-?\\d*)");
const QRegularExpression Geometry::cornerDimension = QRegularExpression("(-?\\d*)[,:](-?\\d*)[+-](-?\\d*)[+-](-?\\d*)");
const QRegularExpression Geometry::cornerDimensionAlternate = QRegularExpression("(\\d*)x(\\d*)[+]?(-?\\d+)?[+]?(-?\\d+)?");

const char *Geometry::formatName(Geometry::Format id)
{
    if (id < Geometry::FormatNone || id >= Geometry::FormatMax)
        id = Geometry::FormatUnknown;
    return QMetaEnum::fromType<Geometry::Format>().key(id);
}

Geometry::Format Geometry::formatId(const QString &name)
{
    return formatId(name.toLatin1().data());
}

Geometry::Format Geometry::formatId(const char *name)
{
    // keyToValue returns -1 for not found, which equals FormatUnknown
    return static_cast<Format>(QMetaEnum::fromType<Geometry::Format>().keyToValue(name));
}

Geometry::Format Geometry::set(const QString &str)
{
    qDebug()<<"Trying to detect format of "<<str;
    QRegularExpressionMatch match;
    if(str.isEmpty()){
        format = FormatNone;
    }
    else if((match =corners.match(str)).hasMatch()) {
        corner[0][0] = match.captured(1).toInt();
        corner[0][1] = match.captured(2).toInt();
        corner[1][0] = match.captured(3).toInt();
        corner[1][1] = match.captured(4).toInt();
        adjustCorners();
        // Order is important here!
        computeDimensions();
        computeCenter();
        format = Geometry::Corners;
    }
    else if((match =centerDimension.match(str)).hasMatch()){
        center[0]    = match.captured(1).toInt();
        center[1]    = match.captured(2).toInt();
        dimension[0] = match.captured(3).toInt();
        dimension[1] = match.captured(4).toInt();
        computeCorner0();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        format = Geometry::CenterDimensions;
    }
    else if((match = cornerDimension.match(str)).hasMatch()){
        corner[0][0] = match.captured(1).toInt();
        corner[0][1] = match.captured(2).toInt();
        dimension[0] = match.captured(3).toInt();
        dimension[1] = match.captured(4).toInt();
        computeCenter();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        format = Geometry::CornerDimensions;
    }
    else if((match = cornerDimensionAlternate.match(str)).hasMatch()){
        if(match.lastCapturedIndex() ==2){
            center[0] = 0;
            center[1] = 0;
            dimension[0] = match.captured(1).toInt();
            dimension[1] = match.captured(2).toInt();
            computeCorner0();
            computeCorner1();
            if (adjustCorners()) {
                // Order is important here!
                computeDimensions();
                computeCenter();
            }
            format = Geometry::CenterDimensions;
        }
        else if(match.lastCapturedIndex() ==4){
            corner[0][0] = match.captured(3).toInt();
            corner[0][1] = match.captured(4).toInt();
            dimension[0] = match.captured(1).toInt();
            dimension[1] = match.captured(2).toInt();
            computeCenter();
            computeCorner1();
            if (adjustCorners()) {
                // Order is important here!
                computeDimensions();
                computeCenter();
            }
            format = Geometry::CornerDimensions;
        }
        else format = Geometry::FormatCustom;
    }
    else {
        qDebug()<<"Warning: Could not parse format of string: "<<str;
        format = Geometry::FormatCustom;
    }
    // Thanks to Qt's meta enum qDebug makes pretty printing of format
    qDebug() << "Format is:" << format;
    return format;

}
void Geometry::setMax()
{
    for (int i=0; i<2; i++) {
        center[i] = 0;
        dimension[i] = 65536;
    }
    computeCorner0();
    computeCorner1();
}

bool Geometry::adjustCorners()
{
    bool adjusted = false;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            if (corner[j][i] < -32768) {
                corner[j][i] = -32768;
                adjusted = true;
            }
            if (corner[j][i] > 32767) {
                corner[j][i] = 32767;
                adjusted = true;
            }
        }
    }
    return adjusted;
}

void Geometry::setCenterDimensions(int cx, int cy, int dx, int dy)
{
    center[0] = cx;
    center[1] = cy;
    dimension[0] = dx;
    dimension[1] = dy;
    computeCorner0();
    computeCorner1();
}

void Geometry::setCornerDimensions(int cx, int cy, int dx, int dy)
{
    corner[0][0] = cx;
    corner[0][1] = cy;
    dimension[0] = dx;
    dimension[1] = dy;
    computeCenter();
    computeCorner1();
}

void Geometry::setCorners(int c0x, int c0y, int c1x, int c1y)
{
    corner[0][0] = c0x;
    corner[0][1] = c0y;
    corner[1][0] = c1x;
    corner[1][1] = c1y;
    computeDimensions();
    computeCenter();
}

QString Geometry::getString(Geometry::Format format)
{
    if(format == FormatKeep)
        format = this->format; // Use the preferred format
    switch (format) {
        case CenterDimensions:
            if(center[0]==0 && center[1] ==0)
                return QString("%1x%2")
                        .arg(dimension[0])
                        .arg(dimension[1]);
            return QString("%1,%2:%3x%4")
                    .arg(center[0])
                    .arg(center[1])
                    .arg(dimension[0])
                    .arg(dimension[1]);
            break;
        case CornerDimensions:
            return QString("%1,%2+%3+%4")
                    .arg(corner[0][0])
                    .arg(corner[0][1])
                    .arg(dimension[0])
                    .arg(dimension[1]);
            break;
        case Corners:
        default:
            return QString("%1,%2:%3,%4")
                    .arg(corner[0][0])
                    .arg(corner[0][1])
                    .arg(corner[1][0])
                    .arg(corner[1][1]);
            break;
    }

}

void Geometry::computeCorner0()
{
    for (int i = 0; i < 2; i++) {
        if (dimension[i] < 0)
            corner[0][i] = center[i] + (-dimension[i]) / 2;
        else
            corner[0][i] = center[i] - dimension[i] / 2;
    }
}

void Geometry::computeCorner1()
{
    for (int i = 0; i < 2; i++) {
        if (dimension[i] < 0)
            corner[1][i] = corner[0][i] + dimension[i] + 1;
        else
            corner[1][i] = corner[0][i] + dimension[i] - 1;
    }
}

void Geometry::computeCenter()
{
    for (int i = 0; i < 2; i++) {
        if (corner[0][i] > corner[1][i])
            center[i] = corner[0][i] - (-dimension[i]) / 2;
        else
            center[i] = corner[0][i] + dimension[i] / 2;
    }
}

void Geometry::computeDimensions()
{
    for (int i = 0; i < 2; i++) {
        if (corner[0][i] > corner[1][i])
            dimension[i] = corner[1][i] - corner[0][i] - 1;
        else
            dimension[i] = corner[1][i] - corner[0][i] + 1;
    }
}
