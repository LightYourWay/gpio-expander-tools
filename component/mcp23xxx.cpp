#include "mcp23xxx.h"

mcp23xxx::mcp23xxx(spi_api* spi_handle, uint8_t hardware_address) : spiHandle(*spi_handle), hardware_addr(hardware_address) {
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


void mcp23xxx::pinMode(uint8_t pin, bool mode) {
    uint8_t iodir = readRegister(MCP23XXX_IODIR);
    if (mode) {
        iodir |= (1 << pin);
    } else {
        iodir &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_IODIR, iodir);
}

void mcp23xxx::writePin(uint8_t pin, bool value) {
    uint8_t gpio = readRegister(MCP23XXX_GPIO);
    if (value) {
        gpio |= (1 << pin);
    } else {
        gpio &= ~(1 << pin);
    }
    writeRegister(MCP23XXX_GPIO, gpio);
}

void mcp23xxx::togglePin(uint8_t pin) {
    uint8_t gpio = readRegister(MCP23XXX_GPIO);
    gpio ^= (1 << pin);
    writeRegister(MCP23XXX_GPIO, gpio);
}