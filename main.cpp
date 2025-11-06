#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDebug>

#include "Core/CauTrucDuLieu/MangDong.h"
#include "Core/CauTrucDuLieu/DanhSachLienKet.h"
#include "Core/CauTrucDuLieu/Ngan.h"
#include "Core/CauTrucDuLieu/HangDoi.h"
#include "Core/CauTrucDuLieu/ThoiGian.h"
#include "Core/CauTrucDuLieu/NgayThang.h"
#include "Core/CauTrucDuLieu/NgayGio.h"

// Models - Week 2
#include "Core/Models/ConNguoi.h"
#include "Core/Models/NguoiDung.h"
#include "Core/Models/QuanTriVien.h"
#include "Core/Models/NhanVien.h"
#include "Core/Models/KhachHang.h"
#include "Core/Models/San.h"
#include "Core/Models/KhungGio.h"
#include "Core/Models/DichVu.h"

// Models - Week 3
#include "Core/Models/DichVuDat.h"
#include "Core/Models/DatSan.h"
#include "Core/Models/ThanhToan.h"
#include "Core/Models/ThanhToanTienMat.h"
#include "Core/Models/ThanhToanThe.h"
#include "Core/Models/ThanhToanChuyenKhoan.h"

// System Management - Week 3
#include "Core/QuanLy/HeThongQuanLy.h"
#include "Core/QuanLy/FileManager.h"

// Statistics - Week 3
#include "Core/ThongKe/ThongKe.h"
#include "Core/ThongKe/ThongKeDoanhThu.h"
#include "Core/ThongKe/ThongKeKhachHang.h"

// Algorithms - Week 3
#include "Core/ThuatToan/QuickSort.h"
#include "Core/ThuatToan/MergeSort.h"
#include "Core/ThuatToan/BinarySearchTree.h"
#include "Core/ThuatToan/HashTable.h"

// UI Layer - Qt6 Widgets
#include "UI/MainWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
     // Initialize Qt Application (GUI mode)
     QApplication app(argc, argv);

     // Set application info
     app.setApplicationName("Football Field Manager");
     app.setOrganizationName("FootballManager");
     app.setApplicationVersion("1.0.0");

     cout << "========================================" << endl;
     cout << "   HE THONG QUAN LY SAN BONG DA" << endl;
     cout << "   Qt6 Widgets - GUI APPLICATION" << endl;
     cout << "========================================" << endl;

     // Initialize system
     cout << "Initializing system..." << endl;
     HeThongQuanLy *heThong = HeThongQuanLy::getInstance();

     // Add sample data if system is empty
     if (heThong->tongSoKhachHang() == 0)
     {
          cout << "Adding sample data..." << endl;

          // ===== CUSTOMERS (8 customers) =====
          KhachHang *kh1 = new KhachHang("Nguyen Van A", "0912345678", "Ha Noi", "KH001");
          KhachHang *kh2 = new KhachHang("Tran Thi B", "0923456789", "Ho Chi Minh", "KH002");
          KhachHang *kh3 = new KhachHang("Le Van C", "0934567890", "Da Nang", "KH003");
          KhachHang *kh4 = new KhachHang("Pham Thi D", "0945678901", "Hai Phong", "KH004");
          KhachHang *kh5 = new KhachHang("Hoang Van E", "0956789012", "Can Tho", "KH005");
          KhachHang *kh6 = new KhachHang("Vu Thi F", "0967890123", "Hue", "KH006");
          KhachHang *kh7 = new KhachHang("Do Van G", "0978901234", "Nha Trang", "KH007");
          KhachHang *kh8 = new KhachHang("Bui Thi H", "0989012345", "Vung Tau", "KH008");

          heThong->themKhachHang(kh1);
          heThong->themKhachHang(kh2);
          heThong->themKhachHang(kh3);
          heThong->themKhachHang(kh4);
          heThong->themKhachHang(kh5);
          heThong->themKhachHang(kh6);
          heThong->themKhachHang(kh7);
          heThong->themKhachHang(kh8);

          // ===== FIELDS (6 fields) =====
          San *san1 = new San("S01", "San A1", LoaiSan::SAN_5, 300000);
          San *san2 = new San("S02", "San A2", LoaiSan::SAN_5, 300000);
          San *san3 = new San("S03", "San B1", LoaiSan::SAN_7, 500000);
          San *san4 = new San("S04", "San B2", LoaiSan::SAN_7, 500000);
          San *san5 = new San("S05", "San C1", LoaiSan::SAN_11, 800000);
          San *san6 = new San("S06", "San C2", LoaiSan::SAN_11, 800000);

          heThong->themSan(san1);
          heThong->themSan(san2);
          heThong->themSan(san3);
          heThong->themSan(san4);
          heThong->themSan(san5);
          heThong->themSan(san6);

          // ===== STAFF =====
          NhanVien *nv1 = new NhanVien("Le Van X", "0911111111", "Ha Noi", "staff1", "staff123", "NV001", 8000000, CaLamViec::SANG);
          NhanVien *nv2 = new NhanVien("Nguyen Thi Y", "0922222222", "HCM", "staff2", "staff123", "NV002", 7500000, CaLamViec::CHIEU);
          heThong->themNhanVien(nv1);
          heThong->themNhanVien(nv2);

          // ===== SERVICES =====
          DichVu *dv1 = new DichVu("DV001", "Nuoc suoi", 10000, LoaiDichVu::DO_UONG);
          DichVu *dv2 = new DichVu("DV002", "Ao dau", 50000, LoaiDichVu::THIET_BI);
          DichVu *dv3 = new DichVu("DV003", "Bao hiem", 20000, LoaiDichVu::BAO_HIEM);
          heThong->themDichVu(dv1);
          heThong->themDichVu(dv2);
          heThong->themDichVu(dv3);

          // ===== BOOKINGS (15 bookings) =====
          NgayGio now;
          KhungGio khungSang(ThoiGian(7, 0, 0), ThoiGian(9, 0, 0));
          KhungGio khungChieu(ThoiGian(14, 0, 0), ThoiGian(16, 0, 0));

          // Today bookings
          NgayGio today1(7, 0, 0, now.getNgay(), now.getThang(), now.getNam());
          NgayGio today2(9, 0, 0, now.getNgay(), now.getThang(), now.getNam());
          NgayGio today3(14, 0, 0, now.getNgay(), now.getThang(), now.getNam());

          DatSan *ds1 = heThong->taoDatSan(kh1, san1, today1, khungSang);
          if (ds1)
               ds1->setTrangThai(TrangThaiDatSan::DA_XAC_NHAN);

          DatSan *ds2 = heThong->taoDatSan(kh2, san3, today2, khungSang);
          if (ds2)
               ds2->setTrangThai(TrangThaiDatSan::CHO_XAC_NHAN);

          DatSan *ds3 = heThong->taoDatSan(kh3, san5, today3, khungChieu);
          if (ds3)
               ds3->setTrangThai(TrangThaiDatSan::DA_XAC_NHAN);

          // Create more bookings for last 7 days
          for (int i = 1; i <= 10; i++)
          {
               int ngay = now.getNgay() - i;
               int thang = now.getThang();
               int nam = now.getNam();
               if (ngay < 1)
               {
                    ngay = 28;
                    thang--;
                    if (thang < 1)
                    {
                         thang = 12;
                         nam--;
                    }
               }

               NgayGio ngayDat(8 + (i % 10), 0, 0, ngay, thang, nam);
               San *sanChon = (i % 3 == 0) ? san1 : (i % 3 == 1) ? san3
                                                                 : san5;
               KhachHang *khChon = (i % 4 == 0) ? kh1 : (i % 4 == 1) ? kh2
                                                    : (i % 4 == 2)   ? kh3
                                                                     : kh4;
               KhungGio khungChon = (i % 2 == 0) ? khungSang : khungChieu;

               DatSan *dsI = heThong->taoDatSan(khChon, sanChon, ngayDat, khungChon);
               if (dsI)
                    dsI->setTrangThai(TrangThaiDatSan::HOAN_THANH);
          }

          // ===== PAYMENTS =====
          const MangDong<DatSan *> &danhSachDatSan = heThong->layDanhSachDatSan();
          for (int i = 0; i < danhSachDatSan.size(); i++)
          {
               DatSan *ds = danhSachDatSan[i];
               if (ds->getTrangThai() == TrangThaiDatSan::HOAN_THANH)
               {
                    PhuongThucThanhToan phuongThuc = (i % 3 == 0)   ? PhuongThucThanhToan::TIEN_MAT
                                                     : (i % 3 == 1) ? PhuongThucThanhToan::THE
                                                                    : PhuongThucThanhToan::CHUYEN_KHOAN;
                    heThong->taoThanhToan(ds, phuongThuc);
               }
          }

          cout << "✅ Sample data added successfully!" << endl;
     }

     cout << "System initialized with:" << endl;
     cout << "  - Customers: " << heThong->tongSoKhachHang() << endl;
     cout << "  - Fields: " << heThong->tongSoSan() << endl;
     cout << "  - Staff: " << heThong->tongSoNhanVien() << endl;
     cout << "  - Bookings: " << heThong->tongSoDatSan() << endl;
     cout << "  - Payments: " << heThong->tongSoThanhToan() << endl;
     cout << endl;

     // Load stylesheet
     QFile styleFile(":/styles/main.qss");
     if (styleFile.open(QFile::ReadOnly))
     {
          QString styleSheet = QLatin1String(styleFile.readAll());
          app.setStyleSheet(styleSheet);
          styleFile.close();
          cout << "Stylesheet loaded!" << endl;
     }

     // Create and show main window
     cout << "Starting main window..." << endl;
     MainWindow mainWindow;
     mainWindow.showMaximized();

     cout << "Application ready!" << endl;
     cout << "========================================" << endl;

     return app.exec();
}
