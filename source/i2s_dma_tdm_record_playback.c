/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2s_dma.h"
#include "fsl_codec_common.h"
#include "fsl_codec_adapter.h"
#include "fsl_gpio.h"
#include <stdbool.h>
#include "fsl_cs42448.h"
#include <math.h>
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_I2S_MASTER_CLOCK_FREQUENCY CLOCK_GetMclkClkFreq()
#define DEMO_AUDIO_SAMPLE_RATE          (48000)
#define DEMO_AUDIO_PROTOCOL             kCODEC_BusI2S
#define DEMO_I2S_TX                     (I2S3)
#define DEMO_I2S_RX                     (I2S1)
#define DEMO_DMA                        (DMA0)
#define DEMO_I2S_TX_CHANNEL             (7)
#define DEMO_I2S_RX_CHANNEL             (2)
#define DEMO_I2S_CLOCK_DIVIDER          (24576000 / DEMO_AUDIO_SAMPLE_RATE / 32 / 8)
#define DEMO_I2S_TX_MODE                kI2S_MasterSlaveNormalSlave
#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalMaster
#define DEMO_CODEC_I2C_BASEADDR         I2C2
#define DEMO_CODEC_I2C_INSTANCE         2U
#define DEMO_TDM_DATA_START_POSITION    1U
// Increase buffer size to accommodate adding sine into one channel
#define CHANNEL_PAIRS (4U)
#define SAMPLE_SIZE_MS (8)
#define SAMPLE_PER_MS (48)
#define BYTES_PER_SAMPLE (4)
#define NUM_CHANNELS (8)
#define BUFFER_SIZE   (SAMPLE_SIZE_MS * SAMPLE_PER_MS * BYTES_PER_SAMPLE * NUM_CHANNELS)
#define BUFFER_NUMBER (4U)
#define CONST_DATA (0xdeadbeef)
#define M_PI 3.14159265358979323846

// For SW2 functionality
#define APP_GPIO_INTA_IRQHandler GPIO_INTA_DriverIRQHandler
#define APP_SW_IRQ               GPIO_INTA_IRQn

// Adding macros to handle array alignment
#if defined(__GNUC__) /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(4)))
#endif
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif
#ifndef __ALIGN_BEGIN
#if defined(__CC_ARM) || defined(__ARMCC_VERSION) /* ARM Compiler */
#define __ALIGN_BEGIN __attribute__((aligned(4)))
#elif defined(__ICCARM__) /* IAR Compiler */
#define __ALIGN_BEGIN
#endif
#endif
#endif


/* demo audio sample rate */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitCodec(void);
extern void BORAD_CodecReset(bool state);
/*******************************************************************************
 * Variables
 ******************************************************************************/
cs42448_config_t cs42448Config = {
    .DACMode      = kCS42448_ModeSlave,
    .ADCMode      = kCS42448_ModeSlave,
    .reset        = NULL,
    .master       = false,
    .i2cConfig    = {.codecI2CInstance = DEMO_CODEC_I2C_INSTANCE},
    .format       = {.sampleRate = 48000U, .bitWidth = 24U},
    .bus          = kCS42448_BusTDM,
    .slaveAddress = CS42448_I2C_ADDR,
};

codec_config_t boardCodecConfig = {.codecDevType = kCODEC_CS42448, .codecDevConfig = &cs42448Config};
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t Buffer[BUFFER_NUMBER * BUFFER_SIZE], 4);
static uint32_t tx_index = 0U, rx_index = 0U;
volatile uint32_t emptyBlock = BUFFER_NUMBER;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;
static i2s_dma_handle_t s_i2sTxHandle;
static i2s_dma_handle_t s_i2sRxHandle;
static dma_handle_t s_i2sTxDmaHandle;
static dma_handle_t s_i2sRxDmaHandle;
static i2s_transfer_t xfer;

int32_t wave[48] = {0};

bool g_interruptEnabled = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void APP_GPIO_INTA_IRQHandler(void)
{
    /* clear the interrupt status */
    GPIO_PinClearInterruptFlag(SW2_GPIO, SW2_PORT, SW2_PIN, 0);
    /* Change state of switch. */
    g_interruptEnabled = true;
    SDK_ISR_EXIT_BARRIER;
}

static void enable_sw_interrupt()
{
    gpio_interrupt_config_t config = {kGPIO_PinIntEnableEdge, kGPIO_PinIntEnableLowOrFall};

    EnableIRQ(APP_SW_IRQ);
    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_10 (pin J3)  */
    // Ugh...config tool does a half ass job of this
    GPIO_PortInit(SW2_GPIO, SW2_PORT);
//    GPIO_PinInit(SW2_GPIO, SW2_PORT, SW2_PIN, &SW2_config);
    GPIO_SetPinInterruptConfig(SW2_GPIO, SW2_PORT, SW2_PIN, &config);
    GPIO_PinEnableInterrupt(SW2_GPIO, SW2_PORT, SW2_PIN, 0);
}

/** Generate a 1 kHz sine tone and store it in the variable wave. */
static void generate_wave()
{
	// This is generating a shit wave but it works for the moment
	// Volume is 1/4 max
	int32_t max_vol = 536870912;

	PRINTF("Generating wave now...\r\n");

	for (uint8_t i = 0; i < 48; i++)
	{
		wave[i] = (int32_t)(max_vol * sin(2*M_PI /48*i));
	}

}

static void i2s_rx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
	i2s_transfer_t i2s_data = *(i2s_transfer_t *)userData;

	int32_t *new_data = (int32_t *)(i2s_data.data);

	uint32_t num_elements = (SAMPLE_SIZE_MS * SAMPLE_PER_MS *  NUM_CHANNELS);
	uint32_t wave_pos = 0;
	uint32_t i = 0;

	for (; i < num_elements;wave_pos++)
	{
		new_data[i++] = wave[wave_pos % 48];
		new_data[i++] = wave[wave_pos % 48];
		i+=6;
	}

    emptyBlock--;
}

static void i2s_tx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock++;
}

/*!
 * @brief Main function
 */
int main(void)
{

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
	PinsFunc_InitSw2();


    CLOCK_EnableClock(kCLOCK_InputMux);

    /* I2C */
    CLOCK_AttachClk(kFFRO_to_FLEXCOMM2);

    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S1) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    /* attach AUDIO PLL clock to FLEXCOMM3 (I2S3) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM3);

    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;

    /* Set shared signal set 0: SCK, WS from Flexcomm1 */
    SYSCTL1->SHAREDCTRLSET[0] = SYSCTL1_SHAREDCTRLSET_SHAREDSCKSEL(1) | SYSCTL1_SHAREDCTRLSET_SHAREDWSSEL(1);
    /* Set flexcomm3 SCK, WS from shared signal set 0 */
    SYSCTL1->FCCTRLSEL[3] = SYSCTL1_FCCTRLSEL_SCKINSEL(1) | SYSCTL1_FCCTRLSEL_WSINSEL(1);

    cs42448Config.i2cConfig.codecI2CSourceClock = CLOCK_GetFlexCommClkFreq(2);
    cs42448Config.format.mclk_HZ                = CLOCK_GetMclkClkFreq();


	enable_sw_interrupt();


    PRINTF("I2S TDM record playback example started!\n\r");

    /* i2s configurations */
    /*
     * masterSlave = kI2S_MasterSlaveNormalMaster;
     * mode = kI2S_ModeI2sClassic;
     * rightLow = false;
     * leftJust = false;
     * pdmData = false;
     * sckPol = false;
     * wsPol = false;
     * divider = 1;
     * oneChannel = false;
     * dataLength = 16;
     * frameLength = 32;
     * position = 0;
     * fifoLevel = 4;
     */
    I2S_TxGetDefaultConfig(&s_TxConfig);
    s_TxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_TxConfig.mode        = kI2S_ModeDspWsShort;
    s_TxConfig.wsPol       = true;
    s_TxConfig.dataLength  = 32U;
    s_TxConfig.frameLength = 32 * 8U;
    s_TxConfig.position    = DEMO_TDM_DATA_START_POSITION;

    I2S_TxInit(DEMO_I2S_TX, &s_TxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    /* i2s configurations */
    I2S_RxGetDefaultConfig(&s_RxConfig);
    s_RxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_RxConfig.masterSlave = kI2S_MasterSlaveNormalMaster;
    s_RxConfig.mode        = kI2S_ModeDspWsShort;
    s_RxConfig.wsPol       = true;
    s_RxConfig.dataLength  = 32U;
    s_RxConfig.frameLength = 32 * 8U;
    s_RxConfig.position    = DEMO_TDM_DATA_START_POSITION;

    I2S_RxInit(DEMO_I2S_RX, &s_RxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    DMA_Init(DEMO_DMA);

    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_TX_CHANNEL);
    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_RX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_TX_CHANNEL, kDMA_ChannelPriority3);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&s_i2sTxDmaHandle, DEMO_DMA, DEMO_I2S_TX_CHANNEL);
    DMA_CreateHandle(&s_i2sRxDmaHandle, DEMO_DMA, DEMO_I2S_RX_CHANNEL);

    void *usrData = (void *)&xfer;
    I2S_TxTransferCreateHandleDMA(DEMO_I2S_TX, &s_i2sTxHandle, &s_i2sTxDmaHandle, i2s_tx_Callback, NULL);
    I2S_RxTransferCreateHandleDMA(DEMO_I2S_RX, &s_i2sRxHandle, &s_i2sRxDmaHandle, i2s_rx_Callback, usrData);

    /* codec initialization */
    DEMO_InitCodec();
    generate_wave();

    PRINTF("Starting TDM record playback\n\r");

    while (1)
    {
        if (emptyBlock > 0)
        {
            xfer.data     = Buffer + rx_index * BUFFER_SIZE;
            xfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == I2S_RxTransferReceiveDMA(DEMO_I2S_RX, &s_i2sRxHandle, xfer))
            {
                rx_index++;
            }
            if (rx_index == BUFFER_NUMBER)
            {
                rx_index = 0U;
            }
        }
        if (emptyBlock < BUFFER_NUMBER)
        {
            xfer.data     = Buffer + tx_index * BUFFER_SIZE;
            xfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == I2S_TxTransferSendDMA(DEMO_I2S_TX, &s_i2sTxHandle, xfer))
            {
                tx_index++;
            }
            if (tx_index == BUFFER_NUMBER)
            {
                tx_index = 0U;
            }
        }

        if (g_interruptEnabled)
        {
        	PRINTF("Interrupt enabled\r\n");
        	g_interruptEnabled = false;
        }
    }
}

static void DEMO_InitCodec(void)
{
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        PRINTF("CODEC_Init failed!\r\n");
        assert(false);
    }

    PRINTF("\r\nCodec Init Done.\r\n");
}
