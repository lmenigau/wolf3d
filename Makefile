#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/05/11 23:42:36 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	= wolf3d
SRC		= wolf3d.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -Ilibft/ -I../minilibx_macos/ -fsanitize=address
LFLAGS	= -lmlx -framework Appkit -framework OpenGl
LDFLAGS	= -Llibft/ -L../minilibx_macos/ 
LIBDIR	= libft/
LIB		:= $(LIBDIR)/libft.a

.PHONY	:	all clean fclean re lib

all		:	$(NAME)

$(NAME)	:	$(OBJ)# $(LIB)
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJ)

$(LIB)	:	$(LIBDIR)
			$(MAKE) -C $(LIBDIR)

clean	:
			$(RM) $(OBJ)
		#	$(MAKE) -C $(LIBDIR) fclean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
