# Linux-Embedded
[1. Build Image](#1-Build-Image)
[7. Kernel Module](#7-Kernel-Module)
# 1. Build Image
## Tools chain
  Tools chain gồm các thư viện gcc, GDB, ... thư viện glibc

## uboot
  Uboot là chương trình vđk, chạy trước hệ điều hành


# 7. Kernel Module
Các bước viết kernel module (Demo GPIO output)
Bước 1: Enalble 1 chân mà mode GPIO Output: 
*(0x44E07000 + 0x134) |= (1 << 31)
Bước 2: Set giá trị cho chân: 
*(0x44E07000 + 0x194) |= (1 << 31)
Bước 3: Cleer giá trị cho chân 

ioremap:
- Khác với code vđk thì dùng địa chỉ vật lí trực tiếp nhưng Linux không được dùng trực tiếp mà phải thông qua Vitrual Memory.
- Phải xin cấp phát địa chỉ vật lý muốn truy cập và thao tác độc, ghi trên địa chỉ đó.

ioremap__:
- Chỉ thị tiềnm xử lý trong C
- Báo hiệu trình biên dịch khi các câu lệnh đọc, ghi bộ với vào con trỏ iomem. Để không bị sử dụng sai mục đích.

Cùng là lập trình cho 1 chân GPIO có 2 cách
- Cách 1 thao tác trực tiếp lên thanh ghi của module GPIO
  => Platform Driver
- Cách 2 là dùng qua API của kernel
  => Device Driver (Khi dùng Device Driver thì bản chất là gọi Platform Driver)


 





