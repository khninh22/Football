/**
 * @file KhachHang.cpp
 * @brief Implementation của lớp KhachHang
 */

#include "KhachHang.h"
#include "../Utils/FileHelper.h"

// ========== CONSTRUCTORS ==========

KhachHang::KhachHang()
    : ConNguoi(), maKhachHang(""), diemTichLuy(0),
      hang(HangKhachHang::DONG), ngayDangKy(), soLanDatSan(0)
{
}

KhachHang::KhachHang(const std::string &ht, const std::string &sdt, const std::string &dc,
                     const std::string &maKH)
    : ConNguoi(ht, sdt, dc), maKhachHang(maKH), diemTichLuy(0),
      hang(HangKhachHang::DONG), ngayDangKy(), soLanDatSan(0)
{
}

KhachHang::KhachHang(const KhachHang &other)
    : ConNguoi(other), maKhachHang(other.maKhachHang),
      diemTichLuy(other.diemTichLuy), hang(other.hang),
      ngayDangKy(other.ngayDangKy), soLanDatSan(other.soLanDatSan)
{
}

KhachHang::~KhachHang()
{
    // Destructor
}

// ========== GETTERS ==========

std::string KhachHang::layMaKhachHang() const
{
    return maKhachHang;
}

std::string KhachHang::getMaNguoiDung() const
{
    return maKhachHang; // Return customer ID as user ID
}

int KhachHang::layDiemTichLuy() const
{
    return diemTichLuy;
}

HangKhachHang KhachHang::layHang() const
{
    return hang;
}

NgayThang KhachHang::layNgayDangKy() const
{
    return ngayDangKy;
}

int KhachHang::laySoLanDatSan() const
{
    return soLanDatSan;
}

std::string KhachHang::layTenHang() const
{
    switch (hang)
    {
    case HangKhachHang::DONG:
        return std::string("Dong");
    case HangKhachHang::BAC:
        return std::string("Bac");
    case HangKhachHang::VANG:
        return std::string("Vang");
    case HangKhachHang::KIM_CUONG:
        return std::string("Kim Cuong");
    default:
        return std::string("Khong xac dinh");
    }
}

int KhachHang::layPhanTramGiamGia() const
{
    switch (hang)
    {
    case HangKhachHang::DONG:
        return 0;
    case HangKhachHang::BAC:
        return 5;
    case HangKhachHang::VANG:
        return 10;
    case HangKhachHang::KIM_CUONG:
        return 15;
    default:
        return 0;
    }
}

// ========== SETTERS ==========

void KhachHang::datMaKhachHang(const std::string &maKH)
{
    maKhachHang = maKH;
}

// ========== METHODS ==========

void KhachHang::themDiemTichLuy(int diem)
{
    if (diem > 0)
    {
        diemTichLuy += diem;
        capNhatHang();
    }
}

bool KhachHang::truDiemTichLuy(int diem)
{
    if (diem > 0 && diemTichLuy >= diem)
    {
        diemTichLuy -= diem;
        capNhatHang();
        return true;
    }
    return false;
}

void KhachHang::tangSoLanDatSan()
{
    soLanDatSan++;
}

void KhachHang::capNhatHang()
{
    if (diemTichLuy >= 1000)
    {
        hang = HangKhachHang::KIM_CUONG;
    }
    else if (diemTichLuy >= 500)
    {
        hang = HangKhachHang::VANG;
    }
    else if (diemTichLuy >= 100)
    {
        hang = HangKhachHang::BAC;
    }
    else
    {
        hang = HangKhachHang::DONG;
    }
}

void KhachHang::hienThiThongTin() const
{
    std::cout << "===== KHACH HANG =====" << std::endl;
    ConNguoi::hienThiThongTin();
    std::cout << "Ma khach hang: " << maKhachHang << std::endl;
    std::cout << "Diem tich luy: " << diemTichLuy << std::endl;
    std::cout << "Hang thanh vien: " << layTenHang()
              << " (Giam " << layPhanTramGiamGia() << "%)" << std::endl;
    std::cout << "So lan dat san: " << soLanDatSan << std::endl;
}

bool KhachHang::ghiFile(std::ofstream &file) const
{
    if (!file.is_open())
        return false;

    // Ghi thông tin lớp cha
    if (!ConNguoi::ghiFile(file))
        return false;

    // Ghi thông tin lớp con
    if (!FileHelper::ghiString(file, maKhachHang))
        return false;
    file.write(reinterpret_cast<const char *>(&diemTichLuy), sizeof(diemTichLuy));

    int hangInt = static_cast<int>(hang);
    file.write(reinterpret_cast<const char *>(&hangInt), sizeof(hangInt));

    ngayDangKy.ghiFile(file);
    file.write(reinterpret_cast<const char *>(&soLanDatSan), sizeof(soLanDatSan));

    return file.good();
}

bool KhachHang::docFile(std::ifstream &file)
{
    if (!file.is_open())
        return false;

    // Đọc thông tin lớp cha
    if (!ConNguoi::docFile(file))
        return false;

    // Đọc thông tin lớp con
    if (!FileHelper::docString(file, maKhachHang))
        return false;
    file.read(reinterpret_cast<char *>(&diemTichLuy), sizeof(diemTichLuy));

    int hangInt;
    file.read(reinterpret_cast<char *>(&hangInt), sizeof(hangInt));
    hang = static_cast<HangKhachHang>(hangInt);

    ngayDangKy.docFile(file);
    file.read(reinterpret_cast<char *>(&soLanDatSan), sizeof(soLanDatSan));

    return file.good();
}

// ========== OPERATORS ==========

KhachHang &KhachHang::operator=(const KhachHang &other)
{
    if (this != &other)
    {
        ConNguoi::operator=(other);
        maKhachHang = other.maKhachHang;
        diemTichLuy = other.diemTichLuy;
        hang = other.hang;
        ngayDangKy = other.ngayDangKy;
        soLanDatSan = other.soLanDatSan;
    }
    return *this;
}

bool KhachHang::operator==(const KhachHang &other) const
{
    return maKhachHang == other.maKhachHang;
}

std::ostream &operator<<(std::ostream &os, const KhachHang &kh)
{
    os << static_cast<const ConNguoi &>(kh)
       << ", MaKH: " << kh.maKhachHang
       << ", Diem: " << kh.diemTichLuy
       << ", Hang: " << kh.layTenHang();
    return os;
}
