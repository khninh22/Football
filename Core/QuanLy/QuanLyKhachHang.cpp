/**
 * @file QuanLyKhachHang.cpp
 * @brief Triển khai các phương thức của lớp QuanLyKhachHang
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#include "QuanLyKhachHang.h"
#include <iostream>

using namespace std;

QuanLyKhachHang::QuanLyKhachHang() {}

QuanLyKhachHang::~QuanLyKhachHang()
{
    xoaTatCa();
}

bool QuanLyKhachHang::themKhachHang(KhachHang *kh)
{
    if (kh == nullptr || timKhachHang(kh->getMaNguoiDung()) != nullptr)
    {
        return false;
    }
    danhSachKhachHang.push_back(kh);
    return true;
}

bool QuanLyKhachHang::xoaKhachHang(const string &maKH)
{
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        if (danhSachKhachHang[i]->getMaNguoiDung() == maKH)
        {
            delete danhSachKhachHang[i];
            danhSachKhachHang.erase(i);
            return true;
        }
    }
    return false;
}

bool QuanLyKhachHang::capNhatKhachHang(const string &maKH, const KhachHang &khMoi)
{
    KhachHang *kh = timKhachHang(maKH);
    if (kh == nullptr)
        return false;
    *kh = khMoi;
    return true;
}

KhachHang *QuanLyKhachHang::timKhachHang(const string &maKH)
{
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        if (danhSachKhachHang[i]->getMaNguoiDung() == maKH)
        {
            return danhSachKhachHang[i];
        }
    }
    return nullptr;
}

const MangDong<KhachHang *> &QuanLyKhachHang::layDanhSachKhachHang() const
{
    return danhSachKhachHang;
}

KhachHang *QuanLyKhachHang::timKhachHangTheoSDT(const string &sdt)
{
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        if (danhSachKhachHang[i]->getSoDienThoai() == sdt)
        {
            return danhSachKhachHang[i];
        }
    }
    return nullptr;
}

MangDong<KhachHang *> QuanLyKhachHang::timKhachHangTheoTen(const string &ten)
{
    MangDong<KhachHang *> ketQua;
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        if (danhSachKhachHang[i]->getHoTen().find(ten) != string::npos)
        {
            ketQua.push_back(danhSachKhachHang[i]);
        }
    }
    return ketQua;
}

void QuanLyKhachHang::hienThiDanhSachKhachHang() const
{
    cout << "\n===== DANH SACH KHACH HANG =====" << endl;
    cout << "Tong so: " << danhSachKhachHang.size() << endl;
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        cout << "\n[" << (i + 1) << "] ";
        danhSachKhachHang[i]->hienThiThongTin();
    }
}

void QuanLyKhachHang::hienThiThongTinKhachHang(const string &maKH) const
{
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        if (danhSachKhachHang[i]->getMaNguoiDung() == maKH)
        {
            danhSachKhachHang[i]->hienThiThongTin();
            return;
        }
    }
    cout << "Khong tim thay khach hang: " << maKH << endl;
}

int QuanLyKhachHang::tongSoKhachHang() const
{
    return danhSachKhachHang.size();
}

bool QuanLyKhachHang::ghiFile(ofstream &file) const
{
    if (!file.is_open())
        return false;

    int soLuong = danhSachKhachHang.size();
    file.write(reinterpret_cast<const char *>(&soLuong), sizeof(soLuong));

    for (int i = 0; i < soLuong; i++)
    {
        if (!danhSachKhachHang[i]->ghiFile(file))
            return false;
    }
    return file.good();
}

bool QuanLyKhachHang::docFile(ifstream &file)
{
    if (!file.is_open())
        return false;

    xoaTatCa();

    int soLuong;
    file.read(reinterpret_cast<char *>(&soLuong), sizeof(soLuong));

    for (int i = 0; i < soLuong; i++)
    {
        KhachHang *kh = new KhachHang();
        if (!kh->docFile(file))
        {
            delete kh;
            return false;
        }
        danhSachKhachHang.push_back(kh);
    }
    return file.good();
}

void QuanLyKhachHang::xoaTatCa()
{
    for (int i = 0; i < danhSachKhachHang.size(); i++)
    {
        delete danhSachKhachHang[i];
    }
    danhSachKhachHang = MangDong<KhachHang *>();
}
