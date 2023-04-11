#ifndef __MFMC_IO_LEDS_CONF_H__
#define __MFMC_IO_LEDS_CONF_H__

/**
 * Company: MFMC LLC
 * Author: Kurdelias E.U.
 * Date: 2023-04-11
*/

/**
 * ИНСТРУКЦИЯ ПО ПОДКЛЮЧЕНИЮ БИБЛИОТЕКИ
 ******************************************************************************
 * 	1. 	Подключите заголовочный файл mfmc_io_leds.h к вашему проекту.
 * 			#include "mfmc_io_leds.h"
 * 	2. 	(ЕСЛИ НЕОБХОДИМО) Добавте в проект пути для поиска заголовочных и
 *		исходных файлов.
 * 	3. 	Настройте данный файл согласно схеме подключения всетодиодов.
 * 			Если светодиод D3 подключен к выводу PC13 укажите следующее:
 * 			#define MFMC_IO_LEDS_D3_PORT		GPIOС
 *			#define MFMC_IO_LEDS_D3_PIN			GPIO_Pin_13
 * 	4. 	Переопределите функцию uint32_t MFMC_IO_LEDS_GetMs() 
 * 		она должна возвращать время пройдено с момента запуска МК.
 * 	5. 	(ВАЖНО) Библиотека не настраивает перефирию МК поэтому пользователю 
 * 		необходимо разрешить тактирование необходимых портов GPIO.
 * 	6. 	Для инициализации портов GPIO вызвать функцию MFMC_IO_LEDS_Init().
 * 	7. 	В теле программы без условий вызывать вункцию MFMC_IO_LEDS_Control().
 * 	8. 	Для изменения режима мигания используйте функцию MFMC_IO_LEDS_SetMode().
 *
 ******************************************************************************
 * 	ПРИМЕР:
 *
 * 	#include "mfmc_io_leds.h"
 *
 * 	int main()
 * 	{
 *  	RCC_Init();
 *		MFMC_IO_LEDS_Init();
 *
 *		while (1)
 *		{
 *			MFMC_IO_LEDS_Control();
 *
 *			if(error)
 *			{
 *				MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_FOUR_BLINK);
 *			}
 *			else if(on)
 *			{
 *				MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_ON);
 *			}
 *			else
 *			{
 *				MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_OFF);
 *			}
 *		}
 *	}
*/

/**
 * 	НАСТНОЙКИ ПОРТОВ
 ******************************************************************************
 * 	Для настройки светодиода укажите порт к которому он подключен
 * 	в макросе  MFMC_IO_LEDS_x_PORT и номер вывода порта в макросе.
 * 	MFMC_IO_LEDS_x_PIN.
 * 	Если светодиод не использкется установите в маеросе
 * 	MFMC_IO_LEDS_х_PORT значе 0, в таком случае значение макроса
 * 	MFMC_IO_LEDS_x_PIN не имеет значения.
 *
 ******************************************************************************
*/

/* Светодиод D1 */
#define MFMC_IO_LEDS_D1_PORT		GPIOB
#define MFMC_IO_LEDS_D1_PIN			GPIO_Pin_5

/* Светодиод D2 */
#define MFMC_IO_LEDS_D2_PORT		GPIOB
#define MFMC_IO_LEDS_D2_PIN			GPIO_Pin_6

/* Светодиод D3 */
#define MFMC_IO_LEDS_D3_PORT		GPIOB
#define MFMC_IO_LEDS_D3_PIN			GPIO_Pin_7

/* Светодиод D4 */
#define MFMC_IO_LEDS_D4_PORT		GPIOB
#define MFMC_IO_LEDS_D4_PIN			GPIO_Pin_8

/* Светодиод D5 */
#define MFMC_IO_LEDS_D5_PORT		GPIOB
#define MFMC_IO_LEDS_D5_PIN			GPIO_Pin_9

/* Светодиод D6 */
#define MFMC_IO_LEDS_D6_PORT		GPIOB
#define MFMC_IO_LEDS_D6_PIN			GPIO_Pin_10

/* Светодиод D7 */
#define MFMC_IO_LEDS_D7_PORT		GPIOB
#define MFMC_IO_LEDS_D7_PIN			GPIO_Pin_11

/* Светодиод D8 */
#define MFMC_IO_LEDS_D8_PORT		GPIOB
#define MFMC_IO_LEDS_D8_PIN			GPIO_Pin_12

/* Светодиод ERROR */
#define MFMC_IO_LEDS_ERROR_PORT		GPIOB
#define MFMC_IO_LEDS_ERROR_PIN		GPIO_Pin_12

/* Светодиод RUN */
#define MFMC_IO_LEDS_RUN_PORT		GPIOB
#define MFMC_IO_LEDS_RUN_PIN		GPIO_Pin_12

/* Продолжительность фазы свечения светодиода в мс. */
#define MFMC_IO_LEDS_DURATION		200

/* Продолжительность фазы бездействия светодиода в мс. */
#define MFMC_IO_LEDS_INTERVAL		200

#endif /* __MFMC_IO_LEDS_CONF_H__ */
