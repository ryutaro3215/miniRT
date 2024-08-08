CC = cc
CFLAG = -Wall -Wextra -Werror -fsanitize=address
DEBUG_CFLAG = -Wall -Wextra -Werror -fsanitize=address -g
NAME = minirt 
DEBUG_NAME = minirt_debug
SRC = main.c check_file.c color.c hook.c init_data.c utils.c vec_culc.c ray_cross.c
OBJDIR = objs
DEBUG_OBJDIR = debug_objs
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEBUG_OBJ = $(SRC:%.c=$(DEBUG_OBJDIR)/%.o)
LIBFT_DIR = libft
LIBFT = ft
MLX_DIR = minilibx-linux
MLX = mlx
INCLUDE = -I $(LIBFT_DIR) -I $(MLX_DIR) -I includes -I /usr/X11R6/include
LIBRARY = -L$(LIBFT_DIR) -l$(LIBFT) -L$(MLX_DIR) -l$(MLX) -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit

vpath %.c check_file color hook init utils vec ray_cross

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR) > /dev/null
	make -C $(MLX_DIR) > /dev/null
	@$(CC) $(CFLAG) $(LIBRARY) $(OBJ) -o $(NAME)
	@echo "Compilation done"

$(DEBUG_NAME): $(DEBUG_OBJ)
	make -C $(LIBFT_DIR) > /dev/null
	make -C $(MLX_DIR) > /dev/null
	@$(CC) $(DEBUG_CFLAG) $(CFLAG) $(LIBRARY) $(DEBUG_OBJ) -o $(DEBUG_NAME)
	@echo "Debug compilation done"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@
	@echo "Compiled $< successfully"

$(DEBUG_OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(DEBUG_CFLAG) $(CFLAG) $(INCLUDE) -c $< -o $@
	@echo "Compiled $< for debugging successfully"

clean:
	@rm -rf $(OBJDIR)
	@echo "Objs deleted"
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Clean done"

debug_clean:
	@rm -rf $(DEBUG_OBJDIR)
	@echo "Debug objs deleted"
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Debug objs deleted"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Fclean done"

debug_fclean: debug_clean
	@rm -rf $(DEBUG_NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Debug fclean done"

re: fclean all

debug: $(DEBUG_NAME)

.PHONY: all clean fclean re debug
