/**
 * @file BookingPage.h
 * @brief Booking management page with timeline view
 * @details Page for creating and managing field bookings - Timeline style
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef BOOKINGPAGE_H
#define BOOKINGPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QMap>

// Forward declarations
class HeThongQuanLy;
class TimelineSlot;
class San;
class DatSan;

/**
 * @class BookingPage
 * @brief Field booking management page with timeline
 *
 * Features:
 * - Timeline view (6:00 - 22:00, 32 slots of 30 min each)
 * - Click on slot to create booking
 * - Visual booking status (green=available, red=booked, yellow=selected)
 * - Cancel bookings
 * - Date navigation
 */
class BookingPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookingPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private slots:
    void onSlotClicked(TimelineSlot *slot);
    void onCancelBooking();
    void onDateChanged(const QDate &date);
    void onTodayClicked();
    void loadTimeline();

private:
    HeThongQuanLy *m_heThong;

    // UI Components - Toolbar
    QDateEdit *m_dateFilter;
    QPushButton *m_todayBtn;
    QPushButton *m_cancelBookingBtn;
    QPushButton *m_refreshBtn;

    // UI Components - Timeline
    QScrollArea *m_scrollArea;
    QWidget *m_timelineWidget;
    QGridLayout *m_timelineLayout;
    QLabel *m_selectedDateLabel;

    // Timeline data
    // TimeIndex: 6:00 = 0, 6:30 = 1, 7:00 = 2, ..., 21:30 = 31 (32 slots total)
    QMap<San *, QList<TimelineSlot *>> m_timelineSlots;
    QDate m_selectedDate;
    QList<San *> m_fields;
    QList<TimelineSlot *> m_selectedSlots; // Multi-selection for booking

    void setupUI();
    QWidget *createToolbar();
    void createTimelineView();
    void updateTimelineData();

    bool checkSlotAvailable(San *field, int hour, int minute);
    DatSan *getBookingAtSlot(San *field, int hour, int minute);
    void timeIndexToTime(int index, int &hour, int &minute);
    void updateSelectedDateLabel();
};

#endif // BOOKINGPAGE_H
