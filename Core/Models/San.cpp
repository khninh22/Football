/**
 * @file San.cpp
 * @brief Implementation của lớp San
 */

#include "San.h"
#include "../Utils/FileHelper.h"

using namespace std;

// ========== CONSTRUCTORS ==========

San::San()
    : maSan(""), tenSan(""), loaiSan(LoaiSan::SAN_5),
      giaThueGio(0.0), trangThai(TrangThaiSan::TRONG), ghiChu("")
{
}

San::San(const std::string &maSan, const std::string &tenSan,
         LoaiSan loaiSan, double giaThue)
    : maSan(maSan), tenSan(tenSan), loaiSan(loaiSan),
      giaThueGio(giaThue), trangThai(TrangThaiSan::TRONG), ghiChu("")
{
}

San::San(const San &other)
    : maSan(other.maSan), tenSan(other.tenSan), loaiSan(other.loaiSan),
      giaThueGio(other.giaThueGio), trangThai(other.trangThai),
      ghiChu(other.ghiChu)
{
}

San::~San()
{
    // Destructor
}

// ========== GETTERS ==========

std::string San::layMaSan() const
{
    return maSan;
}

std::string San::layTenSan() const
{
    return tenSan;
}

LoaiSan San::layLoaiSan() const
{
    return loaiSan;
}

double San::layGiaThueGio() const
{
    return giaThueGio;
}

TrangThaiSan San::layTrangThai() const
{
    return trangThai;
}

std::string San::layGhiChu() const
{
    return ghiChu;
}

std::string San::layTenLoaiSan() const
{
    switch (loaiSan)
    {
    case LoaiSan::SAN_5:
        return std::string("San 5 nguoi");
    case LoaiSan::SAN_7:
        return std::string("San 7 nguoi");
    case LoaiSan::SAN_11:
        return std::string("San 11 nguoi");
    default:
        return std::string("Khong xac dinh");
    }
}

std::string San::layTenTrangThai() const
{
    switch (trangThai)
    {
    case TrangThaiSan::TRONG:
        return std::string("Trong");
    case TrangThaiSan::DA_DAT:
        return std::string("Da dat");
    case TrangThaiSan::DANG_SU_DUNG:
        return std::string("Dang su dung");
    case TrangThaiSan::BAO_TRI:
        return std::string("Bao tri");
    default:
        return std::string("Khong xac dinh");
    }
}

// ========== SETTERS ==========

void San::datTenSan(const std::string &ten)
{
    tenSan = ten;
}

void San::datGiaThueGio(double gia)
{
    if (gia >= 0)
    {
        giaThueGio = gia;
    }
}

void San::datTrangThai(TrangThaiSan tt)
{
    trangThai = tt;
}

void San::datGhiChu(const std::string &gc)
{
    ghiChu = gc;
}

// ========== METHODS ==========

bool San::coTrong() const
{
    return trangThai == TrangThaiSan::TRONG;
}

double San::tinhTien(double soGio) const
{
    if (soGio <= 0)
        return 0.0;
    return giaThueGio * soGio;
}

void San::hienThiThongTin() const
{
    std::cout << "===== THONG TIN SAN =====" << std::endl;
    std::cout << "Ma san: " << maSan << std::endl;
    std::cout << "Ten san: " << tenSan << std::endl;
    std::cout << "Loai san: " << layTenLoaiSan() << std::endl;
    std::cout << "Gia thue: " << giaThueGio << " VND/gio" << std::endl;
    std::cout << "Trang thai: " << layTenTrangThai() << std::endl;
    if (ghiChu.length() > 0)
    {
        std::cout << "Ghi chu: " << ghiChu << std::endl;
    }
}

bool San::ghiFile(std::ofstream &file) const
{
    if (!file.is_open())
        return false;

    if (!FileHelper::ghiString(file, maSan))
        return false;
    if (!FileHelper::ghiString(file, tenSan))
        return false;

    int loaiSanInt = static_cast<int>(loaiSan);
    file.write(reinterpret_cast<const char *>(&loaiSanInt), sizeof(loaiSanInt));

    file.write(reinterpret_cast<const char *>(&giaThueGio), sizeof(giaThueGio));

    int trangThaiInt = static_cast<int>(trangThai);
    file.write(reinterpret_cast<const char *>(&trangThaiInt), sizeof(trangThaiInt));

    if (!FileHelper::ghiString(file, ghiChu))
        return false;

    return file.good();
}

bool San::docFile(std::ifstream &file)
{
    if (!file.is_open())
        return false;

    if (!FileHelper::docString(file, maSan))
        return false;
    if (!FileHelper::docString(file, tenSan))
        return false;

    int loaiSanInt;
    file.read(reinterpret_cast<char *>(&loaiSanInt), sizeof(loaiSanInt));
    loaiSan = static_cast<LoaiSan>(loaiSanInt);

    file.read(reinterpret_cast<char *>(&giaThueGio), sizeof(giaThueGio));

    int trangThaiInt;
    file.read(reinterpret_cast<char *>(&trangThaiInt), sizeof(trangThaiInt));
    trangThai = static_cast<TrangThaiSan>(trangThaiInt);

    if (!FileHelper::docString(file, ghiChu))
        return false;

    return file.good();
}

// ========== OPERATORS ==========

San &San::operator=(const San &other)
{
    if (this != &other)
    {
        maSan = other.maSan;
        tenSan = other.tenSan;
        loaiSan = other.loaiSan;
        giaThueGio = other.giaThueGio;
        trangThai = other.trangThai;
        ghiChu = other.ghiChu;
    }
    return *this;
}

bool San::operator==(const San &other) const
{
    return maSan == other.maSan;
}

bool San::operator<(const San &other) const
{
    return giaThueGio < other.giaThueGio;
}

std::ostream &operator<<(std::ostream &os, const San &s)
{
    os << "San " << s.maSan << ": " << s.tenSan
       << " (" << s.layTenLoaiSan() << ") - "
       << s.giaThueGio << " VND/gio - " << s.layTenTrangThai();
    return os;
}
