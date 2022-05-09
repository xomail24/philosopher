# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icheri <icheri@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 18:40:43 by icheri            #+#    #+#              #
#    Updated: 2022/05/09 18:43:46 by icheri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

INC_DIR			= ./includes
SRC_DIR			= ./sources
OBJ_DIR			= ./objects

HEADERS			=	$(wildcard $(INC_DIR)/*.h)
SRCS			=	$(wildcard $(SRC_DIR)/*.c)
vpath			%.c $(SRC_DIR)
OBJS			= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

CC				= gcc
CFLAG			= -Wall -Werror -Wextra -fsanitize=thread
RM				= rm
RMFLAGS			= -rf



$(NAME) : $(HEADERS) $(OBJS)
		  $(CC) $(CFLAG) -I $(INC_DIR) $(OBJS) -o $(NAME)
		  @printf "🧶 Successfully Created $@!\n"

PHONY: all clean fclean re

all : $(NAME)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(HEADERS) $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR)  -c $< -o $@

clean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@printf "🧹 Cleaning $(NAME)\n"


re : fclean all


