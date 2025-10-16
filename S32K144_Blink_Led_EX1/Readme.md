# BLINK LED PROJECT
## 1. MODULE PCC AND PORT PRERIPHERAL
FIRC_CLK, SIRC_CLK, SOSC_CLK, SPLL_CLK,PMC clock signal (LPO128K_CLK) and Alternate sources
  
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

*  SYS_CLK và CORE_CLK phải được cấu hình thấp hơn BUS_CLK.
##2. PHÂN LOẠI CÁC ĐƯỜNG XUNG CLOCK
