CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o task.o sim.o output.o
TARGET = scheduler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c task.h sim.h output.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) rate_ddc.out edf_ddc.out