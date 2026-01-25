CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lluxfhe -lm

TARGET = fhe_demo

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean
