# ⚽ Football Field Manager - Qt6 GUI

## 🚀 Chạy Ứng Dụng Nhanh

### Windows (MinGW)

```cmd
# Build
cmake --build build

# Run
build\bin\FootballFieldManager.exe
```

### Hoặc dùng VS Code Task

```
Ctrl+Shift+P → Tasks: Run Task → Run Application
```

## ✨ Giao Diện

### Sidebar (Xanh lá - Bên trái)

- 🏠 **Trang chủ** - Dashboard với thống kê và biểu đồ
- 📅 **Đặt sân** - Quản lý đơn đặt sân
- 💳 **Thanh toán** - Quản lý thanh toán
- ⚽ **Quản lý sân** - Danh sách sân và trạng thái
- 👥 **Khách hàng** - Thông tin khách hàng
- 🛍️ **Dịch vụ** - Dịch vụ đồ uống, thiết bị
- 👨‍💼 **Nhân viên** - Quản lý nhân viên
- 📊 **Thống kê** - Báo cáo doanh thu

### Dashboard Features

✅ 4 thẻ thống kê với màu sắc đẹp mắt  
✅ Biểu đồ doanh thu 7 ngày (Qt Charts)  
✅ Bảng đơn đặt sân gần đây  
✅ Dữ liệu real-time từ Core

### Tính Năng Chính

✅ Tích hợp hoàn chỉnh với Core layer  
✅ Dữ liệu mẫu tự động tạo lần đầu chạy  
✅ Modern Material Design  
✅ Responsive & Scalable  
✅ Custom widgets tái sử dụng

## 📊 Dữ Liệu Mẫu

Khi chạy lần đầu, hệ thống tự tạo:

- 8 khách hàng
- 6 sân (2 sân 5, 2 sân 7, 2 sân 11)
- 2 nhân viên
- 3 dịch vụ
- 13+ đơn đặt sân (trong 7 ngày gần đây)
- Thanh toán tương ứng

## 🎨 Thiết Kế

- **Sidebar**: Gradient xanh lá (#27ae60 → #229954)
- **Cards**: Shadow, hover effects, icon màu
- **Tables**: Header xanh, alternating rows
- **Charts**: Line chart animated

## 📁 Cấu Trúc UI

```
UI/
├── MainWindow           → Cửa sổ chính
├── Widgets/
│   ├── SidebarButton   → Nút menu sidebar
│   ├── StatsCard       → Thẻ thống kê
│   └── CustomTable     → Bảng dữ liệu đẹp
├── Pages/
│   ├── DashboardPage   → Trang chủ
│   ├── BookingPage     → Đặt sân
│   ├── PaymentPage     → Thanh toán
│   ├── FieldManagementPage → Quản lý sân
│   ├── CustomerPage    → Khách hàng
│   ├── ServicePage     → Dịch vụ
│   ├── StaffPage       → Nhân viên
│   └── StatisticsPage  → Thống kê
└── Resources/
    ├── icons/          → SVG icons
    └── styles/         → QSS stylesheet
```

## 🔧 Troubleshooting

### Không chạy được?

```cmd
# Kiểm tra Qt đã cài đúng
qmake --version

# Rebuild
cmake -B build -S . -G "MinGW Makefiles"
cmake --build build
```

### Thiếu DLL?

Copy các DLL cần thiết từ Qt:

- Qt6Core.dll
- Qt6Gui.dll
- Qt6Widgets.dll
- Qt6Charts.dll

Hoặc chạy:

```cmd
windeployqt build\bin\FootballFieldManager.exe
```

## 📖 Tài Liệu Đầy Đủ

- [UI_README.md](UI_README.md) - Chi tiết về UI
- [QT6_GUI_BUILD_GUIDE.md](QT6_GUI_BUILD_GUIDE.md) - Hướng dẫn build

## 🎯 Next Steps

Sau khi chạy thành công:

1. Khám phá các trang trong menu
2. Xem dữ liệu mẫu
3. Test các chức năng
4. Tùy chỉnh giao diện (colors, fonts)
5. Thêm tính năng mới nếu muốn

---

**Enjoy!** 🎉
