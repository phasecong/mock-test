#include "dev_utilities.h"

void dev_uti_show_electric_water(void)
{
	dev_lcd_clear();
	dev_lcd_goto_xy(1,0);
	dev_lcd_send_string(ELEC);
	dev_lcd_goto_xy(2,0);
	dev_lcd_send_string(WATER);
	dev_lcd_goto_xy(1,10);
}

void dev_uti_make_confirmation(void){
	dev_lcd_clear();
	dev_lcd_goto_xy(1,0);
	dev_lcd_send_string("Send it to ESP?");
	dev_lcd_goto_xy(2,0);
	dev_lcd_send_string("A: YES   B: NO");
}

void dev_uti_string_copy(unsigned char *a, unsigned char *b){
	int i=0,j=0;
	while (b[j])
	{
		a[i++]=b[j++];
	}
}

void dev_uti_blink(void)
{
    GPIO_InitTypeDef        GPIO_InitStructure_blink;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure_blink.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_blink.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure_blink.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure_blink);
    
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    dev_systick_delay(100);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    dev_systick_delay(100);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    dev_systick_delay(100);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    dev_systick_delay(100);
}
