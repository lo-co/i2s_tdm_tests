/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define IOPCTL_PIO_ANAMUX_DI 0x00u        /*!<@brief Analog mux is disabled */
#define IOPCTL_PIO_FULLDRIVE_DI 0x00u     /*!<@brief Normal drive */
#define IOPCTL_PIO_FULLDRIVE_EN 0x0100u   /*!<@brief Full drive enable */
#define IOPCTL_PIO_FUNC1 0x01u            /*!<@brief Selects pin function 1 */
#define IOPCTL_PIO_INBUF_DI 0x00u         /*!<@brief Disable input buffer function */
#define IOPCTL_PIO_INBUF_EN 0x40u         /*!<@brief Enables input buffer function */
#define IOPCTL_PIO_INV_DI 0x00u           /*!<@brief Input function is not inverted */
#define IOPCTL_PIO_PSEDRAIN_DI 0x00u      /*!<@brief Pseudo Output Drain is disabled */
#define IOPCTL_PIO_PSEDRAIN_EN 0x0400u    /*!<@brief Pseudo Output Drain is enabled */
#define IOPCTL_PIO_PULLDOWN_EN 0x00u      /*!<@brief Enable pull-down function */
#define IOPCTL_PIO_PULLUP_EN 0x20u        /*!<@brief Enable pull-up function */
#define IOPCTL_PIO_PUPD_DI 0x00u          /*!<@brief Disable pull-up / pull-down function */
#define IOPCTL_PIO_PUPD_EN 0x10u          /*!<@brief Enable pull-up / pull-down function */
#define IOPCTL_PIO_SLEW_RATE_NORMAL 0x00u /*!<@brief Normal mode */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCS42448Pins(void); /* Function assigned for the Cortex-M33 */

#define IOPCTL_PIO_ANAMUX_DI 0x00u        /*!<@brief Analog mux is disabled */
#define IOPCTL_PIO_FULLDRIVE_DI 0x00u     /*!<@brief Normal drive */
#define IOPCTL_PIO_FUNC1 0x01u            /*!<@brief Selects pin function 1 */
#define IOPCTL_PIO_INBUF_DI 0x00u         /*!<@brief Disable input buffer function */
#define IOPCTL_PIO_INBUF_EN 0x40u         /*!<@brief Enables input buffer function */
#define IOPCTL_PIO_INV_DI 0x00u           /*!<@brief Input function is not inverted */
#define IOPCTL_PIO_PSEDRAIN_DI 0x00u      /*!<@brief Pseudo Output Drain is disabled */
#define IOPCTL_PIO_PULLDOWN_EN 0x00u      /*!<@brief Enable pull-down function */
#define IOPCTL_PIO_PUPD_DI 0x00u          /*!<@brief Disable pull-up / pull-down function */
#define IOPCTL_PIO_SLEW_RATE_NORMAL 0x00u /*!<@brief Normal mode */

/*! @name FC0_RXD_SDA_MOSI_DATA (coord G4), JP40[2]
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITDEBUGCONSOLEPINS_DEBUG_UART_RXD_PERIPHERAL FLEXCOMM0
/*!
 * @brief Signal name */
#define BOARD_INITDEBUGCONSOLEPINS_DEBUG_UART_RXD_SIGNAL RXD_SDA_MOSI_DATA
/* @} */

/*! @name FC0_TXD_SCL_MISO_WS (coord G2), J16[1]/U27[3]/U9[12]
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITDEBUGCONSOLEPINS_DEBUG_UART_TXD_PERIPHERAL FLEXCOMM0
/*!
 * @brief Signal name */
#define BOARD_INITDEBUGCONSOLEPINS_DEBUG_UART_TXD_SIGNAL TXD_SCL_MISO_WS
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDebugConsolePins(void); /* Function assigned for the Cortex-M33 */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M33 */

#define IOPCTL_PIO_ANAMUX_DI 0x00u        /*!<@brief Analog mux is disabled */
#define IOPCTL_PIO_FULLDRIVE_DI 0x00u     /*!<@brief Normal drive */
#define IOPCTL_PIO_FUNC0 0x00u            /*!<@brief Selects pin function 0 */
#define IOPCTL_PIO_INBUF_EN 0x40u         /*!<@brief Enables input buffer function */
#define IOPCTL_PIO_INV_DI 0x00u           /*!<@brief Input function is not inverted */
#define IOPCTL_PIO_PSEDRAIN_DI 0x00u      /*!<@brief Pseudo Output Drain is disabled */
#define IOPCTL_PIO_PULLDOWN_EN 0x00u      /*!<@brief Enable pull-down function */
#define IOPCTL_PIO_PUPD_DI 0x00u          /*!<@brief Disable pull-up / pull-down function */
#define IOPCTL_PIO_SLEW_RATE_NORMAL 0x00u /*!<@brief Normal mode */

/*! @name PIO0_10 (coord J3), SW2
  @{ */
/* Routed pin properties */
#define SW2_PERIPHERAL GPIO                   /*!<@brief Peripheral name */
#define SW2_SIGNAL PIO0                       /*!<@brief Signal name */
#define SW2_CHANNEL 10                        /*!<@brief Signal channel */

/* Symbols to be used with GPIO driver */
#define SW2_GPIO GPIO                         /*!<@brief GPIO peripheral base pointer */
#define SW2_GPIO_PIN_MASK (1U << 10U)         /*!<@brief GPIO pin mask */
#define SW2_PORT 0U                           /*!<@brief PORT peripheral base pointer */
#define SW2_PIN 10U                           /*!<@brief PORT pin number */
#define SW2_PIN_MASK (1U << 10U)              /*!<@brief PORT pin mask */
                                              /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void PinsFunc_InitSw2(void); /* Function assigned for the Cortex-M33 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
