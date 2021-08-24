/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_API_H__
#define __SPI_API_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    struct spi_api
    {
        virtual void start() = 0;

        virtual void stop() = 0;

        virtual void sendByte(uint8_t byte) = 0;

        virtual uint8_t receiveByte() = 0;
    };

#ifdef __cplusplus
}
#endif

#endif /* __SPI_API_H__ */