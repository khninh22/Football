#include "TimelineSlot.h"
#include <QPainter>
#include <QLinearGradient>
#include "../../Core/Models/San.h"
#include "../../Core/Models/DatSan.h"

TimelineSlot::TimelineSlot(QWidget *parent)
    : QWidget(parent), m_hour(0), m_minute(0), m_field(nullptr), m_status(AVAILABLE), m_booking(nullptr), m_selected(false), m_hovered(false)
{
    setFixedSize(40, 80); // Kích thước mỗi slot
    setCursor(Qt::PointingHandCursor);
    setMouseTracking(true);
}

void TimelineSlot::setTimeSlot(int hour, int minute)
{
    m_hour = hour;
    m_minute = minute;
    update();
}

void TimelineSlot::setField(San *field)
{
    m_field = field;
    update();
}

void TimelineSlot::setStatus(SlotStatus status)
{
    m_status = status;
    update();
}

void TimelineSlot::setBooking(DatSan *booking)
{
    m_booking = booking;
    m_status = booking ? BOOKED : AVAILABLE;
    update();
}

void TimelineSlot::setSelected(bool selected)
{
    m_selected = selected;
    update();
}

void TimelineSlot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect().adjusted(2, 2, -2, -2);

    // Màu nền theo trạng thái
    QColor bgColor;
    QColor borderColor;

    if (m_selected)
    {
        bgColor = QColor(255, 193, 7, 200); // Vàng - đang chọn
        borderColor = QColor(255, 152, 0);
    }
    else if (m_status == BOOKED)
    {
        bgColor = QColor(244, 67, 54, 200); // Đỏ - đã đặt
        borderColor = QColor(211, 47, 47);
    }
    else
    {
        bgColor = QColor(76, 175, 80, m_hovered ? 230 : 200); // Xanh - trống
        borderColor = QColor(56, 142, 60);
    }

    // Vẽ nền gradient
    QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
    gradient.setColorAt(0, bgColor.lighter(110));
    gradient.setColorAt(1, bgColor);

    painter.setBrush(gradient);
    painter.setPen(QPen(borderColor, 2));
    painter.drawRoundedRect(rect, 4, 4);

    // Vẽ sân bóng mini
    QRect fieldRect = rect.adjusted(5, 5, -5, -25);
    drawFootballField(painter, fieldRect);

    // Vẽ text trạng thái
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(10);
    painter.setFont(font);

    QString statusText;
    if (m_status == BOOKED)
        statusText = "Đã đặt";
    else
        statusText = "Trống";

    QRect textRect = rect.adjusted(0, rect.height() - 20, 0, 0);
    painter.drawText(textRect, Qt::AlignCenter, statusText);
}

void TimelineSlot::drawFootballField(QPainter &painter, const QRect &rect)
{
    painter.save();

    QPen fieldPen(Qt::white, 1.5);
    painter.setPen(fieldPen);
    painter.setBrush(Qt::NoBrush);

    // Viền sân
    painter.drawRect(rect);

    // Vạch giữa sân
    int midY = rect.center().y();
    painter.drawLine(rect.left(), midY, rect.right(), midY);

    // Vòng tròn giữa
    int centerCircleRadius = rect.width() / 6;
    painter.drawEllipse(rect.center(), centerCircleRadius, centerCircleRadius);

    // Chấm giữa
    painter.setBrush(Qt::white);
    painter.drawEllipse(rect.center(), 1, 1);

    // Khung thành trên
    int goalWidth = rect.width() / 3;
    int goalHeight = rect.height() / 8;
    QRect topGoal(rect.center().x() - goalWidth / 2, rect.top(), goalWidth, goalHeight);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(topGoal);

    // Khung thành dưới
    QRect bottomGoal(rect.center().x() - goalWidth / 2, rect.bottom() - goalHeight, goalWidth, goalHeight);
    painter.drawRect(bottomGoal);

    painter.restore();
}

void TimelineSlot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked(this);
    }
    QWidget::mousePressEvent(event);
}

void TimelineSlot::enterEvent(QEnterEvent *event)
{
    m_hovered = true;
    update();
    QWidget::enterEvent(event);
}

void TimelineSlot::leaveEvent(QEvent *event)
{
    m_hovered = false;
    update();
    QWidget::leaveEvent(event);
}
