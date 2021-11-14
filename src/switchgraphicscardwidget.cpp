#include "switchgraphicscardwidget.h"

#include <DGuiApplicationHelper>
#include <DStyle>

DWIDGET_USE_NAMESPACE

SwitchGraphicsCardWidget::SwitchGraphicsCardWidget(QWidget *parent)
    : QWidget(parent)
    , m_hover(false)
    , m_pressed(false)
{
    setMouseTracking(true);
    setMinimumSize(PLUGIN_BACKGROUND_MIN_SIZE, PLUGIN_BACKGROUND_MIN_SIZE);

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [=]() {
        update();
    });
}

void SwitchGraphicsCardWidget::getInfo(SwitchGraphicsCardAppletWidget *m_appletWidget)
{
    // 获取 appletwidget 中的信息
    m_cardName = m_appletWidget->getCardName();

    // 刷新图标
    update();
}

void SwitchGraphicsCardWidget::paintEvent(QPaintEvent *)
{
    QPixmap pixmap;
    QString iconName;
    if (m_cardName == "Intel") {
        iconName = Intel_light;
    } else {
        iconName = NVIDIA_light;
    }
    int iconSize = PLUGIN_ICON_MAX_SIZE;

    // 绘制图标背景
    QPainter painter(this);
    if (std::min(width(), height()) > PLUGIN_BACKGROUND_MIN_SIZE) {
        QColor color;
        if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
            color = Qt::black;
            painter.setOpacity(0.5);

            if (m_hover)
                painter.setOpacity(0.6);

            if (m_pressed)
                painter.setOpacity(0.3);
        } else {
            color = Qt::white;
            painter.setOpacity(0.1);

            if (m_hover)
                painter.setOpacity(0.2);

            if (m_pressed)
                painter.setOpacity(0.05);
        }

        painter.setRenderHint(QPainter::Antialiasing, true);

        DStyleHelper dstyle(style());
        const int radius = dstyle.pixelMetric(DStyle::PM_FrameRadius);

        QPainterPath path;

        int minSize = std::min(width(), height());
        QRect rc(0, 0, minSize, minSize);
        rc.moveTo(rect().center() - rc.center());

        path.addRoundedRect(rc, radius, radius);
        painter.fillPath(path, color);
    } else if (DGuiApplicationHelper::instance()->themeType() == DGuiApplicationHelper::LightType) {
        if (m_cardName == "Intel") {
            iconName = Intel_dark;
        } else {
            iconName = NVIDIA_dark;
        }
    }

    pixmap = loadSVG(iconName, QSize(iconSize, iconSize));

    painter.setOpacity(1);
    const QRectF &rf = QRectF(rect());
    const QRectF &rfp = QRectF(pixmap.rect());
    painter.drawPixmap(rf.center() - rfp.center() / devicePixelRatioF(), pixmap);
}

void SwitchGraphicsCardWidget::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    update();

    QWidget::mousePressEvent(event);
}

void SwitchGraphicsCardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    m_hover = false;
    update();

    QWidget::mouseReleaseEvent(event);
}

void SwitchGraphicsCardWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_hover = true;

    QWidget::mouseMoveEvent(event);
}

void SwitchGraphicsCardWidget::leaveEvent(QEvent *event)
{
    m_hover = false;
    m_pressed = false;
    update();

    QWidget::leaveEvent(event);
}

void SwitchGraphicsCardWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

const QPixmap SwitchGraphicsCardWidget::loadSVG(const QString &fileName, const QSize &size) const
{
    const auto ratio = devicePixelRatioF();

    QPixmap pixmap;
    pixmap = QIcon::fromTheme(fileName).pixmap(size * ratio);
    pixmap.setDevicePixelRatio(ratio);

    return pixmap;
}
