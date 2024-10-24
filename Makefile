# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 12:32:35 by alisseye          #+#    #+#              #
#    Updated: 2024/10/24 14:22:30 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

${NAME}: 
	cc ${CFLAGS} server.c -o ${SERVER}
	cc ${CFLAGS} client.c -o ${CLIENT}

all: ${NAME}
	
clean:
	rm -f ${OBJS} ${BOBJS}

fclean: clean
	rm -f ${SERVER} ${CLIENT}

re: fclean all

.PHONY: all clean fclean re