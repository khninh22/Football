/**
 * @file FieldManagementPage.h
 */

#ifndef FIELDMANAGEMENTPAGE_H
#define FIELDMANAGEMENTPAGE_H

#include <QWidget>
class HeThongQuanLy;
class CustomTable;

class FieldManagementPage : public QWidget
{
    Q_OBJECT
public:
    explicit FieldManagementPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    CustomTable *m_fieldTable;
    void setupUI();
    void loadFields();
};

#endif
