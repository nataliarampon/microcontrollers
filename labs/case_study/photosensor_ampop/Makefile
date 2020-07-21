TARGET=photosensor_ampop
SRCS=$(TARGET).c

#FLAGS=-O2 -Wall -g -MMD -DTRIG_SYSFS
FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I. -I./../include
LIBDIR=-L../lib
LIBS=-lgalileo2 -lm

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET) transfer

$(TARGET): $(SRCS:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

transfer:
	scp ../init.d/config_$(TARGET) $(TARGET) galileo:

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
