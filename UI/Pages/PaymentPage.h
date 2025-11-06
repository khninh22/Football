/**
 * @file PaymentPage.h
 * @brief Payment management page
 */

#ifndef PAYMENTPAGE_H
#define PAYMENTPAGE_H

#include <QWidget>
class HeThongQuanLy;
class CustomTable;

class PaymentPage : public QWidget
{
    Q_OBJECT
public:
    explicit PaymentPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    CustomTable *m_paymentTable;
    void setupUI();
    void loadPayments();
};

#endif
