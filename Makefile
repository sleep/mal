CFLAGS=-Wall -Werror -g
CFLAGS+= `pkg-config --cflags libpcre`

LDLIBS=-lreadline
LDLIBS+= `pkg-config --libs libpcre`

all:
	make step0_repl
	make step1_repl
	make test
test:
	make tests/linkedlist_test
clean:
	rm -f step*_repl
	rm -f tests/*_test
