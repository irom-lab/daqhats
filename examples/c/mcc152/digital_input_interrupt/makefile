NAME = digital_input_interrupt
OBJ = $(NAME).o
LIBS = -ldaqhats -lm -lbcm_host
CFLAGS = -Wall -I/usr/local/include -g -L/opt/vc/lib
CC = gcc
EXTENSION = .c

all: $(NAME)

%.o: %$(EXTENSION) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	@rm -f *.o *~ core $(NAME)
