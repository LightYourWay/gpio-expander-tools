/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_SPI_H__
#define __STM32_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include "spi_api.h"
#include "spi.h"
    class spi : public spi_api
    {
        SPI_HandleTypeDef *handle;
        GPIO_TypeDef *nssPort;
        uint16_t nssPin;

    public:
        spi(SPI_HandleTypeDef *port_handle, GPIO_TypeDef *nss_port, uint16_t nss_pin);

        void start() override;

        void stop() override;

        void sendByte(uint8_t byte) override;

        uint8_t receiveByte() override;
    };

#ifdef __cplusplus
}
#endif

#endif /* __STM32_SPI_H__ */