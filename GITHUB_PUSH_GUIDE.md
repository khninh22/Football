# Hướng dẫn Push lên GitHub

## ⚠️ Lỗi Permission

Bạn đang gặp lỗi:

```
remote: Permission to khninh22/Football.git denied to LVTIT.
fatal: unable to access 'https://github.com/khninh22/Football.git/': The requested URL returned error: 403
```

Nguyên nhân: Git đang sử dụng credential của user `LVTIT` thay vì `khninh22`.

---

## 🔑 Giải pháp: Sử dụng Personal Access Token (PAT)

### Bước 1: Tạo Personal Access Token

1. Đăng nhập GitHub: https://github.com
2. Click vào **Avatar (góc phải)** → **Settings**
3. Kéo xuống dưới, click **Developer settings** (menu trái)
4. Click **Personal access tokens** → **Tokens (classic)**
5. Click **Generate new token** → **Generate new token (classic)**
6. Điền thông tin:
   - **Note**: `FootballFieldManager`
   - **Expiration**: `90 days` (hoặc No expiration)
   - **Select scopes**: Chọn **`repo`** (full control of private repositories)
7. Click **Generate token**
8. **Copy token** (chỉ hiển thị 1 lần!) → Lưu vào notepad

Token có dạng: `ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`

### Bước 2: Xóa credential cũ

```cmd
# Mở Command Prompt hoặc PowerShell
git config --global --unset credential.helper
```

### Bước 3: Push với token

#### Option 1: Push với URL có token (một lần)

```cmd
cd /d "d:\FootballFieldManager"
git remote remove origin
git remote add origin https://ghp_YOUR_TOKEN_HERE@github.com/khninh22/Football.git
git push -u origin main
```

Thay `ghp_YOUR_TOKEN_HERE` bằng token bạn vừa tạo.

#### Option 2: Push và lưu credential (khuyến nghị)

```cmd
cd /d "d:\FootballFieldManager"

# Enable credential storage
git config --global credential.helper wincred

# Push (sẽ hỏi username và password)
git push -u origin main
```

Khi được hỏi:

- **Username**: `khninh22`
- **Password**: `ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx` (paste token)

Lần sau sẽ không cần nhập lại.

---

## 🚀 Các lệnh Git cần thiết

### Kiểm tra remote

```cmd
git remote -v
```

### Kiểm tra branch

```cmd
git branch -a
```

### Kiểm tra status

```cmd
git status
```

### Push code lên GitHub

```cmd
git push -u origin main
```

### Pull code từ GitHub

```cmd
git pull origin main
```

### Xem commit history

```cmd
git log --oneline
```

---

## 📦 Workflow sau khi push thành công

### 1. Commit thay đổi mới

```cmd
git add .
git commit -m "Your commit message"
git push
```

### 2. Tạo branch mới

```cmd
git checkout -b feature/new-feature
# Make changes
git add .
git commit -m "Add new feature"
git push -u origin feature/new-feature
```

### 3. Merge branch

```cmd
git checkout main
git merge feature/new-feature
git push
```

---

## 🔧 Troubleshooting

### Lỗi: Authentication failed

**Nguyên nhân:** Token sai hoặc hết hạn

**Giải pháp:**

1. Tạo token mới
2. Xóa credential cũ:
   ```cmd
   git config --global --unset credential.helper
   ```
3. Push lại

### Lỗi: Repository not found

**Nguyên nhân:** URL sai hoặc repo chưa được tạo

**Giải pháp:**

1. Kiểm tra repo đã tồn tại: https://github.com/khninh22/Football
2. Kiểm tra URL:
   ```cmd
   git remote -v
   ```
3. Sửa URL nếu sai:
   ```cmd
   git remote set-url origin https://github.com/khninh22/Football.git
   ```

### Lỗi: Push rejected

**Nguyên nhân:** Remote có commit mà local chưa có

**Giải pháp:**

```cmd
git pull --rebase origin main
git push
```

---

## 📝 Lệnh Push đầy đủ (Copy & Paste)

```cmd
# 1. Di chuyển vào thư mục dự án
cd /d "d:\FootballFieldManager"

# 2. Xóa remote cũ (nếu có lỗi)
git remote remove origin

# 3. Thêm remote mới với token
git remote add origin https://ghp_YOUR_TOKEN_HERE@github.com/khninh22/Football.git

# 4. Kiểm tra
git remote -v

# 5. Push lên GitHub
git push -u origin main

# 6. Xác nhận thành công
git status
```

**Thay `ghp_YOUR_TOKEN_HERE` bằng token bạn vừa tạo từ GitHub!**

---

## ✅ Sau khi push thành công

Truy cập: **https://github.com/khninh22/Football**

Bạn sẽ thấy:

- ✅ 137 files
- ✅ README.md hiển thị đẹp
- ✅ Code đầy đủ trong các folder Core/, UI/, Docs/
- ✅ Có thể clone về máy khác

---

## 🎉 Chúc mừng!

Dự án của bạn đã được đẩy lên GitHub thành công! 🚀

**Next steps:**

- Thêm LICENSE file
- Thêm screenshots vào README
- Tạo GitHub Actions để auto-build
- Mời collaborators
- Tạo Issues và Projects để quản lý task

---

**Ngày tạo:** 06/11/2025  
**Người tạo:** Football Field Manager Team
