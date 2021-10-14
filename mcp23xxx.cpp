#include "mcp23xxx.h"

mcp23xxx::mcp23xxx(spi_api *spi_handle, uint8_t hardware_address) : spiHandle(*spi_handle), hardware_addr(hardware_address)
{
    // set HAEN bit to enable hardware addressing
    writeRegister(MCP23XXX_IOCON, readRegister(MCP23XXX_IOCON) | 1 << 3 | 1 << 5);
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
    this->iodir = readRegister(MCP23XXX_IODIR);
#endif

    if (mode)
    {
        this->iodir |= (1 << pin);
    }
    else
    {
        this->iodir &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_IODIR, this->iodir);
}

void mcp23xxx::writePin(uint8_t pin, bool value)
{

#ifndef LOCALREGISTERS
    // read the current register value
    this->gpio = readRegister(MCP23XXX_GPIO);
#endif

    if (value)
    {
        this->gpio |= (1 << pin);
    }
    else
    {
        this->gpio &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_GPIO, this->gpio);
}

bool mcp23xxx::readPin(uint8_t pin)
{
    return (readRegister(MCP23XXX_GPIO) & (1 << pin)) != 0;
}

void mcp23xxx::togglePin(uint8_t pin)
{

#ifndef LOCALREGISTERS
    // read the current register value
    this->gpio = readRegister(MCP23XXX_GPIO);
#endif

    this->gpio ^= (1 << pin);
    writeRegister(MCP23XXX_GPIO, this->gpio);
}

result mcp23xxx::fixIntegrity(int tries)
{
    bool hadError = false;
    // trying to fix the integrity of the registry for defined number of times
    for (int i = 0; i < tries; i++)
    {
        volatile uint8_t read = readRegister(MCP23XXX_GPIO);
        if (read != this->gpio)
        {
            hadError = true;
            writeRegister(MCP23XXX_GPIO, this->gpio);

            // count the number of times the registry was tried to be fixed
            integrityFaultCount++;
        } else {
            // chip has been sucessfully fixed within defined number of tries
            return result {true, hadError};
        }
    }
    // chip has not been fixed within defined number of tries
    return result {false, hadError};
}