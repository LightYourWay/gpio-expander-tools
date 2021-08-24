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
        void start();

        void stop();

        void sendByte(uint8_t byte);

        uint8_t receiveByte();
    };

#ifdef __cplusplus
}
#endif

#endif /* __SPI_API_H__ */