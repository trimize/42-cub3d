NAME = cub3d
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = ./libft/
MINILIBX=$(MINILIBX_PATH)/libmlx_Linux.a
MINILIBX_PATH=minilibx-linux
INCDIR = ./includes/
GNLDIR = ./get_next_line/
SRCSDIR = ./srcs/
OBJDIR = ./objs/

SOURCES = $(wildcard $(SRCSDIR)*.c)
SOURCES += $(wildcard $(GNLDIR)*.c)
OBJECTS = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

CC = cc
LDFLAGS = -L$(MINILIBX_PATH) -L$(LIBFT_PATH) -lmlx_Linux -lX11 -lXext -lm
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(GNLDIR) -g3

all: $(NAME)

bonus: all

$(NAME): $(OBJECTS) $(LIBFT) $(MINILIBX) 
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) -lft
	@echo "$@ has been successfully built!"

$(LIBFT):
	@echo "Building $(LIBFT) library"
	@$(MAKE) -C $(LIBFT_PATH) >/dev/null 2>&1

$(MINILIBX):
	@echo "Building $(MINILIBX) library"
	@$(MAKE) -C $(MINILIBX_PATH) >/dev/null 2>&1

$(OBJDIR)%.o: $(SRCSDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(GNLDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning objects"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_PATH) clean >/dev/null 2>&1
	@$(MAKE) -C $(MINILIBX_PATH) clean >/dev/null 2>&1

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean >/dev/null 2>&1
	@echo "Cleaning MiniLibX"
	@$(MAKE) -C $(MINILIBX_PATH) clean >/dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus