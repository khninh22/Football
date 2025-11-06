/**
 * @file QuanLySan.cpp
 * @brief Triển khai các phương thức của lớp QuanLySan
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#include "QuanLySan.h"
#include <iostream>

using namespace std;

// ========== CONSTRUCTORS ==========

QuanLySan::QuanLySan()
{
}

QuanLySan::~QuanLySan()
{
    xoaTatCa();
}

// ========== CRUD OPERATIONS ==========

bool QuanLySan::themSan(San *san)
{
    if (san == nullptr)
    {
        return false;
    }

    // Kiểm tra trùng mã
    if (timSan(san->layMaSan()) != nullptr)
    {
        return false;
    }

    danhSachSan.push_back(san);
    return true;
}

bool QuanLySan::xoaSan(const string &maSan)
{
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layMaSan() == maSan)
        {
            delete danhSachSan[i];
            danhSachSan.erase(i);
            return true;
        }
    }
    return false;
}

bool QuanLySan::capNhatSan(const string &maSan, const San &sanMoi)
{
    San *san = timSan(maSan);
    if (san == nullptr)
    {
        return false;
    }

    *san = sanMoi;
    return true;
}

San *QuanLySan::timSan(const string &maSan)
{
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layMaSan() == maSan)
        {
            return danhSachSan[i];
        }
    }
    return nullptr;
}

const MangDong<San *> &QuanLySan::layDanhSachSan() const
{
    return danhSachSan;
}

// ========== SEARCH & FILTER ==========

MangDong<San *> QuanLySan::timSanTheoLoai(const string &loai)
{
    MangDong<San *> ketQua;

    // Convert string to LoaiSan enum for comparison
    LoaiSan loaiCanTim;
    if (loai == "SAN_5" || loai == "5")
        loaiCanTim = LoaiSan::SAN_5;
    else if (loai == "SAN_7" || loai == "7")
        loaiCanTim = LoaiSan::SAN_7;
    else if (loai == "SAN_11" || loai == "11")
        loaiCanTim = LoaiSan::SAN_11;
    else
        return ketQua; // Empty result if invalid type

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layLoaiSan() == loaiCanTim)
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }

    return ketQua;
}

MangDong<San *> QuanLySan::timSanTheoTen(const string &ten)
{
    MangDong<San *> ketQua;

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        // Tìm gần đúng (contains)
        if (danhSachSan[i]->layTenSan().find(ten) != string::npos)
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }

    return ketQua;
}

MangDong<San *> QuanLySan::laySanDangHoatDong()
{
    MangDong<San *> ketQua;

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layTrangThai() == TrangThaiSan::TRONG)
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }

    return ketQua;
}

MangDong<San *> QuanLySan::laySanBaoTri()
{
    MangDong<San *> ketQua;

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layTrangThai() == TrangThaiSan::BAO_TRI)
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }

    return ketQua;
}

// ========== AVAILABILITY CHECK ==========

bool QuanLySan::kiemTraSanTrong(San *san, const NgayGio &thoiGian, const KhungGio &khungGio)
{
    if (san == nullptr)
    {
        return false;
    }

    // Kiểm tra trạng thái sân - sân phải TRONG (available)
    if (san->layTrangThai() != TrangThaiSan::TRONG)
    {
        return false;
    }

    // TODO: Cần tích hợp với QuanLyDatSan để kiểm tra lịch đặt
    // Hiện tại chỉ kiểm tra trạng thái sân

    return true;
}

MangDong<San *> QuanLySan::timSanTrong(const NgayGio &thoiGian, const KhungGio &khungGio)
{
    MangDong<San *> ketQua;

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (kiemTraSanTrong(danhSachSan[i], thoiGian, khungGio))
        {
            ketQua.push_back(danhSachSan[i]);
        }
    }

    return ketQua;
}

// ========== STATUS MANAGEMENT ==========

bool QuanLySan::datTrangThaiSan(const string &maSan, TrangThaiSan trangThai)
{
    San *san = timSan(maSan);
    if (san == nullptr)
    {
        return false;
    }

    san->datTrangThai(trangThai);
    return true;
}

// ========== DISPLAY ==========

void QuanLySan::hienThiDanhSachSan() const
{
    cout << "\n========== DANH SACH SAN ==========" << endl;
    cout << "Tong so san: " << danhSachSan.size() << endl;
    cout << "====================================" << endl;

    for (int i = 0; i < danhSachSan.size(); i++)
    {
        cout << "\n[" << (i + 1) << "] ";
        danhSachSan[i]->hienThiThongTin();
    }

    cout << "====================================" << endl;
}

void QuanLySan::hienThiThongTinSan(const string &maSan) const
{
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layMaSan() == maSan)
        {
            danhSachSan[i]->hienThiThongTin();
            return;
        }
    }

    cout << "Khong tim thay san voi ma: " << maSan << endl;
}

// ========== STATISTICS ==========

int QuanLySan::tongSoSan() const
{
    return danhSachSan.size();
}

int QuanLySan::demSanHoatDong() const
{
    int dem = 0;
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layTrangThai() == TrangThaiSan::TRONG)
        {
            dem++;
        }
    }
    return dem;
}

int QuanLySan::demSanBaoTri() const
{
    int dem = 0;
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        if (danhSachSan[i]->layTrangThai() == TrangThaiSan::BAO_TRI)
        {
            dem++;
        }
    }
    return dem;
}

// ========== FILE I/O ==========

bool QuanLySan::ghiFile(ofstream &file) const
{
    if (!file.is_open())
    {
        return false;
    }

    // Ghi số lượng sân
    int soLuong = danhSachSan.size();
    file.write(reinterpret_cast<const char *>(&soLuong), sizeof(soLuong));

    // Ghi từng sân
    for (int i = 0; i < soLuong; i++)
    {
        if (!danhSachSan[i]->ghiFile(file))
        {
            return false;
        }
    }

    return file.good();
}

bool QuanLySan::docFile(ifstream &file)
{
    if (!file.is_open())
    {
        return false;
    }

    // Xóa dữ liệu cũ
    xoaTatCa();

    // Đọc số lượng sân
    int soLuong;
    file.read(reinterpret_cast<char *>(&soLuong), sizeof(soLuong));

    // Đọc từng sân
    for (int i = 0; i < soLuong; i++)
    {
        San *san = new San();
        if (!san->docFile(file))
        {
            delete san;
            return false;
        }
        danhSachSan.push_back(san);
    }

    return file.good();
}

void QuanLySan::xoaTatCa()
{
    for (int i = 0; i < danhSachSan.size(); i++)
    {
        delete danhSachSan[i];
    }
    danhSachSan = MangDong<San *>();
}
