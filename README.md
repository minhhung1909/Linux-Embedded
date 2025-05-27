# Linux-Embedded
[1. Build Image](#1-BUILD-IMAGE)

[2. Shocket](#-SHOCKET)

[7. Kernel Module](#7-KERNEL-MODULE)

# 1. BUILD IMAGE
## Tools chain
  Tools chain gồm các thư viện gcc, GDB, ... thư viện glibc

## uboot
  - Uboot là chương trình vđk, chạy trước hệ điều hành, làm nhiệu vụ load hệ điều hành.
  - Uboot phổ biến với kiến trúc ARM(Embedded thường chạy arm). Uboot được phát triển bởi Cty denx. Các hãng thì sẽ có các bản Patch chứa phần support cho riêng phân cứng của mình.
  - Đối với x86 là kiến trức Grub.
  - Quá trình build uboot image gcc sẽ dùng file cấu hình .config (Makefile sẽ quyết định). File .config thì được generate từ am335x_evm_defconfig.
  - Nếu muốn enable thêm 1 option nào đấy ngoài Default: make menuconfig -> enable option cần.
  - Sau quá trình biên dịch sẽ có file u-boot-dbt.img => đây chính là file uboot cần nạp vào sdcard.

## Build Kernel
```./build_kernel.sh```
Dùng để build kernel nhưng lúc chạy dòng lệnh này sẽ vừa build vừa tải về

# 5. SHOCKET



# 7. KERNEL MODULE
Các bước viết kernel module (Demo GPIO output)

Bước 1: Enalble 1 chân mà mode GPIO Output: 

`*(0x44E07000 + 0x134) |= (1 << 31)`

Bước 2: Set giá trị cho chân: 

`*(0x44E07000 + 0x194) |= (1 << 31)`

Bước 3: Clear giá trị cho chân 

Function: `ioremap()`:
- Khác với code vđk thì dùng địa chỉ vật lí trực tiếp nhưng Linux không được dùng trực tiếp mà phải thông qua Vitrual Memory.
- Phải xin cấp phát địa chỉ vật lý muốn truy cập và thao tác độc, ghi trên địa chỉ đó.

Macro: `__ioremap`
- Chỉ thị tiềnm xử lý trong C
- Báo hiệu trình biên dịch khi các câu lệnh đọc, ghi bộ với vào con trỏ iomem. Để không bị sử dụng sai mục đích.

Cùng là lập trình cho 1 chân GPIO có 2 cách
- Cách 1 thao tác trực tiếp lên thanh ghi của module GPIO.

    => Platform Driver
- Cách 2 là dùng qua API của kernel.

    => Device Driver (Khi dùng Device Driver thì bản chất là gọi Platform Driver)