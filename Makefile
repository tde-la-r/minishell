# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:31:30 by amolbert          #+#    #+#              #
#    Updated: 2024/03/13 09:53:04 by amolbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	cd.c \
		getenv.c \
		find_env_index.c \
		env.c \
		array_dup.c \
		free_array.c \
		error_exit.c
SRCS_DIR = srcs/
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJS_DIR = objs/
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE)
INCLUDE_DIR = include/

CC = clang
CFLAGS = -Wall -Wextra -Werror
GFLAGS = $(CFLAGS) -g

LIB_DIR = libft/
LIBFT = libft.a
LIBFT_INCLUDE = $(LIB_DIR)include/
LIBS = -Llibft -lft

RM = rm -rf

all : $(NAME)

$(LIB_DIR)$(LIBFT): 
	@make -C $(LIB_DIR) --no-print-directory -j4

$(NAME) : $(LIB_DIR)$(LIBFT) $(OBJS_PATH)
	@$(CC) $(OBJS_PATH) -o $(NAME) $(LIB_DIR)$(LIBFT) $(LIBS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(GFLAGS) -c $(INCLUDES) $< -o $@

clean :
	@make clean -C $(LIB_DIR) --no-print-directory
	@$(RM) $(OBJS_PATH)
	@$(RM) $(OBJS_DIR)
	@echo "Files cleaned"

fclean : clean
	@$(RM) $(LIB_DIR)$(LIBFT)
	@$(RM) $(NAME)
	@echo "Files cleaned"

re : fclean all

.PHONY : all clean fclean re
