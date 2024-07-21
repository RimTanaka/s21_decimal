CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
DEBUG_FLAG= -g
COVFLAGS=-fprofile-arcs -ftest-coverage

C_FILES = $(wildcard arithmetic/*.c compares/*.c converters/*.c helpers/*.c other/*.c)

O_FILES = $(subst .c,.o, $(C_FILES))

# Директория для тестов
TEST_DIR=./tests/
TEST_FILES=$(wildcard ./tests/*.c)
OUT_TEST=$(TEST_DIR)test.out
OS := $(shell uname -s)

# Флаги для линукса отдельно
ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
	TEST_LIBS = -lcheck -lsubunit -lrt -lm -pthread
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
	TEST_LIBS = -lcheck
endif

all: s21_decimal.a

s21_decimal.a: $(O_FILES)
	ar rcs s21_decimal.a $^
	ranlib s21_decimal.a

test: rebuild
	${OUT_TEST}

build: clean
	$(CC) $(CFLAGS) -o ${OUT_TEST} $(C_FILES) $(TEST_FILES) $(TEST_LIBS)

debug: clean
	$(CC) $(CFLAGS) $(DEBUG_FLAG) -o ${OUT_TEST} $(C_FILES) $(TEST_FILES) $(TEST_LIBS)

gcov_report:
	$(CC) $(CFLAGS) --coverage $(C_FILES) $(TEST_FILES) -o gcov_test $(TEST_LIBS)
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	$(OPEN_CMD) ./report/index.html

valgrind: rebuild
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt $(OUT_TEST)
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY' 

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n */*.c */*.h
	rm .clang-format

format_style:
	cp ../materials/linters/.clang-format .
	clang-format -i */*.c */*.h
	rm .clang-format

clean: clean_test
	rm -rf */*.o s21_decimal.a *.out report debug test.out leaks_log.txt

clean_test:
	rm -rf *.gc* *.info gcov_test ./tests/report ./tests/*.out

rebuild: clean build

# Собираем docker image с тегом 'v1' на основании dockerfile и создаем контейнер
docker_build:
	cp ../materials/linters/.clang-format ./
	docker build -t vault:v1 .
	docker create -it --name decimal_vault vault:v1

# Запускаем контейнер
docker_start:
	docker start -i decimal_vault

docker_delete:
	docker rm decimal_vault
	docker image rm vault:v1
