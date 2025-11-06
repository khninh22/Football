#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTimeEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QFormLayout>

class HeThongQuanLy;
class San;
class KhachHang;
class DichVu;

/**
 * @brief Dialog đặt sân - hiện khi click vào slot timeline
 * Bao gồm: chọn khách hàng, thời gian, dịch vụ kèm theo
 */
class BookingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookingDialog(QWidget *parent = nullptr);

    void setBookingInfo(San *field, int startHour, int startMinute);

    // Getters cho dữ liệu đặt sân
    KhachHang *getSelectedCustomer() const;
    int getDurationMinutes() const;
    QList<QPair<DichVu *, int>> getSelectedServices() const; // DichVu + số lượng

signals:
    void bookingConfirmed();
    void bookingCancelled();

private slots:
    void onConfirmClicked();
    void onCancelClicked();
    void onAddServiceClicked();
    void onRemoveServiceClicked();
    void onCustomerSearchChanged(const QString &text);

private:
    void setupUI();
    void loadCustomers();
    void loadServices();
    void updateTotalPrice();
    void updateServiceTable();

    HeThongQuanLy *m_heThong;
    San *m_field;
    int m_startHour;
    int m_startMinute;

    // UI Components
    QLabel *m_fieldLabel;
    QLabel *m_timeLabel;
    QLabel *m_totalPriceLabel;

    QLineEdit *m_customerSearch;
    QComboBox *m_customerCombo;
    QSpinBox *m_durationSpin;

    QComboBox *m_serviceCombo;
    QSpinBox *m_serviceQuantitySpin;
    QPushButton *m_addServiceBtn;

    QTableWidget *m_servicesTable; // Bảng dịch vụ đã chọn
    QPushButton *m_removeServiceBtn;

    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;

    // Data
    QList<KhachHang *> m_customers;
    QList<DichVu *> m_services;
    QList<QPair<DichVu *, int>> m_selectedServices; // DichVu + quantity
};

#endif // BOOKINGDIALOG_H
