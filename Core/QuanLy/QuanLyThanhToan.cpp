/**
 * @file QuanLyThanhToan.cpp
 * @brief Triển khai các phương thức của lớp QuanLyThanhToan
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#include "QuanLyThanhToan.h"
#include "../Models/ThanhToanTienMat.h"
#include "../Models/ThanhToanThe.h"
#include "../Models/ThanhToanChuyenKhoan.h"
#include <iostream>

using namespace std;

QuanLyThanhToan::QuanLyThanhToan() {}

QuanLyThanhToan::~QuanLyThanhToan()
{
    xoaTatCa();
}

ThanhToan *QuanLyThanhToan::taoThanhToan(DatSan *datSan, PhuongThucThanhToan phuongThuc)
{
    if (datSan == nullptr)
    {
        return nullptr;
    }

    // Kiểm tra đã có thanh toán chưa
    if (timThanhToanTheoDatSan(datSan->getMaDatSan()) != nullptr)
    {
        cout << "Dat san nay da duoc thanh toan!" << endl;
        return nullptr;
    }

    // Tạo mã thanh toán tự động
    static int soThuTu = 1;
    string maThanhToan = "TT" + to_string(soThuTu++);

    ThanhToan *thanhToan = nullptr;

    // Lấy số tiền cần thanh toán từ đơn đặt sân
    double soTien = datSan->getTongTien();

    // Tạo thanh toán theo phương thức
    switch (phuongThuc)
    {
    case PhuongThucThanhToan::TIEN_MAT:
        thanhToan = new ThanhToanTienMat(maThanhToan, datSan, soTien);
        break;
    case PhuongThucThanhToan::THE:
        thanhToan = new ThanhToanThe(maThanhToan, datSan, soTien);
        break;
    case PhuongThucThanhToan::CHUYEN_KHOAN:
        thanhToan = new ThanhToanChuyenKhoan(maThanhToan, datSan, soTien);
        break;
    default:
        return nullptr;
    }

    if (thanhToan != nullptr)
    {
        danhSachThanhToan.push_back(thanhToan);
    }

    return thanhToan;
}

bool QuanLyThanhToan::xoaThanhToan(const string &maTT)
{
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        if (danhSachThanhToan[i]->getMaThanhToan() == maTT)
        {
            delete danhSachThanhToan[i];
            danhSachThanhToan.erase(i);
            return true;
        }
    }
    return false;
}

ThanhToan *QuanLyThanhToan::timThanhToan(const string &maTT)
{
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        if (danhSachThanhToan[i]->getMaThanhToan() == maTT)
        {
            return danhSachThanhToan[i];
        }
    }
    return nullptr;
}

ThanhToan *QuanLyThanhToan::timThanhToanTheoDatSan(const string &maDatSan)
{
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        if (danhSachThanhToan[i]->getDonDatSan()->getMaDatSan() == maDatSan)
        {
            return danhSachThanhToan[i];
        }
    }
    return nullptr;
}

const MangDong<ThanhToan *> &QuanLyThanhToan::layDanhSachThanhToan() const
{
    return danhSachThanhToan;
}

void QuanLyThanhToan::hienThiDanhSachThanhToan() const
{
    cout << "\n===== DANH SACH THANH TOAN =====" << endl;
    cout << "Tong so: " << danhSachThanhToan.size() << endl;
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        cout << "\n[" << (i + 1) << "] ";
        danhSachThanhToan[i]->hienThi();
    }
}

int QuanLyThanhToan::tongSoThanhToan() const
{
    return danhSachThanhToan.size();
}

double QuanLyThanhToan::tongDoanhThu() const
{
    double tong = 0;
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        tong += danhSachThanhToan[i]->getSoTien();
    }
    return tong;
}

bool QuanLyThanhToan::ghiFile(ofstream &file) const
{
    // TODO: Implement file I/O with proper FILE* to ofstream conversion
    // Current Models use FILE*, need to refactor or use adapter
    return true;

    /*
    if (!file.is_open())
        return false;

    int soLuong = danhSachThanhToan.size();
    file.write(reinterpret_cast<const char *>(&soLuong), sizeof(soLuong));

    for (int i = 0; i < soLuong; i++)
    {
        if (!danhSachThanhToan[i]->ghiFile(file))
            return false;
    }
    return file.good();
    */
}

bool QuanLyThanhToan::docFile(ifstream &file)
{
    // TODO: Implement file I/O with proper FILE* to ifstream conversion
    // Current Models use FILE*, cannot instantiate abstract ThanhToan class
    return true;

    /*
    if (!file.is_open())
        return false;

    xoaTatCa();

    int soLuong;
    file.read(reinterpret_cast<char *>(&soLuong), sizeof(soLuong));

    for (int i = 0; i < soLuong; i++)
    {
        ThanhToan *tt = new ThanhToan(); // ERROR: Cannot instantiate abstract class
        if (!tt->docFile(file))
        {
            delete tt;
            return false;
        }
        danhSachThanhToan.push_back(tt);
    }
    return file.good();
    */
}

void QuanLyThanhToan::xoaTatCa()
{
    for (int i = 0; i < danhSachThanhToan.size(); i++)
    {
        delete danhSachThanhToan[i];
    }
    danhSachThanhToan = MangDong<ThanhToan *>();
}
