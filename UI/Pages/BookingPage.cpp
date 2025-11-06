#include "BookingPage.h"
#include "../Widgets/TimelineSlot.h"
#include "../Widgets/BookingDialog.h"
#include "../../Core/QuanLy/HeThongQuanLy.h"
#include "../../Core/Models/San.h"
#include "../../Core/Models/DatSan.h"
#include "../../Core/Models/KhachHang.h"
#include "../../Core/Models/KhungGio.h"
#include "../../Core/Models/DichVu.h"
#include "../../Core/Models/DichVuDat.h"
#include "../../Core/CauTrucDuLieu/NgayGio.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>

BookingPage::BookingPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong), m_selectedDate(QDate::currentDate())
{
    setupUI();
    loadTimeline();
}

void BookingPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Header
    QLabel *header = new QLabel("Đặt Sân", this);
    header->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50;");
    mainLayout->addWidget(header);

    // Toolbar
    mainLayout->addWidget(createToolbar());

    // Selected date label
    m_selectedDateLabel = new QLabel(this);
    m_selectedDateLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #27ae60; padding: 5px;");
    updateSelectedDateLabel();
    mainLayout->addWidget(m_selectedDateLabel);

    // Timeline view
    createTimelineView();
    mainLayout->addWidget(m_scrollArea, 1);

    // Legend
    QHBoxLayout *legendLayout = new QHBoxLayout();
    legendLayout->addStretch();

    QLabel *availableLabel = new QLabel("  Trống  ", this);
    availableLabel->setStyleSheet("background: #4CAF50; color: white; padding: 5px 10px; border-radius: 3px;");
    legendLayout->addWidget(availableLabel);

    QLabel *bookedLabel = new QLabel("  Đã đặt  ", this);
    bookedLabel->setStyleSheet("background: #f44336; color: white; padding: 5px 10px; border-radius: 3px;");
    legendLayout->addWidget(bookedLabel);

    QLabel *selectedLabel = new QLabel("  Đang chọn  ", this);
    selectedLabel->setStyleSheet("background: #FFC107; color: white; padding: 5px 10px; border-radius: 3px;");
    legendLayout->addWidget(selectedLabel);

    legendLayout->addStretch();
    mainLayout->addLayout(legendLayout);
}

QWidget *BookingPage::createToolbar()
{
    QWidget *toolbar = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(toolbar);
    layout->setContentsMargins(0, 0, 0, 0);

    // Date filter
    QLabel *dateLabel = new QLabel("Ngày:", this);
    m_dateFilter = new QDateEdit(this);
    m_dateFilter->setDate(m_selectedDate);
    m_dateFilter->setCalendarPopup(true);
    m_dateFilter->setDisplayFormat("dd/MM/yyyy");
    connect(m_dateFilter, &QDateEdit::dateChanged, this, &BookingPage::onDateChanged);

    layout->addWidget(dateLabel);
    layout->addWidget(m_dateFilter);

    // Today button
    m_todayBtn = new QPushButton("Hôm nay", this);
    m_todayBtn->setStyleSheet("background: #3498db; color: white; padding: 8px 15px; border-radius: 4px;");
    connect(m_todayBtn, &QPushButton::clicked, this, &BookingPage::onTodayClicked);
    layout->addWidget(m_todayBtn);

    layout->addStretch();

    // Cancel booking button
    m_cancelBookingBtn = new QPushButton("Hủy Đặt Sân", this);
    m_cancelBookingBtn->setStyleSheet("background: #e74c3c; color: white; padding: 8px 15px; border-radius: 4px;");
    connect(m_cancelBookingBtn, &QPushButton::clicked, this, &BookingPage::onCancelBooking);
    layout->addWidget(m_cancelBookingBtn);

    // Refresh button
    m_refreshBtn = new QPushButton("Làm mới", this);
    m_refreshBtn->setStyleSheet("background: #27ae60; color: white; padding: 8px 15px; border-radius: 4px;");
    connect(m_refreshBtn, &QPushButton::clicked, this, &BookingPage::loadTimeline);
    layout->addWidget(m_refreshBtn);

    return toolbar;
}

void BookingPage::createTimelineView()
{
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_timelineWidget = new QWidget();
    m_timelineLayout = new QGridLayout(m_timelineWidget);
    m_timelineLayout->setSpacing(2);
    m_timelineLayout->setContentsMargins(5, 5, 5, 5);

    m_scrollArea->setWidget(m_timelineWidget);
}

void BookingPage::loadTimeline()
{
    if (!m_heThong)
        return;

    // Clear old data
    m_timelineSlots.clear();
    m_selectedSlots.clear();

    // Clear layout
    QLayoutItem *item;
    while ((item = m_timelineLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    // Get all fields
    m_fields.clear();
    const auto &allFields = m_heThong->layDanhSachSan();
    for (int i = 0; i < allFields.size(); ++i)
    {
        if (allFields[i])
            m_fields.append(allFields[i]);
    }

    if (m_fields.isEmpty())
    {
        QLabel *emptyLabel = new QLabel("Chưa có sân nào được thêm vào hệ thống", this);
        emptyLabel->setAlignment(Qt::AlignCenter);
        m_timelineLayout->addWidget(emptyLabel, 0, 0);
        return;
    }

    // === Header row: Time labels ===
    m_timelineLayout->addWidget(new QLabel("Sân", this), 0, 0);

    for (int timeIdx = 0; timeIdx < 32; ++timeIdx)
    {
        int hour, minute;
        timeIndexToTime(timeIdx, hour, minute);

        QLabel *timeLabel = new QLabel(QString("%1:%2").arg(hour, 2, 10, QChar('0')).arg(minute, 2, 10, QChar('0')), this);
        timeLabel->setAlignment(Qt::AlignCenter);
        timeLabel->setStyleSheet("font-weight: bold; background: #ecf0f1; padding: 5px; border: 1px solid #bdc3c7;");
        m_timelineLayout->addWidget(timeLabel, 0, timeIdx + 1);
    }

    // === Field rows ===
    for (int fieldIdx = 0; fieldIdx < m_fields.size(); ++fieldIdx)
    {
        San *field = m_fields[fieldIdx];
        int row = fieldIdx + 1;

        // Field name label
        QString fieldText = QString::fromStdString(field->layTenSan()) + "\n" + QString::fromStdString(field->layTenLoaiSan()) + "\n" + QString::number(field->layGiaThueGio(), 'f', 0) + " đ/h";

        QLabel *fieldLabel = new QLabel(fieldText, this);
        fieldLabel->setAlignment(Qt::AlignCenter);
        fieldLabel->setStyleSheet("font-weight: bold; background: #ecf0f1; padding: 10px; border: 1px solid #bdc3c7;");
        fieldLabel->setMinimumWidth(120);
        m_timelineLayout->addWidget(fieldLabel, row, 0);

        // Create 32 time slots for this field
        QList<TimelineSlot *> slotsForField;

        for (int timeIdx = 0; timeIdx < 32; ++timeIdx)
        {
            int hour, minute;
            timeIndexToTime(timeIdx, hour, minute);

            TimelineSlot *slot = new TimelineSlot(this);
            slot->setTimeSlot(hour, minute);
            slot->setField(field);

            // Check if booked
            DatSan *booking = getBookingAtSlot(field, hour, minute);
            if (booking)
            {
                slot->setBooking(booking);
                slot->setStatus(TimelineSlot::BOOKED);
            }
            else
            {
                slot->setStatus(TimelineSlot::AVAILABLE);
            }

            connect(slot, &TimelineSlot::clicked, this, &BookingPage::onSlotClicked);

            m_timelineLayout->addWidget(slot, row, timeIdx + 1);
            slotsForField.append(slot);
        }

        m_timelineSlots[field] = slotsForField;
    }

    updateSelectedDateLabel();
}

void BookingPage::timeIndexToTime(int index, int &hour, int &minute)
{
    // index 0 = 6:00, index 1 = 6:30, index 2 = 7:00, ...
    int totalMinutes = 6 * 60 + index * 30;
    hour = totalMinutes / 60;
    minute = totalMinutes % 60;
}

DatSan *BookingPage::getBookingAtSlot(San *field, int hour, int minute)
{
    if (!m_heThong || !field)
        return nullptr;

    const auto &bookings = m_heThong->layDanhSachDatSan();

    for (int i = 0; i < bookings.size(); ++i)
    {
        DatSan *booking = bookings[i];
        if (!booking || booking->getTrangThai() == TrangThaiDatSan::DA_HUY)
            continue;

        if (booking->getSan() != field)
            continue;

        // Check date
        NgayGio thoiGian = booking->getThoiGianDat();
        if (thoiGian.getNgayThang().getNgay() != m_selectedDate.day() ||
            thoiGian.getNgayThang().getThang() != m_selectedDate.month() ||
            thoiGian.getNgayThang().getNam() != m_selectedDate.year())
            continue;

        // Check time overlap
        int bookingStartHour = thoiGian.getThoiGian().getGio();
        int bookingStartMinute = thoiGian.getThoiGian().getPhut();

        KhungGio khung = booking->getKhungGio();
        ThoiGian gioBD = khung.layGioBatDau();
        ThoiGian gioKT = khung.layGioKetThuc();

        int durationMinutes = (gioKT.getGio() - gioBD.getGio()) * 60 + (gioKT.getPhut() - gioBD.getPhut());

        int bookingStartTotalMin = bookingStartHour * 60 + bookingStartMinute;
        int bookingEndTotalMin = bookingStartTotalMin + durationMinutes;

        int slotTotalMin = hour * 60 + minute;
        int slotEndTotalMin = slotTotalMin + 30; // Mỗi slot 30 phút

        // Check overlap
        if (slotTotalMin < bookingEndTotalMin && slotEndTotalMin > bookingStartTotalMin)
        {
            return booking;
        }
    }

    return nullptr;
}

void BookingPage::onSlotClicked(TimelineSlot *slot)
{
    if (!slot)
        return;

    // Nếu đã đặt, hiển thị thông tin hoặc hủy
    if (slot->getStatus() == TimelineSlot::BOOKED)
    {
        DatSan *booking = slot->getBooking();
        if (booking)
        {
            QString info = QString("Đơn đặt sân:\n\nMã: %1\nKhách hàng: %2\nSân: %3\nThời gian: %4:%5\nTrạng thái: %6")
                               .arg(QString::fromStdString(booking->getMaDatSan()))
                               .arg(booking->getKhachHang() ? QString::fromStdString(booking->getKhachHang()->layHoTen()) : "N/A")
                               .arg(booking->getSan() ? QString::fromStdString(booking->getSan()->layTenSan()) : "N/A")
                               .arg(booking->getThoiGianDat().getThoiGian().getGio(), 2, 10, QChar('0'))
                               .arg(booking->getThoiGianDat().getThoiGian().getPhut(), 2, 10, QChar('0'))
                               .arg(QString::fromStdString(booking->getSan()->layTenTrangThai()));

            QMessageBox::information(this, "Thông tin đặt sân", info);
        }
        return;
    }

    // Nếu trống, mở dialog đặt sân
    if (slot->getStatus() == TimelineSlot::AVAILABLE)
    {
        BookingDialog *dialog = new BookingDialog(this);
        dialog->setBookingInfo(slot->getField(), slot->getHour(), slot->getMinute());

        if (dialog->exec() == QDialog::Accepted)
        {
            // Tạo đơn đặt sân
            KhachHang *customer = dialog->getSelectedCustomer();
            int durationMinutes = dialog->getDurationMinutes();

            if (!customer)
            {
                QMessageBox::warning(this, "Lỗi", "Không tìm thấy khách hàng!");
                delete dialog;
                return;
            }

            // Tạo NgayGio
            NgayGio thoiGianDat;
            thoiGianDat.getNgayThang().setNgay(m_selectedDate.day());
            thoiGianDat.getNgayThang().setThang(m_selectedDate.month());
            thoiGianDat.getNgayThang().setNam(m_selectedDate.year());
            thoiGianDat.getThoiGian().setGio(slot->getHour());
            thoiGianDat.getThoiGian().setPhut(slot->getMinute());

            // Tạo KhungGio
            int startHour = slot->getHour();
            int startMinute = slot->getMinute();
            int endHour = startHour + (durationMinutes / 60);
            int endMinute = startMinute + (durationMinutes % 60);
            if (endMinute >= 60)
            {
                endHour++;
                endMinute -= 60;
            }

            KhungGio khungGio(startHour, startMinute, endHour, endMinute);

            // Tạo đơn đặt sân
            DatSan *newBooking = m_heThong->taoDatSan(customer, slot->getField(), thoiGianDat, khungGio);

            if (newBooking)
            {
                // Thêm dịch vụ nếu có
                const auto &services = dialog->getSelectedServices();
                for (const auto &pair : services)
                {
                    DichVu *dv = pair.first;
                    int quantity = pair.second;

                    DichVuDat dvDat;
                    dvDat.setDichVu(dv);
                    dvDat.setSoLuong(quantity);
                    newBooking->themDichVu(dvDat);
                }

                QMessageBox::information(this, "Thành công", "Đặt sân thành công!");
                loadTimeline(); // Refresh
            }
            else
            {
                QMessageBox::warning(this, "Lỗi", "Đặt sân thất bại! Có thể sân đã được đặt trong khung giờ này.");
            }
        }

        delete dialog;
    }
}

void BookingPage::onCancelBooking()
{
    // Tìm các slot đang được chọn có booking
    QList<DatSan *> bookingsToCancel;

    for (auto it = m_timelineSlots.begin(); it != m_timelineSlots.end(); ++it)
    {
        for (TimelineSlot *slot : it.value())
        {
            if (slot->isSelected() && slot->getStatus() == TimelineSlot::BOOKED)
            {
                DatSan *booking = slot->getBooking();
                if (booking && !bookingsToCancel.contains(booking))
                {
                    bookingsToCancel.append(booking);
                }
            }
        }
    }

    if (bookingsToCancel.isEmpty())
    {
        QMessageBox::information(this, "Thông báo", "Vui lòng chọn đơn đặt sân cần hủy bằng cách click vào slot đã đặt (màu đỏ)!");
        return;
    }

    QString confirmMsg = QString("Bạn có chắc muốn hủy %1 đơn đặt sản đã chọn?").arg(bookingsToCancel.size());
    auto reply = QMessageBox::question(this, "Xác nhận", confirmMsg, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        int successCount = 0;
        for (DatSan *booking : bookingsToCancel)
        {
            if (m_heThong->huyDatSan(booking->getMaDatSan()))
            {
                successCount++;
            }
        }

        QMessageBox::information(this, "Kết quả", QString("Đã hủy thành công %1/%2 đơn đặt sân!").arg(successCount).arg(bookingsToCancel.size()));
        loadTimeline(); // Refresh
    }
}

void BookingPage::onDateChanged(const QDate &date)
{
    m_selectedDate = date;
    loadTimeline();
}

void BookingPage::onTodayClicked()
{
    m_selectedDate = QDate::currentDate();
    m_dateFilter->setDate(m_selectedDate);
    loadTimeline();
}

void BookingPage::refreshData()
{
    loadTimeline();
}

void BookingPage::updateSelectedDateLabel()
{
    QString dateStr = m_selectedDate.toString("dddd, dd/MM/yyyy");
    m_selectedDateLabel->setText("📅 " + dateStr);
}

bool BookingPage::checkSlotAvailable(San *field, int hour, int minute)
{
    return getBookingAtSlot(field, hour, minute) == nullptr;
}
