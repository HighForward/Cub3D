SRCS		=	./cub3d.c   \
                ./image.c   \
                ./srcs/bonus.c \
                ./srcs/display_cross.c \
                ./srcs/error.c \
                ./srcs/event.c \
                ./srcs/hud.c \
                ./srcs/images_textures.c \
                ./srcs/initialize_struct.c \
                ./srcs/move_rotate.c \
                ./srcs/parse_info.c \
                ./srcs/parse_info_map.c \
                ./srcs/raycasting.c \
                ./srcs/read_map.c \
                ./srcs/save_bmp.c \
                ./get_next_line/get_next_line.c \
                ./get_next_line/get_next_line_utils.c \

NAME		=	Cub3d

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
			    @$(CC) ${OBJS} -L ./libft -lft -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm -lbsd -o ${NAME}
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

map: ${OBJS} ${H}
				@$(CC) ${OBJS} -L ./libft -lft -lmlx -framework AppKit -framework  OpenGL -o ${NAME}
				@${RM} ${OBJS}
				@echo "\033[1;32m > Building <\033[0m\033[1;36m Launching Game\033[0m"
				@./Cub3d maps/map.cub

re:	fclean all

.PHONY: clean fclean re bonus run
