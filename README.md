# EvacuationC

**EvacuationC** -- программа моделирования движения людей в здании.

Резульататом работы программы является время освобождения здания (длительность эвакуации).

# Структура проекта

```
.
├── res             -- Ресурсы. Файлы зданий
├── src             -- Исходные коды программы
├── test            -- Тесты
└── thirdparty      -- Библиотеки, используемые в программе
    ├── arraylist   -- Библиотека для работы с динамическим списком
    ├── c-logger    -- Библиотека для логгирования
    ├── json-c      -- Библиотека для работы с json-файлами
    └── triangle    -- Библиотека для триангуляции поверхности
```

# Сборка

## Интсрументарий

- cmake >= 3.16
- gcc-10 или clang-11 (для Windows рекомендуется использовать MinGW)
- ninja последней версии

1. Скачать репозиторий`git clone https://github.com/bvchirkov/EvacuationC` (неактуально для ветки master на данный момент. TODO: удалить это примечание после внесения изменений в master ветку)
2. Перейти в директорию `cd EvacuationC`
3. Запуск сборки CMake `cmake -G Ninja -B build`
4. Компиляция `cmake --build build`

Исполняемый файл будет находиться в директории build

Использование проекта в качестве пакета для Python3:  
`pip install git+https://github.com/NikBel3476/EvacuationC.git`

# Запуск

Настройки моделируемого сценария задаются в файле-сценарии. Он состоит из нескольких секций:

```
{
  "bim": [],                 -- список цифровых моделей зданий,
  "logger_configure": "",    -- путь к файлу с настроками логгирования
  "distribution": {},        -- настройки распределения людей в здании
  "transits": {},            -- настройки ширины проемов в здании
  "modeling": {}             -- настройки модели движения людского потока в здании
}
```

Примечание: при использовании относительных путей в списке цифровых моделей зданий необходимо учитывать путь от места вызова исполняемого файла

### distribution

Через блок `distribution` можно задать выбрать тип (`type`) распределения людей в здании:

```
uniform   -- равномерное распределение людей в здании с заданной плотностью (density)
from_bim  -- распеделение, которое задано в пространственно-информационной модели здания
```

В поле `density` указывается плотность начального количества людей, чел./м^2

В блоке `special` можно указать специальные настройки для одного или группы областей здания.
Этот блок обрабатывается всегда.

```
"distribution": {
    "type":"uniform",
    "density": 0.1,
    "special": [
        {
            "uuid": [
            "87c49613-44a7-4f3f-82e0-fb4a9ca2f46d"
            ],
            "density": 1.0,
            "_comment": "The uuid is Room_1 by three_zone_three_transit"
        }
    ]
  }
```

### transits

### modeling
