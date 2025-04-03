NAME = cub3D
NAMEBONUS = cub3D
CC := cc
CFLAGS := -Wall -Wextra  \
	-I ./include -I ./src/libft -I ./src/printf -I ./src/get_next_line -I ./MLX42/include
LIBFT := ./src/libft
PRINTF := ./src/printf
GETNEXTLINE := ./src/get_next_line
LIBMLX := ./MLX42
HEADERS = -I $(LIBMLX)/include/MLX42
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm \
	$(LIBFT)/libft.a $(PRINTF)/libftprintf.a $(GETNEXTLINE)/get_next_line.a

SRCS := main.c init_map.c check_map.c tools.c game.c map_tools.c math_tools.c render.c render_tools.c game_action.c\
	$(shell find ./src -iname "*.c")
# SRCSB := ./bonus/so_long_bonus.c ./bonus/parsingmap_bonus.c ./bonus/parsingmap_utils_bonus.c ./bonus/posehook_bonus.c  ./bonus/spirit_hook_bonus.c\
# 	./bonus/hook_utils_bonus.c ./bonus/key_hook_bonus.c ./bonus/map_algorithm_bonus.c ./bonus/initgame_bonus.c ./bonus/initgame_util_bonus.c ./bonus/delete_bonus.c ./bonus/hook_bonus.c \

OBJS := ${SRCS:.c=.o}
# OBJSB := ${SRCSB:.c=.o}
REPO_URL=https://github.com/codam-coding-college/MLX42.git
REPO_DIR=MLX42

all: clone libmlx $(NAME)

bonus: clone libmlx $(NAMEBONUS)

clone:
	@if [ ! -d "$(REPO_DIR)" ]; then \
		git clone $(REPO_URL); \
	else \
		echo "$(REPO_DIR) already exists."; \
	fi

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4


%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${MAKE} -C ${GETNEXTLINE}
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

# $(NAMEBONUS): $(OBJSB)
# 	${MAKE} -C ${LIBFT}
# 	${MAKE} -C ${PRINTF}
# 	${MAKE} -C ${GETNEXTLINE}
# 	@$(CC) $(OBJSB) $(LIBS) $(HEADERS) -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJS) $(OBJSB)
	@rm -rf $(LIBMLX)/build
	${MAKE} -C ${LIBFT} fclean
	${MAKE} -C ${PRINTF} clean
	${MAKE} -C ${GETNEXTLINE} clean

fclean: clean
	@rm -rf $(NAME) $(NAMEBONUS)

re: fclean all

.PHONY: all clean fclean re bonus clone
