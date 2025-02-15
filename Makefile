SERVER = server
CLIENT = client

SERVER_SOURCE = server.c
CLIENT_SOURCE = client.c
SERVER_OBJ = $(SERVER_SOURCE:.c=.o)
CLIENT_OBJ = $(CLIENT_SOURCE:.c=.o)

LIBFT_DIR = libft

CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

INCLUDES = -I. -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(@)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(FLAGS) $(SERVER_OBJ) -o $(SERVER) -L$(LIBFT_DIR) -lft

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(FLAGS) $(CLIENT_OBJ) -o $(CLIENT) -L$(LIBFT_DIR) -lft

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) -s clean

fclean: clean
	@$(RM) $(SERVER) $(CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) -s fclean 

re: fclean all

.PHONY: all clean fclean re