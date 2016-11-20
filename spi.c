#include "hal.h"
#include "spi.h"
#include "helpers.h"

const SPIConfig spiconfigFlash =
{
    NULL,
    GPIOB,
    GPIOB_PB12_SPI2CSN,
    SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2,
    0
};

void spiTKInit(void)
{
    spiStart(&SPID2, &spiconfigFlash);
}
