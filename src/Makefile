CC = gcc
FLAG_C = -c
FLAG_O = -o
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra

all: clean gcov_report

s21_math.a:
	$(CC) $(FLAG_ER) $(FLAG_C) s21_math.c
	ar rc s21_math.a s21_math.o
	ranlib s21_math.a

test: s21_math.a
	$(CC) $(FLAG_ER) $(FLAG_C) tests.c main.c 
	ar rc suite.a tests.o
	ranlib suite.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_math.a suite.a s21_math.c main.o tests.o -lcheck -lm -lpthread
	./test

test_ubuntu: s21_math.a
	$(CC) $(FLAG_ER) $(FLAG_C) tests.c main.c 
	ar rc suite.a tests.o
	ranlib suite.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_math.a suite.a s21_math.c main.o tests.o -lcheck -lsubunit -lm -lpthread
	./test


gcov_report: test
	gcov s21_*.gcda	
	gcovr
	gcovr --html-details -o report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f test
	-rm -f report