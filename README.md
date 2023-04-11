
# Библиотека MFMC_IO_LEDS

## ИНСТРУКЦИЯ ПО ПОДКЛЮЧЕНИЮ БИБЛИОТЕКИ

1. Подключите заголовочный файл mfmc_io_leds.h к вашему проекту.
	```c
	#include "mfmc_io_leds.h"
	```
2. (_ЕСЛИ НЕОБХОДИМО_) Добавте в проект пути для поиска заголовочных и исходных файлов.
3. Настройте данный файл согласно схеме подключения всетодиодов. Подробнее об этом описано [здесь](#tutorial "Настройка портов").
Если светодиод D3 подключен к выводу PC13 укажите следующее:
	```c
	#define MFMC_IO_LEDS_D3_PORT	GPIOС
	#define MFMC_IO_LEDS_D3_PIN		GPIO_Pin_13
	```
4. Переопределите функцию uint32_t MFMC_IO_LEDS_GetMs() она должна возвращать время 	пройдено с момента запуска МК.

5. (__ВАЖНО__) Библиотека не настраивает перефирию МК поэтому пользователю необходимо разрешить тактирование необходимых портов GPIO.
6. Для инициализации портов GPIO вызвать функцию `MFMC_IO_LEDS_Init()`.
7. В теле программы без условий вызывать вункцию `MFMC_IO_LEDS_Control()`.
8. Для изменения режима мигания используйте функцию `MFMC_IO_LEDS_SetMode()`.

### ПРИМЕР:
```c
#include "mfmc_io_leds.h"

int main()
{
	RCC_Init();
	MFMC_IO_LEDS_Init();

	while (1)
	{
		MFMC_IO_LEDS_Control();

		if(error)
		{
			MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_FOUR_BLINK);
		}
		else if(on)
		{
			MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_ON);
		}
		else
		{
			MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_OFF);
		}
	}
}
```

## <p id="tutorial">НАСТНОЙКА ПОРТОВ</p>

Для настройки портов отредактируйте файл `mfmc_io_leds.h` для каждого светодиода укажите порт к которому он подключен в макросе  `MFMC_IO_LEDS_x_PORT` и номер вывода порта в макросе `MFMC_IO_LEDS_x_PIN`, где x - `D1..8`, `ERROR` или `RUN`.

Если светодиод не использкется, установите в маеросе `MFMC_IO_LEDS_х_PORT` значе 0, в  таком случае значение макроса `MFMC_IO_LEDS_x_PIN` не имеет значения.








