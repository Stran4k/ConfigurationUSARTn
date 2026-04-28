#ifndef ConfigurationUSARTn_H
#define ConfigurationUSARTn_H
/*
#include "ConfigurationUSARTn.h"


create by Sikorsky VI
*/
//uncomment your processor
#define GD32F303_
//#define GD32F450_

#define SENDING_VIA_USART // functions of sending via USART without DMA
/*
#define USARTx_PORT         GPIOA
#define USARTx_PIN_TX       GPIO_PIN_9  
#define USARTx_PIN_RX       GPIO_PIN_10

#define USARTx_PORT_SWITCH	GPIOA
#define USARTx_PIN_SWITCH   GPIO_PIN_11

#define USARTx_RX           gpio_bit_reset( USARTx_PORT, USARTx_PIN_SWITCH ) 
#define USARTx_TX           gpio_bit_set  ( USARTx_PORT, USARTx_PIN_SWITCH ) 
*/

enum confInterrupt
{
    non             = 0x00, // without interruptions
    receiveRBNE     = 0x01, // reception interruption
    transmissionTBE = 0x02, // transmitter buffer empty interrupt
    transmissionTC  = 0x04, // ransmission complete interrupt
};
enum confInterruptDMAReciev
{    
    non_IRQn_Rx     = 0x00, // without interruptions
    reciev_UartIRQn = 0x80, // reception interruption thith usart
    reciev_DmaIRQn  = 0x01  // reception interruption thith dma 
};
enum confInterruptDMATransmit
{    
    non_IRQn_Tx      = 0x00,// without interruptions
    transmit_DmaIRQn = 0x01 // reception interruption thith dma 
};

#ifdef GD32F303_
#include "gd32f30x.h" 

enum usartDMA
{
    Usart0 = USART0,
    Usart1 = USART1,
    Uart3  = UART3
};
/*!
 \arg when using dma, you first call ConfigUsart, then ConfigDmaFromRecievUsart

    \brief      config USARTx
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  baudrate: USART0 <=5000000 USARTx(x=1,2)/UARTx(x=3,4) <=~2500000
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg       USART_MSBF_LSB: LSB first
      \arg       USART_MSBF_MSB: MSB first           
    \param[in]  configIrqn: bitmask from using an interrupt    (enum confInterrupt)
                only one parameter can be selected which is shown as below:
      \arg       non             - without interruptions
      \arg       recievRBNE      - reception interruption
      \arg       transmissionTBE - transmitter buffer empty interrupt
      \arg       transmissionTC  - ransmission complete interrupt
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[out] none
    \retval     none
*/
void ConfigUsart (uint32_t usart, uint32_t baudrate, uint32_t msbf, uint8_t configIrqn, uint8_t priority, uint8_t sub_priority);

/*!
 \arg when using dma, you first call ConfigUsart, then ConfigUsartDMA_Tx
    \brief      enable DMAx
    \param[in]  usart: usart_periph
    \param[in]  buf: buffer for received data
    \param[in]  lenBuf: size buffer
    \param[in]  circulationEnable: 1/0
    \param[in]  channelPriorityDMA:
                only one parameter can be selected which is shown as below:
      \arg       DMA_PRIORITY_LOW, DMA_PRIORITY_MEDIUM, DMA_PRIORITY_HIGH, DMA_PRIORITY_ULTRA_HIGH
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[in]  iRQn: bitmask from using an interrupt    (enum confInterruptTransmit)
      \arg       non_IRQn_Tx       - without interruptions
      \arg       transmit_DmaIRQn    - reception interruption DMA
    \param[out] none
    \retval     none
*/
void ConfigUsartDMA_Tx(enum usartDMA  usart, uint32_t* buf, uint32_t lenBuf, _Bool circulationEnable, 
                              uint32_t channelPriorityDMA, uint8_t priority, uint8_t sub_priority, uint8_t iRQn);
/*!
 \arg when using dma, you first call ConfigUsart, then ConfigUsartDMA_Rx
    \brief      enable DMAx
    \param[in]  usart: usart_periph
    \param[in]  buf: buffer for received data
    \param[in]  lenBuf: size buffer
    \param[in]  circulationEnable: 1/0
    \param[in]  channelPriorityDMA:
                only one parameter can be selected which is shown as below:
      \arg       DMA_PRIORITY_LOW, DMA_PRIORITY_MEDIUM, DMA_PRIORITY_HIGH, DMA_PRIORITY_ULTRA_HIGH
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[in]  iRQn: bitmask from using an interrupt    (enum confInterruptReciev)
      \arg       non_IRQn_Rx       - without interruptions
      \arg       reciev_UartIRQn   - reception interruption Usart
      \arg       reciev_DmaIRQn    - reception interruption DMA
    \param[out] none
    \retval     none
*/
void ConfigUsartDMA_Rx(enum usartDMA  usart, uint32_t* buf, uint32_t lenBuf, _Bool circulationEnable, 
                              uint32_t channelPriorityDMA, uint8_t priority, uint8_t sub_priority, uint8_t iRQn);
                              
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void UART3_IRQHandler (void);
void UART4_IRQHandler (void);

void DMA0_Channel3_IRQHandler   (void);//USART0 TX
void DMA0_Channel4_IRQHandler   (void);//USART0 RX

void DMA0_Channel6_IRQHandler   (void);//USART1 TX
void DMA0_Channel5_IRQHandler   (void);//USART1 RX

void DMA1_Channel3_4_IRQHandler (void);//UART3  TX 
void DMA1_Channel2_IRQHandler   (void);//UART3  RX
#endif
#ifdef GD32F450_
#include "gd32f4xx.h"
/*!
 \arg when using dma, you first call ConfigUsart, then ConfigDmaFromRecievUsart

    \brief      config USARTx
    \param[in]  usart: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  oversample: 
      \arg      USART_OVSMOD_8
      \arg      USART_OVSMOD_16
    \param[in]  baudrate:         
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg       USART_MSBF_LSB: LSB first
      \arg       USART_MSBF_MSB: MSB first           
    \param[in]  configIrqn: bitmask from using an interrupt    (enum confInterrupt)
                only one parameter can be selected which is shown as below:
      \arg       non             - without interruptions
      \arg       reciev          - reception interruption
      \arg       transmissionTBE - transmitter buffer empty interrupt
      \arg       transmissionTC  - ransmission complete interrupt
      \arg       recievOnDMA     - reception interruption thith dma (only USARTx(x=0,1)/UART3)
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[out] none
    \retval     none
    
    \example: ConfigUsart(USART0,5000000,receive,0,4);
*/
void ConfigUsart(uint32_t usart, uint8_t oversample, uint32_t baudrate, uint32_t msbf, uint8_t configIrqn, uint8_t priority, uint8_t sub_priority);
/*!
 \arg when using dma, you first call ConfigUsart, then ConfigUsartDMA_Tx
    \brief      enable DMAx
    \param[in]  usart: usart_periph
    \param[in]  buf: buffer for received data
    \param[in]  lenBuf: size buffer
    \param[in]  circulationEnable: 1/0
    \param[in]  channelPriorityDMA:
                only one parameter can be selected which is shown as below:
      \arg       DMA_PRIORITY_LOW, DMA_PRIORITY_MEDIUM, DMA_PRIORITY_HIGH, DMA_PRIORITY_ULTRA_HIGH
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[in]  iRQn: bitmask from using an interrupt    (enum confInterruptTransmit)
      \arg       non_IRQn_Tx       - without interruptions
      \arg       transmit_DmaIRQn    - reception interruption DMA
    \param[out] none
    \retval     none
*/
void ConfigUsartDMA_Tx(uint32_t usart, uint8_t* buf, uint32_t lenBuf, _Bool circulationEnable, 
                       uint32_t channelPriorityDMA, uint8_t priority, uint8_t sub_priority, uint8_t iRQn);
/*!
 \arg when using dma, you first call ConfigUsart, then ConfigUsartDMA_Rx
    \brief      enable DMAx
    \param[in]  usart: usart_periph
    \param[in]  buf: buffer for received data
    \param[in]  lenBuf: size buffer
    \param[in]  circulationEnable: 1/0
    \param[in]  channelPriorityDMA:
                only one parameter can be selected which is shown as below:
      \arg        DMA_PRIORITY_LOW, DMA_PRIORITY_MEDIUM, DMA_PRIORITY_HIGH, DMA_PRIORITY_ULTRA_HIGH
    \param[in]  priority:     using an interrupt
    \param[in]  sub_priority: using an interrupt
    \param[in]  iRQn: bitmask from using an interrupt    (enum confInterruptReciev)
      \arg       non_IRQn_Rx       - without interruptions
      \arg       reciev_UartIRQn   - reception interruption Usart
      \arg       reciev_DmaIRQn    - reception interruption DMA
    \param[out] none
    \retval     none
*/
void ConfigUsartDMA_Rx(uint32_t usart, uint8_t* buf, uint32_t lenBuf, _Bool circulationEnable, 
                       uint32_t channelPriorityDMA, uint8_t priority, uint8_t sub_priority, uint8_t iRQn);

void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void UART3_IRQHandler (void);
void UART4_IRQHandler (void);
void USART5_IRQHandler(void);
void UART6_IRQHandler (void);
void UART7_IRQHandler (void);

void DMA0_Channel0_IRQHandler(void);// rx uart4    tx uart7
void DMA0_Channel1_IRQHandler(void);// rx usart2   tx uart6
void DMA0_Channel2_IRQHandler(void);// rx uart3
void DMA0_Channel3_IRQHandler(void);// rx uart6    tx usart2
void DMA0_Channel5_IRQHandler(void);// rx usart1
void DMA0_Channel6_IRQHandler(void);// rx uart7    tx usart1
void DMA0_Channel7_IRQHandler(void);//             tx uart4
void DMA0_Channel4_IRQHandler(void);//             tx uart3

void DMA1_Channel1_IRQHandler(void);// rx usart5
void DMA1_Channel5_IRQHandler(void);// rx usart0
void DMA1_Channel7_IRQHandler(void);//             tx usart0
void DMA1_Channel6_IRQHandler(void);//             tx usart5

#endif 

#if  defined(GD32F303_) && defined(GD32F450_)
#error Error ConfigurationUSARTn
#endif
#endif


#ifdef SENDING_VIA_USART
void Usart_send_byte  ( uint8_t byte, uint32_t usart_perith);
void Usart_send_buf   ( uint8_t* buf, uint32_t usart_perith, const uint32_t len);
void Usart_send_string( uint8_t* str, uint32_t usart_perith);
#endif
