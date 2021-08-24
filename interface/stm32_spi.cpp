#include "stm32_spi.h"

spi::spi(SPI_HandleTypeDef *port_handle, GPIO_TypeDef *nss_port, uint16_t nss_pin)
{
    handle = port_handle;
    nssPort = nss_port;
    nssPin = nss_pin;
}

void spi::start()
{
    HAL_GPIO_WritePin(nssPort, nssPin, GPIO_PIN_RESET);
}

void spi::stop()
{
    HAL_GPIO_WritePin(nssPort, nssPin, GPIO_PIN_SET);
}

void spi::sendByte(uint8_t byte)
{
    assert(HAL_SPI_Transmit(handle, &byte, 1, HAL_MAX_DELAY) == HAL_OK);
}

uint8_t spi::receiveByte()
{
    uint8_t byte;
    assert(HAL_SPI_Receive(handle, &byte, 1, HAL_MAX_DELAY) == HAL_OK);
    return byte;
}
