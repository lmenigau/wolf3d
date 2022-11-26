#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/11/01 10:14:22 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	=	wolf3d
CC		=	clang
SRC		=	dda.c drawing.c movements.c hooks.c map.c raycasting.c wolf3d.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -Iminilibx-linux/ -g -Ofast -march=native
LFLAGS	=	-lmlx -lX11 -lXext -lm
LDFLAGS	=	-Lminilibx-linux/ 
MLXDIR	=	minilibx-linux
MLX		=	$(MLXDIR)/libmlx.a
MAKE	=	make

.PHONY	:	all clean fclean re lib

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(MLX)
			$(CC) $(CFLAGS)  -o $@ $(OBJ) $(LFLAGS) $(LDFLAGS)

$(MLX)	:	FORCE
			$(MAKE) -C $(MLXDIR)
FORCE:

clean	:
			$(RM) $(OBJ)
			$(MAKE)	-C $(MLXDIR) clean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
