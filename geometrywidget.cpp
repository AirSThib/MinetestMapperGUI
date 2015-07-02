#include "geometrywidget.h"
#include "ui_geometrywidget.h"


QMap<Geometry::Format, QString> Geometry::geometryIdNameMap;
QMap<QString, Geometry::Format> Geometry::geometryNameIdMap;

bool Geometry::set(const char *s)
{
    char sign[2];
    if (4 == sscanf_s(s," %d , %d : %d , %d", corner[0]+0, corner[0]+1, corner[1]+0, corner[1]+1)) {
        adjustCorners();
        // Order is important here!
        computeDimensions();
        computeCenter();

        //GeometryWidget::setFormat(Corners);
        //todo select correct dropdown entry in widget
    }
    else if (4 == sscanf_s(s," %d , %d : %d x %d", center+0, center+1, dimension+0, dimension+1)) {
        computeCorner0();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }

        //GeometryWidget::setFormat(CornerDimensions);
        //todo select correct dropdown entry in widget
    }
    else if (4 == sscanf_s(s," %d , %d %c %d %c %d", corner[0]+0, corner[0]+1, sign+0, dimension+0, sign+1, dimension+1)) {
        for (int i = 0; i < 2; i++)
            if (sign[i] == '-') dimension[i] = -dimension[i];
        computeCenter();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        //GeometryWidget::setFormat(CornerDimensions);
        //todo select correct dropdown entry in widget
    }
    else if (4 == sscanf_s(s," %d x %d %c %d %c %d", dimension+0, dimension+1, sign+0, corner[0]+0, sign+1, corner[0]+1)) {
        for (int i = 0; i < 2; i++)
            if (sign[i] == '-') corner[0][i] = -corner[0][i];
        computeCenter();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        //GeometryWidget::setFormat(CornerDimensions);
        //todo select correct dropdown entry in widget
    }
    else if (2 == sscanf_s(s," %d x %d", dimension+0, dimension+1)) {
        center[0] = 0;
        center[1] = 0;
        computeCorner0();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        //GeometryWidget::setFormat(CenterDimensions);
        //todo select correct dropdown entry in widget
    }
    else {
        //GeometryWidget::setFormat(FormatNone);
        //todo
        return false;

    }
    return true;
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
    #define BUFSIZE 1024
    char buffer[BUFSIZE];
    buffer[0] = '\0';
    int n = -1;
    switch (format) {
        case CenterDimensions:
            n = _snprintf_s(buffer, BUFSIZE, "%d,%d:%dx%d", center[0], center[1], dimension[0], dimension[1]);
            //search alternative for snptintf
            break;
        case CornerDimensions:
            n = _snprintf_s(buffer, BUFSIZE, "%d,%d+%d+%d", corner[0][0], corner[0][1], dimension[0], dimension[1]);
            //search alternative for snptintf
            break;
        case Corners:
        default:
            n = _snprintf_s(buffer, BUFSIZE, "%d,%d:%d,%d", corner[0][0], corner[0][1], corner[1][0], corner[1][1]);
            //search alternative for snptintf
            break;
    }
    if (n > 0 && n < BUFSIZE)
        return QString(buffer);
    else
        return QString();
    #undef BUFSIZE
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

template<class Q, class V>
static void setQWidgetValue(Q *object, V value)
{
    object->blockSignals(true);
    object->setValue(value);
    object->blockSignals(false);
}


GeometryWidget::GeometryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeometryWidget)
{
    ui->setupUi(this);
    m_ui_stack = ui->geometryStackedWidget;
    m_ui_CD_center[0] = ui->geometry_CD_CenterX;
    m_ui_CD_center[1] = ui->geometry_CD_CenterY;
    m_ui_CD_dimension[0] = ui->geometry_CD_DimensionX;
    m_ui_CD_dimension[1] = ui->geometry_CD_DimensionY;
    m_ui_C0D_corner[0] = ui->geometry_C0D_CornerX;
    m_ui_C0D_corner[1] = ui->geometry_C0D_CornerY;
    m_ui_C0D_dimension[0] = ui->geometry_C0D_DimensionX;
    m_ui_C0D_dimension[1] = ui->geometry_C0D_DimensionY;
    m_ui_C01_corner[0][0] = ui->geometry_C01_Corner1X;
    m_ui_C01_corner[0][1] = ui->geometry_C01_Corner1Y;
    m_ui_C01_corner[1][0] = ui->geometry_C01_Corner2X;
    m_ui_C01_corner[1][1] = ui->geometry_C01_Corner2Y;
}

GeometryWidget::~GeometryWidget()
{
    delete ui;
}

void GeometryWidget::set(const QString gstr)
{
    Geometry g;
    if (gstr=="") {
        g.setMax();
    }
    else if (!g.set(gstr)) {
        QMessageBox::warning(this, tr("Failure Loading Settings"),
                             tr("WARNING: Failed to parse the geometry string<br>"
                                "geometry string: <i>%1</i>").arg(gstr));
        g.setMax();
    }
    for (int i=0; i<2; i++) {
        setQWidgetValue(m_ui_CD_center[i], g.center[i]);
        setQWidgetValue(m_ui_CD_dimension[i], g.dimension[i]);
        setQWidgetValue(m_ui_C0D_corner[i], g.corner[0][i]);
        setQWidgetValue(m_ui_C0D_dimension[i], g.dimension[i]);
        setQWidgetValue(m_ui_C01_corner[0][i], g.corner[0][i]);
        setQWidgetValue(m_ui_C01_corner[1][i], g.corner[1][i]);
    }
}

QString GeometryWidget::getGeometry()
{
    Geometry geometry;
    int format = m_ui_stack->currentIndex();
    switch (format) {
        case Geometry::FormatNone:
        case Geometry::CenterDimensions:
            geometry.setCenterDimensions(
                m_ui_CD_center[0]->value(),
                m_ui_CD_center[1]->value(),
                m_ui_CD_dimension[0]->value(),
                m_ui_CD_dimension[1]->value());
            break;
        case Geometry::CornerDimensions:
            geometry.setCornerDimensions(
                m_ui_C0D_corner[0]->value(),
                m_ui_C0D_corner[1]->value(),
                m_ui_C0D_dimension[0]->value(),
                m_ui_C0D_dimension[1]->value());
            break;
        case Geometry::Corners:
            geometry.setCorners(
                m_ui_C01_corner[0][0]->value(),
                m_ui_C01_corner[0][1]->value(),
                m_ui_C01_corner[1][0]->value(),
                m_ui_C01_corner[1][1]->value());
            break;
        default:
            //exception ?
            break;
    }
    return geometry.getString();
}

void GeometryWidget::setFormat(Geometry::Format format)
{
    if (format < Geometry::FormatNone || format >= Geometry::FormatMax)
        {} //Exception ???
    Geometry::Format prevFormat = static_cast<Geometry::Format>(m_ui_stack->currentIndex());
    if (format != prevFormat) {
        set(getGeometry());
    m_ui_stack->setCurrentIndex(format);
    }
}

Geometry::Format GeometryWidget::getFormat(void)
{
    Geometry::Format format = static_cast<Geometry::Format>(m_ui_stack->currentIndex());
    if (format < 0 || format >= Geometry::FormatMax)
        format = Geometry::FormatUnknown;
    return format;
}

void GeometryWidget::on_geometryFormat_currentIndexChanged(int index)
{
    setFormat(index);
}

void GeometryWidget::on_geometry_CD_CenterX_editingFinished()
{
    int center = ui->geometry_CD_CenterX->value();
    int dimension = ui->geometry_CD_DimensionX->value();
    if (center + dimension/2 > 32767)
        ui->geometry_CD_DimensionX->setValue(65536 - 2 * center);
    else if (center + (dimension - 1)/2 < -32768)
        ui->geometry_CD_DimensionX->setValue(65536 + 2 * (center - 1));
}

void GeometryWidget::on_geometry_CD_CenterY_editingFinished()
{
    int center = ui->geometry_CD_CenterY->value();
    int dimension = ui->geometry_CD_DimensionY->value();
    if (center + dimension/2 > 32767)
        ui->geometry_CD_DimensionY->setValue(65536 - 2 * center);
    else if (center + (dimension - 1)/2 < -32768)
        ui->geometry_CD_DimensionY->setValue(65536 + 2 * (center - 1));
}

void GeometryWidget::on_geometry_CD_DimensionX_editingFinished()
{
    int dimension = ui->geometry_CD_DimensionX->value();
    int center = ui->geometry_CD_CenterX->value();
    if (center + dimension/2 > 32767)
        ui->geometry_CD_DimensionX->setValue(65536 - 2 * center);
    else if (center + (dimension - 1)/2 < -32768)
        ui->geometry_CD_DimensionX->setValue(65536 + 2 * (center - 1));
}

void GeometryWidget::on_geometry_CD_DimensionY_editingFinished()
{
    int dimension = ui->geometry_CD_DimensionY->value();
    int center = ui->geometry_CD_CenterY->value();
    if (center + dimension/2 > 32767)
        ui->geometry_CD_DimensionY->setValue(65536 - 2 * center);
    else if (center + (dimension - 1)/2 < -32768)
        ui->geometry_CD_DimensionY->setValue(65536 + 2 * (center - 1));
}

void GeometryWidget::on_geometry_C0D_CornerX_editingFinished()
{
    int corner = ui->geometry_C0D_CornerX->value();
    int dimension = ui->geometry_C0D_DimensionX->value();
    if (corner + dimension - 1 > 32767)
        ui->geometry_C0D_DimensionX->setValue(32767 + 1 - corner);
    else if (corner + dimension - 1 < -32768)
        ui->geometry_C0D_DimensionX->setValue(-32768 + 1 - corner);
}

void GeometryWidget::on_geometry_C0D_CornerY_editingFinished()
{
    int corner = ui->geometry_C0D_CornerY->value();
    int dimension = ui->geometry_C0D_DimensionY->value();
    if (corner + dimension - 1 > 32767)
        ui->geometry_C0D_DimensionY->setValue(32767 + 1 - corner);
    else if (corner + dimension - 1 < -32768)
        ui->geometry_C0D_DimensionY->setValue(-32768 + 1 - corner);
}

void GeometryWidget::on_geometry_C0D_DimensionX_editingFinished()
{
    int dimension = ui->geometry_C0D_DimensionX->value();
    int corner = ui->geometry_C0D_CornerX->value();
    if (corner + dimension - 1 > 32767)
        ui->geometry_C0D_DimensionX->setValue(32767 + 1 - corner);
    else if (corner + dimension - 1 < -32768)
        ui->geometry_C0D_DimensionX->setValue(-32768 + 1 - corner);
}

void GeometryWidget::on_geometry_C0D_DimensionY_editingFinished()
{
    int dimension = ui->geometry_C0D_DimensionY->value();
    int corner = ui->geometry_C0D_CornerY->value();
    if (corner + dimension - 1 > 32767)
        ui->geometry_C0D_DimensionY->setValue(32767 + 1 - corner);
    else if (corner + dimension - 1 < -32768)
        ui->geometry_C0D_DimensionY->setValue(-32768 + 1 - corner);
}
