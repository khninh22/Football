/**
 * @file ServicePage.h
 */

#ifndef SERVICEPAGE_H
#define SERVICEPAGE_H

#include <QWidget>
class HeThongQuanLy;
class CustomTable;

class ServicePage : public QWidget
{
    Q_OBJECT
public:
    explicit ServicePage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    CustomTable *m_serviceTable;
    void setupUI();
    void loadServices();
};

#endif
