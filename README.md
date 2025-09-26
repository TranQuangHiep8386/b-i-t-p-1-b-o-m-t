# b-i-t-p-1-b-o-m-t
bài tập bảo mật
TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
Caesar
Affine
Hoán vị
Vigenère
Playfair
# giải 
-Caesar
1) Caesar cipher

Tên gọi: Caesar (mã của Julius Caesar — dịch ký tự bằng dịch dịch vị trí trong bảng chữ cái)

Thuật toán (Giả sử chữ cái A–Z, modulo 26):

Khóa: k (số nguyên 0..25)

Mã hoá: C = (P + k) mod 26 với P là vị trí chữ cái gốc (A=0)

Giải mã: P = (C - k + 26) mod 26

Pseudocode

Encrypt: for mỗi ký tự ch nếu là chữ hoa: ((ch - 'A') + k) %26 + 'A'; nếu chữ thường tương tự.

Decrypt: dùng -k.

Không gian khóa: 26 (thực tế 25 hữu dụng vì k=0 là danh nghĩa)

Cách phá mã (không cần khóa):

Brute force: thử tất cả 26 giá trị k (rất nhỏ).

Phân tích tần suất: so sánh tần suất ký tự trong bản mã với tần suất tiếng mục tiêu (ví dụ E phổ biến).
<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/0621042d-3307-47f1-99b1-783f6b24d4ea" />
<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/d645e8f8-2ad0-442b-89d0-3a10416e5d24" />
-Affine
2) Affine cipher

Tên gọi: Affine (tổ hợp phép nhân và cộng trên modulo 26)

Thuật toán:

Khóa: cặp (a, b) với a coprime(26) (tức gcd(a,26)=1) và b trong 0..25.

Mã hoá: C = (a * P + b) mod 26

Giải mã: P = a_inv * (C - b) mod 26 với a_inv là nghịch đảo modulo 26 của a.

Không gian khóa: số a hợp lệ × 26 = φ(26) * 26 = 12 * 26 = 312 (vì φ(26)=12: các a là 1,3,5,7,9,11,15,17,19,21,23,25)

Cách phá mã (không cần khóa):

Brute force: thử mọi a hợp lệ và mọi b — 312 thử là nhỏ.

Phân tích tần suất hoặc dùng known-plaintext để suy ra a,b.
<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/420cd255-2e88-443b-93ad-b5adc8bf674c" />
<img width="2545" height="1439" alt="image" src="https://github.com/user-attachments/assets/cfc25b94-3df4-4d4c-8ae3-6ae4f869e14f" />
-Hoán vị
3) Hoán vị / Transposition cipher (ví dụ: Columnar transposition)

Tên gọi: Hoán vị (Transposition) — không thay đổi ký tự, chỉ đổi vị trí.

Thuật toán (Columnar transposition cơ bản):

Khóa: một hoán vị cột (ví dụ một từ khoá KEY = "ZEBRA" → gán số theo thứ tự chữ cái: E=1, A=0...).

Mã hoá:

Viết bản rõ theo hàng vào ma trận có số cột = chiều dài khóa.

Đọc các cột theo thứ tự khóa (sắp chữ theo thứ tự tăng của ký tự trong khóa).

Giải mã: biết thứ tự cột, điền kích thước cột theo chiều dài bản mã và đọc theo hàng.

Không gian khóa: số hoán vị của n cột = n! (với n = độ dài khóa). Ví dụ n=6 → 720.

Cách phá mã (không cần khóa):

Brute force (n! lớn nhanh nên chỉ khả dụng với n nhỏ).

Phân tích mẫu từ (bigrams/trigrams) và kiểm tra tính hợp lý của tiếng tự nhiên.

Kết hợp hill-climbing / simulated annealing để tìm hoán vị tốt nhất (phổ biến trong cryptanalysis cổ điển).
<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/57e418c7-5fb0-4fb7-909f-109757fdfd65" />
<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/0769cd92-c760-434b-8b3d-626b06a9a194" />
-Vigenère
4) Vigenère cipher

Tên gọi: Vigenère (polyalphabetic substitution dùng chuỗi khóa lặp)

Thuật toán:

Khóa: chuỗi K độ dài m. Với vị trí i, shift = K[i mod m].

Mã hoá: C_i = (P_i + K_{i mod m}) mod 26.

Giải mã: P_i = (C_i - K_{i mod m} + 26) mod 26.

Không gian khóa: 26^m (với m là độ dài khóa; rất lớn khi m lớn)

Cách phá mã (không cần khóa):

Kasiski examination: tìm khoảng cách giữa các pattern lặp để ước đoán độ dài khóa m.

Phân tích khoảng cách và dùng phân tích tần suất trên mỗi "chuỗi" tương ứng vị trí trong khóa (chiến lược phân tách theo modulo m).

Friedman test (index of coincidence) để ước lượng độ dài khóa.
<img width="2559" height="1439" alt="image" src="https://github.com/user-attachments/assets/347f28b5-989b-4a94-a2f8-ae34ff05ff12" />
<img width="2559" height="1439" alt="image" src="https://github.com/user-attachments/assets/4de4b8fd-2ad6-406e-935e-b6c8732fcb7f" />
-Playfair
5) Playfair cipher

Tên gọi: Playfair (mã hóa cặp ký tự bằng ma trận 5×5)

Thuật toán:

Khóa: chuỗi tạo ma trận 5×5 (thường J cùng I, loại bỏ chữ trùng)

Bước chuẩn bị bản rõ: tách thành digraphs (cặp). Nếu hai ký tự giống nhau thêm filler (thường 'X'), nếu lẻ thêm 'X'.

Mã hoá mỗi digraph (pair) (A,B) theo luật:

Nếu A và B cùng hàng: thay bằng chữ bên phải của từng ký tự (wrap-around).

Nếu cùng cột: thay bằng chữ dưới mỗi ký tự (wrap-around).

Nếu khác hàng và cột: thay bằng chữ cùng hàng của A và cột của B, và ngược lại (hình chữ nhật).

Giải mã: áp dụng quy tắc ngược (trái / trên / hình chữ nhật tương tự).

Không gian khóa: chuỗi khóa có thể là bất kỳ -> số khả dĩ ≈ 25! (rất lớn), nhưng thường khóa là một từ/phrase giới hạn.

Cách phá mã (không cần khóa):

Brute force không khả thi trực tiếp.

Kỹ thuật phân tích digraph frequency (thống kê tần suất digrams), heuristics và phương pháp hill-climbing để tối ưu hoá bảng 5×5 sao cho bản giải có nhiều từ vựng hợp lý.

Dùng known-plaintext hoặc crib giúp giảm không gian.
<img width="2559" height="1439" alt="image" src="https://github.com/user-attachments/assets/8c6a0155-63ae-4121-a892-9a98d1186154" />
<img width="2559" height="1439" alt="image" src="https://github.com/user-attachments/assets/4d9bab56-5e52-4e0e-819d-f6df8762ea54" />
