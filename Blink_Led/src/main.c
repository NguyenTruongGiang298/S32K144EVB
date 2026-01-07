#include "S32K144.h"

#include <stdio.h>

#define PTD0 0 		/* BLUE  */
#define PTD15 15 	/* RED 	 */
#define PTD16 16 	/* GREEN */
int counter=0;
void SOSCInit_8Mhz(void)
{
	IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
	IP_SCG->SOSCCFG = SCG_SOSCCFG_EREFS(1) | SCG_SOSCCFG_HGO(0) | SCG_SOSCCFG_RANGE(2);
	while(IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);
	IP_SCG->SOSCCSR = 0x00000001;
	while(((IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)>> SCG_SOSCCSR_SOSCVLD_SHIFT)!=1){}
}
void SPLLInit_160Mhz(void)
{
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
	IP_SCG->SPLLCSR = 0x00000000;
	IP_SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(2) | SCG_SPLLDIV_SPLLDIV2(3);
	IP_SCG->SPLLCFG = SCG_SPLLCFG_MULT(24) | SCG_SPLLCFG_PREDIV(0);
	/* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
    /* MULT=24:  Multiply SPLL by 40 */
    /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK) >> SCG_SPLLCSR_LK_SHIFT)==1);
	IP_SCG->SPLLCSR = 0x00000001;
	while(((IP_SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)>> SCG_SPLLCSR_SPLLVLD_SHIFT)!=1){}
}
void SetNormalRUNMode_80MHz(void)
{
	IP_SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(2) | SCG_RCCR_DIVSLOW(3);
	while((( IP_SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) !=6){}
}
void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3000; j++);
}

void PORTInit(void)
{
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC(1);
	IP_PORTD->PCR[0]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[15]= PORT_PCR_MUX(1);
	IP_PORTD->PCR[16]= PORT_PCR_MUX(1);
	IP_PTD->PDDR |= (1<<PTD0 | 1<<PTD15 | 1<<PTD16);
}


int main(void) {
    SOSCInit_8Mhz();
    SPLLInit_160Mhz();
    SetNormalRUNMode_80MHz();
    PORTInit();
    while(1){

    		IP_PTD -> PTOR |= (1<<PTD15);
    		delay_ms(3000);

    		IP_PTD -> PTOR |= (1<<PTD16);
    		delay_ms(3000);

    		IP_PTD -> PTOR |= (1<<PTD0);
    		delay_ms(3000);
            counter++;
    	}

    return 0;
}
