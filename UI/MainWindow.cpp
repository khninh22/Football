/**
 * @file MainWindow.cpp
 * @brief Implementation of MainWindow
 *
 * @author Football Field Management System
 * @date 2025-11-06
 */

#include "MainWindow.h"
#include "Widgets/SidebarButton.h"
#include "Pages/DashboardPage.h"
#include "Pages/BookingPage.h"
#include "Pages/PaymentPage.h"
#include "Pages/FieldManagementPage.h"
#include "Pages/CustomerPage.h"
#include "Pages/ServicePage.h"
#include "Pages/StaffPage.h"
#include "Pages/StatisticsPage.h"

#include "Core/QuanLy/HeThongQuanLy.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_currentPage(0)
{
    // Get management system instance
    m_heThong = HeThongQuanLy::getInstance();

    setupWindow();
    setupSidebar();
    setupPages();
    setupConnections();

    // Navigate to dashboard
    navigateToPage(0);
}

MainWindow::~MainWindow()
{
    // HeThongQuanLy is singleton, don't delete
}

void MainWindow::setupWindow()
{
    // Window properties
    setWindowTitle("Football Field Manager - Quản Lý Sân Bóng");
    setMinimumSize(1280, 720);

    // Center window on screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Create central widget
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    // Main layout
    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    // Apply window styling
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f5f6fa;
        }
    )");
}

void MainWindow::setupSidebar()
{
    // Sidebar container
    m_sidebar = new QWidget(this);
    m_sidebar->setFixedWidth(240);
    m_sidebar->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #27ae60, stop:1 #229954);
        }
    )");

    m_sidebarLayout = new QVBoxLayout(m_sidebar);
    m_sidebarLayout->setContentsMargins(16, 24, 16, 24);
    m_sidebarLayout->setSpacing(8);

    // App logo/title
    QLabel *logoLabel = new QLabel("⚽ FOOTBALL FIELD", m_sidebar);
    logoLabel->setStyleSheet(R"(
        QLabel {
            color: #ffffff;
            font-size: 18px;
            font-weight: bold;
            padding: 16px 8px;
            background: transparent;
        }
    )");
    logoLabel->setAlignment(Qt::AlignCenter);
    m_sidebarLayout->addWidget(logoLabel);

    // Separator
    QFrame *separator = new QFrame(m_sidebar);
    separator->setFrameShape(QFrame::HLine);
    separator->setStyleSheet("background-color: rgba(255, 255, 255, 0.2); max-height: 1px;");
    m_sidebarLayout->addWidget(separator);
    m_sidebarLayout->addSpacing(16);

    // Menu buttons
    QStringList menuItems = {
        "🏠 Trang chủ",
        "📅 Đặt sân",
        "💳 Thanh toán",
        "⚽ Quản lý sân",
        "👥 Khách hàng",
        "🛍️ Dịch vụ",
        "👨‍💼 Nhân viên",
        "📊 Thống kê"};

    for (int i = 0; i < menuItems.size(); ++i)
    {
        SidebarButton *btn = new SidebarButton("", menuItems[i], m_sidebar);
        m_menuButtons.append(btn);
        m_sidebarLayout->addWidget(btn);

        // Connect button click to navigation
        connect(btn, &QPushButton::clicked, this, [this, i]()
                { navigateToPage(i); });
    }

    // Add stretch to push buttons to top
    m_sidebarLayout->addStretch();

    // Version info at bottom
    QLabel *versionLabel = new QLabel("v1.0.0", m_sidebar);
    versionLabel->setStyleSheet(R"(
        QLabel {
            color: rgba(255, 255, 255, 0.6);
            font-size: 11px;
            padding: 8px;
            background: transparent;
        }
    )");
    versionLabel->setAlignment(Qt::AlignCenter);
    m_sidebarLayout->addWidget(versionLabel);

    // Add sidebar to main layout
    m_mainLayout->addWidget(m_sidebar);
}

void MainWindow::setupPages()
{
    // Create stacked widget for pages
    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->setStyleSheet("background-color: #f5f6fa;");

    // Create and add pages
    m_stackedWidget->addWidget(new DashboardPage(m_heThong, this));       // 0
    m_stackedWidget->addWidget(new BookingPage(m_heThong, this));         // 1
    m_stackedWidget->addWidget(new PaymentPage(m_heThong, this));         // 2
    m_stackedWidget->addWidget(new FieldManagementPage(m_heThong, this)); // 3
    m_stackedWidget->addWidget(new CustomerPage(m_heThong, this));        // 4
    m_stackedWidget->addWidget(new ServicePage(m_heThong, this));         // 5
    m_stackedWidget->addWidget(new StaffPage(m_heThong, this));           // 6
    m_stackedWidget->addWidget(new StatisticsPage(m_heThong, this));      // 7

    // Add to main layout
    m_mainLayout->addWidget(m_stackedWidget, 1);
}

void MainWindow::setupConnections()
{
    // Connections are already set up in setupSidebar
}

void MainWindow::navigateToPage(int index)
{
    if (index < 0 || index >= m_stackedWidget->count())
    {
        return;
    }

    // Update button states
    for (int i = 0; i < m_menuButtons.size(); ++i)
    {
        m_menuButtons[i]->setActive(i == index);
    }

    // Switch page
    m_stackedWidget->setCurrentIndex(index);
    m_currentPage = index;
}

QWidget *MainWindow::createPageHeader(const QString &title)
{
    QWidget *header = new QWidget(this);
    header->setStyleSheet("background-color: #ffffff; border-bottom: 1px solid #e0e0e0;");
    header->setFixedHeight(70);

    QHBoxLayout *layout = new QHBoxLayout(header);
    layout->setContentsMargins(24, 0, 24, 0);

    QLabel *titleLabel = new QLabel(title, header);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: 700; color: #2c3e50;");

    layout->addWidget(titleLabel);
    layout->addStretch();

    return header;
}
