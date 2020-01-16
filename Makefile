NAME		=	cub3d

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
                ./libft/ft_strlen.c                      \
                ./libft/ft_strncat.c                \
                ./libft/ft_strnew.c                 \
                ./libft/ft_strcpy.c                 \
                ./libft/ft_split.c               \
                ./libft/ft_strnstr.c                   \
                ./libft/ft_putstr.c                 \
                ./libft/ft_strdup.c                 \
                ./libft/ft_bzero.c                  \
                ./libft/ft_isprint.c                \
                ./libft/ft_putchar.c              \

H           =   includes/cub3d.h

OBJS		=	${SRCS:.c=.o}

BOBJS		=	${BONUS_SRCS:.c=.o}

FLAGS		=	-Iincludes

CC			=	gcc

LINK        =   $(MAKE) -C libft/

RM			=	rm -f

.c.o:
				$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} ${H}
			    $(CC) ${OBJS} -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm -lbsd -o ${NAME}

all: $(NAME)

clean:
				${RM} ${OBJS}

fclean: clean
			    ${RM} $(NAME)

run: fclean all clean
			    ${RM} ${OBJS}
re:	fclean all

.PHONY: all clean fclean re bonus run
