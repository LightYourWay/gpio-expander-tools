#include "mcp23xxx.h"

mcp23xxx::mcp23xxx(spi_api* spi_handle) : spiHandle(*spi_handle) {}

void mcp23xxx::writeRegister(uint8_t register_addr, uint8_t data)
{
    spiHandle.start();
    spiHandle.sendByte(0b01000000);
    spiHandle.sendByte(register_addr);
    spiHandle.sendByte(data);
    spiHandle.stop();
}

uint8_t mcp23xxx::readRegister(uint8_t register_addr)
{
    spiHandle.start();
    spiHandle.sendByte(0b01000001);
    spiHandle.sendByte(register_addr);
    uint8_t read = spiHandle.receiveByte();
    spiHandle.stop();
    return read;
}
