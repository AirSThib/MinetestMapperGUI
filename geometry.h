#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QDebug>
#include <QMap>
#include <QMetaEnum>
#include <QObject> // For Q_GADGET
#include <QRegularExpression>

class Geometry
{
    Q_GADGET
public:
    enum Format
    {
        FormatKeep = -2, // Special value used when setting geometry: don't change current format.
        FormatUnknown = -1,
        FormatNone = 0,
        CenterDimensions = 1,
        CornerDimensions = 2,
        Corners = 3,
        FormatCustom,
        FormatMax
    };
    Q_ENUM(Format)
    static const QMetaEnum metaEnumFormat;

    static const char *formatName(Geometry::Format id);
    static Geometry::Format formatId(const QString &name);
    static Geometry::Format formatId(const char *name);

    int center[2];
    int dimension[2];
    int corner[2][2];

    Geometry(void) { setMax(); }
    Geometry(const char *s) { set(s); }
    Geometry(const QString &s) { set(s); }
    // Geometry(const Geometry &g);

    Geometry::Format set(const QString &str);
    void setMax(void);
    void setCenterDimensions(int cx, int cy, int dx, int dy);
    void setCornerDimensions(int cx, int cy, int dx, int dy);
    void setCorners(int c0x, int c0y, int c1x, int c1y);
    QString getString(Geometry::Format format = Geometry::FormatNone);

private:
    static const QRegularExpression corners;
    static const QRegularExpression centerDimension;
    static const QRegularExpression cornerDimension;
    static const QRegularExpression cornerDimensionAlternate;
    bool adjustCorners(void);
    void computeCorner0(void);
    void computeCorner1(void);
    void computeCenter(void); // Depends dimensions to be correct !
    void computeDimensions(void);

    Format format = FormatNone;
};

#endif // GEOMETRY_H
