#include "drawmapfigure.h"

DrawMapFigure::DrawMapFigure(QObject *parent) :
    QObject(parent)
{
    geometry = new Geometry();
}

DrawMapFigure::DrawMapFigure(const QString &str, QObject *parent) :
    QObject(parent)
{
    const QRegularExpression parser = QRegularExpression("^--draw(?<map>map)?(?<type>\\w+) \"(?<params>.+)*\"$");
    QRegularExpressionMatch match = parser.match(str);

    QStringList xy;
    if(match.hasMatch()){
        useImageCoordinates = (match.captured("map")=="map");
        QString params = match.captured("params");

        color.setNamedColor(params.section(' ', 1, 1));
        bool ok;
        figure = getFigure(match.captured("type"));
        if(color.isValid() && ok){
            switch (figure) {
            case Text:
                //parse text and fall through for point
                text = params.section(' ', 2);// everything after the 3rd whitespace
            case Point:
                //parse point and color
                xy = params.section(' ', 0, 0).split(',');
                point.setX(xy[0].toInt());
                point.setY(xy[1].toInt());
                break;
            case Circle:
            case Arrow:
            case Line:
            case Rectangle:
            case Ellipse:
                //parse geometry
                geometry = new Geometry(params.section(' ', 0, 0));
                break;
            default:
                figure = Unknown;
                geometry = new Geometry();
                break;
            }
        }
        else{
            geometry = new Geometry();
            figure = Unknown;
        }


    }
    else{
        geometry = new Geometry();
        figure = Unknown;
    }
}

bool DrawMapFigure::requiresPoint() const
{
    return (figure == Text || figure == Point);
}

bool DrawMapFigure::requiresGeometry() const
{
    return (figure != Text && figure != Point);
}

bool DrawMapFigure::requiresText() const
{
    return (figure == Text);
}

QString DrawMapFigure::getString() const
{
    QStringList splitted = getSplittedString();

    return QString("%1 \"%2\"").arg(splitted.at(0)).arg(splitted.at(1));

}

QStringList DrawMapFigure::getSplittedString() const
{
    QString param;
    QString argument;

    param = "--draw";
    if(useImageCoordinates)
        param += "map";
    param += QString(metaFigure.key(figure)).toLower();

    if(requiresGeometry())
        argument += geometry->getString();
    if(requiresPoint())
        argument += QString("%1,%2").arg(point.x()).arg(point.y());
    argument += ' '+ color.name();
    if(requiresText())
        argument += ' '+text;

    return QStringList()<<param<<argument;
}



bool DrawMapFigure::getUseImageCoordinates() const
{
    return useImageCoordinates;
}

DrawMapFigure::Figure DrawMapFigure::getFigure() const
{
    return figure;
}

DrawMapFigure::Figure DrawMapFigure::getFigure(const QString &str) const
{
    const QString temp = str.left(1).toUpper()+str.mid(1);
    return static_cast<Figure>(metaFigure.keyToValue(temp.toUtf8().constData()));
}

int DrawMapFigure::getFigureIndex() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Figure>();
    return metaEnum.value(figure);
}

QPoint DrawMapFigure::getPoint() const
{
    return point;
}

QString DrawMapFigure::getText() const
{
    return text;
}

QColor DrawMapFigure::getColor() const
{
    return color;
}

QStringList DrawMapFigure::getFigureList()
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Figure>();
    QStringList list;
    for(int i =0; i<metaEnum.keyCount();i++){
        list <<  metaEnum.key(i);
    }
    return list;
}

void DrawMapFigure::setFigure(const Figure &value)
{
    figure = value;
}

void DrawMapFigure::setFigure(int value)
{
    figure = static_cast<Figure>(value);
}

void DrawMapFigure::setText(const QString &value)
{
    text = value;
}

void DrawMapFigure::setColor(const QColor &value)
{
    color = value;
}

Geometry *DrawMapFigure::getGeometry()
{
    return this->geometry;
}

void DrawMapFigure::setGeometry(Geometry *value)
{
    geometry = value;
}

void DrawMapFigure::setUseImageCoordinates(bool value)
{
    useImageCoordinates = value;
}

void DrawMapFigure::setPoint(const QPoint &value)
{
    point = value;
}

void DrawMapFigure::setPoint(const QVariant &value)
{
    point = value.toPoint();
}

void DrawMapFigure::setPoint(const QString &value)
{
    static const QRegularExpression regex("(\\-?\\d+)[ |,](\\-?\\d+)");
    QRegularExpressionMatch match = regex.match(value);
    if(match.hasMatch()){
        point = QPoint(match.captured(1).toInt(), match.captured(2).toInt());
    }
    else{
        qDebug() <<"Could not match point from String "<<value;
        point = QPoint();
    }
}

QIcon DrawMapFigure::getIcon() const
{
    return getIcon(figure);
}

QIcon DrawMapFigure::getIcon(DrawMapFigure::Figure figure)
{
    const char* a = QMetaEnum::fromType<Figure>().key(figure);
    return QIcon(QString(":/images/draw-%1").arg(a).toLower());
}






