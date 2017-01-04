#include <string.h>
#include "hal.h"
#include "spi.h"
#include "spiflash.h"

static void flashWaitBusy(void)
{
    uint8_t txBuf[2];
    uint8_t rxBuf[2];

    txBuf[0] = SPI_FLASH_STATUS_REG1;
    txBuf[1] = 0xFF;

    rxBuf[0] = 0xFF;
    rxBuf[1] = 0xFF;

    while (rxBuf[1] & 0x01)
    {
        chThdSleepMilliseconds(100);
        spiSelect(&SPID2);
        spiExchange(&SPID2, 2, txBuf, rxBuf);
        spiUnselect(&SPID2);
    }
}

static void flashWriteEnable(void)
{
    uint8_t txBuf[1];

    txBuf[0] = SPI_FLASH_WRITE_ENABLE;

    spiSelect(&SPID2);
    spiSend(&SPID2, 1, txBuf);
    spiUnselect(&SPID2);
}

int flashSectorErase(flashsector_t sector)
{
    uint8_t txBuf[4];
    uint32_t addr = (FLASH_SECTOR_BASE + FLASH_SECTOR_SIZE * sector);

    flashWriteEnable();

    txBuf[0] = SPI_FLASH_SECTOR_ERASE;
    txBuf[1] = (addr >> 16) & 0xff;
    txBuf[2] = (addr >> 8)  & 0xff;
    txBuf[3] = addr & 0xff;

    spiSelect(&SPID2);
    spiSend(&SPID2, 4, txBuf);
    spiUnselect(&SPID2);

    flashWaitBusy();

    /* Successfully erased sector */
    return FLASH_RETURN_SUCCESS;
}

int flashRead(flashaddr_t address, char* buffer, size_t size)
{
    uint8_t txBuf[20];
    uint8_t rxBuf[20];
    uint32_t addr;
    uint32_t offset = 0;
    size_t count = 16;
    uint8_t *ptr = rxBuf+4;

    for (addr = address ; addr < (address+size); addr += 16)
    {
        txBuf[0] = SPI_FLASH_READ;
        txBuf[1] = (addr >> 16) & 0xff;
        txBuf[2] = (addr >> 8)  & 0xff;
        txBuf[3] = addr & 0xff;

        if ( (addr+16) > (address+size) )
            count = (address+size) - addr;

        spiSelect(&SPID2);
        spiExchange(&SPID2, count+4, txBuf, rxBuf);
        spiUnselect(&SPID2);

        memcpy(buffer + offset, ptr, count);

        offset += count;
    }
    return FLASH_RETURN_SUCCESS;
}

int flashWrite(flashaddr_t address, const char* buffer, size_t size)
{
    uint8_t txBuf[20];
    uint32_t addr;
    uint32_t offset = 0;
    size_t count = 16;

    for (addr = address ; addr < (address+size); addr += 16)
    {
        uint32_t i;

        txBuf[0] = SPI_FLASH_PAGE_PROGRAM;
        txBuf[1] = (addr >> 16) & 0xff;
        txBuf[2] = (addr >> 8)  & 0xff;
        txBuf[3] = addr & 0xff;

        if ( (addr+16) > (address+size) )
            count = (address+size) - addr;

        for (i = offset; i < offset + count ; i++)
            txBuf[i+4] = *(buffer+i);

        flashWriteEnable();

        spiSelect(&SPID2);
        spiSend(&SPID2, count+4, txBuf);
        spiUnselect(&SPID2);

        flashWaitBusy();

        offset += count;
    }

    return FLASH_RETURN_SUCCESS;
}

