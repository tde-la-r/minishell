# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:31:30 by amolbert          #+#    #+#              #
#    Updated: 2024/03/14 16:56:44 by tde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror
GFLAGS = $(CFLAGS) -g
SRCS =	ft_isalpha.c \
		ft_abs.c \
		ft_isdigit.c \
		ft_isbase.c \
		ft_islower.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strchr_next.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_atoi_base.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstpenultimate.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew_int.c \
		ft_lstadd_front_int.c \
		ft_lstsize_int.c \
		ft_lstlast_int.c \
		ft_lstpenultimate_int.c \
		ft_lstadd_back_int.c \
		ft_lstdelone_int.c \
		ft_lstclear_int.c \
		ft_lstiter_int.c \
		ft_lstmap_int.c \
		ft_putnbr.c \
		ft_putnbrus.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_dectohexa.c \
		ft_lennum.c \
		ft_lennumus.c \
		ft_lennumhexa.c \
		ft_lennumhexaull.c \
		ft_pointtohexa.c \
		ft_count_words.c \
		ft_printf.c \
		printf_args.c \
		get_next_line.c \
		ft_lower.c \
		ft_superior.c

OBJS = $(SRCS:.c=.o)		

INCLUDE = -I$(INCLUDE_DIR)
INCLUDE_DIR = include/

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
