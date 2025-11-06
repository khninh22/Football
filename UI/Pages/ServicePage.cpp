/**
 * @file ServicePage.cpp
 */

#include "ServicePage.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/Models/DichVu.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

ServicePage::ServicePage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void ServicePage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("🛍️ Quản lý dịch vụ", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QGroupBox *tableGroup = new QGroupBox("Danh sách dịch vụ", this);
    tableGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; background-color: #fff; border-radius: 8px; padding: 16px; }");

    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    m_serviceTable = new CustomTable(this);
    m_serviceTable->setupHeaders({"Mã DV", "Tên dịch vụ", "Loại", "Đơn giá", "Đơn vị", "Còn lại"});
    tableLayout->addWidget(m_serviceTable);

    mainLayout->addWidget(tableGroup);
}

void ServicePage::refreshData()
{
    loadServices();
}

void ServicePage::loadServices()
{
    if (!m_heThong)
        return;
    m_serviceTable->clearData();

    const auto &services = m_heThong->layDanhSachDichVu();
    for (int i = 0; i < services.size(); ++i)
    {
        DichVu *service = services[i];
        if (!service)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(service->layMaDichVu());
        rowData << QString::fromStdString(service->layTenDichVu());
        rowData << QString::fromStdString(service->layTenLoaiDichVu());
        rowData << QString::number(service->layDonGia(), 'f', 0) + " đ";
        rowData << (service->coConHang() ? "Còn hàng" : "Hết hàng");
        rowData << QString::fromStdString(service->layMoTa());

        m_serviceTable->addDataRow(rowData);
    }
}
