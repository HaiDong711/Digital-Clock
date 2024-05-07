#include <16f887.h>
#Fuses hs
#use delay(clock=20M)

#define START_BUTTON PIN_A0
#define STOP_BUTTON  PIN_A1

unsigned int8 ma7doan[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
signed int32 giay, phut, i;
boolean isCounting = FALSE;

void hienthi()
{
    output_d(ma7doan[phut / 10]);
    output_low(pin_c3);
    delay_ms(1);
    output_high(pin_c3);

    output_d(ma7doan[phut % 10]);
    output_low(pin_c2);
    delay_ms(1);
    output_high(pin_c2);

    output_d(ma7doan[giay / 10]);
    output_low(pin_c1);
    delay_ms(1);
    output_high(pin_c1);

    output_d(ma7doan[giay % 10]);
    output_low(pin_c0);
    delay_ms(1);
    output_high(pin_c0);
}

void nhap_nhay()
{
    for (i = 0; i < 125; i++) //for tuong ?ng 0,5s
    {
        hienthi();
    }

    for (i = 0; i < 125; i++) //for tuong ?ng 0,5s
    {
        hienthi();
    }
}

void nn_on()
{
   if(input(START_BUTTON)==0)  
   {
      isCounting = TRUE; // B?t bi?n d?m
   }
}

void nn_off()
{
   if(input(STOP_BUTTON)==0 && isCounting)  
   {
      isCounting = FALSE; // T?t bi?n d?m
   }
}

void main()
{
    set_tris_a(0xFF); // C�i d?t PORTA l� input
    set_tris_c(0x00); // C�i d?t PORTC l� output
    set_tris_d(0x00); // C�i d?t PORTD l� output

    giay = 0;
    phut = 0;

    while (true)
    {    
        nn_on(); // Ki?m tra tr?ng th�i c?a n�t b?t d?u
        nn_off(); // Ki?m tra tr?ng th�i c?a n�t d?ng

        if (isCounting) // N?u dang d?m, th?c hi?n d?m v� hi?n th?
        {   
            giay++;
            nhap_nhay(); // C?p nh?t hi?n th? sau m?i gi�y
            if (giay > 58)
            {   
                phut++;
                giay = 0;
                if (phut > 58)
                {
                    phut = 0;
                }
            }
        }
        else 
        {
        
            hienthi();
            
        }
    }
}

