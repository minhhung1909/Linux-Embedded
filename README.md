# Linux-Embedded
[1. Build Image](#1-BUILD-IMAGE)

[5. Shared Memory](#5.-SHARED-MEMORY)

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

# 5. SHARED MEMORY
## Vitrual Memory
- Trong một hệ điều hành hiện đại như Linux, nhiều chương trình (process) có thể chạy song song. Để đảm bảo mỗi tiến trình hoạt động một cách độc lập và an toàn, hệ điều hành sử dụng bộ nhớ ảo (virtual memory).

- Bộ nhớ ảo cho phép mỗi tiến trình "nhìn thấy" một không gian địa chỉ riêng biệt (virtual address space), ngay cả khi tất cả tiến trình thực sự dùng chung RAM vật lý (physical memory).

- Khi một tiến trình truy cập đến một địa chỉ ảo, hệ điều hành và phần cứng (MMU – Memory Management Unit) sẽ chuyển đổi địa chỉ ảo thành địa chỉ vật lý thông qua bảng trang (page table).

Cơ chế này giúp:

- Cô lập bộ nhớ giữa các tiến trình → tránh tình trạng tiến trình này ghi đè vùng nhớ của tiến trình khác.

- Chia sẻ tài nguyên hiệu quả thông qua các kỹ thuật như Copy-on-Write hoặc Shared Memory.

- Hỗ trợ swap (trang bộ nhớ có thể bị lưu tạm ra đĩa để giải phóng RAM).

## Shared Memory trong IPC (Inter-Process Communication)
Là một phương pháp để hai hoặc nhiều tiến trình có thể truy cập chung một vùng nhớ vật lý – giúp trao đổi dữ liệu nhanh chóng mà không cần gọi hàm kernel nhiều lần như pipe hay socket.

Các bước:
- Bước 1: Tạo file định danh

```int fd = shm_open (name, O_CREAT | O_RDWR, 0666)```



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
