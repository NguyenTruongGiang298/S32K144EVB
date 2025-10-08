# So sánh kiến trúc CISC và RISC
## 1.1. Giới thiệu khái niệm cơ bản về CISC (Complex Instruction Set Computer) và RISC (Reduced Instruction Set Computer).
* CISC:
Kiến trúc CISC bao gồm một bộ mạch chuyên dụng đầy đủ để thực hiện các lệnh này với tốc độ rất cao. Những bộ xử lý này cung cấp cho người dùng hàng trăm lệnh có độ dài thay đổi. Các lệnh này tương tác với bộ nhớ bằng cách sử dụng các chế độ địa chỉ hóa phức tạp. Kiến trúc CISC giúp giảm kích thước chương trình, do đó cần ít chu kỳ bộ nhớ hơn để thực thi chương trình. Việc này tăng tốc độ thực thi tổng thể.
* RISC:
Đây là một loại kiến trúc vi xử lý sử dụng một tập lệnh nhỏ có độ dài đồng đều. Những lệnh đơn giản và thường được thực thi trong một chu kỳ xung nhịp. Vi điều khiển có kiểu kiến trúc RISC tương đối đơn giản để thiết kế và giá thành thấp. Hạn chế của thiết kế này là máy tính phải lặp lại các thao tác đơn giản nhiều lần để thực hiện một chương trình lớn có nhiều phép xử lý phức tạp.
  
## 1.2. Trình bày ưu điểm và nhược điểm của từng loại kiến trúc.
### 1.2.1. CISC
* Ưu điểm
  * Kích thước mã nhỏ hơn: Bộ xử lý CISC có thể thực hiện các phép toán phức tạp với một lệnh duy nhất, thường dẫn đến mã gọn hơn và giảm mức sử dụng bộ nhớ.
  * Tập lệnh phong phú: Bộ tập lệnh đa dạng với các lệnh phức tạp có thể làm cho việc lập trình trở nên dễ dàng và trực quan hơn cho một số tác vụ, đặc biệt trong ngôn ngữ hợp ngữ.
  * Tương thích ngược: Kiến trúc CISC, như x86, thường duy trì khả năng tương thích với phần mềm cũ, giúp việc nâng cấp hệ thống dễ dàng hơn cho người dùng và doanh nghiệp.
* Nhược điểm
  * Tốc độ thực thi chậm hơn: Các lệnh phức tạp thường mất nhiều thời gian hơn để thực hiện, có thể dẫn đến hiệu suất tổng thể chậm hơn so với bộ xử lý RISC.
  * Tiêu thụ điện năng cao hơn: Phần cứng phức tạp hơn của bộ xử lý CISC thường dẫn đến mức tiêu thụ điện năng cao hơn, làm cho chúng kém phù hợp với các thiết bị di động.
  * Thiết kế phần cứng phức tạp hơn: Bộ xử lý CISC cần mạch điện phức tạp hơn để xử lý nhiều loại lệnh, điều này khiến việc thiết kế và chế tạo trở nên khó khăn và tốn kém hơn.
### 1.2.2. RISC
* Ưu điểm
  * Tốc độ thực thi nhanh hơn: Bộ xử lý RISC sử dụng các lệnh đơn giản có thể được thực thi nhanh hơn, dẫn đến hiệu suất tổng thể được cải thiện trong nhiều tác vụ.
  * Tiêu thụ điện năng thấp hơn: Thiết kế đơn giản của bộ xử lý RISC thường dẫn đến mức tiêu thụ điện năng thấp hơn, khiến chúng trở nên lý tưởng cho các thiết bị di động và máy tính tiết kiệm năng lượng.
  * Dễ thiết kế và sản xuất: Bộ xử lý RISC có kiến trúc đơn giản, điều này có thể khiến chúng dễ và có tiềm năng rẻ hơn trong việc thiết kế và chế tạo.
* Nhược điểm
  * Kích thước mã lớn hơn: Bộ xử lý RISC thường cần nhiều dòng mã hơn để thực hiện các tác vụ phức tạp, điều này có thể dẫn đến chương trình có kích thước lớn hơn và tăng mức sử dụng bộ nhớ.
  * Trình biên dịch phải làm nhiều việc hơn: Tập lệnh đơn giản đồng nghĩa với việc trình biên dịch cho bộ xử lý RISC cần làm nhiều công việc hơn để chuyển ngôn ngữ lập trình cấp cao thành mã máy.
  * Chức năng tích hợp bị giới hạn: Bộ xử lý RISC có ít lệnh phức tạp hơn được tích hợp trong phần cứng, điều này có thể làm cho một số tác vụ chuyên biệt kém hiệu quả nếu không có sự hỗ trợ thêm từ phần mềm.
## 1.3. So sánh CISC và RISC theo các tiêu chí
### 1.3.1. Cấu trúc tập lệnh

### 1.3.2. Tốc độ xử lý
- Tốc độ xử lý của hệ thống có kiến trúc RISC nhanh hơn hệ thống sử dụng kiến trúc CISC
- CISC cố gắng giảm thiểu số lượng lệnh trong mỗi chương trình, nhưng phải đánh đổi bằng việc tăng số chu kỳ cần để thực thi mỗi lệnh. Trong khi đó Bộ xử lý RISC sử dụng các lệnh đơn giản có thể được thực thi nhanh hơn, dẫn đến hiệu suất tổng thể được cải thiện trong nhiều tác vụ.
### 1.3.3. Kích thước chương trình
- kiến trúc CISC sử dụng ít bộ nhớ hơn, vì mỗi lệnh rất phức tạp và có thể thực hiện nhiều thao tác trong một lệnh duy nhất. Điều đó dẫn đến một lệnh CISC có thể thay thế nhiều lệnh RISC đơn giản. Kết quả Mã nguồn ngắn hơn, File chương trình nhỏ hơn và tốn ít bộ nhớ hơn.
### 1.3.4. Độ phức tạp phần cứng
- Phần cứng thiết bị sử dụng kiến trúc CISC sẽ phức tạp hơn nhiều so với thiết bị sở hữu kiến trúc RISC. Bởi vì những bộ xử lý này cung cấp cho người dùng hàng trăm lệnh có độ dài khác nhau, các lệnh này tương tác với bộ nhớ bằng cách sử dụng các chế độ địa chỉ hóa phức tạp, và thực hiện nhiều tác vụ phức tạp trong 1 lệnh. Trong khi đó, kiến trúc RISC lại dùng những câu lệnh đơn giản nên phần cứng sẽ có ít độ phức tạp hơn.
### 1.3.5. Ứng dụng thực tế (ví dụ: Intel, ARM, v.v.)
* Kiến trúc CISC được sử dụng trong trong kiến trúc Intel hay AMD.
* Kiến trúc RISC được sử dụng trong trong SPARC (Scalable Processor Architecture), ARM Cortex-M, RISC-V
## 1.4. Trong bối cảnh phát triển hệ thống nhúng hiện nay, kiến trúc nào phù hợp hơn? Vì sao?
- Kiến trúc RISC phù hợp hơn cho hệ thống nhúng hiện nay, vì:
1. Tiêu thụ điện năng thấp: Hệ thống nhúng (như thiết bị IoT, cảm biến, thiết bị y tế, thiết bị di động…) rất nhạy cảm với điện năng do thường chạy bằng pin hoặc nguồn năng lượng giới hạn. Kiến trúc RISC có thiết kế đơn giản, nên tiêu thụ điện năng ít hơn so với CISC.
2. Hiệu suất cao trên các tác vụ đơn giản: Trong hệ thống nhúng, các tác vụ thường đơn giản, có thể lặp đi lặp lại (đọc cảm biến, điều khiển thiết bị, xử lý dữ liệu cơ bản…). Các lệnh RISC đơn giản và thực hiện trong một chu kỳ xung nhịp nên có tốc độ xử lý nhanh và sẽ làm tăng hiệu suất.
3. Chi phí và kích thước phần cứng thấp: RISC có thiết kế phần cứng đơn giản, giá thành rẽ hơn nên dễ tích hợp trên các vi điều khiển.
