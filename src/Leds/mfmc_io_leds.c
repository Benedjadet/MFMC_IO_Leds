

/**
 * Company: MFMC LLC
 * Author: Kurdelias E.U.
 * Date: 2023-04-11
*/


#include "mfmc_io_leds.h"
#ifdef DEBUGGING
#include <stdio.h>
#endif

MFMC_IO_LEDS_PIN_TypeDef MFMC_IO_LEDS_List[MFMC_IO_LEDS_MAX] = {
	{MFMC_IO_LEDS_D1_PORT, MFMC_IO_LEDS_D1_PIN},
	{MFMC_IO_LEDS_D2_PORT, MFMC_IO_LEDS_D2_PIN},
	{MFMC_IO_LEDS_D3_PORT, MFMC_IO_LEDS_D3_PIN},
	{MFMC_IO_LEDS_D4_PORT, MFMC_IO_LEDS_D4_PIN},
	{MFMC_IO_LEDS_D5_PORT, MFMC_IO_LEDS_D5_PIN},
	{MFMC_IO_LEDS_D6_PORT, MFMC_IO_LEDS_D6_PIN},
	{MFMC_IO_LEDS_D7_PORT, MFMC_IO_LEDS_D7_PIN},
	{MFMC_IO_LEDS_D8_PORT, MFMC_IO_LEDS_D8_PIN},
	{MFMC_IO_LEDS_ERROR_PORT, MFMC_IO_LEDS_ERROR_PIN},
	{MFMC_IO_LEDS_RUN_PORT, MFMC_IO_LEDS_RUN_PIN},
};
MFMC_IO_LEDS_MODE_TypeDef MFMC_IO_LEDS_State[MFMC_IO_LEDS_MAX] = {
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
	MFMC_IO_LEDS_MODE_OFF,
};
uint8_t MFMC_IO_LEDS_Pulse = 0;
uint8_t MFMC_IO_LEDS_Phase = 0;
uint32_t MFMC_IO_LEDS_Time = 0;

MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_NumIsOk(uint16_t Num);
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_Set(MFMC_IO_LEDS_NUM_TypeDef Num, BitAction Value);
uint8_t MFMC_IO_LEDS_Loop(void);
uint16_t MFMC_IO_LEDS_Calc(MFMC_IO_LEDS_MODE_TypeDef status);

/**
 * @brief Прверка номера светодиода.
 * Функция проверяет являится значение Num доступным для ввода.
 * @param Num Номер светодиода.
 * @return MFMC_IO_LEDS_STATUS_TypeDef
 */
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_NumIsOk(uint16_t Num)
{
	if ((Num < MFMC_IO_LEDS_MAX) && (MFMC_IO_LEDS_List[Num].Port != 0))
	{
		return MFMC_IO_LEDS_STATUS_OK;
	}
	return MFMC_IO_LEDS_STATUS_ERROR;

	//return MFMC_IO_LEDS_STATUS_OK;
}

/**
 * @brief Инициализация светодиодов.
 * Функция настраивает GPIO светодиодов в соответствии с файлом конфигурации mfmc_io_leds.h.
 * @return MFMC_IO_LEDS_STATUS_TypeDef
 */
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_Init(void)
{
	GPIO_InitTypeDef LedSettings = {0};

	for (uint8_t i = 0; i < MFMC_IO_LEDS_MAX; i++)
	{
		if (MFMC_IO_LEDS_NumIsOk(i) == MFMC_IO_LEDS_STATUS_OK)
		{
			LedSettings.GPIO_Mode = GPIO_Mode_Out_PP;
			LedSettings.GPIO_Pin = MFMC_IO_LEDS_List[i].Pin;
			LedSettings.GPIO_Speed = GPIO_Speed_10MHz;
			GPIO_TypeDef* Port = MFMC_IO_LEDS_List[i].Port;
			uint16_t Pin = MFMC_IO_LEDS_List[i].Pin;
			GPIO_Init(Port, &LedSettings);
			GPIO_WriteBit(Port, Pin, RESET);
		}
	}
	#ifdef DEBUGGING
	printf("Init\n");
	#endif
	return MFMC_IO_LEDS_STATUS_OK;
}

/**
 * @brief Установить состояние светодиа.
 * Функция устанавливает состояние светодиода.
 * @param Num Номер светодиода.
 * @param Value Состояние светодиодаю
 * @return MFMC_IO_LEDS_STATUS_TypeDef
 */
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_Set(MFMC_IO_LEDS_NUM_TypeDef Num, BitAction Value)
{
	if (MFMC_IO_LEDS_NumIsOk(Num) == MFMC_IO_LEDS_STATUS_OK)
	{
		GPIO_TypeDef* Port = MFMC_IO_LEDS_List[Num].Port;
		uint16_t Pin = MFMC_IO_LEDS_List[Num].Pin;
		GPIO_WriteBit(Port, Pin, Value);
		return MFMC_IO_LEDS_STATUS_OK;
	}
	return MFMC_IO_LEDS_STATUS_ERROR;
}

/**
 * @brief Установить режим светодиода.
 * Функция устанавливает режим мигания светодиода.
 * @param Num Номер светодиода. *
 * @param Mode Режим мигания светодиода. *
 * @return MFMC_IO_LEDS_STATUS_TypeDef
 */
MFMC_IO_LEDS_STATUS_TypeDef MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_NUM_TypeDef Num, MFMC_IO_LEDS_MODE_TypeDef Mode)
{
	if (MFMC_IO_LEDS_NumIsOk(Num) == MFMC_IO_LEDS_STATUS_OK)
	{
		MFMC_IO_LEDS_State[Num] = Mode;
		return MFMC_IO_LEDS_STATUS_OK;
	}
	return MFMC_IO_LEDS_STATUS_ERROR;
}

/**
 * @brief Циклический вызов для реализации мигания.
 * Функция реализует эфект мигания.
 * @return Возвращает 1 при изменении фазы мигания.
 */
uint8_t MFMC_IO_LEDS_Loop(void)
{
	uint32_t millisNum = (uint32_t)MFMC_IO_LEDS_GetMs();
	uint8_t Trigger = 0;

	if (MFMC_IO_LEDS_Pulse && ((millisNum - MFMC_IO_LEDS_Time) >= MFMC_IO_LEDS_DURATION))
	{
		MFMC_IO_LEDS_Pulse = 0;
		MFMC_IO_LEDS_Time = millisNum;
		MFMC_IO_LEDS_Phase++;
		Trigger = 1;
		if (MFMC_IO_LEDS_Phase > 3)
		{
			MFMC_IO_LEDS_Phase = 0;
		}
	}
	else if (!MFMC_IO_LEDS_Pulse && ((millisNum - MFMC_IO_LEDS_Time) >= MFMC_IO_LEDS_INTERVAL))
	{
		MFMC_IO_LEDS_Pulse = 1;
		MFMC_IO_LEDS_Time = millisNum;
		Trigger = 1;
	}

	return Trigger;
}

/**
 * @brief Рассчитать состояния светодиода.
 * Функция расчитывает состояние всетодиода в данный момент времени.
 * @param Mode Режим мигания светодиода.
 * @return 1 если светодилд должен гореть, иначе 0.
 */
uint16_t MFMC_IO_LEDS_Calc(MFMC_IO_LEDS_MODE_TypeDef Mode)
{
	uint16_t Result = 0;
	if (Mode == MFMC_IO_LEDS_MODE_ON)
	{
		Result = 1;
	}
	else if ((Mode == MFMC_IO_LEDS_MODE_LONG_BLINK) && (MFMC_IO_LEDS_Pulse || !MFMC_IO_LEDS_Pulse) && (MFMC_IO_LEDS_Phase < 3))
	{
		Result = 1;
	}
	 else if ((Mode == MFMC_IO_LEDS_MODE_ONE_BLINK) && MFMC_IO_LEDS_Pulse && (MFMC_IO_LEDS_Phase < 1))
	{
		Result = 1;
	}
	else if ((Mode == MFMC_IO_LEDS_MODE_TWO_BLINK) && MFMC_IO_LEDS_Pulse && (MFMC_IO_LEDS_Phase < 2))
	{
		Result = 1;
	}
	else if ((Mode == MFMC_IO_LEDS_MODE_THREE_BLINK) && MFMC_IO_LEDS_Pulse && (MFMC_IO_LEDS_Phase < 3))
	{
		Result = 1;
	}
	else if ((Mode == MFMC_IO_LEDS_MODE_FOUR_BLINK) && MFMC_IO_LEDS_Pulse && (MFMC_IO_LEDS_Phase <= 3))
	{
		Result = 1;
	}
	else
	{
		Result = 0;
	}
	return Result;
}

/**
 * @brief Управление светодиодами.
 * Функция управляет светодиодами в соответствии с режимом который для них установлен.
 * Должна вызываться в бесконечном цикле.
 */
void MFMC_IO_LEDS_Control()
{
	uint8_t Result = MFMC_IO_LEDS_Loop();

	if(Result)
	{
		for (uint8_t i = 0; i < MFMC_IO_LEDS_MAX; i++)
		{
			uint8_t state = MFMC_IO_LEDS_Calc(MFMC_IO_LEDS_State[i]);

			if (state)
			{
				MFMC_IO_LEDS_Set(i, SET);
			}
			else
			{
				MFMC_IO_LEDS_Set(i, RESET);
			}
		}
		#ifdef DEBUGGING
		printf("Calc\n");
		#endif
	}
}

/**
 * @brief Получить время в мс.
 * Функция возвращает время пройденное с запуска процессора в милисекундах.
 * @warning Эта функция оьявлена с атрибутом __WEAK и должна быть переобьявлена пользователем.
 * @return Возврашает время в мс.
 */
__WEAK uint32_t MFMC_IO_LEDS_GetMs(void)
{
	return 0;
}