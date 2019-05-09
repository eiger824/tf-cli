CC		 := gcc
CFLAGS	 := -Wall -Wextra -std=c11 -g -lcurl

PROGRAMS := tf-monitor \
	tf-config \
	tf-query \
	tf-configdb

all: $(PROGRAMS)

tf-monitor: monitor.c
	$(CC) -o $@ $< $(CFLAGS)

tf-config: config.c
	$(CC) -o $@ $< $(CFLAGS)

tf-query: query.c
	$(CC) -o $@ $< $(CFLAGS)

tf-configdb: configdb.c
	$(CC) -o $@ $< $(CFLAGS)
