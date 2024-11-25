
CC = cc
CFLAGS = -Wall -Wextra -Werror  -fPIC
AR = ar
ARFLAGS = rcs
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
LIB = get_next_line.a

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re: fclean all
