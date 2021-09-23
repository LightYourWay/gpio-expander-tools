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
    class mcp23xxx
    {
        int OpCode = 0b01000;
        spi_api& spiHandle;
        int hardware_addr;

    public:
        mcp23xxx(spi_api* spi_handle, uint8_t hardware_address = 0);

        void writeRegister(uint8_t register_addr, uint8_t data);

        uint8_t readRegister(uint8_t register_addr);

        void pinMode(uint8_t pin, bool mode);

        void writePin(uint8_t pin, bool value);
        
        void togglePin(uint8_t pin);
    };

#ifdef __cplusplus
}
#endif

#endif /* __MCP23XXX_H__ */