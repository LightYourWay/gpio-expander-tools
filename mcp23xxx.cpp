#include "mcp23xxx.h"

// initialize the registers locally to default values
uint8_t iodir = 0b00000000;
uint8_t gpio = 0b00000000;

mcp23xxx::mcp23xxx(spi_api *spi_handle, uint8_t hardware_address) : spiHandle(*spi_handle), hardware_addr(hardware_address)
{
    // set HAEN bit to enable hardware addressing
    writeRegister(MCP23XXX_IOCON, readRegister(MCP23XXX_IOCON) | 1 << 3);
}

void mcp23xxx::writeRegister(uint8_t register_addr, uint8_t data)
{
    spiHandle.start();
    spiHandle.sendByte(OpCode << 3 | hardware_addr << 1);
    spiHandle.sendByte(register_addr);
    spiHandle.sendByte(data);
    spiHandle.stop();
}

uint8_t mcp23xxx::readRegister(uint8_t register_addr)
{
    spiHandle.start();
    spiHandle.sendByte(OpCode << 3 | hardware_addr << 1 | 1);
    spiHandle.sendByte(register_addr);
    uint8_t read = spiHandle.receiveByte();
    spiHandle.stop();
    return read;
}

void mcp23xxx::pinMode(uint8_t pin, bool mode)
{

#ifndef LOCALREGISTERS
    // read the current register value
    iodir = readRegister(MCP23XXX_IODIR);
#endif

    if (mode)
    {
        iodir |= (1 << pin);
    }
    else
    {
        iodir &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_IODIR, iodir);
}

void mcp23xxx::writePin(uint8_t pin, bool value)
{

#ifndef LOCALREGISTERS
    // read the current register value
    gpio = readRegister(MCP23XXX_GPIO);
#endif

    if (value)
    {
        gpio |= (1 << pin);
    }
    else
    {
        gpio &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_GPIO, gpio);
}

void mcp23xxx::togglePin(uint8_t pin)
{

#ifndef LOCALREGISTERS
    // read the current register value
    gpio = readRegister(MCP23XXX_GPIO);
#endif

    gpio ^= (1 << pin);
    writeRegister(MCP23XXX_GPIO, gpio);
}

void mcp23xxx::fixIntegrity()
{
    while (readRegister(MCP23XXX_GPIO) != gpio)
    {
        writeRegister(MCP23XXX_GPIO, gpio);
        integrityFault++;
    }
}