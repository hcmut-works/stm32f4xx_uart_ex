/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_uart.h"
#include "diag/trace.h"

// ----------------------------------------------------------------------------
//
// STM32F4 UART Example (USART2 on PA2=TX, PA3=RX)
//
// This example initializes USART2 at 115200 baud, transmits a welcome
// message, then echoes back any received characters.
//
// Wiring: Connect a USB-to-Serial adapter to PA2 (TX) and PA3 (RX).
// On STM32F4-Discovery, USART2 PA2/PA3 is commonly available.
//

// ----- UART handle ----------------------------------------------------------

UART_HandleTypeDef huart2;

// ----- Private function prototypes ------------------------------------------

static void UART2_Init(void);

// ----- main() ---------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed by __initialize_hardware().

  // Initialize USART2
  UART2_Init();

  // Transmit a welcome message
  char *msg = "Hello from STM32F4 UART!\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);

  uint8_t rx_data;

  // Infinite loop: echo received characters
  while (1)
    {
      // Wait to receive 1 byte (blocking, with 1-second timeout)
      if (HAL_UART_Receive(&huart2, &rx_data, 1, 1000) == HAL_OK)
        {
          // Echo the received byte back
          HAL_UART_Transmit(&huart2, &rx_data, 1, HAL_MAX_DELAY);
        }
    }
}

#pragma GCC diagnostic pop

// ----- UART2 Initialization -------------------------------------------------

/**
  * @brief  Initialize USART2: 115200 baud, 8N1, no flow control.
  */
static void UART2_Init(void)
{
  huart2.Instance          = USART2;
  huart2.Init.BaudRate     = 115200;
  huart2.Init.WordLength   = UART_WORDLENGTH_8B;
  huart2.Init.StopBits     = UART_STOPBITS_1;
  huart2.Init.Parity       = UART_PARITY_NONE;
  huart2.Init.Mode         = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart2) != HAL_OK)
    {
      // Initialization error – stay here
      trace_printf("UART2 init failed!\n");
      while (1) {}
    }
}

// ----------------------------------------------------------------------------
