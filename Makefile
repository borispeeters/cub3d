# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/24 18:35:09 by bpeeters       #+#    #+#                 #
#    Updated: 2020/03/02 09:51:01 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = bmp.c check_map.c draw_sprite.c error_exit.c events.c fc_tex.c game.c \
	  get_next_line_utils.c get_next_line.c main.c movement.c parse_color.c \
	  parse_cub.c parse_res.c parse_tex.c parse_utils.c ray_utils.c raycalc.c \
	  raycast.c set_pos.c sprite.c store_map.c create_title.c \
	  allocate_map_sprites.c
OBJ = $(SRC:.c=.o)
B_SRC = bmp.c check_map.c draw_sprite.c error_exit.c events.c fc_tex.c \
		game_bonus.c get_next_line_utils.c get_next_line.c main.c \
		movement_bonus.c parse_color.c parse_cub_bonus.c parse_res.c \
		parse_tex.c parse_utils_bonus.c ray_utils.c raycalc.c raycast_bonus.c \
		set_pos.c sprite.c store_map.c health.c game_over.c hp_system_bonus.c \
		create_title.c allocate_map_sprites.c
B_OBJ = $(B_SRC:.c=.o)
BMP = screenshot.bmp
CFLAGS = -Wall -Wextra -Werror -Ofast
LIBFT = libft
MLX = mlx

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@make -C $(MLX)
	@cp mlx/libmlx.dylib ./libmlx.dylib
	@cp libft/libft.a ./libft.a
	@$(CC) -L mlx/ -lmlx -framework OpenGL -framework AppKit -Ofast \
	$(OBJ) libft.a -o $(NAME)

bonus: $(B_OBJ)
	@touch bonus
	@make -C $(LIBFT)
	@make -C $(MLX)
	@cp mlx/libmlx.dylib ./libmlx.dylib
	@cp libft/libft.a ./libft.a
	@$(CC) -L mlx/ -lmlx -framework OpenGL -framework AppKit -Ofast \
	$(B_OBJ) libft.a -o $(NAME)

%.o: %.c
	@printf "Compiling $?\n"
	@gcc $(CFLAGS) -I mlx -I libft -c $? -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) $(B_OBJ)
	@$(RM) bonus
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)

fclean: clean
	@$(RM) $(BMP)
	@$(RM) $(NAME)
	@$(RM) libmlx.dylib
	@$(RM) libft.a
	@make fclean -C $(LIBFT)

re: fclean all
