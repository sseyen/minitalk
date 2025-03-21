# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 12:32:35 by alisseye          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/03/21 18:43:21 by alisseye         ###   ########.fr        #
=======
#    Updated: 2025/03/17 17:31:29 by alisseye         ###   ########.fr        #
>>>>>>> c37ba346611bfce5362cdeea41e782c75c13d53b
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SERVER_SRCS = srcs/server/server.c srcs/server/utils.c
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
