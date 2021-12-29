# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cowen <cowen@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 18:13:29 by cowen             #+#    #+#              #
#    Updated: 2021/12/23 18:39:46 by cowen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	env_utils.c \
		main.c \
		env_utils_second.c \
		env_create.c \
		builtins.c  \
		builtins_second.c \
		parse_tokens.c \
		parse_tokens_second.c \
		parse_tokens_third.c  \
		parse_tokens_utils.c \
		parse_token_utils_second.c \
		export_utils.c			\
		redirects_r.c		\
		redirects_l.c		\
		get_cmd_and_argv.c \
		free_utils.c       \
		export.c 		\
		run_cmd.c		\
		run_cmd_int_out_pipe.c \
		run_cmd_redirects.c \
		run_cmd_child.c     \
		signals.c			\
		check_bultins.c		\
		parse_line.c		\
		work_with_dir.c		\
		envp.c				\
		get_cmd_utils.c		\
		get_cmd_utils_second.c \
		get_cmd_utils_third.c
	
LIBDIR =   ./libft/

LIBFT =   libft.a	

OBJS 	=	$(SRCS:%.c=%.o)

DEP	=	$(SRCS:%.c=%.d)

CC = gcc

HOMEBREW_PREFIX := $(shell test -n "$$(which brew)" \
                        && brew config | grep HOMEBREW_PREFIX | cut -d' ' -f2)

RM = rm -f

INC_DIR 	= ./includes/

LDLIBS = -lreadline

RL_INC_DIR	:=	$(HOMEBREW_PREFIX)/opt/readline/include

RL_LIB_DIR	:=	$(HOMEBREW_PREFIX)/opt/readline/lib

CPPFLAGS 	= -I$(INC_DIR) -I$(RL_INC_DIR)

LDFLAGS 	= -L$(RL_LIB_DIR)

CFLAGS 		= -MMD -Wall -Wextra -Werror -g3

all		:	libmake $(NAME)

libmake :	
			@make -C $(LIBDIR) 

$(NAME)	:	$(OBJS) $(LIBDIR)$(LIBFT)
			@cp $(LIBDIR)$(LIBFT) $(LIBFT)
			@$(CC)  $(CFLAGS) $(CPPFLAGS) -g $(LDFLAGS) $(LIBFT) $(LDLIBS) $(OBJS) -o $@  
			@printf "\e[38;5;226m./$@ successfully build\n"

%.o 	: 	%.c
			@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEP)

clean	: 		
			@make clean -C $(LIBDIR)
			@$(RM) $(OBJS) $(DEP)
			@printf "\e[38;5;121m.o files deleted\n"

fclean	:	clean
			@make fclean -C $(LIBDIR)
			@$(RM) $(NAME) $(LIBFT) 
			@printf "\e[38;5;121mBinaries deleted\n"

re		:	fclean all

.PHONY	: 	all clean fclean re libmake