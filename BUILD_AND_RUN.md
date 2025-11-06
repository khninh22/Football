# Hướng dẫn Build và Run - Football Field Manager

## 🎯 Tổng quan

Dự án đã được cấu hình để **tự động build và run** sau mỗi lần thay đổi code. Build output được thống nhất tại: `build/bin/FootballFieldManager.exe`

---

## 📁 Cấu trúc Build

```
d:\FootballFieldManager\
├── build/                          # Build directory (thống nhất)
│   ├── bin/                       # Executables
│   │   ├── FootballFieldManager.exe  ← Chạy file này
│   │   └── Data/                  # Data files
│   ├── CMakeFiles/                # CMake generated files
│   └── Makefile                   # Build scripts
├── CMakeLists.txt                 # CMake configuration
└── .vscode/
    └── tasks.json                 # VS Code tasks
```

**Lưu ý:** Folder `build/mingw-debug/` đã bị xóa để tránh nhầm lẫn. Tất cả build đều output vào `build/bin/`

---

## 🚀 Cách chạy ứng dụng

### Phương án 1: Chạy trực tiếp file EXE

```cmd
d:\FootballFieldManager\build\bin\FootballFieldManager.exe
```

### Phương án 2: Sử dụng VS Code Task

1. **Ctrl+Shift+P** → Gõ "Run Task"
2. Chọn một trong các task sau:

   - **"Run Application"** - Build (nếu cần) và chạy
   - **"Build and Run"** - Force rebuild rồi chạy
   - **"CMake: Build"** - Chỉ build
   - **"CMake: Configure"** - Chỉ configure CMake
   - **"CMake: Clean"** - Xóa build artifacts

### Phương án 3: Keyboard shortcut

- **Ctrl+Shift+B** - Run default build task (CMake: Build)
- Sau đó chạy task "Run Application" để launch app

---

## 🔧 Quy trình Auto Build & Run

Sau mỗi lần sửa code, chỉ cần:

```
1. Lưu file (Ctrl+S)
2. Ctrl+Shift+P → "Run Task" → "Build and Run"
3. Hoặc chạy lệnh terminal:
   cmake --build "d:\FootballFieldManager\build" && "d:\FootballFieldManager\build\bin\FootballFieldManager.exe"
```

---

## 🛠️ Build Commands (Manual)

### Configure CMake

```cmd
cmake -B build -S . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

### Build Project

```cmd
cmake --build build --config Debug -- -j 4
```

### Clean Build

```cmd
cmake --build build --target clean
```

### Rebuild from scratch

```cmd
cmake --build build --clean-first
```

### Full clean (xóa build folder)

```cmd
rmdir /s /q build
cmake -B build -S . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug -- -j 4
```

---

## 📋 Kiểm tra Build thành công

### Check file exe tồn tại

```cmd
dir "d:\FootballFieldManager\build\bin\FootballFieldManager.exe"
```

Kết quả mong muốn:

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----         11/6/2025   6:26 PM       13202253 FootballFieldManager.exe
```

### Check errors trong code

- VS Code sẽ hiển thị errors trong **Problems** panel (Ctrl+Shift+M)
- Hoặc xem trong Terminal output khi build

---

## ⚡ Workflow khuyên dùng

### Khi phát triển tính năng mới:

1. **Lần đầu sau khi mở VS Code:**

   ```cmd
   Ctrl+Shift+P → Run Task → "CMake: Configure"
   ```

2. **Sau mỗi lần sửa code:**

   ```cmd
   Ctrl+S (save)
   Ctrl+Shift+P → Run Task → "Build and Run"
   ```

3. **Nếu gặp lỗi compile:**

   - Xem **Problems** panel (Ctrl+Shift+M)
   - Sửa lỗi → Ctrl+S → Run "Build and Run" lại

4. **Nếu cần clean build:**
   ```cmd
   Ctrl+Shift+P → Run Task → "CMake: Rebuild"
   ```

---

## 🐛 Troubleshooting

### Lỗi: "File not found" khi chạy exe

**Nguyên nhân:** CMake chưa configure hoặc build failed

**Giải pháp:**

```cmd
cmake -B build -S . -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug -- -j 4
```

### Lỗi: "layKichThuoc() không tồn tại"

**Nguyên nhân:** MangDong class sử dụng `size()` thay vì `layKichThuoc()`

**Giải pháp:** Đã sửa tất cả UI Pages sử dụng `.size()` thay vì `.layKichThuoc()`

### Lỗi: Build folder có nhiều subfolder (mingw-debug, build/bin)

**Nguyên nhân:** CMakePresets.json và CMakeLists.txt conflict

**Giải pháp:** Đã xóa `build/mingw-debug/` và thống nhất output vào `build/bin/`

### Lỗi: Qt headers not found

**Nguyên nhân:** Qt6 chưa được cài đặt hoặc CMake không tìm thấy

**Giải pháp:**

```cmd
# Kiểm tra Qt6 installed
cmake -B build -S . -G "MinGW Makefiles"
# Output sẽ hiển thị: Qt6 Found: 1
```

---

## 📝 Ghi chú quan trọng

### Build output luôn ở:

```
d:\FootballFieldManager\build\bin\FootballFieldManager.exe
```

### Task dependencies:

- "Run Application" → depends on → "CMake: Build"
- "CMake: Build" → depends on → "CMake: Configure"

### Compiler warnings (có thể ignore):

- `unused parameter` - Parameters không dùng trong Core
- `format '%ld'` - Format specifier trong Core models
- QSS `Unknown property` - IntelliSense warning, không ảnh hưởng runtime

---

## 🎨 Sau khi chạy ứng dụng

Bạn sẽ thấy:

- ✅ Main Window với sidebar xanh lá
- ✅ 8 menu items: Trang chủ, Đặt sân, Thanh toán, Quản lý sân, Khách hàng, Dịch vụ, Nhân viên, Thống kê
- ✅ Dashboard với stats cards, biểu đồ doanh thu, bảng đặt sân gần nhất
- ✅ Dữ liệu mẫu tự động tạo (8 khách hàng, 6 sân, 13+ đặt sân)

Click vào từng menu item để chuyển trang!

---

**Tác giả:** Football Field Manager Team  
**Ngày tạo:** 06/11/2025  
**Phiên bản:** 1.0.0
