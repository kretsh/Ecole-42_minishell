# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2021/12/23 14:29:51 by utygett          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_L	=	libft.a

SRC		=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c	\
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c	\
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstnew_bonus.c	\
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstmap_bonus.c
			
OBJ_M	=	$(SRC:%.c=%.o)

DEP_M	=	$(SRC:%.c=%.d)

CFLAGS	=	-MD -Wall -Werror -Wextra

CC		=	gcc

RM		=	rm -f

all		:	$(NAME_L)

$(NAME_L)	:	$(OBJ_M)
			@ar rc $(NAME_L) $?
			@printf "\e[38;5;226m./$@ successfully build\n"
%.o		:	%.c
			@$(CC) $(CFLAGS) -c $< -o $@
	
clean	:
			@$(RM) $(OBJ_M) $(DEP_M) 

fclean	:	clean
			@$(RM) $(NAME_L)
	
re		:	fclean all


-include $(DEP_M) 

.PHONY	:	all clean fclean re 