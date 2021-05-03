#include <msp430.h> 

void init_time()
{
    if (CALBC1_1MHZ == 0xFF)
    {
        while(1);
    }
    DCOCTL  = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void init_spi()
{
    __delay_cycles(250);

    P1SEL |= (BIT5 | BIT6 | BIT7);
    P1SEL2 |= (BIT5 + BIT6 + BIT7);

    UCB0CTL1 |= UCSWRST;

    UCB0CTL0 |= (UCMODE_0 | UCSYNC |UCMSB);
    UCB0CTL0 &= ~(UCCKPH | UCCKPL | UC7BIT | UCMST);
    UCB0CTL1 |= UCSSEL_2;

    UCB0CTL1 &= ~UCSWRST;
    IE2 |= UCB0RXIE;
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    init_time();
    init_spi();
    P1DIR |= BIT0;
    P1OUT |= BIT0;
    __enable_interrupt();
}


#pragma vector = USCIAB0RX_VECTOR
__interrupt void receive(void){
    if(UCB0RXBUF == 0x31)
    {
        P1OUT ^= BIT0;
    }
    else
    {
        UCB0TXBUF = UCB0RXBUF;
        P1OUT &= ~BIT0;
    }
}
