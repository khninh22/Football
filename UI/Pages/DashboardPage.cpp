/**
 * @file DashboardPage.cpp
 * @brief Implementation of DashboardPage
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#include "DashboardPage.h"
#include "Widgets/StatsCard.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/QuanLy/QuanLyDatSan.h"
#include "Core/QuanLy/QuanLyThanhToan.h"
#include "Core/Models/DatSan.h"
#include "Core/Models/ThanhToan.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QDateTime>
#include <QLocale>

DashboardPage::DashboardPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void DashboardPage::setupUI()
{
    // Main layout with scroll area
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Scroll area for content
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background-color: #f5f6fa; border: none; }");

    // Content widget
    QWidget *contentWidget = new QWidget(scrollArea);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(24, 24, 24, 24);
    contentLayout->setSpacing(24);

    // Page header
    QLabel *headerLabel = new QLabel("📊 Trang chủ", contentWidget);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    contentLayout->addWidget(headerLabel);

    // Subtitle
    QLabel *subtitleLabel = new QLabel("Tổng quan hoạt động kinh doanh", contentWidget);
    subtitleLabel->setStyleSheet("font-size: 14px; color: #7f8c8d; margin-bottom: 8px;");
    contentLayout->addWidget(subtitleLabel);

    // Stats section
    contentLayout->addWidget(createStatsSection());

    // Chart section
    contentLayout->addWidget(createChartSection());

    // Recent bookings section
    contentLayout->addWidget(createRecentBookingsSection());

    contentLayout->addStretch();

    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);
}

QWidget *DashboardPage::createStatsSection()
{
    QWidget *section = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(section);
    layout->setSpacing(16);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create stats cards
    m_revenueCard = new StatsCard("Tổng doanh thu", "0 đ", "", QColor("#3498db"), section);
    m_bookingsCard = new StatsCard("Đơn đặt sân", "0", "", QColor("#2ecc71"), section);
    m_customersCard = new StatsCard("Khách hàng", "0", "", QColor("#e74c3c"), section);
    m_fieldsCard = new StatsCard("Sân hoạt động", "0", "", QColor("#f39c12"), section);

    layout->addWidget(m_revenueCard);
    layout->addWidget(m_bookingsCard);
    layout->addWidget(m_customersCard);
    layout->addWidget(m_fieldsCard);

    return section;
}

QWidget *DashboardPage::createChartSection()
{
    QWidget *section = new QWidget(this);
    section->setStyleSheet("background-color: #ffffff; border-radius: 12px;");
    section->setMinimumHeight(350);

    QVBoxLayout *layout = new QVBoxLayout(section);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(16);

    // Section header
    QLabel *headerLabel = new QLabel("📈 Doanh thu 7 ngày gần đây", section);
    headerLabel->setStyleSheet("font-size: 18px; font-weight: 600; color: #2c3e50;");
    layout->addWidget(headerLabel);

    // Create chart
    QChart *chart = new QChart();
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);
    chart->legend()->setVisible(false);

    // Create series
    QLineSeries *series = new QLineSeries();
    series->setName("Doanh thu");

    // Sample data - will be replaced with real data
    for (int i = 0; i < 7; ++i)
    {
        series->append(i, (rand() % 5 + 3) * 1000000);
    }

    QPen pen(QColor("#2ecc71"));
    pen.setWidth(3);
    series->setPen(pen);

    chart->addSeries(series);

    // Create axes
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 6);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Ngày");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 10000000);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Doanh thu (đ)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Chart view
    m_chartView = new QChartView(chart, section);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setStyleSheet("border: none; background-color: transparent;");

    layout->addWidget(m_chartView);

    return section;
}

QWidget *DashboardPage::createRecentBookingsSection()
{
    QWidget *section = new QWidget(this);
    section->setStyleSheet("background-color: #ffffff; border-radius: 12px;");

    QVBoxLayout *layout = new QVBoxLayout(section);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(16);

    // Section header
    QLabel *headerLabel = new QLabel("📋 Đặt sân gần đây", section);
    headerLabel->setStyleSheet("font-size: 18px; font-weight: 600; color: #2c3e50;");
    layout->addWidget(headerLabel);

    // Create table
    m_recentTable = new CustomTable(section);
    m_recentTable->setupHeaders({"Mã đơn", "Khách hàng", "Sân", "Thời gian", "Trạng thái"});
    m_recentTable->setMaximumHeight(300);

    layout->addWidget(m_recentTable);

    return section;
}

void DashboardPage::refreshData()
{
    loadStatistics();
    loadRecentBookings();
}

void DashboardPage::loadStatistics()
{
    if (!m_heThong)
        return;

    // Get data from management system
    int totalCustomers = m_heThong->tongSoKhachHang();
    int totalBookings = m_heThong->tongSoDatSan();
    int totalFields = m_heThong->tongSoSan();

    // Calculate total revenue
    double totalRevenue = 0.0;
    const auto &payments = m_heThong->layDanhSachThanhToan();
    for (int i = 0; i < payments.size(); ++i)
    {
        if (payments[i])
        {
            totalRevenue += payments[i]->getSoTien();
        }
    }

    // Format numbers
    QLocale locale(QLocale::Vietnamese);

    // Update cards
    m_revenueCard->setValue(locale.toString(totalRevenue, 'f', 0) + " đ");
    m_revenueCard->setSubtitle("Tổng thu");

    m_bookingsCard->setValue(QString::number(totalBookings));
    m_bookingsCard->setSubtitle("Tổng đơn");

    m_customersCard->setValue(QString::number(totalCustomers));
    m_customersCard->setSubtitle("Tổng khách");

    m_fieldsCard->setValue(QString::number(totalFields));
    m_fieldsCard->setSubtitle("Tổng sân");
}

void DashboardPage::loadRecentBookings()
{
    if (!m_heThong)
        return;

    m_recentTable->clearData();

    // Get recent bookings (last 10)
    const auto &bookings = m_heThong->layDanhSachDatSan();
    int count = qMin(10, bookings.size());

    for (int i = bookings.size() - 1; i >= bookings.size() - count && i >= 0; --i)
    {
        DatSan *booking = bookings[i];
        if (!booking)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(booking->getMaDatSan());
        rowData << (booking->getKhachHang() ? QString::fromStdString(booking->getKhachHang()->layHoTen()) : "N/A");
        rowData << (booking->getSan() ? QString::fromStdString(booking->getSan()->layTenSan()) : "N/A");

        // Format time
        NgayGio thoiGian = booking->getThoiGianDat();
        rowData << QString("%1/%2/%3 %4:%5")
                       .arg(thoiGian.getNgayThang().getNgay())
                       .arg(thoiGian.getNgayThang().getThang())
                       .arg(thoiGian.getNgayThang().getNam())
                       .arg(thoiGian.getThoiGian().getGio(), 2, 10, QChar('0'))
                       .arg(thoiGian.getThoiGian().getPhut(), 2, 10, QChar('0'));

        rowData << QString::fromStdString(booking->getTrangThaiText());

        m_recentTable->addDataRow(rowData);
    }
}
