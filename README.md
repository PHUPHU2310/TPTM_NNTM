# TPTM_NNTM
Giới thiệu chung về sản phẩm

Hệ thống Cảnh Báo Đột Nhập Thông Minh là một giải pháp an ninh dành cho nhà ở sử dụng vi điều khiển ESP32. Khi có chuyển động (PIR) hoặc cửa mở trái phép (cảm biến từ cửa), hệ thống sẽ:

- Kích hoạt còi hú và đèn LED cảnh báo.
- Gửi lệnh đến ESP32-CAM để chụp ảnh hiện trường.
- Hiển thị thông báo trạng thái trên Serial Monitor.
- Có thể mở rộng gửi ảnh lên Telegram hoặc lưu trữ.

Sơ đồ hệ thống và chức năng
ESP32 WiFi:
- Đọc tín hiệu từ PIR và cảm biến từ cửa.
- Điều khiển còi và đèn.
- Gửi lệnh UART sang ESP32-CAM khi có sự kiện.

ESP32-CAM:
Nhận lệnh UART từ ESP32 WiFi.
Chụp ảnh và xử lý (gửi lên Telegram hoặc lưu thẻ nhớ).

Cảm biến:
PIR: Phát hiện chuyển động người.
Reed Switch: Phát hiện cửa mở.

Công nghệ, kỹ thuật sử dụng

- Vi điều khiển: ESP32 WiFi + ESP32-CAM
- Giao tiếp: UART (Serial)
- Phần mềm: Arduino IDE, PlatformIO
- Driver CH340 và CP2102 để kết nối máy tính
- Thiết kế mạch trên breadboard với nguồn 5V DC




![hẹ thống](https://github.com/user-attachments/assets/fcfc1f53-8395-4a8b-91f2-6c38cd27ab79)


![arduino](https://github.com/user-attachments/assets/c593b7ae-bd1b-46cf-9331-934bfc9da689)
