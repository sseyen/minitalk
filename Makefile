# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 12:32:35 by alisseye          #+#    #+#              #
#    Updated: 2025/03/13 12:21:28 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SERVER_SRCS = srcs/server/server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_SRCS = srcs/client/client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(SERVER) $(CLIENT)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH) -I includes 

$(SERVER): $(LIBFT) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(SERVER) -L $(LIBFT_PATH) -lft

$(CLIENT): $(LIBFT) $(CLIENT_OBJS)
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

.PHONY: all clean fclean re $(SERVER) $(CLIENT) $(LIBFT)
