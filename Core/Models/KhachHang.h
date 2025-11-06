/**
 * @file KhachHang.h
 * @brief Lớp đại diện cho Khách hàng
 * @details Kế thừa từ ConNguoi, không cần tài khoản đăng nhập
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#ifndef KHACHHANG_H
#define KHACHHANG_H
#include <string>

#include "ConNguoi.h"
#include "../CauTrucDuLieu/NgayThang.h"

/**
 * @enum HangKhachHang
 * @brief Hạng khách hàng dựa trên điểm tích lũy
 */
enum class HangKhachHang
{
    DONG,     ///< Đồng (0-99 điểm) - Giảm 0%
    BAC,      ///< Bạc (100-499 điểm) - Giảm 5%
    VANG,     ///< Vàng (500-999 điểm) - Giảm 10%
    KIM_CUONG ///< Kim cương (1000+ điểm) - Giảm 15%
};

/**
 * @class KhachHang
 * @brief Lớp đại diện cho Khách hàng
 *
 * Khách hàng:
 * - Không cần tài khoản đăng nhập
 * - Có mã khách hàng riêng
 * - Tích lũy điểm qua mỗi lần đặt sân
 * - Được hưởng ưu đãi theo hạng
 */
class KhachHang : public ConNguoi
{
private:
    std::string maKhachHang; ///< Mã khách hàng (VD: KH001)
    int diemTichLuy;         ///< Điểm tích lũy
    HangKhachHang hang;      ///< Hạng khách hàng
    NgayThang ngayDangKy;    ///< Ngày đăng ký thành viên
    int soLanDatSan;         ///< Tổng số lần đặt sân

public:
    // ========== CONSTRUCTORS ==========

    /**
     * @brief Constructor mặc định
     */
    KhachHang();

    /**
     * @brief Constructor có tham số
     * @param ht Họ tên
     * @param sdt Số điện thoại
     * @param dc Địa chỉ
     * @param maKH Mã khách hàng
     */
    KhachHang(const std::string &ht, const std::string &sdt, const std::string &dc,
              const std::string &maKH);

    /**
     * @brief Copy constructor
     * @param other Đối tượng KhachHang khác
     */
    KhachHang(const KhachHang &other);

    /**
     * @brief Destructor
     */
    virtual ~KhachHang();

    // ========== GETTERS ==========

    // Inherited from base classes - forward declaration
    std::string getMaNguoiDung() const; // Alias for compatibility

    /**
     * @brief Lấy mã khách hàng
     * @return Mã khách hàng
     */
    std::string layMaKhachHang() const;

    /**
     * @brief Lấy điểm tích lũy
     * @return Điểm tích lũy
     */
    int layDiemTichLuy() const;

    /**
     * @brief Lấy hạng khách hàng
     * @return Hạng khách hàng
     */
    HangKhachHang layHang() const;

    /**
     * @brief Lấy ngày đăng ký
     * @return Ngày đăng ký
     */
    NgayThang layNgayDangKy() const;

    /**
     * @brief Lấy số lần đặt sân
     * @return Số lần đặt sân
     */
    int laySoLanDatSan() const;

    /**
     * @brief Lấy tên hạng khách hàng
     * @return Tên hạng dạng chuỗi
     */
    std::string layTenHang() const;

    /**
     * @brief Lấy phần trăm giảm giá theo hạng
     * @return Phần trăm giảm giá (0-15)
     */
    int layPhanTramGiamGia() const;

    // ========== SETTERS ==========

    /**
     * @brief Đặt mã khách hàng
     * @param maKH Mã khách hàng mới
     */
    void datMaKhachHang(const std::string &maKH);

    // ========== METHODS ==========

    /**
     * @brief Thêm điểm tích lũy (sau mỗi lần đặt sân)
     * @param diem Số điểm cần thêm
     */
    void themDiemTichLuy(int diem);

    /**
     * @brief Trừ điểm tích lũy (đổi quà, ưu đãi)
     * @param diem Số điểm cần trừ
     * @return true nếu trừ thành công
     */
    bool truDiemTichLuy(int diem);

    /**
     * @brief Tăng số lần đặt sân
     */
    void tangSoLanDatSan();

    /**
     * @brief Cập nhật hạng khách hàng dựa trên điểm
     */
    void capNhatHang();

    /**
     * @brief Hiển thị thông tin khách hàng (override)
     */
    virtual void hienThiThongTin() const override;

    /**
     * @brief Ghi thông tin ra file nhị phân (override)
     * @param file File stream để ghi
     * @return true nếu ghi thành công
     */
    virtual bool ghiFile(std::ofstream &file) const override;

    /**
     * @brief Đọc thông tin từ file nhị phân (override)
     * @param file File stream để đọc
     * @return true nếu đọc thành công
     */
    virtual bool docFile(std::ifstream &file) override;

    // ========== OPERATORS ==========

    /**
     * @brief Toán tử gán
     * @param other Đối tượng KhachHang khác
     * @return Tham chiếu đến đối tượng hiện tại
     */
    KhachHang &operator=(const KhachHang &other);

    /**
     * @brief Toán tử so sánh (theo mã khách hàng)
     * @param other Đối tượng KhachHang khác
     * @return true nếu mã khách hàng giống nhau
     */
    bool operator==(const KhachHang &other) const;

    /**
     * @brief Toán tử xuất ra stream
     * @param os Output stream
     * @param kh Đối tượng KhachHang
     * @return Tham chiếu đến output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const KhachHang &kh);
};

#endif // KHACHHANG_H
