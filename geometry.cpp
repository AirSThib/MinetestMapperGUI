#include "geometry.h"


QMap<Geometry::Format, QString> Geometry::geometryIdNameMap;
QMap<QString, Geometry::Format> Geometry::geometryNameIdMap;
const Geometry::InitStatics initStatics;

Geometry::InitStatics::InitStatics()
{
    Geometry::geometryIdNameMap[Geometry::FormatUnknown] = "unknown";
    Geometry::geometryIdNameMap[Geometry::FormatNone] = "none";
    Geometry::geometryIdNameMap[Geometry::CenterDimensions] = "center-dimensions";
    Geometry::geometryIdNameMap[Geometry::CornerDimensions] = "corner-dimensions";
    Geometry::geometryIdNameMap[Geometry::Corners] = "corners";
    Geometry::geometryIdNameMap[Geometry::FormatCustom] = "custom";

    for (int i = Geometry::FormatNone; i < Geometry::FormatMax; i++)
        Geometry::geometryNameIdMap[Geometry::geometryIdNameMap[static_cast<Format>(i)]] = static_cast<Format>(i);

}

const QString &Geometry::formatName(Geometry::Format id)
{
    if (id < Geometry::FormatNone || id >= Geometry::FormatMax)
        id = Geometry::FormatUnknown;
    return geometryIdNameMap[id];
}

Geometry::Format Geometry::formatId(const QString &name)
{
    if (geometryNameIdMap.find(name) == geometryNameIdMap.end())
        return Geometry::FormatUnknown;
    else
        return geometryNameIdMap[name];
}

Geometry::Format Geometry::set(QString str)
{
    qDebug()<<"Trying to detect format of "<<str;
    QRegularExpressionMatch match;
    if(str.isEmpty()){
        qDebug()<<"format is FormatNone";
        return FormatNone;
    }
    else if((match =corners.match(str)).hasMatch()) {
        qDebug()<<"format is Corners";
        corner[0][0] = match.captured(1).toInt();
        corner[0][1] = match.captured(2).toInt();
        corner[1][0] = match.captured(3).toInt();
        corner[1][1] = match.captured(4).toInt();
        adjustCorners();
        // Order is important here!
        computeDimensions();
        computeCenter();
        return Geometry::Corners;
    }
    else if((match =centerDimension.match(str)).hasMatch()){
        qDebug()<<"format is CenterDimensions";
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
        return Geometry::CenterDimensions;
    }
    else if((match = cornerDimension.match(str)).hasMatch()){
        qDebug()<<"format is CornerDimensions";
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
        return Geometry::CornerDimensions;
    }
    else if((match = cornerDimensionAlternate.match(str)).hasMatch()){
        qDebug() << "format is <width>x<height>[<+|-xoffset><+|-yoffset>]";
        if(match.lastCapturedIndex() ==2){
            qDebug() << "format is CenterDimensions with center =0,0";
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
            return Geometry::CenterDimensions;
        }
        else if(match.lastCapturedIndex() ==4){
            qDebug() << "format is CornerDimensions";
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
            return Geometry::CornerDimensions;
        }
        else return Geometry::FormatCustom;
    }
    else {
        qDebug()<<"Warning: Could not parse format of string: "<<str;
        return Geometry::FormatCustom;
    }

}
void Geometry::setMax(void)
{
    for (int i=0; i<2; i++) {
        center[i] = 0;
        dimension[i] = 65536;
    }
    computeCorner0();
    computeCorner1();
}

bool Geometry::adjustCorners(void)
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

void Geometry::computeCorner0(void)
{
    for (int i = 0; i < 2; i++) {
        if (dimension[i] < 0)
                corner[0][i] = center[i] + (-dimension[i]) / 2;
            else
                corner[0][i] = center[i] - dimension[i] / 2;
    }
}

void Geometry::computeCorner1(void)
{
    for (int i = 0; i < 2; i++) {
        if (dimension[i] < 0)
                corner[1][i] = corner[0][i] + dimension[i] + 1;
            else
                corner[1][i] = corner[0][i] + dimension[i] - 1;
    }
}

void Geometry::computeCenter(void)
{
    for (int i = 0; i < 2; i++) {
        if (corner[0][i] > corner[1][i])
                center[i] = corner[0][i] - (-dimension[i]) / 2;
            else
                center[i] = corner[0][i] + dimension[i] / 2;
    }
}

void Geometry::computeDimensions(void)
{
    for (int i = 0; i < 2; i++) {
        if (corner[0][i] > corner[1][i])
                dimension[i] = corner[1][i] - corner[0][i] - 1;
            else
                dimension[i] = corner[1][i] - corner[0][i] + 1;
    }
}
