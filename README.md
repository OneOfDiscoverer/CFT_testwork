````markdown
# 🛠 Утилиты для сортировки и тестирования

## 📁 Сборка из корня проекта

make
````

* Собирает все утилиты (`SortUtility`, `TestUtility`)
* Выполняет тестирование

Дополнительные команды:

```bash
make test     # Выполняет тесты
make build    # Только собирает, без запуска тестов
```

## 📂 Каталог `/SortUtility`

Содержит утилиту сортировки и генератор тестовых данных.

### 🔧 Сборка

```bash
make
```

Собирает основную утилиту сортировки.

### ▶️ Запуск утилиты сортировки

```bash
./main.out [input_file_1] [input_file_2] [output_result_file]
```

Пример:

```bash
./main.out statdata1.bin statdata2.bin result.bin
```

### 🧪 Генератор mock-файлов

Сборка генератора:

```bash
make generator
```

Запуск генерации файла:

```bash
./generate_statdata [filename.bin]
```

Пример:

```bash
./generate_statdata statdata1.bin
```

## 📂 Каталог `/TestUtility`

Содержит утилиту для тестирования.

### 🔧 Сборка

```bash
make
```

### ▶️ Запуск тестов

```bash
./main.out
```
