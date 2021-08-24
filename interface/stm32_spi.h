/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_SPI_H__
#define __STM32_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include "spi.h"
    namespace spi
    {
        class port
        {
            SPI_HandleTypeDef *handle;
            GPIO_TypeDef *nssPort;
            uint16_t nssPin;

        public:
            port(SPI_HandleTypeDef *port_handle, GPIO_TypeDef *nss_port, uint16_t nss_pin);

            void start();

            void stop();

            void sendByte(uint8_t byte);

            uint8_t receiveByte();
        };
    }

#ifdef __cplusplus
}
#endif

#endif /* __STM32_SPI_H__ */