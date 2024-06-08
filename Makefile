NAME = cub3d
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = ./libft/
MINILIBX=$(LIBFT_PATH)/libmlx_Linux.a
MINILIBX_PATH=minilibx-linux
INCDIR = ./includes/
GNLDIR = ./get_next_line/
SRCSDIR = ./
OBJDIR = ./objs/

SOURCES = $(wildcard $(SRCSDIR)*.c)
SOURCES += $(wildcard $(GNLDIR)*.c)
OBJECTS = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

CC = cc
LDFLAGS += -L$(MINILIBX_PATH)
LDFLAGS += -L$(LIBFT_PATH)
LDFLAGS += -lmlx_Linux
LDFLAGS += -lX11
LDFLAGS += -lXext
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)$(GNL_DIR) -g3

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	@echo "Linking $@ || NEED FIXING, MAKEFILE IS RELINKING"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) -lft
	@echo "$@ has been successfully built!"

$(LIBFT):
	@echo "Building $(LIBFT) library"
	@make -C $(LIBFT_PATH) >/dev/null 2>&1

$(MINILIBX):
	@echo "Building $(MINILIBX) library"
	@make -C $(MINILIBX_PATH) >/dev/null 2>&1

$(OBJDIR)%.o: $(SRCSDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(GNLDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning objects"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_PATH) clean >/dev/null 2>&1
	@make -C $(MINILIBX_PATH) clean >/dev/null 2>&1

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean >/dev/null 2>&1
	@echo "Cleaning MiniLibX"
	@make -C $(MINILIBX_PATH) clean >/dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus