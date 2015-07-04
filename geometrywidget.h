#ifndef GEOMETRYWIDGET_H
#define GEOMETRYWIDGET_H

#include <QWidget>
#include <QtWidgets>
class Geometry;
class GeometryWidget;
namespace Ui {
class GeometryWidget;
}

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
    friend class InitStatics;

    int center[2];
    int dimension[2];
    int corner[2][2];

    Geometry(void) { setMax(); }
    Geometry(const char *s) { set(s); }
    Geometry(const QString &s) { set(s); }
    Geometry(const Geometry &g);

    bool set(const char *s);
    bool set(const QString &s) { return set(s.toStdString().c_str()); }
    void setMax(void);
    void setCenterDimensions(int cx, int cy, int dx, int dy);
    void setCornerDimensions(int cx, int cy, int dx, int dy);
    void setCorners(int c0x, int c0y, int c1x, int c1y);
    QString getString(Geometry::Format format = Geometry::FormatNone);
private:
    bool adjustCorners(void);
    void computeCorner0(void);
    void computeCorner1(void);
    void computeCenter(void);           // Depends dimensions to be correct !
    void computeDimensions(void);
};

class GeometryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeometryWidget(QWidget *parent = 0);
    ~GeometryWidget();

    bool set(const char *geomStr, Geometry::Format format = Geometry::FormatUnknown);
    bool set(const QString geomStr, Geometry::Format format = Geometry::FormatUnknown) { return set(geomStr.toStdString().c_str(), format); }
    bool setDefault(void) { return set(""); }
    bool setFormat(int i) { setFormat(static_cast<Geometry::Format>(i)); }
    bool setFormat(Geometry::Format format);
    bool setFormat(QString formatStr) { setFormat(Geometry::formatId(formatStr)); }
    Geometry::Format getFormat(void);
    QString getFormatStr(void) { return Geometry::formatName(getFormat()); }
    QString getGeometry();

private slots:
    void on_geometryFormat_currentIndexChanged(int index);
    void on_geometry_C0D_CornerX_editingFinished();
    void on_geometry_C0D_DimensionX_editingFinished();
    void on_geometry_C0D_DimensionY_editingFinished();
    void on_geometry_C0D_CornerY_editingFinished();
    void on_geometry_CD_CenterX_editingFinished();
    void on_geometry_CD_CenterY_editingFinished();
    void on_geometry_CD_DimensionX_editingFinished();
    void on_geometry_CD_DimensionY_editingFinished();

    void on_geometry_parse_clicked();

private:
    Ui::GeometryWidget *ui;

    QStackedWidget *m_ui_stack;
    QSpinBox *m_ui_CD_center[2];
    QSpinBox *m_ui_CD_dimension[2];
    QSpinBox *m_ui_C0D_corner[2];
    QSpinBox *m_ui_C0D_dimension[2];
    QSpinBox *m_ui_C01_corner[2][2];

};

#endif // GEOMETRYWIDGET_H
