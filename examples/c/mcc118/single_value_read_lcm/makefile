NAME = single_value_read_lcm
OBJ = $(NAME).o
LIBS = -ldaqhats -lm -lbcm_host
CFLAGS = -Wall -I/usr/local/include -I./ -g -L/opt/vc/lib `pkg-config --cflags lcm`
LDFLAGS=`pkg-config --libs lcm`
CC = gcc
EXTENSION = .c

all: $(NAME)

%.o: %$(EXTENSION) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f *.o *~ core $(NAME)
