#ifndef DRAWMAPFIGURE_H
#define DRAWMAPFIGURE_H

#include <QObject>
#include <QPoint>
#include <QColor>
#include <QMetaEnum>
#include <QIcon>

#include "geometry.h"

class DrawMapFigure : public QObject
{

public:
    enum Figure{
        Unknown,
        Arrow,
        Circle,
        Ellipse,
        Line,
        Point,
        Rectangle,
        Text

    };
    Q_ENUM(Figure)

    explicit DrawMapFigure(QObject *parent = 0);
    /**
     * @brief DrawMapFigure
     * @param str QString to convert to DrawMapFigure
     * @param parent
     */
    explicit DrawMapFigure(const QString &str, QObject *parent = 0);

    explicit DrawMapFigure(QColor color, QObject *parent = 0) :
        color(color), QObject(parent) { }

    explicit DrawMapFigure(QPoint point, QColor color, QObject *parent = 0) :
        point(point), color(color), QObject(parent) {}

    explicit DrawMapFigure(Geometry *geometry, QColor color, QObject *parent = 0) :
        geometry(geometry), color(color), QObject(parent) { }

    //DrawMapFigure(const DrawMapFigure &f) {}
    bool requiresPoint(void) const;
    bool requiresGeometry(void) const;
    bool requiresText(void) const;

    QString getString(void) const;
    QStringList getSplittedString(void) const;
    bool getUseImageCoordinates() const;

    int getFigureIndex() const;

    QPoint getPoint() const;

    QString getText() const;
    /**
     * @brief getColor
     * @return
     */
    QColor getColor() const;

    static QStringList getFigureList();

    void setFigure(const Figure &value);
    void setFigure(int value);

    void setText(const QString &value);

    void setColor(const QColor &value);

    Geometry* getGeometry();
    void setGeometry(Geometry *value);

    void setUseImageCoordinates(bool value);
    void setPoint(const QString &value);
    void setPoint(const QPoint &value);

    QIcon getIcon() const;
    static QIcon getIcon(Figure figure);

    void setPoint(const QVariant &value);

    Figure getFigure() const;
    Figure getFigure(const QString &str) const;

signals:

public slots:

protected:
    bool useImageCoordinates;
    Figure figure = Unknown;
    QPoint point;
    Geometry *geometry;
    QString text;
    QColor color;
    QMetaEnum metaFigure = QMetaEnum::fromType<Figure>();
private:
    Q_OBJECT
    static QStringList figuresList;
};

#endif // DRAWMAPFIGURE_H
