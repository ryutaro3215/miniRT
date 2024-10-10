CC = cc
CFLAG = -Wall -Wextra -Werror 
DEBUG_CFLAG = -Wall -Wextra -Werror -fsanitize=address -g
NAME = minirt 
DEBUG_NAME = minirt_debug
SRC = main.c check_file.c color.c hook.c init_data.c utils.c vec_culc.c phong.c ray_cross.c search_nearest_obj.c is_shadow.c \
        sphere.c plane.c cylinder.c cylinder_utils.c free_env.c free_scene.c init_camera.c init_cylinder.c init_light.c init_plane.c \
                init_scene.c init_sphere.c vec_culc2.c vec_culc3.c  color_utils.c calc_color.c reflection_calc.c
OBJDIR = objs
DEBUG_OBJDIR = debug_objs
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEBUG_OBJ = $(SRC:%.c=$(DEBUG_OBJDIR)/%.o)
LIBFT_DIR = libft
LIBFT = ft
MLX_DIR = minilibx-linux
MLX = mlx
INCLUDE = -I $(LIBFT_DIR) -I $(MLX_DIR) -I includes -I /usr/local/include
LIBRARY = -L$(MLX_DIR) -l$(MLX) -L/usr/local/lib -lX11 -lXext -lm -L$(LIBFT_DIR) -l$(LIBFT) 

vpath %.c check_file color hook init utils vec ray_cross shadow

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) $(INCLUDE) $(LIBRARY) -lm
	@echo "Compilation done"

$(DEBUG_NAME): $(DEBUG_OBJ)
	make -C $(LIBFT_DIR) > /dev/null
	make -C $(MLX_DIR) > /dev/null
	$(CC) $(DEBUG_CFLAG) $(DEBUG_OBJ) -o $(DEBUG_NAME) $(INCLUDE) $(LIBRARY) -lm
	@echo "Debug compilation done"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@
	@echo "Compiled $< successfully"

$(DEBUG_OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_CFLAG) $(INCLUDE) -c $< -o $@
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
