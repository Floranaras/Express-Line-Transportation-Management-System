CC = gcc
CFLAGS = -Wall -std=c99
TARGET = arrows_express
SOURCE = arrows_express.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET) *.o test*_output.txt Trip-*.txt

test: $(TARGET)
	chmod +x test_arrows.sh
	./test_arrows.sh

.PHONY: all clean test