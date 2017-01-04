#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QMap>
#include <QRegularExpression>
#include <QDebug>

class Geometry
{
public:
    enum Format {
        FormatKeep = -2,        // Special value used when setting geometry: don't change current format.
        FormatUnknown = -1,
        FormatNone = 0,
        CenterDimensions = 1,
        CornerDimensions = 2,
        Corners = 3,
        FormatCustom,
        FormatMax
    };
    static QMap<Geometry::Format, QString> geometryIdNameMap;
    static QMap<QString, Geometry::Format> geometryNameIdMap;

    static const QString &formatName(Geometry::Format id);
    static Geometry::Format formatId(const QString &name);
    struct InitStatics { InitStatics(void); };
    static const InitStatics initStatics;
    friend struct InitStatics;

    int center[2];
    int dimension[2];
    int corner[2][2];

    Geometry(void) { setMax(); }
    Geometry(const char *s) { set(s); }
    Geometry(const QString &s) { set(s); }
    //Geometry(const Geometry &g);

    Geometry::Format set(QString str);
    void setMax(void);
    void setCenterDimensions(int cx, int cy, int dx, int dy);
    void setCornerDimensions(int cx, int cy, int dx, int dy);
    void setCorners(int c0x, int c0y, int c1x, int c1y);
    QString getString(Geometry::Format format = Geometry::FormatNone);
private:
    const QRegularExpression corners = QRegularExpression("(-?\\d*),(-?\\d*):(-?\\d*),(-?\\d*)");
    const QRegularExpression centerDimension = QRegularExpression("(-?\\d*),(-?\\d*):(-?\\d*)x(-?\\d*)");
    const QRegularExpression cornerDimension = QRegularExpression("(-?\\d*)[,:](-?\\d*)[+-](-?\\d*)[+-](-?\\d*)");
    const QRegularExpression cornerDimensionAlternate = QRegularExpression("(\\d*)x(\\d*)[+]?(-?\\d+)?[+]?(-?\\d+)?");
    bool adjustCorners(void);
    void computeCorner0(void);
    void computeCorner1(void);
    void computeCenter(void);           // Depends dimensions to be correct !
    void computeDimensions(void);

    Format format = FormatNone;
};

#endif // GEOMETRY_H
