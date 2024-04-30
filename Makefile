# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:31:30 by amolbert          #+#    #+#              #
#    Updated: 2024/04/30 14:21:27 by amolbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	cd.c \
		cmd_lst.c \
		cmd_lst_utils.c \
		create_node.c \
		create_node_utils.c \
		del_quote.c \
		echo.c \
		env.c \
		error_exit.c \
		exec_utils.c \
		exec.c \
		exit.c \
		expand_variables.c \
		expand_variables_utils.c \
		export.c \
		export_no_args.c \
		export_utils.c \
		export_utils_2.c \
		format_cmd.c \
		here_doc.c \
		here_doc_utils.c \
		init_fds.c \
		lexer_syntax.c \
		lexer_utils.c \
		ln_lst_utils.c \
		main.c \
		init_data.c \
		parse_line.c \
		prompt.c \
		pwd.c \
		split_args.c \
		unset.c \
		utils.c \
		utils_2.c
SRCS_DIR = srcs/

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
LIBS = -lreadline

VFLAGS = --leak-check=full --track-fds=yes --trace-children=yes --suppressions=$(SUPP_FILE)
STILL_REACHABLE = --show-leak-kinds=all
SUPP_FILE = rdline_supp

RM = rm -rf

all : libft $(NAME)

libft : 
	@make -C $(LIB_DIR) --no-print-directory

$(NAME) : $(OBJS_PATH)
	@$(CC) $(OBJS_PATH) -o $(NAME) $(LIB_DIR)$(LIBFT) $(LIBS) 
	@echo "Minishell compiled"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(GFLAGS) -c $(INCLUDES) $< -o $@

run : all
	./$(NAME)

valgrind : all
	valgrind $(VFLAGS) ./$(NAME)

valgrind_sreach : all
	valgrind $(VFLAGS) $(STILL_REACHABLE) ./$(NAME)

valgrind_without_env : all
	valgrind $(VFLAGS) env -i ./$(NAME)

gdb : all
	gdb --tui $(NAME) -ex 'start'

clean :
	@make clean -C $(LIB_DIR) --no-print-directory
	@$(RM) $(OBJS_DIR)
	@echo "Files cleaned"

fclean : clean
	@$(RM) $(LIB_DIR)$(LIBFT)
	@$(RM) $(NAME)
	@echo "Files cleaned"

re : fclean all

.PHONY : all libft clean fclean re run valgrind valgrind_sreach valgrind_without_env gdb
