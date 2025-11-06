/**
 * @file CustomerPage.cpp
 */

#include "CustomerPage.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/Models/KhachHang.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

CustomerPage::CustomerPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void CustomerPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("👥 Quản lý khách hàng", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QGroupBox *tableGroup = new QGroupBox("Danh sách khách hàng", this);
    tableGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; background-color: #fff; border-radius: 8px; padding: 16px; }");

    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    m_customerTable = new CustomTable(this);
    m_customerTable->setupHeaders({"Mã KH", "Họ tên", "SĐT", "Địa chỉ", "Điểm tích lũy", "Hạng", "Số lần đặt"});
    tableLayout->addWidget(m_customerTable);

    mainLayout->addWidget(tableGroup);
}

void CustomerPage::refreshData()
{
    loadCustomers();
}

void CustomerPage::loadCustomers()
{
    if (!m_heThong)
        return;
    m_customerTable->clearData();

    const auto &customers = m_heThong->layDanhSachKhachHang();
    for (int i = 0; i < customers.size(); ++i)
    {
        KhachHang *customer = customers[i];
        if (!customer)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(customer->layMaKhachHang());
        rowData << QString::fromStdString(customer->layHoTen());
        rowData << QString::fromStdString(customer->laySoDienThoai());
        rowData << QString::fromStdString(customer->layDiaChi());
        rowData << QString::number(customer->layDiemTichLuy());
        rowData << QString::fromStdString(customer->layTenHang());
        rowData << QString::number(customer->laySoLanDatSan());

        m_customerTable->addDataRow(rowData);
    }
}
