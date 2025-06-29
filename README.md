Сборка в корне make (собирается утилита сортировки и утилита для тестирования)
	make собирает все утилиты и тестирует. 
	make test выполняет тест. 
	make build только собирает.
В каталоге /SortUtility 
	make собирает основную утилиту. Запуск ./main.out [path to file 1][path to file 2][path to result file]
	make generator собирает утилиту генерации mock файлов (примеры statdata1.bin & statdata2.bin). Запуск ./generate_statdata [filename.bin]
В каталоге /TestUtility
	make собирает утилиту для тестирования. Запуск ./main.out
