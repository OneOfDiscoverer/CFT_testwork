FOLDER1 := ./SortUtility
FOLDER2 := ./TestUtility
APP_PATH := $(FOLDER2)/main.out

all: build test

build:
	@echo "Compile $(FOLDER1)"
	@$(MAKE) -C $(FOLDER1)
	@echo "\nComlile $(FOLDER2)"
	@$(MAKE) -C $(FOLDER2)

test:
	@echo "\nRun test"
	@$(APP_PATH)

clean:
	@$(MAKE) -C $(FOLDER1) clean
	@$(MAKE) -C $(FOLDER2) clean

.PHONY: all build clean
