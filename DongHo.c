#include <16f877A.h>
#Fuses hs
#use delay(clock=20M)

#define START_BUTTON PIN_A0
#define RB 0x06

unsigned int8 ma7doan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
signed int32 ptgiay, giay;
// signed int32 ptgiay, giay, i;
boolean isCounting = FALSE;

#INT_EXT
void EXT_isr(void)
{
    isCounting = FALSE;
}

void hienthi()
{
    output_d(ma7doan[giay / 10]);
    output_low(pin_b3);
    delay_ms(2);
    output_high(pin_b3);

    output_d(ma7doan[giay % 10]);
    output_low(pin_b4);
    delay_ms(2);
    output_high(pin_b4);

    output_d(ma7doan[ptgiay / 10]);
    output_low(pin_b1);
    delay_ms(2);
    output_high(pin_b1);

    output_d(ma7doan[ptgiay % 10]);
    output_low(pin_b2);
    delay_ms(2);
    output_high(pin_b2);
    delay_ms(2);
}

// void nhap_nhay()
// {
//    for (i = 0; i < 2; i++)   // 8ms
//    {
//        hienthi();
//    }
// }

void nn_on()
{
   if(input(START_BUTTON)==0)  
   {
      isCounting = TRUE; // B?t bi?n d?m
   }
}

void main()
{
    enable_interrupts(INT_EXT);
    enable_interrupts(GLOBAL);
    
    set_tris_a(0xFF); // Cài d?t PORTA là input
    set_tris_c(0x00); // Cài d?t PORTC là output
    set_tris_d(0x00); // Cài d?t PORTD là output

    ptgiay = 0;
    giay = 0;

    while (true)
    {    
        nn_on(); // Ki?m tra tr?ng thái c?a nút b?t d?u
        
        if (isCounting) // N?u dang d?m, th?c hi?n d?m và hi?n th?
        {   
            if (ptgiay > 99)
            {   
                giay++;
                ptgiay = 0;
                if (giay > 99)
                {
                    giay = 0;
                }
            }
            hienthi();
            // nhap_nhay();
            ptgiay++;
        }
        else 
        {
            hienthi();
        }
    }
}

