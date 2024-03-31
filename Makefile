# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 18:04:01 by gabsanch          #+#    #+#              #
#    Updated: 2024/03/15 14:11:40 by glopez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
RM = rm -rf

FLAGS = -Wall -Wextra -Werror -D READLINE_LIBRARY=1 #-g -fsanitize=address

SRC = constructors.c \
	  tokenizer.c \
	  lexer_utils.c \
	  tokencheck.c \
	  utils_heredoc.c \
	  doc_here.c \
	  executor.c \
	  redfuncs.c \
	  findfuncts.c \
	  isstrin.c \
	  parser.c \
	  exegg_utils.c \
	  destructors.c \
	  unclosed.c \
	  builtins/exebi.c \
	  builtins/cd.c \
	  builtins/env.c \
	  builtins/exit.c \
	  builtins/pwd.c \
	  builtins/echo.c \
	  builtins/export_utils.c\
	  builtins/export_utils2.c\
	  builtins/export.c \
	  builtins/unset.c \
	  expansor/utils_expansor.c \
	  expansor/cleanpieces.c \
	  expansor/expandstr.c \
	  utils_parser.c \
	  utils_piece.c \
	  ultrasplit.c \
	  signals.c \
	  main.c

READL = readline/
LIBFT = libft/libft.a
RDL = readline/libreadline.a
HIS = readline/libhistory.a

INC = -I libft/libft.h\
		-I readline/

HEADER = minishell.h

OBJ_MAIN = $(MAIN:%.c=%.o)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: rum $(RDL) $(NAME)

rum:
	make -C ./libft/

$(RDL):
	cd $(READL) && ./configure
	make -C $(READL)

%.o: %.c Makefile $(HEADER)
	$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ_MAIN) $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(MAIN) $(OBJ) $(LIBFT) $(RDL) $(HIS) -ltermcap -lreadline -o $(NAME)

clean:
	make clean -C ./libft/
	make clean -C $(READL)
	$(RM) $(OBJ_MAIN) $(OBJ) $(DEP)

fclean: clean
	make fclean -C ./libft/
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re rum
-include $(DEP)
