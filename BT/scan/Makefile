# Makefile
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lbluetooth
TARGET = bt_scan_example
OBJS = main.o hci_manager.o

all: $(TARGET)
	
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
