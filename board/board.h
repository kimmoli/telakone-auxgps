/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for Kimmoli's telakone GPS STM32F410RB board.
 */

/*
 * Board identifier.
 */
#define BOARD_KIMMOLI_TELAKONE
#define BOARD_NAME                  "Kimmoli's telakone GPS STM32F410RB"

/*
 * Use watchdog
 */

// #define TK_USE_WDOG

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25000000U
#endif

//#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F410Rx

/*
 * Board specific analog stuff
 */
#define EXT_VREF                   ( (float)(3.300) )
#define ADC_MEAS12V_SCALE          ( (float)(EXT_VREF/4096*(5900+825)/825) )

/*
 * IO pins assignments.
 */
#define GPIOA_PA0_MEAS12V           0U
#define GPIOA_PA1_ACCLINKTXE        1U
#define GPIOA_PA2_ACCLINKTX         2U
#define GPIOA_PA3_ACCLINKRX         3U
#define GPIOA_PA4_NC                4U
#define GPIOA_PA5_NC                5U
#define GPIOA_PA6_NC                6U
#define GPIOA_PA7_NC                7U
#define GPIOA_PA8_GPS1PPS           8U
#define GPIOA_PA9_USART1TX          9U
#define GPIOA_PA10_USART1RX         10U
#define GPIOA_PA11_USART6TX         11U
#define GPIOA_PA12_USART6RX         12U
#define GPIOA_PA13_SWDIO            13U
#define GPIOA_PA14_SWCLK            14U
#define GPIOA_PA15_NC               15U

#define GPIOB_PB0_NC                0U
#define GPIOB_PB1_NC                1U
#define GPIOB_PB2_BOOT1             2U
#define GPIOB_PB3_NC                3U
#define GPIOB_PB4_NC                4U
#define GPIOB_PB5_NC                5U
#define GPIOB_PB6_I2C1SCL           6U
#define GPIOB_PB7_I2C1SDA           7U
#define GPIOB_PB8_NC                8U
#define GPIOB_PB9_NC                9U
#define GPIOB_PB10_NC               10U
#define GPIOB_PB11_NC               11U
#define GPIOB_PB12_SPI2CSN          12U
#define GPIOB_PB13_SPI2CLK          13U
#define GPIOB_PB14_SPI2MISO         14U
#define GPIOB_PB15_SPI2MOSI         15U

#define GPIOC_PC0_IN1               0U
#define GPIOC_PC1_IN2               1U
#define GPIOC_PC2_IN3               2U
#define GPIOC_PC3_IN4               3U
#define GPIOC_PC4_OUT1              4U
#define GPIOC_PC5_OUT2              5U
#define GPIOC_PC6_NC                6U
#define GPIOC_PC7_NC                7U
#define GPIOC_PC8_GREENLED          8U
#define GPIOC_PC9_REDLED            9U
#define GPIOC_PC10_NC               10U
#define GPIOC_PC11_NC               11U
#define GPIOC_PC12_NC               12U
#define GPIOC_PC13_NC               13U
#define GPIOC_PC14_NC               14U
#define GPIOC_PC15_NC               15U

#define GPIOH_PH0_OSC_IN            0U
#define GPIOH_PH1_OSC_OUT           1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

/*
 * IO lines assignments.
 */

#define LINE_MEAS12V                PAL_LINE(GPIOA, 0U)
#define LINE_ACCLINKTXE             PAL_LINE(GPIOA, 1U)
#define LINE_ACCLINKTX              PAL_LINE(GPIOA, 2U)
#define LINE_ACCLINKRX              PAL_LINE(GPIOA, 3U)
#define LINE_GPS1PPS                PAL_LINE(GPIOA, 8U)
#define LINE_USART1TX               PAL_LINE(GPIOA, 9U)
#define LINE_USART1RX               PAL_LINE(GPIOA, 10U)
#define LINE_USART6TX               PAL_LINE(GPIOA, 11U)
#define LINE_USART6RX               PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)

#define LINE_BOOT1                  PAL_LINE(GPIOB, 2U)
#define LINE_I2C1SCL                PAL_LINE(GPIOB, 6U)
#define LINE_I2C1SDA                PAL_LINE(GPIOB, 7U)
#define LINE_SPI2CSN                PAL_LINE(GPIOB, 12U)
#define LINE_SPI2CLK                PAL_LINE(GPIOB, 13U)
#define LINE_SPI2MISO               PAL_LINE(GPIOB, 14U)
#define LINE_SPI2MOSI               PAL_LINE(GPIOB, 15U)

#define LINE_IN1                    PAL_LINE(GPIOC, 1U)
#define LINE_IN2                    PAL_LINE(GPIOC, 2U)
#define LINE_IN3                    PAL_LINE(GPIOC, 3U)
#define LINE_IN4                    PAL_LINE(GPIOC, 4U)
#define LINE_OUT1                   PAL_LINE(GPIOC, 4U)
#define LINE_OUT2                   PAL_LINE(GPIOC, 5U)
#define LINE_GREENLED               PAL_LINE(GPIOC, 8U)
#define LINE_REDLED                 PAL_LINE(GPIOC, 9U)

#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))



#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_PA0_MEAS12V) /* ADC1 IN0 */| \
                                     PIN_MODE_OUTPUT(GPIOA_PA1_ACCLINKTXE) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA2_ACCLINKTX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA3_ACCLINKRX) | \
                                     PIN_MODE_INPUT(GPIOA_PA4_NC) | \
                                     PIN_MODE_OUTPUT(GPIOA_PA5_NC) | \
                                     PIN_MODE_INPUT(GPIOA_PA6_NC) | \
                                     PIN_MODE_INPUT(GPIOA_PA7_NC) | \
                                     PIN_MODE_INPUT(GPIOA_PA8_GPS1PPS) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA9_USART1TX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA10_USART1RX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA11_USART6TX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA12_USART6RX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA13_SWDIO) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PA14_SWCLK) | \
                                     PIN_MODE_INPUT(GPIOA_PA15_NC))

#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PA0_MEAS12V) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA1_ACCLINKTXE) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA2_ACCLINKTX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA3_ACCLINKRX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA4_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA5_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA6_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA7_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA8_GPS1PPS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA9_USART1TX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA10_USART1RX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA11_USART6TX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA12_USART6RX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA13_SWDIO) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA14_SWCLK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA15_NC))

#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PA0_MEAS12V) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA1_ACCLINKTXE) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA2_ACCLINKTX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA3_ACCLINKRX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA4_NC) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA5_NC) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA6_NC) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA7_NC) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA8_GPS1PPS) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA9_USART1TX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA10_USART1RX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA11_USART6TX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA12_USART6RX) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA13_SWDIO) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA14_SWCLK) | \
                                     PIN_OSPEED_HIGH(GPIOA_PA15_NC))

#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PA0_MEAS12V) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA1_ACCLINKTXE) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA2_ACCLINKTX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA3_ACCLINKRX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA4_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA5_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA6_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA7_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA8_GPS1PPS) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA9_USART1TX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA10_USART1RX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA11_USART6TX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA12_USART6RX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA13_SWDIO) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA14_SWCLK) | \
                                     PIN_PUPDR_PULLUP(GPIOA_PA15_NC))

#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PA0_MEAS12V) | \
                                     PIN_ODR_LOW(GPIOA_PA1_ACCLINKTXE) | \
                                     PIN_ODR_HIGH(GPIOA_PA2_ACCLINKTX) | \
                                     PIN_ODR_HIGH(GPIOA_PA3_ACCLINKRX) | \
                                     PIN_ODR_HIGH(GPIOA_PA4_NC) | \
                                     PIN_ODR_LOW(GPIOA_PA5_NC) | \
                                     PIN_ODR_HIGH(GPIOA_PA6_NC) | \
                                     PIN_ODR_HIGH(GPIOA_PA7_NC) | \
                                     PIN_ODR_HIGH(GPIOA_PA8_GPS1PPS) | \
                                     PIN_ODR_HIGH(GPIOA_PA9_USART1TX) | \
                                     PIN_ODR_HIGH(GPIOA_PA10_USART1RX) | \
                                     PIN_ODR_HIGH(GPIOA_PA11_USART6TX) | \
                                     PIN_ODR_HIGH(GPIOA_PA12_USART6RX) | \
                                     PIN_ODR_HIGH(GPIOA_PA13_SWDIO) | \
                                     PIN_ODR_HIGH(GPIOA_PA14_SWCLK) | \
                                     PIN_ODR_HIGH(GPIOA_PA15_NC))

#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PA0_MEAS12V, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA1_ACCLINKTXE, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA2_ACCLINKTX, 7) | /* USART2TX */ \
                                     PIN_AFIO_AF(GPIOA_PA3_ACCLINKRX, 7) | /* USART2RX */ \
                                     PIN_AFIO_AF(GPIOA_PA4_NC, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA5_NC, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA6_NC, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA7_NC, 0))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PA8_GPS1PPS, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA9_USART1TX, 7) | /* USART1TX */ \
                                     PIN_AFIO_AF(GPIOA_PA10_USART1RX, 7) | /* USART1RX */ \
                                     PIN_AFIO_AF(GPIOA_PA11_USART6TX, 8) | /* USART6TX */ \
                                     PIN_AFIO_AF(GPIOA_PA12_USART6RX, 8) | /* USART6RX */ \
                                     PIN_AFIO_AF(GPIOA_PA13_SWDIO, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA14_SWCLK, 0) | \
                                     PIN_AFIO_AF(GPIOA_PA15_NC, 0))

#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PB0_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB1_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB2_BOOT1) | \
                                     PIN_MODE_INPUT(GPIOB_PB3_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB4_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB5_NC) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PB6_I2C1SCL) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PB7_I2C1SDA) | \
                                     PIN_MODE_INPUT(GPIOB_PB8_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB9_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB10_NC) | \
                                     PIN_MODE_INPUT(GPIOB_PB11_NC) | \
                                     PIN_MODE_OUTPUT(GPIOB_PB12_SPI2CSN) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PB13_SPI2CLK) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PB14_SPI2MISO) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PB15_SPI2MOSI))

#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PB0_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB1_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB2_BOOT1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB3_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB4_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB5_NC) | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PB6_I2C1SCL) | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PB7_I2C1SDA) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB8_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB9_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB10_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB11_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB12_SPI2CSN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB13_SPI2CLK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB14_SPI2MISO) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PB15_SPI2MOSI))

#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PB0_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB1_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB2_BOOT1) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB3_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB4_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB5_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB6_I2C1SCL) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB7_I2C1SDA) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB8_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB9_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB10_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB11_NC) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB12_SPI2CSN) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB13_SPI2CLK) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB14_SPI2MISO) | \
                                     PIN_OSPEED_HIGH(GPIOB_PB15_SPI2MOSI))

#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_PB0_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB1_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB2_BOOT1) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB3_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB4_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB5_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB6_I2C1SCL) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB7_I2C1SDA) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB8_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB9_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB10_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB11_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB12_SPI2CSN) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB13_SPI2CLK) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB14_SPI2MISO) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PB15_SPI2MOSI))

#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PB0_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB1_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB2_BOOT1) | \
                                     PIN_ODR_HIGH(GPIOB_PB3_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB4_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB5_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB6_I2C1SCL) | \
                                     PIN_ODR_HIGH(GPIOB_PB7_I2C1SDA) | \
                                     PIN_ODR_HIGH(GPIOB_PB8_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB9_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB10_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB11_NC) | \
                                     PIN_ODR_HIGH(GPIOB_PB12_SPI2CSN) | \
                                     PIN_ODR_HIGH(GPIOB_PB13_SPI2CLK) | \
                                     PIN_ODR_HIGH(GPIOB_PB14_SPI2MISO) | \
                                     PIN_ODR_HIGH(GPIOB_PB15_SPI2MOSI))

#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PB0_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB1_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB2_BOOT1, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB3_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB4_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB5_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB6_I2C1SCL, 4) | /* I2C1SCL */ \
                                     PIN_AFIO_AF(GPIOB_PB7_I2C1SDA, 4)) /* I2C1SDA */
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PB8_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB9_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB10_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB11_NC, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB12_SPI2CSN, 0) | \
                                     PIN_AFIO_AF(GPIOB_PB13_SPI2CLK, 5) | /* SPI2CLK */ \
                                     PIN_AFIO_AF(GPIOB_PB14_SPI2MISO, 5) | /* SPI2MISO */ \
                                     PIN_AFIO_AF(GPIOB_PB15_SPI2MOSI, 5)) /* SPI2MOSI */

#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PC0_IN1) | \
                                     PIN_MODE_INPUT(GPIOC_PC1_IN2) | \
                                     PIN_MODE_INPUT(GPIOC_PC2_IN3) | \
                                     PIN_MODE_INPUT(GPIOC_PC3_IN4) | \
                                     PIN_MODE_ALTERNATE(GPIOC_PC4_OUT1) | \
                                     PIN_MODE_ALTERNATE(GPIOC_PC5_OUT2) | \
                                     PIN_MODE_INPUT(GPIOC_PC6_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC7_NC) | \
                                     PIN_MODE_OUTPUT(GPIOC_PC8_GREENLED) | \
                                     PIN_MODE_OUTPUT(GPIOC_PC9_REDLED) | \
                                     PIN_MODE_INPUT(GPIOC_PC10_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC11_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC12_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC13_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC14_NC) | \
                                     PIN_MODE_INPUT(GPIOC_PC15_NC))

#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PC0_IN1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC1_IN2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC2_IN3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC3_IN4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC4_OUT1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC5_OUT2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC6_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC7_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC8_GREENLED) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC9_REDLED) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC10_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC11_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC12_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC13_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC14_NC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PC15_NC))

#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PC0_IN1) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC1_IN2) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC2_IN3) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC3_IN4) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC4_OUT1) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC5_OUT2) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC6_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC7_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC8_GREENLED) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC9_REDLED) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC10_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC11_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC12_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC13_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC14_NC) | \
                                     PIN_OSPEED_HIGH(GPIOC_PC15_NC))

#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_PC0_IN1) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC1_IN2) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC2_IN3) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC3_IN4) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC4_OUT1) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC5_OUT2) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC6_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC7_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC8_GREENLED) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC9_REDLED) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC10_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC11_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC12_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC13_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC14_NC) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PC15_NC))

#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PC0_IN1) | \
                                     PIN_ODR_HIGH(GPIOC_PC1_IN2) | \
                                     PIN_ODR_HIGH(GPIOC_PC2_IN3) | \
                                     PIN_ODR_HIGH(GPIOC_PC3_IN4) | \
                                     PIN_ODR_HIGH(GPIOC_PC4_OUT1) | \
                                     PIN_ODR_HIGH(GPIOC_PC5_OUT2) | \
                                     PIN_ODR_HIGH(GPIOC_PC6_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC7_NC) | \
                                     PIN_ODR_LOW(GPIOC_PC8_GREENLED) | \
                                     PIN_ODR_HIGH(GPIOC_PC9_REDLED) | \
                                     PIN_ODR_HIGH(GPIOC_PC10_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC11_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC12_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC13_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC14_NC) | \
                                     PIN_ODR_HIGH(GPIOC_PC15_NC))

#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PC0_IN1, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC1_IN2, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC2_IN3, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC3_IN4, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC4_OUT1, 3) | /* TIM9_CH1 */ \
                                     PIN_AFIO_AF(GPIOC_PC5_OUT2, 3) | /* TIM9_CH2 */ \
                                     PIN_AFIO_AF(GPIOC_PC6_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC7_NC, 0))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PC8_GREENLED, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC9_REDLED, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC10_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC11_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC12_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC13_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC14_NC, 0) | \
                                     PIN_AFIO_AF(GPIOC_PC15_NC, 0))

#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_PH0_OSC_IN) | \
                                     PIN_MODE_INPUT(GPIOH_PH1_OSC_OUT) | \
                                     PIN_MODE_INPUT(GPIOH_PIN2) | \
                                     PIN_MODE_INPUT(GPIOH_PIN3) | \
                                     PIN_MODE_INPUT(GPIOH_PIN4) | \
                                     PIN_MODE_INPUT(GPIOH_PIN5) | \
                                     PIN_MODE_INPUT(GPIOH_PIN6) | \
                                     PIN_MODE_INPUT(GPIOH_PIN7) | \
                                     PIN_MODE_INPUT(GPIOH_PIN8) | \
                                     PIN_MODE_INPUT(GPIOH_PIN9) | \
                                     PIN_MODE_INPUT(GPIOH_PIN10) | \
                                     PIN_MODE_INPUT(GPIOH_PIN11) | \
                                     PIN_MODE_INPUT(GPIOH_PIN12) | \
                                     PIN_MODE_INPUT(GPIOH_PIN13) | \
                                     PIN_MODE_INPUT(GPIOH_PIN14) | \
                                     PIN_MODE_INPUT(GPIOH_PIN15))

#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_PH0_OSC_IN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PH1_OSC_OUT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))

#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_PH0_OSC_IN) | \
                                     PIN_OSPEED_HIGH(GPIOH_PH1_OSC_OUT) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN4) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN5) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN6) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN9) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN10) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))

#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_PH0_OSC_IN) | \
                                     PIN_PUPDR_FLOATING(GPIOH_PH1_OSC_OUT) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) | \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))

#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_PH0_OSC_IN) | \
                                     PIN_ODR_HIGH(GPIOH_PH1_OSC_OUT) | \
                                     PIN_ODR_HIGH(GPIOH_PIN2) | \
                                     PIN_ODR_HIGH(GPIOH_PIN3) | \
                                     PIN_ODR_HIGH(GPIOH_PIN4) | \
                                     PIN_ODR_HIGH(GPIOH_PIN5) | \
                                     PIN_ODR_HIGH(GPIOH_PIN6) | \
                                     PIN_ODR_HIGH(GPIOH_PIN7) | \
                                     PIN_ODR_HIGH(GPIOH_PIN8) | \
                                     PIN_ODR_HIGH(GPIOH_PIN9) | \
                                     PIN_ODR_HIGH(GPIOH_PIN10) | \
                                     PIN_ODR_HIGH(GPIOH_PIN11) | \
                                     PIN_ODR_HIGH(GPIOH_PIN12) | \
                                     PIN_ODR_HIGH(GPIOH_PIN13) | \
                                     PIN_ODR_HIGH(GPIOH_PIN14) | \
                                     PIN_ODR_HIGH(GPIOH_PIN15))

#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_PH0_OSC_IN, 0) | \
                                     PIN_AFIO_AF(GPIOH_PH1_OSC_OUT, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0) | \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0))

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
