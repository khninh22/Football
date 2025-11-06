/**
 * @file StatisticsPage.h
 */

#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>
class HeThongQuanLy;

class StatisticsPage : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsPage(HeThongQuanLy *heThong, QWidget *parent = nullptr);
    void refreshData();

private:
    HeThongQuanLy *m_heThong;
    void setupUI();
};

#endif
