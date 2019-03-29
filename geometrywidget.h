#ifndef GEOMETRYWIDGET_H
#define GEOMETRYWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QRegularExpression>

#include "geometry.h"

class GeometryWidget;
namespace Ui {
class GeometryWidget;
}



class GeometryWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString geometry READ getGeometry WRITE set NOTIFY editingFinished USER true)

public:
    explicit GeometryWidget(QWidget *parent = nullptr);
    ~GeometryWidget() override;

    bool set(const QString& geomStr, Geometry::Format format = Geometry::FormatUnknown); //{ return set(geomStr.toStdString().c_str(), format); }
    bool setDefault() { return set(""); }
    bool setFormat(int i) { return setFormat(static_cast<Geometry::Format>(i)); }
    bool setFormat(Geometry::Format format);
    bool setFormat(QString formatStr) { return setFormat(Geometry::formatId(formatStr)); }
    Geometry::Format getFormat() const;
    QString getFormatStr() { return Geometry::formatName(getFormat()); }
    QString getGeometry() const;

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
signals:
    void editingFinished();

};

#endif // GEOMETRYWIDGET_H
