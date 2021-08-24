/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCP23XXX_H__
#define __MCP23XXX_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "spi_api.h"
    class mcp23xxx
    {
        int OpCode = 0b01000;
        int hardware_addr = 0;
        spi_api& spiHandle;

    public:
        mcp23xxx(spi_api* spi_handle);

        void writeRegister(uint8_t register_addr, uint8_t data);

        uint8_t readRegister(uint8_t register_addr);
    };

#ifdef __cplusplus
}
#endif

#endif /* __MCP23XXX_H__ */