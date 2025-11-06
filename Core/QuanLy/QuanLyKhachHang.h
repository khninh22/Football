/**
 * @file QuanLyKhachHang.h
 * @brief Lớp quản lý khách hàng
 * @details Tách logic quản lý khách hàng từ HeThongQuanLy
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#ifndef QUANLYKHACHHANG_H
#define QUANLYKHACHHANG_H

#include "../Models/KhachHang.h"
#include "../CauTrucDuLieu/MangDong.h"
#include <string>

/**
 * @class QuanLyKhachHang
 * @brief Lớp quản lý khách hàng
 *
 * Chức năng:
 * - CRUD khách hàng
 * - Tìm kiếm theo mã, SĐT, tên
 * - Quản lý điểm tích lũy
 */
class QuanLyKhachHang
{
private:
    MangDong<KhachHang *> danhSachKhachHang; ///< Danh sách khách hàng

public:
    // ========== CONSTRUCTORS ==========
    QuanLyKhachHang();
    ~QuanLyKhachHang();

    // ========== CRUD OPERATIONS ==========
    bool themKhachHang(KhachHang *kh);
    bool xoaKhachHang(const std::string &maKH);
    bool capNhatKhachHang(const std::string &maKH, const KhachHang &khMoi);
    KhachHang *timKhachHang(const std::string &maKH);
    const MangDong<KhachHang *> &layDanhSachKhachHang() const;

    // ========== SEARCH ==========
    KhachHang *timKhachHangTheoSDT(const std::string &sdt);
    MangDong<KhachHang *> timKhachHangTheoTen(const std::string &ten);

    // ========== DISPLAY ==========
    void hienThiDanhSachKhachHang() const;
    void hienThiThongTinKhachHang(const std::string &maKH) const;

    // ========== STATISTICS ==========
    int tongSoKhachHang() const;

    // ========== FILE I/O ==========
    bool ghiFile(std::ofstream &file) const;
    bool docFile(std::ifstream &file);
    void xoaTatCa();
};

#endif // QUANLYKHACHHANG_H
