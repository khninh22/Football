/**
 * @file San.h
 * @brief Lớp đại diện cho Sân bóng đá
 * @details Chứa thông tin về sân, giá thuê, trạng thái
 *
 * @author Football Field Management System
 * @date 2025-11-03
 */

#ifndef SAN_H
#define SAN_H
#include <string>

#include <iostream>
#include <fstream>

/**
 * @enum LoaiSan
 * @brief Loại sân bóng đá
 */
enum class LoaiSan
{
    SAN_5, ///< Sân 5 người
    SAN_7, ///< Sân 7 người
    SAN_11 ///< Sân 11 người
};

/**
 * @enum TrangThaiSan
 * @brief Trạng thái hiện tại của sân
 */
enum class TrangThaiSan
{
    TRONG,        ///< Sân đang trống
    DA_DAT,       ///< Đã có người đặt
    DANG_SU_DUNG, ///< Đang được sử dụng
    BAO_TRI       ///< Đang bảo trì
};

/**
 * @class San
 * @brief Lớp đại diện cho một sân bóng đá
 *
 * Thông tin sân bao gồm:
 * - Mã sân, tên sân
 * - Loại sân (5, 7, 11 người)
 * - Giá thuê theo giờ
 * - Trạng thái hiện tại
 * - Ghi chú
 */
class San
{
private:
    std::string maSan;        ///< Mã sân (VD: S01, S02)
    std::string tenSan;       ///< Tên sân
    LoaiSan loaiSan;        ///< Loại sân
    double giaThueGio;      ///< Giá thuê mỗi giờ (VND)
    TrangThaiSan trangThai; ///< Trạng thái hiện tại
    std::string ghiChu;       ///< Ghi chú về sân

public:
    // ========== CONSTRUCTORS ==========

    /**
     * @brief Constructor mặc định
     */
    San();

    /**
     * @brief Constructor có tham số
     * @param maSan Mã sân
     * @param tenSan Tên sân
     * @param loaiSan Loại sân
     * @param giaThue Giá thuê mỗi giờ
     */
    San(const std::string &maSan, const std::string &tenSan,
        LoaiSan loaiSan, double giaThue);

    /**
     * @brief Copy constructor
     * @param other Đối tượng San khác
     */
    San(const San &other);

    /**
     * @brief Destructor
     */
    ~San();

    // ========== GETTERS ==========

    /**
     * @brief Lấy mã sân
     * @return Mã sân
     */
    std::string layMaSan() const;
    std::string getMaSan() const { return maSan; } // Alias

    /**
     * @brief Lấy tên sân
     * @return Tên sân
     */
    std::string layTenSan() const;
    std::string getTenSan() const { return tenSan; } // Alias

    /**
     * @brief Lấy loại sân
     * @return Loại sân
     */
    LoaiSan layLoaiSan() const;

    /**
     * @brief Lấy giá thuê
     * @return Giá thuê/giờ
     */
    double layGiaThueGio() const;
    double getGiaThue() const { return giaThueGio; } // Alias

    /**
     * @brief Lấy trạng thái sân
     * @return Trạng thái hiện tại
     */
    TrangThaiSan layTrangThai() const;

    /**
     * @brief Lấy ghi chú
     * @return Ghi chú
     */
    std::string layGhiChu() const;

    /**
     * @brief Lấy tên loại sân
     * @return Tên loại sân dạng chuỗi
     */
    std::string layTenLoaiSan() const;

    /**
     * @brief Lấy tên trạng thái sân
     * @return Tên trạng thái dạng chuỗi
     */
    std::string layTenTrangThai() const;

    // ========== SETTERS ==========

    /**
     * @brief Đặt tên sân
     * @param ten Tên sân mới
     */
    void datTenSan(const std::string &ten);

    /**
     * @brief Đặt giá thuê
     * @param gia Giá thuê mới
     */
    void datGiaThueGio(double gia);

    /**
     * @brief Đặt trạng thái sân
     * @param tt Trạng thái mới
     */
    void datTrangThai(TrangThaiSan tt);

    /**
     * @brief Đặt ghi chú
     * @param gc Ghi chú mới
     */
    void datGhiChu(const std::string &gc);

    // ========== METHODS ==========

    /**
     * @brief Kiểm tra sân có trống không
     * @return true nếu sân đang trống
     */
    bool coTrong() const;

    /**
     * @brief Tính tiền thuê sân theo số giờ
     * @param soGio Số giờ thuê
     * @return Tổng tiền
     */
    double tinhTien(double soGio) const;

    /**
     * @brief Hiển thị thông tin sân
     */
    void hienThiThongTin() const;

    /**
     * @brief Ghi thông tin ra file nhị phân
     * @param file File stream để ghi
     * @return true nếu ghi thành công
     */
    bool ghiFile(std::ofstream &file) const;

    /**
     * @brief Đọc thông tin từ file nhị phân
     * @param file File stream để đọc
     * @return true nếu đọc thành công
     */
    bool docFile(std::ifstream &file);

    // ========== OPERATORS ==========

    /**
     * @brief Toán tử gán
     * @param other Đối tượng San khác
     * @return Tham chiếu đến đối tượng hiện tại
     */
    San &operator=(const San &other);

    /**
     * @brief Toán tử so sánh (theo mã sân)
     * @param other Đối tượng San khác
     * @return true nếu mã sân giống nhau
     */
    bool operator==(const San &other) const;

    /**
     * @brief Toán tử so sánh < (theo giá thuê)
     * @param other Đối tượng San khác
     * @return true nếu giá thuê nhỏ hơn
     */
    bool operator<(const San &other) const;

    /**
     * @brief Toán tử xuất ra stream
     * @param os Output stream
     * @param s Đối tượng San
     * @return Tham chiếu đến output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const San &s);
};

#endif // SAN_H
