/**
 * @file StaffPage.h
 */

#ifndef STAFFPAGE_H
#define STAFFPAGE_H

#include <QWidget>
class HeThongQuanLy;
class CustomTable;

class StaffPage : public QWidget
{
    Q_OBJECT
public:
    explicit StaffPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    CustomTable *m_staffTable;
    void setupUI();
    void loadStaff();
};

#endif
