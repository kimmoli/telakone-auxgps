#ifndef TK_SPIFLASH_H
#define TK_SPIFLASH_H

/* Use only one sector */

#define FLASH_SECTOR 0
#define FLASH_SECTOR_BASE 0x000000
#define FLASH_SECTOR_SIZE 0x1000

#define SPI_FLASH_SECTOR_ERASE 0x20
#define SPI_FLASH_STATUS_REG1  0x05
#define SPI_FLASH_READ         0x03
#define SPI_FLASH_WRITE_ENABLE 0x06
#define SPI_FLASH_PAGE_PROGRAM 0x02

/* Error codes */

#define FLASH_RETURN_SUCCESS MSG_OK
#define FLASH_RETURN_NO_PERMISSION -1
#define FLASH_RETURN_BAD_FLASH -11

typedef uint32_t flashdata_t;
typedef uint32_t flashaddr_t;
typedef uint8_t flashsector_t;

int flashSectorErase(flashsector_t sector);
int flashRead(flashaddr_t address, char* buffer, size_t size);
int flashWrite(flashaddr_t address, const char* buffer, size_t size);


#endif /* FLASH_H */

