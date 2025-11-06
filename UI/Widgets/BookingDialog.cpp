#include "BookingDialog.h"
#include "../../Core/QuanLy/HeThongQuanLy.h"
#include "../../Core/Models/San.h"
#include "../../Core/Models/KhachHang.h"
#include "../../Core/Models/DichVu.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>

BookingDialog::BookingDialog(QWidget *parent)
    : QDialog(parent), m_heThong(nullptr), m_field(nullptr), m_startHour(0), m_startMinute(0)
{
    m_heThong = HeThongQuanLy::getInstancePtr();
    setupUI();
    loadCustomers();
    loadServices();

    setWindowTitle("Đặt Sân Bóng");
    setMinimumSize(600, 700);
    setModal(true);
}

void BookingDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // === Thông tin sân và thời gian ===
    QGroupBox *infoGroup = new QGroupBox("Thông Tin Đặt Sân", this);
    QFormLayout *infoLayout = new QFormLayout(infoGroup);

    m_fieldLabel = new QLabel(this);
    m_timeLabel = new QLabel(this);
    m_totalPriceLabel = new QLabel("0 đ", this);
    m_totalPriceLabel->setStyleSheet("color: #e74c3c; font-weight: bold; font-size: 14px;");

    infoLayout->addRow("Sân:", m_fieldLabel);
    infoLayout->addRow("Thời gian bắt đầu:", m_timeLabel);
    infoLayout->addRow("Tổng tiền:", m_totalPriceLabel);

    mainLayout->addWidget(infoGroup);

    // === Chọn khách hàng ===
    QGroupBox *customerGroup = new QGroupBox("Khách Hàng", this);
    QVBoxLayout *customerLayout = new QVBoxLayout(customerGroup);

    m_customerSearch = new QLineEdit(this);
    m_customerSearch->setPlaceholderText("Tìm kiếm khách hàng (SĐT, tên)...");
    connect(m_customerSearch, &QLineEdit::textChanged, this, &BookingDialog::onCustomerSearchChanged);

    m_customerCombo = new QComboBox(this);
    m_customerCombo->setEditable(false);

    customerLayout->addWidget(m_customerSearch);
    customerLayout->addWidget(m_customerCombo);

    mainLayout->addWidget(customerGroup);

    // === Thời lượng ===
    QGroupBox *durationGroup = new QGroupBox("Thời Lượng", this);
    QFormLayout *durationLayout = new QFormLayout(durationGroup);

    m_durationSpin = new QSpinBox(this);
    m_durationSpin->setMinimum(60);    // Tối thiểu 1 tiếng
    m_durationSpin->setMaximum(180);   // Tối đa 3 tiếng
    m_durationSpin->setSingleStep(30); // Bước nhảy 30 phút
    m_durationSpin->setValue(60);
    m_durationSpin->setSuffix(" phút");
    connect(m_durationSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookingDialog::updateTotalPrice);

    durationLayout->addRow("Đá bao lâu:", m_durationSpin);

    mainLayout->addWidget(durationGroup);

    // === Dịch vụ kèm theo ===
    QGroupBox *serviceGroup = new QGroupBox("Dịch Vụ Kèm Theo", this);
    QVBoxLayout *serviceLayout = new QVBoxLayout(serviceGroup);

    QHBoxLayout *addServiceLayout = new QHBoxLayout();
    m_serviceCombo = new QComboBox(this);
    m_serviceQuantitySpin = new QSpinBox(this);
    m_serviceQuantitySpin->setMinimum(1);
    m_serviceQuantitySpin->setMaximum(100);
    m_serviceQuantitySpin->setValue(1);
    m_serviceQuantitySpin->setPrefix("SL: ");

    m_addServiceBtn = new QPushButton("Thêm", this);
    m_addServiceBtn->setStyleSheet("background: #27ae60; color: white; padding: 5px 15px; border-radius: 3px;");
    connect(m_addServiceBtn, &QPushButton::clicked, this, &BookingDialog::onAddServiceClicked);

    addServiceLayout->addWidget(m_serviceCombo, 3);
    addServiceLayout->addWidget(m_serviceQuantitySpin, 1);
    addServiceLayout->addWidget(m_addServiceBtn, 1);

    serviceLayout->addLayout(addServiceLayout);

    // Bảng dịch vụ đã chọn
    m_servicesTable = new QTableWidget(this);
    m_servicesTable->setColumnCount(4);
    m_servicesTable->setHorizontalHeaderLabels({"Dịch vụ", "Đơn giá", "SL", "Thành tiền"});
    m_servicesTable->horizontalHeader()->setStretchLastSection(true);
    m_servicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_servicesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_servicesTable->setMaximumHeight(150);

    serviceLayout->addWidget(m_servicesTable);

    m_removeServiceBtn = new QPushButton("Xóa dịch vụ đã chọn", this);
    m_removeServiceBtn->setStyleSheet("background: #e74c3c; color: white; padding: 5px 15px; border-radius: 3px;");
    connect(m_removeServiceBtn, &QPushButton::clicked, this, &BookingDialog::onRemoveServiceClicked);

    serviceLayout->addWidget(m_removeServiceBtn);

    mainLayout->addWidget(serviceGroup);

    // === Nút hành động ===
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_cancelBtn = new QPushButton("Hủy", this);
    m_cancelBtn->setStyleSheet("background: #95a5a6; color: white; padding: 8px 20px; border-radius: 4px;");
    connect(m_cancelBtn, &QPushButton::clicked, this, &BookingDialog::onCancelClicked);

    m_confirmBtn = new QPushButton("Xác Nhận Đặt Sân", this);
    m_confirmBtn->setStyleSheet("background: #2ecc71; color: white; padding: 8px 20px; border-radius: 4px; font-weight: bold;");
    connect(m_confirmBtn, &QPushButton::clicked, this, &BookingDialog::onConfirmClicked);

    buttonLayout->addWidget(m_cancelBtn);
    buttonLayout->addWidget(m_confirmBtn);

    mainLayout->addLayout(buttonLayout);
}

void BookingDialog::setBookingInfo(San *field, int startHour, int startMinute)
{
    m_field = field;
    m_startHour = startHour;
    m_startMinute = startMinute;

    if (m_field)
    {
        m_fieldLabel->setText(QString::fromStdString(m_field->layTenSan()) + " - " + QString::fromStdString(m_field->layTenLoaiSan()));
    }

    QString timeStr = QString("%1:%2").arg(startHour, 2, 10, QChar('0')).arg(startMinute, 2, 10, QChar('0'));
    m_timeLabel->setText(timeStr);

    updateTotalPrice();
}

void BookingDialog::loadCustomers()
{
    m_customerCombo->clear();
    m_customers.clear();

    if (!m_heThong)
        return;

    const auto &customers = m_heThong->layDanhSachKhachHang();
    for (int i = 0; i < customers.size(); ++i)
    {
        KhachHang *kh = customers[i];
        if (kh)
        {
            m_customers.append(kh);
            QString displayText = QString::fromStdString(kh->layHoTen()) + " - " + QString::fromStdString(kh->laySoDienThoai());
            m_customerCombo->addItem(displayText);
        }
    }
}

void BookingDialog::loadServices()
{
    m_serviceCombo->clear();
    m_services.clear();

    if (!m_heThong)
        return;

    const auto &services = m_heThong->layDanhSachDichVu();
    for (int i = 0; i < services.size(); ++i)
    {
        DichVu *dv = services[i];
        if (dv && dv->coConHang())
        {
            m_services.append(dv);
            QString displayText = QString::fromStdString(dv->layTenDichVu()) + " - " + QString::number(dv->layDonGia(), 'f', 0) + " đ";
            m_serviceCombo->addItem(displayText);
        }
    }
}

void BookingDialog::onCustomerSearchChanged(const QString &text)
{
    QString searchLower = text.toLower();

    m_customerCombo->clear();

    for (KhachHang *kh : m_customers)
    {
        QString name = QString::fromStdString(kh->layHoTen()).toLower();
        QString phone = QString::fromStdString(kh->laySoDienThoai()).toLower();

        if (name.contains(searchLower) || phone.contains(searchLower))
        {
            QString displayText = QString::fromStdString(kh->layHoTen()) + " - " + QString::fromStdString(kh->laySoDienThoai());
            m_customerCombo->addItem(displayText);
        }
    }
}

void BookingDialog::onAddServiceClicked()
{
    int idx = m_serviceCombo->currentIndex();
    if (idx < 0 || idx >= m_services.size())
        return;

    DichVu *dv = m_services[idx];
    int quantity = m_serviceQuantitySpin->value();

    // Kiểm tra đã tồn tại chưa
    for (int i = 0; i < m_selectedServices.size(); ++i)
    {
        if (m_selectedServices[i].first == dv)
        {
            // Cập nhật số lượng
            m_selectedServices[i].second += quantity;
            updateServiceTable();
            updateTotalPrice();
            return;
        }
    }

    // Thêm mới
    m_selectedServices.append(qMakePair(dv, quantity));
    updateServiceTable();
    updateTotalPrice();
}

void BookingDialog::onRemoveServiceClicked()
{
    int row = m_servicesTable->currentRow();
    if (row >= 0 && row < m_selectedServices.size())
    {
        m_selectedServices.removeAt(row);
        updateServiceTable();
        updateTotalPrice();
    }
}

void BookingDialog::updateServiceTable()
{
    m_servicesTable->setRowCount(0);

    for (int i = 0; i < m_selectedServices.size(); ++i)
    {
        DichVu *dv = m_selectedServices[i].first;
        int quantity = m_selectedServices[i].second;
        double price = dv->layDonGia();
        double total = price * quantity;

        m_servicesTable->insertRow(i);
        m_servicesTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dv->layTenDichVu())));
        m_servicesTable->setItem(i, 1, new QTableWidgetItem(QString::number(price, 'f', 0) + " đ"));
        m_servicesTable->setItem(i, 2, new QTableWidgetItem(QString::number(quantity)));
        m_servicesTable->setItem(i, 3, new QTableWidgetItem(QString::number(total, 'f', 0) + " đ"));
    }
}

void BookingDialog::updateTotalPrice()
{
    if (!m_field)
        return;

    double total = 0;

    // Tiền sân
    int durationMinutes = m_durationSpin->value();
    double hours = durationMinutes / 60.0;
    double fieldPrice = m_field->layGiaThueGio() * hours;
    total += fieldPrice;

    // Tiền dịch vụ
    for (const auto &pair : m_selectedServices)
    {
        total += pair.first->layDonGia() * pair.second;
    }

    m_totalPriceLabel->setText(QString::number(total, 'f', 0) + " đ");
}

void BookingDialog::onConfirmClicked()
{
    // Validate
    if (!m_field)
    {
        QMessageBox::warning(this, "Lỗi", "Chưa chọn sân!");
        return;
    }

    if (m_customerCombo->currentIndex() < 0)
    {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn khách hàng!");
        return;
    }

    emit bookingConfirmed();
    accept();
}

void BookingDialog::onCancelClicked()
{
    emit bookingCancelled();
    reject();
}

KhachHang *BookingDialog::getSelectedCustomer() const
{
    int idx = m_customerCombo->currentIndex();

    // Tìm khách hàng từ text hiện tại
    QString currentText = m_customerCombo->currentText();
    for (KhachHang *kh : m_customers)
    {
        QString displayText = QString::fromStdString(kh->layHoTen()) + " - " + QString::fromStdString(kh->laySoDienThoai());
        if (displayText == currentText)
            return kh;
    }

    return nullptr;
}

int BookingDialog::getDurationMinutes() const
{
    return m_durationSpin->value();
}

QList<QPair<DichVu *, int>> BookingDialog::getSelectedServices() const
{
    return m_selectedServices;
}
