/**
 * @file CustomerPage.h
 */

#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <QWidget>
class HeThongQuanLy;
class CustomTable;

class CustomerPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    CustomTable *m_customerTable;
    void setupUI();
    void loadCustomers();
};

#endif
