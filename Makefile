# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 12:32:35 by alisseye          #+#    #+#              #
#    Updated: 2025/03/10 16:04:20 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SERVER_SRCS = server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_SRCS = client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

SERVER_BSRCS = server_bonus.c
SERVER_BOBJS = $(SERVER_BSRCS:.c=.o)
CLIENT_BSRCS = client_bonus.c
CLIENT_BOBJS = $(CLIENT_BSRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(SERVER) $(CLIENT)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER) -L $(LIBFT_PATH) -lft

$(CLIENT): $(LIBFT) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT) -L $(LIBFT_PATH) -lft

$(LIBFT):
	make -s -C $(LIBFT_PATH)

bonus: all $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(LIBFT) $(SERVER_BOBJS)
	$(CC) $(CFLAGS) $(SERVER_BOBJS) -o $(SERVER_BONUS) -L $(LIBFT_PATH) -lft

$(CLIENT_BONUS): $(LIBFT) $(CLIENT_BOBJS)
	$(CC) $(CFLAGS) $(CLIENT_BOBJS) -o $(CLIENT_BONUS) -L $(LIBFT_PATH) -lft

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_BOBJS) $(CLIENT_BOBJS)
	make -s -C $(LIBFT_PATH) clean

fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
