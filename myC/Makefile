CFLAGS=-Wall -Werror -g
CFLAGS+= `pkg-config --cflags libpcre`

LDLIBS=-lreadline
LDLIBS+= `pkg-config --libs libpcre`
LDLIBS+=types.c linkedlist.c reader.c

all:
	make step0_repl
	make step1_repl
	make test
test:
	make tests/linkedlist_test
	make tests/reader_test
	make tests/types_test
run_tests:
	valgrind ./tests/types_test && \
	valgrind ./tests/linkedlist_test && \
	valgrind ./tests/reader_test
clean:
	rm -f step*_repl
	rm -f tests/*_test
