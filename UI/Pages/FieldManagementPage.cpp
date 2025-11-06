/**
 * @file FieldManagementPage.cpp
 */

#include "FieldManagementPage.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/Models/San.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

FieldManagementPage::FieldManagementPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void FieldManagementPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("⚽ Quản lý sân bóng", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QGroupBox *tableGroup = new QGroupBox("Danh sách sân", this);
    tableGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; background-color: #fff; border-radius: 8px; padding: 16px; }");

    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    m_fieldTable = new CustomTable(this);
    m_fieldTable->setupHeaders({"Mã sân", "Tên sân", "Loại sân", "Giá thuê/giờ", "Trạng thái", "Ghi chú"});
    tableLayout->addWidget(m_fieldTable);

    mainLayout->addWidget(tableGroup);
}

void FieldManagementPage::refreshData()
{
    loadFields();
}

void FieldManagementPage::loadFields()
{
    if (!m_heThong)
        return;
    m_fieldTable->clearData();

    const auto &fields = m_heThong->layDanhSachSan();
    for (int i = 0; i < fields.size(); ++i)
    {
        San *field = fields[i];
        if (!field)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(field->layMaSan());
        rowData << QString::fromStdString(field->layTenSan());
        rowData << QString::fromStdString(field->layTenLoaiSan());
        rowData << QString::number(field->layGiaThueGio(), 'f', 0) + " đ/giờ";
        rowData << QString::fromStdString(field->layTenTrangThai());
        rowData << QString::fromStdString(field->layGhiChu());

        m_fieldTable->addDataRow(rowData);
    }
}
