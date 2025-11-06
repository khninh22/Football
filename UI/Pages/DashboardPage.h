/**
 * @file DashboardPage.h
 * @brief Dashboard page with statistics and charts
 * @details Main overview page with revenue, bookings, and customer stats
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>
#include <QVector>

// Forward declarations
class HeThongQuanLy;
class StatsCard;
class CustomTable;
class QVBoxLayout;
class QHBoxLayout;
class QChartView;
class QLineSeries;

QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

/**
 * @class DashboardPage
 * @brief Main dashboard page
 *
 * Features:
 * - Statistics cards (revenue, bookings, customers, fields)
 * - Revenue chart
 * - Recent bookings table
 * - Quick actions
 */
class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param heThong Management system instance
     * @param parent Parent widget
     */
    explicit DashboardPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);

    /**
     * @brief Refresh dashboard data
     */
    void refreshData();

private:
    HeThongQuanLy *m_heThong; ///< Management system

    // Stats cards
    StatsCard *m_revenueCard;   ///< Total revenue card
    StatsCard *m_bookingsCard;  ///< Total bookings card
    StatsCard *m_customersCard; ///< Total customers card
    StatsCard *m_fieldsCard;    ///< Active fields card

    // Chart
    QChartView *m_chartView; ///< Revenue chart view

    // Recent bookings table
    CustomTable *m_recentTable; ///< Recent bookings table

    /**
     * @brief Setup page UI
     */
    void setupUI();

    /**
     * @brief Create statistics cards section
     * @return Widget containing stats cards
     */
    QWidget *createStatsSection();

    /**
     * @brief Create revenue chart section
     * @return Widget containing chart
     */
    QWidget *createChartSection();

    /**
     * @brief Create recent bookings table section
     * @return Widget containing table
     */
    QWidget *createRecentBookingsSection();

    /**
     * @brief Load and display statistics
     */
    void loadStatistics();

    /**
     * @brief Load recent bookings into table
     */
    void loadRecentBookings();
};

#endif // DASHBOARDPAGE_H
