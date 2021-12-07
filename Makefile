# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 15:45:42 by dcyprien          #+#    #+#              #
#    Updated: 2021/12/06 18:34:30 by dcyprien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	pipex.c \
			pipex_utils.c\
			ft_split.c\
			ft_strchr.c

NAME	=	pipex

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f


$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:		${NAME}

clean:		
			${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
			${RM} ${NAME}

bonus:		${OBJS}
			${CC} ${CFLAGS} -c ${SRCSBONUS}
			${CCLIB} ${NAME} ${OBJS} ${OBJSBONUS}

re:			fclean all

.PHONY = all clean fclean re bonus