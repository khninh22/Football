# 📋 KẾ HOẠCH TUẦN 5 - MAIN WINDOW & LAYOUT

## 🎯 Mục tiêu

Xây dựng UI cơ bản cho ứng dụng Qt Widgets với MainWindow, Header, Sidebar và LoginDialog.

---

## 📦 Deliverables

### 1. **MainWindow (Cửa sổ chính)**

- [ ] `UI/MainWindow/MainWindow.h`
- [ ] `UI/MainWindow/MainWindow.cpp`
- [ ] `UI/MainWindow/MainWindow.ui` (Qt Designer)

**Chức năng:**

- Chứa layout chính: Header (top) + Sidebar (left) + Content Area (center)
- Quản lý navigation giữa các pages
- Kết nối với MainViewModel để lấy dữ liệu dashboard
- Xử lý events: login, logout, navigation
- Load stylesheet từ `Resources/styles/app.qss`

### 2. **Header Component**

- [ ] `UI/MainWindow/Header.h`
- [ ] `UI/MainWindow/Header.cpp`
- [ ] `UI/MainWindow/Header.ui`

**Chức năng:**

- Search bar (tìm kiếm nhanh)
- User profile dropdown (avatar, tên, vai trò)
- Notifications badge (optional)
- Logout button

### 3. **Sidebar Component**

- [ ] `UI/MainWindow/Sidebar.h`
- [ ] `UI/MainWindow/Sidebar.cpp`
- [ ] `UI/MainWindow/Sidebar.ui`

**Chức năng:**

- Logo/branding ở đầu
- Menu navigation với icons:
  - 📊 Dashboard
  - 📅 Đặt sân
  - 💳 Thanh toán
  - ⚽ Quản lý sân
  - 👥 Quản lý khách hàng
  - 🛒 Quản lý dịch vụ
  - 👔 Quản lý nhân viên
  - 📈 Thống kê
- Highlight menu item đang active
- Collapsible (có thể thu gọn) - optional

### 4. **LoginDialog**

- [ ] `UI/Pages/Login/LoginDialog.h`
- [ ] `UI/Pages/Login/LoginDialog.cpp`
- [ ] `UI/Pages/Login/LoginDialog.ui`

**Chức năng:**

- Form đăng nhập: username, password
- Checkbox "Remember me" (optional)
- Button "Đăng nhập"
- Kết nối với MainViewModel::login()
- Hiển thị lỗi nếu đăng nhập sai
- Đóng dialog và mở MainWindow nếu thành công

### 5. **Stylesheet**

- [ ] `UI/Resources/styles/app.qss`

**Nội dung:**

- Modern dark theme (giống web version)
- Colors:
  - Primary: `#3b82f6` (blue)
  - Success: `#10b981` (green)
  - Warning: `#f59e0b` (orange)
  - Danger: `#ef4444` (red)
  - Background: `#1e293b` (dark gray)
  - Text: `#f1f5f9` (light gray)
- Styling cho QPushButton, QLineEdit, QTableWidget, QLabel, etc.

### 6. **Resources**

- [ ] Icons (SVG hoặc PNG):
  - `dashboard.svg`
  - `booking.svg`
  - `payment.svg`
  - `field.svg`
  - `customer.svg`
  - `service.svg`
  - `staff.svg`
  - `statistics.svg`
  - `logo.png`
- [ ] `UI/Resources/resources.qrc` (Qt Resource file)

### 7. **Main Entry Point**

- [ ] Update `main.cpp`:
  - Khởi tạo QApplication
  - Load stylesheet
  - Hiển thị LoginDialog
  - Nếu login thành công → show MainWindow
  - Chạy app.exec()

---

## 🔗 Kết nối với Bridge Layer

### MainViewModel (đã có ✅)

**Sử dụng trong LoginDialog:**

```cpp
// LoginDialog.cpp
MainViewModel* viewModel = new MainViewModel(this);

// Kết nối signal
connect(viewModel, &MainViewModel::loginSuccess, this, &LoginDialog::onLoginSuccess);
connect(viewModel, &MainViewModel::loginFailed, this, &LoginDialog::onLoginFailed);

// Login
viewModel->login(username, password);
```

**Sử dụng trong MainWindow:**

```cpp
// MainWindow.cpp
MainViewModel* viewModel = new MainViewModel(this);
viewModel->initialize();

// Lấy stats dashboard
QVariantMap stats = viewModel->getSystemStats();
int totalFields = stats["totalFields"].toInt();
int todayBookings = stats["todayBookings"].toInt();
// ...

// Kết nối signal
connect(viewModel, &MainViewModel::dataChanged, this, &MainWindow::refreshDashboard);
```

---

## 🛠️ Công việc chi tiết

### **Bước 1: Cấu hình Qt Project**

1. **Cập nhật CMakeLists.txt:**

   - Đảm bảo `AUTOMOC`, `AUTOUIC`, `AUTORCC` = ON
   - Link Qt6::Widgets
   - Thêm UI files vào build

2. **Tạo thư mục UI:**
   ```bash
   FootballFieldManager/
   └── UI/
       ├── MainWindow/
       ├── Pages/Login/
       └── Resources/
           ├── icons/
           └── styles/
   ```

### **Bước 2: Thiết kế MainWindow.ui**

Sử dụng Qt Designer:

1. Tạo `MainWindow.ui`
2. Layout:
   ```
   ┌─────────────────────────────────────────┐
   │           Header (QWidget)              │  ← Fixed height ~60px
   ├────────┬────────────────────────────────┤
   │        │                                │
   │ Side   │      Content Area              │
   │ bar    │      (QStackedWidget)          │  ← Pages sẽ thay đổi ở đây
   │        │                                │
   │        │                                │
   └────────┴────────────────────────────────┘
   ```
3. Widgets:
   - `QWidget* centralWidget`
   - `QVBoxLayout* mainLayout`
   - `Header* headerWidget` (custom)
   - `QHBoxLayout* contentLayout`
   - `Sidebar* sidebarWidget` (custom)
   - `QStackedWidget* stackedWidget` (chứa pages)

### **Bước 3: Implement Header.h/cpp/ui**

**Header.ui layout:**

```
┌──────────────────────────────────────────────────────────┐
│  [Logo]  [SearchBox.................]  [👤] [User ▼] [🔔] │
└──────────────────────────────────────────────────────────┘
```

**Header.h:**

```cpp
#ifndef HEADER_H
#define HEADER_H

#include <QWidget>

namespace Ui {
class Header;
}

class Header : public QWidget
{
    Q_OBJECT

public:
    explicit Header(QWidget *parent = nullptr);
    ~Header();

    void setUserInfo(const QString &name, const QString &role);

signals:
    void searchRequested(const QString &query);
    void logoutRequested();

private slots:
    void onSearchTextChanged();
    void onLogoutClicked();

private:
    Ui::Header *ui;
};

#endif // HEADER_H
```

### **Bước 4: Implement Sidebar.h/cpp/ui**

**Sidebar.ui layout:**

```
┌──────────────┐
│   [Logo]     │
├──────────────┤
│ 📊 Dashboard │ ← QPushButton với icon
│ 📅 Đặt sân   │
│ 💳 Thanh toán│
│ ⚽ Quản lý sân│
│ 👥 Khách hàng│
│ 🛒 Dịch vụ   │
│ 👔 Nhân viên │
│ 📈 Thống kê  │
└──────────────┘
```

**Sidebar.h:**

```cpp
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();

    void setActiveMenu(int index);

signals:
    void menuClicked(int index);

private slots:
    void onMenuButtonClicked();

private:
    Ui::Sidebar *ui;
    QList<QPushButton*> menuButtons;
    int activeIndex = 0;

    void setupMenuButtons();
};

#endif // SIDEBAR_H
```

### **Bước 5: Implement LoginDialog.h/cpp/ui**

**LoginDialog.ui layout:**

```
┌──────────────────────────────┐
│      [Logo]                  │
│   Hệ thống quản lý sân bóng  │
│                              │
│  Username: [____________]    │
│  Password: [____________]    │
│                              │
│  [ ] Remember me             │
│                              │
│      [   Đăng nhập   ]       │
│                              │
│  [Error label if any]        │
└──────────────────────────────┘
```

**LoginDialog.h:**

```cpp
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "Bridge/ViewModels/MainViewModel.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void onLoginClicked();
    void onLoginSuccess(const QString &username, const QString &role);
    void onLoginFailed(const QString &error);

private:
    Ui::LoginDialog *ui;
    MainViewModel *viewModel;
};

#endif // LOGINDIALOG_H
```

### **Bước 6: Update main.cpp**

```cpp
#include <QApplication>
#include <QFile>
#include "UI/Pages/Login/LoginDialog.h"
#include "UI/MainWindow/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load stylesheet
    QFile styleFile(":/styles/app.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        styleFile.close();
    }

    // Show login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // Login success → show main window
        MainWindow mainWindow;
        mainWindow.showMaximized();
        return app.exec();
    }

    // User closed login → exit
    return 0;
}
```

### **Bước 7: Tạo Stylesheet (app.qss)**

```css
/* app.qss - Modern Dark Theme */

/* Global */
* {
  font-family: "Segoe UI", Arial, sans-serif;
  font-size: 14px;
}

QMainWindow {
  background-color: #0f172a;
}

/* Buttons */
QPushButton {
  background-color: #3b82f6;
  color: white;
  border: none;
  border-radius: 6px;
  padding: 8px 16px;
}

QPushButton:hover {
  background-color: #2563eb;
}

QPushButton:pressed {
  background-color: #1d4ed8;
}

/* Input fields */
QLineEdit {
  background-color: #1e293b;
  color: #f1f5f9;
  border: 1px solid #334155;
  border-radius: 6px;
  padding: 8px;
}

QLineEdit:focus {
  border-color: #3b82f6;
}

/* Tables */
QTableWidget {
  background-color: #1e293b;
  color: #f1f5f9;
  gridline-color: #334155;
  border: 1px solid #334155;
}

QHeaderView::section {
  background-color: #0f172a;
  color: #94a3b8;
  padding: 8px;
  border: none;
  font-weight: bold;
}

/* Sidebar */
#Sidebar {
  background-color: #1e293b;
  border-right: 1px solid #334155;
}

#Sidebar QPushButton {
  text-align: left;
  padding: 12px 16px;
  background-color: transparent;
  border-radius: 0;
}

#Sidebar QPushButton:hover {
  background-color: #334155;
}

#Sidebar QPushButton:checked {
  background-color: #3b82f6;
  border-left: 4px solid #60a5fa;
}

/* Header */
#Header {
  background-color: #1e293b;
  border-bottom: 1px solid #334155;
}

/* Labels */
QLabel {
  color: #f1f5f9;
}

/* More styles... */
```

### **Bước 8: Tạo resources.qrc**

```xml
<!DOCTYPE RCC>
<RCC version="1.0">
    <qresource prefix="/">
        <file>icons/dashboard.svg</file>
        <file>icons/booking.svg</file>
        <file>icons/payment.svg</file>
        <file>icons/field.svg</file>
        <file>icons/customer.svg</file>
        <file>icons/service.svg</file>
        <file>icons/staff.svg</file>
        <file>icons/statistics.svg</file>
        <file>images/logo.png</file>
        <file>styles/app.qss</file>
    </qresource>
</RCC>
```

### **Bước 9: Cập nhật CMakeLists.txt**

```cmake
# Add UI sources
set(UI_SOURCES
    UI/MainWindow/MainWindow.cpp
    UI/MainWindow/Header.cpp
    UI/MainWindow/Sidebar.cpp
    UI/Pages/Login/LoginDialog.cpp
)

set(UI_HEADERS
    UI/MainWindow/MainWindow.h
    UI/MainWindow/Header.h
    UI/MainWindow/Sidebar.h
    UI/Pages/Login/LoginDialog.h
)

set(UI_FORMS
    UI/MainWindow/MainWindow.ui
    UI/MainWindow/Header.ui
    UI/MainWindow/Sidebar.ui
    UI/Pages/Login/LoginDialog.ui
)

# Resources
set(PROJECT_RESOURCES
    UI/Resources/resources.qrc
)

# Add to executable
add_executable(${PROJECT_NAME}
    ${CORE_SOURCES}
    ${BRIDGE_SOURCES}
    ${UI_SOURCES}
    ${MAIN_SOURCES}
    ${PROJECT_RESOURCES}
)
```

---

## ✅ Testing Checklist

### 1. Build & Run

- [ ] Project builds without errors
- [ ] Application launches successfully
- [ ] Stylesheet loads correctly

### 2. LoginDialog

- [ ] Dialog hiển thị đúng layout
- [ ] Username/password input working
- [ ] Login với admin/admin123 thành công
- [ ] Login với sai password hiển thị lỗi
- [ ] Dialog đóng và mở MainWindow khi login thành công

### 3. MainWindow

- [ ] MainWindow hiển thị full screen
- [ ] Header hiển thị đúng user info
- [ ] Sidebar hiển thị đầy đủ menu items
- [ ] Click vào menu items highlight đúng

### 4. Navigation

- [ ] Click menu item chuyển page (hiện tại chỉ có Dashboard - placeholder)
- [ ] Active menu được highlight

### 5. Header Features

- [ ] Search box hoạt động (emit signal)
- [ ] Logout button hoạt động (back to login)

---

## 📊 Timeline Estimate

| Task                           | Time | Priority |
| ------------------------------ | ---- | -------- |
| Setup project structure        | 1h   | High     |
| Design MainWindow.ui           | 2h   | High     |
| Implement MainWindow           | 3h   | High     |
| Design & implement Header      | 2h   | High     |
| Design & implement Sidebar     | 3h   | High     |
| Design & implement LoginDialog | 2h   | High     |
| Create stylesheet (app.qss)    | 3h   | Medium   |
| Create icons/resources         | 2h   | Medium   |
| Update main.cpp                | 1h   | High     |
| Integration testing            | 2h   | High     |
| Bug fixes & polish             | 2h   | Medium   |

**Total: ~23 hours (~3 days full-time)**

---

## 🎯 Success Criteria

- ✅ Application khởi động được
- ✅ LoginDialog hiển thị và login được
- ✅ MainWindow hiển thị với Header + Sidebar + Content
- ✅ Navigation giữa menu items hoạt động
- ✅ Stylesheet được áp dụng (modern dark theme)
- ✅ Kết nối với MainViewModel thành công
- ✅ Code clean, có comments
- ✅ No errors, minimal warnings

---

## 📚 Next Steps (Week 6)

Sau khi hoàn thành Week 5, Week 6 sẽ làm:

1. **DashboardWidget**

   - StatCard components (Total Fields, Today Bookings, Revenue, etc.)
   - Charts (QtCharts: Line, Bar, Pie)
   - Recent bookings table

2. **Reusable Components**

   - CustomTable
   - SearchBox (advanced)
   - DateTimePicker
   - StatusBadge
   - ConfirmDialog

3. **Dashboard Integration**
   - Connect với MainViewModel để lấy real data
   - Refresh data periodically
   - Interactive charts

---

## 🔗 Related Documents

- **Week 4 Complete**: `WEEK4_COMPLETE.md` (Bridge Layer đã xong)
- **Architecture**: `QT_PROJECT_STRUCTURE.md` (Kế hoạch tổng thể)
- **Build Guide**: `BUILD.md`
- **Project Status**: `STATUS.md`

---

**Status**: 🔜 Ready to Start  
**Dependencies**: ✅ Bridge Layer (Week 4) Complete  
**Estimated Duration**: 3-4 days  
**Difficulty**: Medium

**LET'S BUILD THE UI! 🚀**
