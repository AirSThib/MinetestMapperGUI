#include "geometrywidget.h"
#include "ui_geometrywidget.h"
#include "porting.h"


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

Geometry::Format Geometry::set(const char *s)
{
    char sign[2];
    Geometry::Format result;
    if (4 == sscanf(s," %d , %d : %d , %d", corner[0]+0, corner[0]+1, corner[1]+0, corner[1]+1)) {
        adjustCorners();
        // Order is important here!
        computeDimensions();
        computeCenter();
        result = Corners;
    }
    else if (4 == sscanf(s," %d , %d : %d x %d", center+0, center+1, dimension+0, dimension+1)) {
        computeCorner0();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        result = CenterDimensions;
    }
    else if (6 == sscanf(s," %d , %d %c %d %c %d", corner[0]+0, corner[0]+1, sign+0, dimension+0, sign+1, dimension+1)) {
        for (int i = 0; i < 2; i++)
            if (sign[i] == '-') dimension[i] = -dimension[i];
        computeCenter();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        result = CornerDimensions;
    }
    else if (6 == sscanf(s," %d x %d %c %d %c %d", dimension+0, dimension+1, sign+0, corner[0]+0, sign+1, corner[0]+1)) {
        for (int i = 0; i < 2; i++)
            if (sign[i] == '-') corner[0][i] = -corner[0][i];
        computeCenter();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        result = CornerDimensions;
    }
    else if (2 == sscanf(s," %d x %d", dimension+0, dimension+1)) {
        center[0] = 0;
        center[1] = 0;
        computeCorner0();
        computeCorner1();
        if (adjustCorners()) {
            // Order is important here!
            computeDimensions();
            computeCenter();
        }
        result = CenterDimensions;
    }
    else {
        result = FormatCustom;
    }
    return result;
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
            n = snprintf(buffer, BUFSIZE, "%d,%d:%dx%d", center[0], center[1], dimension[0], dimension[1]);
            break;
        case CornerDimensions:
            n = snprintf(buffer, BUFSIZE, "%d,%d+%d+%d", corner[0][0], corner[0][1], dimension[0], dimension[1]);
            break;
        case Corners:
        default:
            n = snprintf(buffer, BUFSIZE, "%d,%d:%d,%d", corner[0][0], corner[0][1], corner[1][0], corner[1][1]);
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

// Is it possible to parameterize the method ??
template<class Q, class I>
static void setQWidgetCurrentIndex(Q *object, I index)
{
    object->blockSignals(true);
    object->setCurrentIndex(index);
    object->blockSignals(false);
}


GeometryWidget::GeometryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeometryWidget)
{
    ui->setupUi(this);

    // Make sure the following two correspond:
    setQWidgetCurrentIndex(ui->geometryFormat, 0);
    ui->geometryStackedWidget->setCurrentIndex(0);

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

// Return true when parsing succeeded
//        false when not (string was still accepted, mode was set to custom)
bool GeometryWidget::set(const char *geomStr, Geometry::Format requestedFormat)
{
    Geometry geometry;
    Geometry::Format parsedFormat;
    if (!geomStr || !*geomStr) {
        geometry.setMax();
        setQWidgetCurrentIndex(ui->geometryFormat, Geometry::FormatNone);
        ui->geometryStackedWidget->setCurrentIndex(Geometry::FormatNone);
        parsedFormat = Geometry::FormatNone;
    }
    else if (Geometry::FormatCustom == (parsedFormat = geometry.set(geomStr))) {
        // TODO (??): verify if string contains '#' or '.' - if not, the problem is serious...
        if (requestedFormat != Geometry::FormatKeep) {
            ui->geometry_custom->setText(geomStr);
            setQWidgetCurrentIndex(ui->geometryFormat, parsedFormat);
            ui->geometryStackedWidget->setCurrentIndex(parsedFormat);
        }
        return false;
    }
    ui->geometry_custom->setText(geomStr);
    for (int i=0; i<2; i++) {
        setQWidgetValue(m_ui_CD_center[i], geometry.center[i]);
        setQWidgetValue(m_ui_CD_dimension[i], geometry.dimension[i]);
        setQWidgetValue(m_ui_C0D_corner[i], geometry.corner[0][i]);
        setQWidgetValue(m_ui_C0D_dimension[i], geometry.dimension[i]);
        setQWidgetValue(m_ui_C01_corner[0][i], geometry.corner[0][i]);
        setQWidgetValue(m_ui_C01_corner[1][i], geometry.corner[1][i]);
    }
    if (requestedFormat == Geometry::FormatKeep)
        {} // Don't change anything
    if (requestedFormat == Geometry::FormatUnknown) {
        setQWidgetCurrentIndex(ui->geometryFormat, parsedFormat);
        ui->geometryStackedWidget->setCurrentIndex(parsedFormat);
    }
    else {
        setQWidgetCurrentIndex(ui->geometryFormat, requestedFormat);
        ui->geometryStackedWidget->setCurrentIndex(requestedFormat);
    }
    return true;
}

QString GeometryWidget::getGeometry()
{
    Geometry geometry;
    Geometry::Format format = getFormat();
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
        case Geometry::FormatCustom:
            return ui->geometry_custom->text();
        default:
            return "";
            break;
    }
    return geometry.getString(format);
}

bool GeometryWidget::setFormat(Geometry::Format format)
{
    if (format < Geometry::FormatNone || format >= Geometry::FormatMax)
        return false;
    Geometry::Format prevFormat = getFormat();
    if (format != prevFormat)
        // Update all invisible widgets
        return set(getGeometry(), format);
    else
        return true;
}

Geometry::Format GeometryWidget::getFormat(void)
{
    Geometry::Format format = static_cast<Geometry::Format>(ui->geometryStackedWidget->currentIndex());
    // Usage of '0' instead of a symbolic value is intentional. The currentIndex() should never be less than 0.
    if (format < 0 || format >= Geometry::FormatMax)
        format = Geometry::FormatUnknown;
    return format;
}

void GeometryWidget::on_geometryFormat_currentIndexChanged(int index)
{
    if (!setFormat(index)) {
        QMessageBox::warning(this, tr("Invalid or unrecognised geometry"),
                 tr("<h1>WARNING</h1> <h2>Geometry string was not recognised</h2>"
                    "The given geometry is either invalid, or only supported in <i>custom</i> mode."));
    }
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

void GeometryWidget::on_geometry_parse_clicked()
{
    if (!set(ui->geometry_custom->text())) {
        QMessageBox::warning(this, tr("Invalid or unrecognised geometry"),
                 tr("<h1>WARNING</h1> <h2>Geometry string was not recognised</h2>"
                    "The given geometry is either invalid, or only supported in <i>custom</i> mode."));
    }
}
