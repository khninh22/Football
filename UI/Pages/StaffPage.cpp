/**
 * @file StaffPage.cpp
 */

#include "StaffPage.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/Models/NhanVien.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

StaffPage::StaffPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void StaffPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("👨‍💼 Quản lý nhân viên", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QGroupBox *tableGroup = new QGroupBox("Danh sách nhân viên", this);
    tableGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; background-color: #fff; border-radius: 8px; padding: 16px; }");

    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    m_staffTable = new CustomTable(this);
    m_staffTable->setupHeaders({"Mã NV", "Họ tên", "SĐT", "Chức vụ", "Lương", "Trạng thái"});
    tableLayout->addWidget(m_staffTable);

    mainLayout->addWidget(tableGroup);
}

void StaffPage::refreshData()
{
    loadStaff();
}

void StaffPage::loadStaff()
{
    if (!m_heThong)
        return;
    m_staffTable->clearData();

    const auto &staff = m_heThong->layDanhSachNhanVien();
    for (int i = 0; i < staff.size(); ++i)
    {
        NhanVien *nv = staff[i];
        if (!nv)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(nv->layMaNhanVien());
        rowData << QString::fromStdString(nv->layHoTen());
        rowData << QString::fromStdString(nv->laySoDienThoai());
        rowData << QString::fromStdString(nv->layTenCaLamViec());
        rowData << QString::number(nv->layLuongCoBan(), 'f', 0) + " đ";
        rowData << QString::number(nv->laySoNgayLam()) + " ngày";

        m_staffTable->addDataRow(rowData);
    }
}
