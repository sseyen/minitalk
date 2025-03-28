# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 21:23:18 by alisseye          #+#    #+#              #
#    Updated: 2025/03/22 09:51:23 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SERVER_SRCS = srcs/server/server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_SRCS = srcs/client/client.c srcs/client/utils.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH) -I includes 

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER) -L $(LIBFT_PATH) -lft

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(CLIENT) -L $(LIBFT_PATH) -lft

$(LIBFT):
	make -s -C $(LIBFT_PATH)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	make -s -C $(LIBFT_PATH) clean

fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
