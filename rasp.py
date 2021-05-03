import spidev
from time import sleep

# spi master mode configuration
spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz = 1000000

#function send a character to MSP430
def write_pot(input):
    msb = input >> 8
    lsb = input & 0xFF
    spi.xfer([msb,lsb])
    
write_pot(0x31);
