/**
 * @file PaymentPage.cpp
 */

#include "PaymentPage.h"
#include "Widgets/CustomTable.h"
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/Models/ThanhToan.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

PaymentPage::PaymentPage(HeThongQuanLy *heThong, QWidget *parent)
    : QWidget(parent), m_heThong(heThong)
{
    setupUI();
    refreshData();
}

void PaymentPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    QLabel *headerLabel = new QLabel("💳 Quản lý thanh toán", this);
    headerLabel->setStyleSheet("font-size: 28px; font-weight: 700; color: #2c3e50;");
    mainLayout->addWidget(headerLabel);

    QGroupBox *tableGroup = new QGroupBox("Danh sách thanh toán", this);
    tableGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; background-color: #fff; border-radius: 8px; padding: 16px; }");

    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    m_paymentTable = new CustomTable(this);
    m_paymentTable->setupHeaders({"Mã TT", "Mã đơn", "Số tiền", "Phương thức", "Trạng thái", "Ngày TT"});
    tableLayout->addWidget(m_paymentTable);

    mainLayout->addWidget(tableGroup);
}

void PaymentPage::refreshData()
{
    loadPayments();
}

void PaymentPage::loadPayments()
{
    if (!m_heThong)
        return;
    m_paymentTable->clearData();

    const auto &payments = m_heThong->layDanhSachThanhToan();
    for (int i = 0; i < payments.size(); ++i)
    {
        ThanhToan *payment = payments[i];
        if (!payment)
            continue;

        QStringList rowData;
        rowData << QString::fromStdString(payment->getMaThanhToan());
        rowData << (payment->getDonDatSan() ? QString::fromStdString(payment->getDonDatSan()->getMaDatSan()) : "N/A");
        rowData << QString::number(payment->getSoTien(), 'f', 0) + " đ";
        rowData << QString::fromStdString(payment->getPhuongThucText());

        NgayGio ngayTT = payment->getNgayThanhToan();
        rowData << QString("%1/%2/%3").arg(ngayTT.getNgayThang().getNgay()).arg(ngayTT.getNgayThang().getThang()).arg(ngayTT.getNgayThang().getNam());

        m_paymentTable->addDataRow(rowData);
    }
}
