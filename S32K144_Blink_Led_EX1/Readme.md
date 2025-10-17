# BLINK LED PROJECT
## 1. CLOCK DISTRIBUTION
### 1.1 Tổng quan
    PLL (FIRC_CLK, SIRC_CLK, SPLL_CLK), SOSC_CLK, PMC clock signal (LPO128K_CLK) and Alternate sources
           │
           ▼  
    ┌──────────────┐
    │     SCG      │ → Tạo và quản lý clock của vi điều khiển (system clock) từ internal references, external crystals, and external clocks
                     → Chia nguồn xung ra thành nhiều miền xung nhịp (clock domains): system bus masters, system bus slaves, and flash memory.
    └──────────────┘
           │
           ▼
    ┌──────────────┐
    │     PCC      │  → Lựa chọn xung clock cho tất cả module
    └──────────────┘
           │
           ▼
    ┌──────────────┐
    │ Peripheral   │  → PORT, LSPI, LI2C..
    └──────────────┘

*  SYS_CLK và CORE_CLK phải được cấu hình lớn hơn BUS_CLK.
### 1.2 Các nguồn xung clock
SIRC – Slow Internal RC oscillator (Tiêu thụ điện năng thấp )

FIRC – Fast Internal RC oscillator (Clock chính mặc định sau khi RESET)

SOSC – System Oscillator ( Dùng thạch anh ngoài)

SPLL – System PLL (Phase Locked Loop) (Thạch anh nội nhân lên từ SIRC hoặc FIRC)
### 1.3 Các loại clock chính
| Clock     | Nguồn CLOCK  | Vai trò                |
| ----------|:------------:|:----------------------:|
| CORE_CLK  |PLL Hoặc SOSC | CLOCK cho CPU          |
| BUS_CLK   | CORE_CLK     | CLOCK cho ngoại vi     |
| FLASH_CLK | CORE_CLK     | CLOCK cho bộ nhớ FLASH |

### 1.4 INTERNAL CLOCKING REQUIREMENTS
| Clock             | HSRUN     | RUN       | VLPR  | NOTE                                                                                    |
| ------------------|:---------:|:---------:|:-----:|:---------------------------------------------------------------------------------------:|
| CORE_CLK/SYS_CLK  | 112 MHz    |80 MHz    |4 MHz  | Phải được cấu hình lớn hơn hoặc bằng BUS_CLK                                            |
| BUS_CLK           | 56 MHz     |48/40 MHz |4 MHz  | Phải là giá trị bằng CORE_CLK chia cho một số nguyên (1, 2, 3, 4, ...)                  |
| FLASH_CLK         | 28 MHz     |26,67 MHz |1 MHz  | Phải là giá trị bằng CORE_CLK chia cho một số nguyên, và tỷ lệ CORE_CLK / FLASH_CLK <=8 |

## 2. System Clock Generator (SCG)
### 2.1 Features
* Mỗi nguồn clock chính (SIRC, FIRC, SOSC, SPLL) trong SCG (System Clock Generator) có hai bộ chia đầu ra độc lập:

  * DIV1: Dùng cho System Clock domain (CORE/BUS/FLASH) hoặc làm nguồn cho các khối trong SCG

  * DIV2: Dùng làm nguồn clock cho các module ngoại vi thông qua PCC (Peripheral Clock Control)
   
### 2.2 Định nghĩa các thanh ghi
SCG_VERID: dùng để nhận diện phiên bản (version) của module SCG trong chip

SCG_PARAM: Cung cấp thông tin DIVSLOW, DIVBUS, DIVCORE, và nguồn CLOCK

SCG_CSR: Trạng thái hiện tại của SCG (nguồn đang chọn, tần số)

SCG_RCCR:	Cấu hình clock cho chế độ RUN

SCG_VCCR:	Cấu hình clock cho chế độ VLPR

SCG_HCCR:	Cấu hình clock cho chế độ HSRUN

SCG_SIRCCFG, SCG_FIRCCFG, SCG_SOSCCFG, SCG_SPLLCFG:	Cấu hình từng nguồn clock

SCG_SIRCDIV, SCG_FIRCDIV, SCG_SOSCDIV, SCG_SPLLDIV:	Thiết lập hệ số chia DIV1/DIV2 cho từng nguồn



### 1.4 INTERNAL CLOCKING REQUIREMENTS
| Clock             | HSRUN     | RUN       | VLPR  | NOTE                                                                                    |
| ------------------|:---------:|:---------:|:-----:|:---------------------------------------------------------------------------------------:|
| CORE_CLK/SYS_CLK  | 112 MHz    |80 MHz    |4 MHz  | Phải được cấu hình lớn hơn hoặc bằng BUS_CLK                                            |
| BUS_CLK           | 56 MHz     |48/40 MHz |4 MHz  | Phải là giá trị bằng CORE_CLK chia cho một số nguyên (1, 2, 3, 4, ...)                  |
| FLASH_CLK         | 28 MHz     |26,67 MHz |1 MHz  | Phải là giá trị bằng CORE_CLK chia cho một số nguyên, và tỷ lệ CORE_CLK / FLASH_CLK <=8 |



