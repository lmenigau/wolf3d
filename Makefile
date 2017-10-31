#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/10/31 16:12:05 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	=	wolf3d
CC		=	clang
SRC		=	dda.c drawing.c movements.c hooks.c map.c raycasting.c wolf3d.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -Iminilibx_macos/ -Ofast -march=native
LFLAGS	=	-lmlx -framework Appkit -framework OpenGl
LDFLAGS	=	-Lminilibx_macos/ 
MLXA	=	libmlx.a
MLXDIR	=	minilibx_macos
MLX		=	$(MLXDIR)/$(MLXA)


.PHONY	:	all clean fclean re lib

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(MLX)
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJ)

$(MLX)	:	$(MLXDIR)
			$(MAKE) -C $(MLXDIR)

clean	:
			$(RM) $(OBJ)
			$(MAKE)	-C $(MLXDIR) clean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
