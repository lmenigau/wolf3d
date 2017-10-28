#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/10/28 19:13:40 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	=	wolf3d
CC		=	clang
SRC		=	dda.c drawing.c movements.c hooks.c map.c raycasting.c wolf3d.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -Iminilibx_macos/ -Ofast -march=native -fsanitize=address
LFLAGS	= -lmlx -framework Appkit -framework OpenGl
LDFLAGS	= -Llibft/ -Lminilibx_macos/ 
LIBDIR	= libft/
LIB		:= $(LIBDIR)/libft.a

.PHONY	:	all clean fclean re lib

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJ)

$(LIB)	:	$(LIBDIR)
			$(MAKE) -C $(LIBDIR)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
