# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:31:30 by amolbert          #+#    #+#              #
#    Updated: 2024/05/01 14:04:08 by amolbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export_no_args.c \
		builtins/export_utils.c \
		builtins/export_utils_2.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		exec/exec_utils.c \
		exec/exec.c \
		exec/format_cmd.c \
		exec/here_doc_utils.c \
		exec/here_doc.c \
		init/init_data.c \
		init/init_fds.c \
		init/prompt.c \
		parser/cmd_lst_utils.c \
		parser/cmd_lst.c \
		parser/create_node_utils.c \
		parser/create_node.c \
		parser/del_quote.c \
		parser/expand_variables.c \
		parser/lexer_syntax.c \
		parser/lexer_utils.c \
		parser/expand_variables_utils.c \
		parser/ln_lst_utils.c \
		parser/parse_line.c \
		parser/split_args.c \
		utils/error_exit.c \
		utils/utils.c \
		utils/utils_2.c \
		main.c
#BUILTINS = 	cd.c echo.c env.c exit.c export_no_args.c export_utils.c \
#			export_utils_2.c export.c pwd.c unset.c
#EXEC = exec_utils.c exec.c format_cmd.c here_doc.c here_doc_utils.c
#PARSER = 	cmd_lst.c cmd_lst_utils.c create_node_utils.c create_node.c del_quote.c \
#			expand_variables.c expand_variables_utils.c lexer_syntax.c \
#			lexer_utils.c ln_lst_utils.c parse_line.c split_args.c
#UTILS = error_exit.c utils.c utils_2.c
#INIT = init_data.c init_fds.c prompt.c

#SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
#SRCS_PATH += $(addprefix $(SRCS_DIR), $(addprefix $(BUILTINS_DIR), $(BUILTINS)))
#SRCS_PATH += $(addprefix $(SRCS_DIR), $(addprefix $(EXEC_DIR), $(EXEC)))
#SRCS_PATH += $(addprefix $(SRCS_DIR), $(addprefix $(PARSER_DIR), $(PARSER)))
#SRCS_PATH += $(addprefix $(SRCS_DIR), $(addprefix $(UTILS_DIR), $(UTILS)))
#SRCS_PATH += $(addprefix $(SRCS_DIR), $(addprefix $(INIT_DIR), $(INIT)))

##========== COLORS ==========##

BASE_COLOR 	=		\001\033[0;39m\002
GRAY 		=		\001\033[0;90m\002
RED 		=		\001\033[0;91m\002
GREEN 		=		\001\033[0;92m\002
YELLOW 		=		\001\033[0;93m\002
BLUE 		=		\001\033[0;94m\002
MAGENTA		=		\001\033[0;95m\002
CYAN 		=		\001\033[0;96m\002
WHITE		=		\001\033[0;97m\002

SRCS_DIR = srcs/
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

INCLUDE_DIR = include/
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE)
LIB_DIR = libft/
LIBFT = libft.a
LIBFT_INCLUDE = $(LIB_DIR)include/
LIBS = -lreadline

CC = clang
CFLAGS = -Wall -Wextra -Werror
GFLAGS = $(CFLAGS) -g

ifdef FAST
	J4 = -j$(nproc)
endif

VFLAGS = --leak-check=full --track-fds=yes --trace-children=yes --suppressions=$(SUPP_FILE)
STILL_REACHABLE = --show-leak-kinds=all
SUPP_FILE = rdline_supp

RM = rm -rf

NUM_SRC = $(words $(SRCS))
INDEX = 0

all : libft $(NAME)

libft : 
	@make -C $(LIB_DIR) $(J4) --no-print-directory

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LIB_DIR)$(LIBFT) $(INCLUDES) $(LIBS) 
	@echo "Minishell compiled"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@clear
	@echo "$(GREEN)Compiling Minishell$(BASE_COLOR)"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "╔═══════════════════════════════════════════════════╗"
	@echo -n "║$(GREEN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 50 - $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚═══════════════════════════════════════════════════╝"
	@echo "Compiling : $<"
	@mkdir -p $(dir $@)
	$(CC) $(GFLAGS) $(INCLUDES) -c $< -o $@

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
