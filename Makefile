SRCS		=	./cub3d.c   \
                ./srcs/error.c \
                ./srcs/event.c \
                ./get_next_line/get_next_line.c \
                ./get_next_line/get_next_line_utils.c \
                ./srcs/parsing_header/get_value_header.c \
                ./srcs/parsing_header/reading.c \
                ./srcs/parsing_header/search_key.c \
                ./srcs/parsing_header/utils.c \
                ./srcs/parsing_header/images_textures.c \
                ./srcs/parsing_map/check_map.c \
                ./srcs/parsing_map/init_player.c \
                ./srcs/parsing_map/map_utils.c \
                ./srcs/parsing_map/read_map.c \
                ./srcs/display/sprite.c \
                ./srcs/display/const_display.c \
                ./srcs/display/cross.c \
                ./srcs/display/display_utils.c \
                ./srcs/display/health_bar.c \
                ./srcs/display/mini_map.c \
                ./srcs/setup/args.c \
                ./srcs/setup/setup.c \
                ./srcs/utility/damage.c \
                ./srcs/utility/function_utils.c \
                ./srcs/utility/secret_door.c \
                ./srcs/vector_player/move_rotate.c \
                ./srcs/raycasting/data_raycasting.c \
                ./srcs/raycasting/raycasting.c \
                ./srcs/utility/save_bmp.c	\

NAME		=	cub3D

H           =   includes/cub3d.h

OBJS		=	${SRCS:.c=.o}

FLAGS		=	-Iincludes

CC			=	gcc

RM			=	rm -f

.c.o:
				@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: ${NAME}

link:
				@$(MAKE) -C ./libft/

${NAME}: ${OBJS} ${H} link
			    @$(CC) ${OBJS} -Wall -Wextra -Werror -L ./libft -lft -lmlx -framework AppKit -framework  OpenGL -o ${NAME}
			    @echo "\033[1;32m > Building <\033[0m\033[1;35m .o files\033[0m"
			    @echo "\033[1;32m > Building <\033[0m\033[1;36m ${NAME}\033[0m"
			    @echo "\033[1;32m > Building <\033[0m\033[1;36m Binary successfully create\033[0m"

clean:
				@${RM} ${OBJS}
				@$(MAKE) clean -C ./libft/
				@echo "\033[1;31m > Deleting <\033[0m\033[1;35m .o files\033[0m"

fclean: clean
			    @${RM} $(NAME)
			    @$(MAKE) fclean -C ./libft/
			    @echo "\033[1;31m > Deleting <\033[0m\033[1;35m ${NAME} \033[0m"

run: fclean all clean
			    @${RM} ${OBJS}

map: ${OBJS} ${H} link
				@$(CC) ${OBJS} -Wall -Wextra -Werror -L ./libft -lft -lmlx -framework AppKit -framework  OpenGL -o ${NAME}
				@${RM} ${OBJS}
				@echo "\033[1;32m > Building <\033[0m\033[1;36m Launching Game\033[0m"
				@./cub3d maps/map.cub

re:	fclean all

.PHONY: clean fclean re bonus run
