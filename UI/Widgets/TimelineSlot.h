#ifndef TIMELINESLOT_H
#define TIMELINESLOT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

class San;
class DatSan;

/**
 * @brief Widget hiển thị 1 slot thời gian trên timeline (30 phút)
 * Hình sân bóng mini với trạng thái: Trống (xanh) / Đã đặt (đỏ)
 */
class TimelineSlot : public QWidget
{
    Q_OBJECT

public:
    enum SlotStatus
    {
        AVAILABLE, // Trống - xanh
        BOOKED,    // Đã đặt - đỏ
        SELECTED   // Đang chọn - vàng
    };

    explicit TimelineSlot(QWidget *parent = nullptr);

    void setTimeSlot(int hour, int minute); // Đặt thời gian (vd: 6, 0 = 6:00)
    void setField(San *field);              // Đặt sân
    void setStatus(SlotStatus status);      // Đặt trạng thái
    void setBooking(DatSan *booking);       // Gắn thông tin đặt sân
    void setSelected(bool selected);        // Chọn/bỏ chọn slot

    int getHour() const { return m_hour; }
    int getMinute() const { return m_minute; }
    San *getField() const { return m_field; }
    SlotStatus getStatus() const { return m_status; }
    DatSan *getBooking() const { return m_booking; }
    bool isSelected() const { return m_selected; }

signals:
    void clicked(TimelineSlot *slot);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void drawFootballField(QPainter &painter, const QRect &rect);

    int m_hour;
    int m_minute;
    San *m_field;
    SlotStatus m_status;
    DatSan *m_booking;
    bool m_selected;
    bool m_hovered;
};

#endif // TIMELINESLOT_H
