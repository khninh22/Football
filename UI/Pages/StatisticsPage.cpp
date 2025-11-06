/**
 * @file StatisticsPage.cpp
 */

#include "StatisticsPage.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

StatisticsPage::StatisticsPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void StatisticsPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("📊 Thống kê báo cáo", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QLabel *placeholderLabel = new QLabel("Trang thống kê với biểu đồ chi tiết sẽ được triển khai sau.", this);
    placeholderLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 40px;");
    placeholderLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(placeholderLabel);

    mainLayout->addStretch();
}

void StatisticsPage::refreshData()
{
    // TODO: Implement statistics
}
