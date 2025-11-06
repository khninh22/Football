# 📋 KẾ HOẠCH TUẦN 6 - DASHBOARD & STATISTICS

## 🎯 Mục Tiêu

Xây dựng **Dashboard Page** đầy đủ với statistics, charts, và recent data tables. Đây sẽ là trang đầu tiên người dùng thấy sau khi login.

---

## 📦 Deliverables

### 1. **DashboardWidget (Main Component)**

- [ ] `UI/Pages/Dashboard/DashboardWidget.h`
- [ ] `UI/Pages/Dashboard/DashboardWidget.cpp`
- [ ] `UI/Pages/Dashboard/DashboardWidget.ui`

**Layout:**

```
┌────────────────────────────────────────────────────────────┐
│  📊 Dashboard                                    [Refresh] │
├────────────────────────────────────────────────────────────┤
│  [StatCard 1]  [StatCard 2]  [StatCard 3]  [StatCard 4]  │
├────────────────────┬───────────────────────────────────────┤
│                    │                                       │
│  Revenue Chart     │    Bookings by Field Type (Bar)      │
│  (Line Chart)      │                                       │
│                    │                                       │
├────────────────────┴───────────────────────────────────────┤
│  Recent Bookings (Table)                                   │
│  ┌──────┬─────────┬──────────┬─────────┬────────┐        │
│  │ ID   │ Field   │ Customer │ Time    │ Status │        │
│  ├──────┼─────────┼──────────┼─────────┼────────┤        │
│  │ ...  │ ...     │ ...      │ ...     │ ...    │        │
│  └──────┴─────────┴──────────┴─────────┴────────┘        │
└────────────────────────────────────────────────────────────┘
```

**Chức năng:**

- Hiển thị 4 stat cards với số liệu tổng quan
- 2 charts (Revenue line chart + Bookings bar chart)
- Recent bookings table (10 bookings gần nhất)
- Refresh button để cập nhật dữ liệu
- Kết nối với StatisticsViewModel

---

### 2. **StatCard Component (Reusable)**

- [ ] `UI/Components/StatCard/StatCard.h`
- [ ] `UI/Components/StatCard/StatCard.cpp`
- [ ] `UI/Components/StatCard/StatCard.ui`

**Design:**

```
┌─────────────────────┐
│  [Icon]    Title    │
│                     │
│       Value         │
│                     │
│  ↑ +12% vs last mon│
└─────────────────────┘
```

**Props:**

- `QString title` (e.g., "Total Fields")
- `QString value` (e.g., "24")
- `QString icon` (e.g., ":/icons/field.svg")
- `QString change` (e.g., "+12%")
- `bool isPositive` (green ↑ or red ↓)

**4 Stat Cards:**

1. **Total Fields** (⚽)
   - Value: Tổng số sân
   - Change: So với tháng trước
2. **Today's Bookings** (📅)

   - Value: Số lượt đặt sân hôm nay
   - Change: So với hôm qua

3. **Total Revenue** (💰)

   - Value: Tổng doanh thu (format: 123,456,789 VND)
   - Change: So với tháng trước

4. **Active Customers** (👥)
   - Value: Số khách hàng active
   - Change: So với tháng trước

---

### 3. **Charts Integration (QtCharts)**

#### A. **Revenue Line Chart**

- [ ] `UI/Components/Charts/RevenueChart.h`
- [ ] `UI/Components/Charts/RevenueChart.cpp`

**Features:**

- X-axis: Time (last 7 days / 30 days / 12 months)
- Y-axis: Revenue (VND)
- Line chart với points
- Hover tooltip showing exact values
- Legend: "Doanh thu"
- Colors: Green theme (#16a34a)

**Data Source:**

```cpp
StatisticsViewModel::getRevenueOverTime(int days)
// Returns: QMap<QDate, double>
```

#### B. **Bookings Bar Chart**

- [ ] `UI/Components/Charts/BookingsChart.h`
- [ ] `UI/Components/Charts/BookingsChart.cpp`

**Features:**

- X-axis: Field types (5-a-side, 7-a-side, 11-a-side)
- Y-axis: Number of bookings
- Vertical bar chart
- Different colors per field type
- Hover tooltip

**Data Source:**

```cpp
StatisticsViewModel::getBookingsByFieldType()
// Returns: QMap<QString, int>
```

---

### 4. **Recent Bookings Table**

- [ ] `UI/Components/Tables/RecentBookingsTable.h`
- [ ] `UI/Components/Tables/RecentBookingsTable.cpp`

**Columns:**

1. ID (Mã đặt sân)
2. Field Name (Tên sân)
3. Customer Name (Khách hàng)
4. Date & Time (Ngày giờ)
5. Status (Trạng thái: Confirmed/Pending/Cancelled)
6. Actions (View Details button)

**Features:**

- QTableWidget với custom styling
- Status badges (green/yellow/red)
- Sortable columns
- Click row → show booking details
- Max 10 rows, với pagination (optional)

**Data Source:**

```cpp
StatisticsViewModel::getRecentBookings(int limit = 10)
// Returns: QList<QVariantMap>
```

---

### 5. **Refresh Mechanism**

- [ ] Refresh button ở góc phải Dashboard
- [ ] Auto-refresh every 5 minutes (QTimer)
- [ ] Loading indicator khi đang refresh
- [ ] Show last updated time

---

### 6. **Integrate with MainWindow**

- [ ] Replace Dashboard placeholder page với DashboardWidget
- [ ] Connect navigation từ Sidebar
- [ ] Pass StatisticsViewModel instance to DashboardWidget
- [ ] Handle page switching correctly

---

## 🛠️ Công Việc Chi Tiết

### **Bước 1: Setup QtCharts**

1. **Update CMakeLists.txt:**

```cmake
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Charts)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Charts
)
```

2. **Verify Qt6Charts installed:**

```bash
# Check Qt installation includes Charts module
# If not, install via Qt Maintenance Tool
```

---

### **Bước 2: Create StatCard Component**

**StatCard.h:**

```cpp
#ifndef STATCARD_H
#define STATCARD_H

#include <QWidget>

namespace Ui {
class StatCard;
}

class StatCard : public QWidget
{
    Q_OBJECT

public:
    explicit StatCard(QWidget *parent = nullptr);
    ~StatCard();

    void setTitle(const QString &title);
    void setValue(const QString &value);
    void setIcon(const QString &iconPath);
    void setChange(const QString &change, bool isPositive);

private:
    Ui::StatCard *ui;
    void updateStyle();
};

#endif
```

**StatCard.ui:**

```
┌─────────────────────────────┐
│  [Icon Label]  [Title Label]│
│                             │
│  [Value Label (Large)]      │
│                             │
│  [Change Label (Small)]     │
└─────────────────────────────┘
```

- QLabel for icon (QPixmap)
- QLabel for title
- QLabel for value (font-size: 32px, bold)
- QLabel for change (font-size: 12px, colored)

**StatCard.cpp:**

```cpp
void StatCard::setChange(const QString &change, bool isPositive)
{
    ui->changeLabel->setText(change);

    // Set color
    if (isPositive) {
        ui->changeLabel->setStyleSheet("color: #10b981;"); // Green
    } else {
        ui->changeLabel->setStyleSheet("color: #ef4444;"); // Red
    }
}
```

---

### **Bước 3: Create Revenue Line Chart**

**RevenueChart.h:**

```cpp
#ifndef REVENUECHART_H
#define REVENUECHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

class RevenueChart : public QWidget
{
    Q_OBJECT

public:
    explicit RevenueChart(QWidget *parent = nullptr);
    ~RevenueChart();

    void setData(const QMap<QDate, double> &data);
    void setTitle(const QString &title);

private:
    QChartView *chartView;
    void setupChart();
};

#endif
```

**RevenueChart.cpp:**

```cpp
void RevenueChart::setupChart()
{
    // Create chart
    QChart *chart = new QChart();
    chart->setTitle("Revenue Over Time");
    chart->setAnimationOptions(QChart::AllAnimations);

    // Create line series
    QLineSeries *series = new QLineSeries();
    series->setName("Revenue (VND)");

    // Add sample data
    series->append(0, 1000000);
    series->append(1, 1500000);
    // ...

    chart->addSeries(series);

    // Setup axes
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("dd/MM");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Chart view
    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
}
```

---

### **Bước 4: Create Bookings Bar Chart**

Similar to RevenueChart but use `QBarSeries` and `QBarSet`:

```cpp
QBarSet *set = new QBarSet("Bookings");
*set << 10 << 15 << 8;  // 5-a-side, 7-a-side, 11-a-side

QBarSeries *series = new QBarSeries();
series->append(set);

chart->addSeries(series);

QBarCategoryAxis *axisX = new QBarCategoryAxis();
axisX->append(QStringList() << "5-a-side" << "7-a-side" << "11-a-side");
chart->addAxis(axisX, Qt::AlignBottom);
```

---

### **Bước 5: Create Recent Bookings Table**

**RecentBookingsTable.cpp:**

```cpp
void RecentBookingsTable::setupTable()
{
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(6);

    QStringList headers;
    headers << "ID" << "Field" << "Customer" << "Date & Time"
            << "Status" << "Actions";
    table->setHorizontalHeaderLabels(headers);

    // Style
    table->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            border: 1px solid #e5e7eb;
            border-radius: 8px;
        }
        QHeaderView::section {
            background-color: #f3f4f6;
            padding: 12px;
            border: none;
            font-weight: bold;
        }
    )");

    // Populate with sample data
    loadData();
}

void RecentBookingsTable::loadData()
{
    // Get data from StatisticsViewModel
    QList<QVariantMap> bookings = viewModel->getRecentBookings(10);

    table->setRowCount(bookings.size());

    for (int i = 0; i < bookings.size(); ++i) {
        QVariantMap booking = bookings[i];

        table->setItem(i, 0, new QTableWidgetItem(booking["id"].toString()));
        table->setItem(i, 1, new QTableWidgetItem(booking["fieldName"].toString()));
        table->setItem(i, 2, new QTableWidgetItem(booking["customerName"].toString()));
        // ...

        // Status badge
        QLabel *statusLabel = new QLabel(booking["status"].toString());
        statusLabel->setStyleSheet(getStatusStyle(booking["status"].toString()));
        table->setCellWidget(i, 4, statusLabel);
    }
}

QString RecentBookingsTable::getStatusStyle(const QString &status)
{
    if (status == "Confirmed") {
        return "background: #dcfce7; color: #15803d; padding: 4px 8px; border-radius: 4px;";
    } else if (status == "Pending") {
        return "background: #fef3c7; color: #92400e; padding: 4px 8px; border-radius: 4px;";
    } else {
        return "background: #fee2e2; color: #991b1b; padding: 4px 8px; border-radius: 4px;";
    }
}
```

---

### **Bước 6: Assemble DashboardWidget**

**DashboardWidget.ui layout:**

```
QVBoxLayout (main)
  ├─ QHBoxLayout (top row - title + refresh)
  │   ├─ QLabel "📊 Dashboard"
  │   ├─ Spacer
  │   └─ QPushButton "Refresh"
  │
  ├─ QHBoxLayout (stat cards row)
  │   ├─ StatCard 1
  │   ├─ StatCard 2
  │   ├─ StatCard 3
  │   └─ StatCard 4
  │
  ├─ QHBoxLayout (charts row)
  │   ├─ RevenueChart (width: 60%)
  │   └─ BookingsChart (width: 40%)
  │
  └─ QVBoxLayout (table section)
      ├─ QLabel "Recent Bookings"
      └─ RecentBookingsTable
```

**DashboardWidget.cpp:**

```cpp
#include "Bridge/ViewModels/StatisticsViewModel.h"

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DashboardWidget)
{
    ui->setupUi(this);

    // Initialize ViewModel
    viewModel = new StatisticsViewModel(this);

    // Setup components
    setupStatCards();
    setupCharts();
    setupTable();

    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked,
            this, &DashboardWidget::refreshData);

    // Setup auto-refresh timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DashboardWidget::refreshData);
    timer->start(300000); // 5 minutes

    // Load initial data
    refreshData();
}

void DashboardWidget::setupStatCards()
{
    // Get stats from ViewModel
    QVariantMap stats = viewModel->getOverviewStats();

    ui->statCard1->setTitle("Total Fields");
    ui->statCard1->setValue(stats["totalFields"].toString());
    ui->statCard1->setIcon(":/icons/field.svg");
    ui->statCard1->setChange("+2 this month", true);

    ui->statCard2->setTitle("Today's Bookings");
    ui->statCard2->setValue(stats["todayBookings"].toString());
    ui->statCard2->setIcon(":/icons/booking.svg");
    ui->statCard2->setChange("+15% vs yesterday", true);

    // ... stat cards 3 & 4
}

void DashboardWidget::setupCharts()
{
    // Revenue chart
    QMap<QDate, double> revenueData = viewModel->getRevenueOverTime(30);
    ui->revenueChart->setData(revenueData);

    // Bookings chart
    QMap<QString, int> bookingsData = viewModel->getBookingsByFieldType();
    ui->bookingsChart->setData(bookingsData);
}

void DashboardWidget::refreshData()
{
    setupStatCards();
    setupCharts();
    ui->recentBookingsTable->loadData();

    // Show last updated time
    ui->lastUpdatedLabel->setText(
        "Last updated: " + QDateTime::currentDateTime().toString("hh:mm:ss")
    );
}
```

---

### **Bước 7: Update MainWindow**

**MainWindow.cpp:**

```cpp
#include "UI/Pages/Dashboard/DashboardWidget.h"

void MainWindow::setupPages()
{
    // Remove placeholder, add real DashboardWidget
    DashboardWidget *dashboard = new DashboardWidget(this);
    ui->stackedWidget->addWidget(dashboard);

    // Other pages (still placeholders)
    // ...
}
```

---

## 🔗 Kết Nối với Bridge Layer

### StatisticsViewModel API

**Methods cần implement trong StatisticsViewModel:**

```cpp
// Overview stats
QVariantMap getOverviewStats();
// Returns: {
//   "totalFields": int,
//   "todayBookings": int,
//   "totalRevenue": double,
//   "activeCustomers": int,
//   "changeFields": QString,
//   "changeBookings": QString,
//   "changeRevenue": QString,
//   "changeCustomers": QString
// }

// Time-series data
QMap<QDate, double> getRevenueOverTime(int days = 30);

// Aggregated data
QMap<QString, int> getBookingsByFieldType();
QMap<QString, int> getPaymentMethods();

// Recent data
QList<QVariantMap> getRecentBookings(int limit = 10);
// Each booking: {
//   "id", "fieldName", "customerName",
//   "dateTime", "status", "price"
// }
```

**Implementation trong StatisticsViewModel.cpp:**

```cpp
QVariantMap StatisticsViewModel::getOverviewStats()
{
    ThongKe *thongKe = heThong->layThongKe();

    QVariantMap stats;
    stats["totalFields"] = heThong->laySoLuongSan();
    stats["todayBookings"] = thongKe->demDatSanTheoNgay(QDate::currentDate());
    stats["totalRevenue"] = thongKe->tinhDoanhThu();
    stats["activeCustomers"] = heThong->laySoLuongKhachHang();

    // Calculate changes vs last month (implement later)
    stats["changeFields"] = "+2";
    stats["changeBookings"] = "+15%";
    // ...

    return stats;
}

QMap<QDate, double> StatisticsViewModel::getRevenueOverTime(int days)
{
    ThongKe *thongKe = heThong->layThongKe();
    QMap<QDate, double> data;

    for (int i = 0; i < days; ++i) {
        QDate date = QDate::currentDate().addDays(-i);
        double revenue = thongKe->tinhDoanhThuTheoNgay(date);
        data[date] = revenue;
    }

    return data;
}

// ... implement other methods
```

---

## ✅ Testing Checklist

### 1. Build & Run

- [ ] QtCharts module found and linked
- [ ] Project builds without errors
- [ ] Dashboard page displays correctly

### 2. StatCard Components

- [ ] 4 stat cards render with correct data
- [ ] Icons display properly
- [ ] Change percentages show with correct colors (green/red)
- [ ] Cards styled correctly (white, shadow, rounded corners)

### 3. Charts

- [ ] Revenue line chart displays with real data
- [ ] X-axis (dates) and Y-axis (revenue) labeled correctly
- [ ] Hover tooltips work on line chart
- [ ] Bookings bar chart shows field type distribution
- [ ] Chart colors match theme (#16a34a green)
- [ ] Charts resize properly with window

### 4. Recent Bookings Table

- [ ] Table shows 10 most recent bookings
- [ ] All columns display correct data
- [ ] Status badges styled (green/yellow/red)
- [ ] Table rows alternating colors
- [ ] Click row shows booking details (or logs ID for now)

### 5. Refresh Mechanism

- [ ] Refresh button updates all data
- [ ] Last updated time displays correctly
- [ ] Auto-refresh works every 5 minutes
- [ ] No lag or freeze during refresh

### 6. Integration

- [ ] Dashboard is default page on login
- [ ] Navigation from sidebar works
- [ ] StatisticsViewModel provides correct data
- [ ] No memory leaks

---

## 📊 Timeline Estimate

| Task                             | Time | Priority |
| -------------------------------- | ---- | -------- |
| Setup QtCharts                   | 1h   | High     |
| Create StatCard component        | 2h   | High     |
| Implement Revenue Line Chart     | 3h   | High     |
| Implement Bookings Bar Chart     | 2h   | Medium   |
| Create Recent Bookings Table     | 3h   | High     |
| Assemble DashboardWidget         | 3h   | High     |
| Connect with StatisticsViewModel | 2h   | High     |
| Styling & polish                 | 2h   | Medium   |
| Testing & bug fixes              | 3h   | High     |
| **Total**                        | 21h  | ~3 days  |

---

## 🎯 Success Criteria

- ✅ Dashboard displays 4 stat cards with real data
- ✅ 2 charts (line + bar) render correctly with QtCharts
- ✅ Recent bookings table shows latest 10 bookings
- ✅ Refresh button and auto-refresh work
- ✅ Styling matches green theme
- ✅ StatisticsViewModel integration complete
- ✅ No performance issues (charts render < 1s)
- ✅ Code clean, documented

---

## 📚 Next Steps (Week 7)

After Week 6:

1. **Booking Page (Calendar View)**

   - Full calendar widget (month/week/day views)
   - Drag-and-drop booking creation
   - Click time slot → booking form
   - Booking details sidebar

2. **Field Management Page**

   - CRUD operations (Create/Read/Update/Delete)
   - Fields table with search & filters
   - Add/Edit field dialog
   - Field status management

3. **Customer Management Page**
   - Customer list with search
   - Customer details view
   - Booking history per customer
   - Add/Edit customer dialog

---

## 🔗 Related Documents

- **Week 5 Complete**: `WEEK5_COMPLETE.md` (Main Window done)
- **Week 4 Complete**: `WEEK4_COMPLETE.md` (Bridge Layer)
- **Architecture**: `QT_PROJECT_STRUCTURE.md`
- **Build Guide**: `BUILD.md`

---

**Status**: 🔜 Ready to Start  
**Dependencies**: ✅ Week 5 Complete, QtCharts installed  
**Estimated Duration**: 3 days  
**Difficulty**: Medium-High (Charts integration new)

**LET'S BUILD A BEAUTIFUL DASHBOARD! 📊🎨**

---

_Created: November 4, 2025_  
_Version: 1.0.0_  
_Author: AI Assistant + Development Team_
