#ifndef __MFMC_IO_LEDS_H__
#define __MFMC_IO_LEDS_H__

/**
 * Company: MFMC LLC
 * Author: Kurdelias E.U.
 * Date: 2023-04-11
*/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "mfmc_io_leds_conf.h"

#define MFMC_IO_LEDS_MAX (10)

/**
 * @brief Перечисление доступных светодиодов.
 * Здесь перечислены все светодиоды доступные для упрвления.
 * @warning Для выбора светодиода используйте определения из этого перечисления. Не используйте целочисленные значения.
 * @param MFMC_IO_LEDS_D1
 * @param MFMC_IO_LEDS_D2
 * @param MFMC_IO_LEDS_D3
 * @param MFMC_IO_LEDS_D4
 * @param MFMC_IO_LEDS_D5
 * @param MFMC_IO_LEDS_D6
 * @param MFMC_IO_LEDS_D7
 * @param MFMC_IO_LEDS_D8
 * @param MFMC_IO_LEDS_ERROR
 * @param MFMC_IO_LEDS_RUN
 */
typedef enum
{
	MFMC_IO_LEDS_D1,
	MFMC_IO_LEDS_D2,
	MFMC_IO_LEDS_D3,
	MFMC_IO_LEDS_D4,
	MFMC_IO_LEDS_D5,
	MFMC_IO_LEDS_D6,
	MFMC_IO_LEDS_D7,
	MFMC_IO_LEDS_D8,
	MFMC_IO_LEDS_ERROR,
	MFMC_IO_LEDS_RUN
} MFMC_IO_LEDS_NUM_TypeDef;

/**
 * @brief Структура определяющая вывод светодиода.
 * @param Port Адрес порта вывода.
 * @param Pin Номер вывода.
 */
typedef struct
{
	GPIO_TypeDef* Port;
	uint16_t Pin;
} MFMC_IO_LEDS_PIN_TypeDef;

/**
 * @brief Перечисление режимов светодиода.
 * @param MFMC_IO_LEDS_MODE_OFF Светодиод отключен.
 * @param MFMC_IO_LEDS_MODE_ON	Светодиод включен всегда.
 * @param MFMC_IO_LEDS_MODE_ONE_BLINK Светодиод делает одно короткое мигание.
 * @param MFMC_IO_LEDS_MODE_TWO_BLINK Светодиод делает два коротких мигания.
 * @param MFMC_IO_LEDS_MODE_THREE_BLINK Светодиод делает три коротких мигания.
 * @param MFMC_IO_LEDS_MODE_FOUR_BLINK Светодиод делает непрерывные короткие мигания.
 * @param MFMC_IO_LEDS_MODE_LONG_BLINK Светодиод делает длинное мигание с заполнением 3/1 от цикла мигания.
 */
typedef enum
{
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_ON,
	MFMC_IO_LEDS_MODE_ONE_BLINK,
	MFMC_IO_LEDS_MODE_TWO_BLINK,
	MFMC_IO_LEDS_MODE_THREE_BLINK,
	MFMC_IO_LEDS_MODE_FOUR_BLINK,
	MFMC_IO_LEDS_MODE_LONG_BLINK,
} MFMC_IO_LEDS_MODE_TypeDef;

/**
 * @brief Перечисление состояний.
 * @param MFMC_IO_LEDS_STATUS_OK Успешное выполнение.
 * @param MFMC_IO_LEDS_STATUS_ERROR Ошибка при выполнении.
 */
typedef enum
{
	MFMC_IO_LEDS_STATUS_OK,
	MFMC_IO_LEDS_STATUS_ERROR,
} MFMC_IO_LEDS_STATUS_TypeDef;

MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_Init(void);
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_NUM_TypeDef Num, MFMC_IO_LEDS_MODE_TypeDef Mode);
void MFMC_IO_LEDS_Control(void);
uint32_t MFMC_IO_LEDS_GetMs(void);

#endif /* __MFMC_IO_LEDS_H__ */
