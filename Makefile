# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 12:32:35 by alisseye          #+#    #+#              #
#    Updated: 2024/10/24 19:20:42 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SERVER_SRCS = server.c
CLIENT_SRCS = client.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(SERVER) $(CLIENT)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER):$(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER) -L $(LIBFT_PATH) -lft

$(CLIENT): $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT) -L $(LIBFT_PATH) -lft

$(LIBFT):
	make -s -C $(LIBFT_PATH)

clean:
	make -s -C $(LIBFT_PATH) clean

fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
