/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCP23XXX_H__
#define __MCP23XXX_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "spi_api.h"

// define register addresses
#define MCP23XXX_IODIR 0x00
#define MCP23XXX_IPOL 0x01
#define MCP23XXX_GPINTEN 0x02
#define MCP23XXX_DEFVAL 0x03
#define MCP23XXX_INTCON 0x04
#define MCP23XXX_IOCON 0x05
#define MCP23XXX_GPPU 0x06
#define MCP23XXX_INTF 0x07
#define MCP23XXX_INTCAP 0x08
#define MCP23XXX_GPIO 0x09
#define MCP23XXX_OLAT 0x0A

// define values
#define OUTPUT 0
#define INPUT 1

// define local registers to prevent reading error from causing serious damage
// this does not affect the low level reading and writing register functions
// #define LOCALREGISTERS

    struct result
    {
        bool fixable;
        bool hadError;
    };

    class mcp23xxx
    {
        int OpCode = 0b01000;
        spi_api &spiHandle;
        int hardware_addr;

        // initialize the registers locally to default values
        uint8_t iodir = 0b00000000;
        uint8_t gpio = 0b00000000;
        uint8_t gpinten = 0b00000000;
        uint8_t defval = 0b00000000;
        uint8_t intcon = 0b00000000;

    public:
        int integrityFaultCount = 0;

        mcp23xxx(spi_api *spi_handle, uint8_t hardware_address = 0);

        void writeRegister(uint8_t register_addr, uint8_t data);

        uint8_t readRegister(uint8_t register_addr);

        void pinMode(uint8_t pin, bool mode);

        void enableInterrupt(uint8_t pin, bool default_value = 0, bool comparator_value = 0);

        void writePin(uint8_t pin, bool value);

        bool readPin(uint8_t pin);

        void togglePin(uint8_t pin);

        // checks gpio register for correct values
        result fixIntegrity(int tries);
    };

#ifdef __cplusplus
}
#endif

#endif /* __MCP23XXX_H__ */