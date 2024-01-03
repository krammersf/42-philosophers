# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 20:45:23 by fde-carv          #+#    #+#              #
#    Updated: 2023/10/23 18:22:29 by fde-carv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colours
RESET				=	\033[0m
BLACK 				=	\033[1;30m
RED 				=	\033[1;31m
GREEN 				=	\033[1;32m
YELLOW 				=	\033[1;33m
BLUE				=	\033[1;34m
PURPLE 				=	\033[1;35m
CYAN 				=	\033[1;36m
WHITE 				=	\033[1;37m

# Name
NAME 				= 	philo

# Mandatory files
SRC_FILES 			= 	main.c \
						routine_utils.c \
						routine.c \
						utils.c \
						threads.c \
						print.c
						
SRC_DIR 			= 	src
SRC 				= 	${addprefix ${SRC_DIR}/, ${SRC_FILES}}

# Object files
OBJS 				= 	${addprefix obj/, ${SRC_FILES:.c=.o}}

# Header files same folder
HEADER_FILES 		= 	philo.h
HEADER_DIR 			= 	include
HEADER 				= 	${addprefix ${HEADER_DIR}/, ${HEADER_FILES}}

#
INCLUDE 			= 	-I include
CC 					= 	cc
CC2 				= 	clang
RM 					= 	rm -f
CFLAGS 				= 	-Wall -Wextra -Werror -pthread -g #-fsanitize=thread
CFLAGS2				=	-fsanitize=thread -o minishell

# Rules
all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS} 
	@echo "\n[${YELLOW}$$(echo ${NAME} | tr '[:lower:]' '[:upper:]')${WHITE}] ${GREEN}--> created${WHITE}\n"

obj/%.o: ${SRC_DIR}/%.c ${HEADER}
	@mkdir -p obj
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
	@echo "[${CYAN}Object $(basename $(notdir $@)) files${WHITE}] ${GREEN}--> created${WHITE}"

clean:
	@${RM} ${OBJS}
	@${RM} -r obj
	@echo "\n[${CYAN}Object files${WHITE}] ${RED}--> removed${WHITE}\n"

fclean: clean
	@${RM} ${NAME}
	@echo "[${YELLOW}$$(echo ${NAME} | tr '[:lower:]' '[:upper:]')${WHITE}] ${RED}--> removed${WHITE}\n"

re: fclean
	@sleep 0.6
	@$(MAKE) all

norm:
	@norminette -R CheckForbiddenSourceHeader > /dev/null 2>&1
	@norminette -R CheckDefine includes > /dev/null 2>&1
	@norminette -R . > /dev/null 2>&1
	@echo "$(GREEN)\n*** >>>  NORMINETTE is OK  <<< ***\n"

norm2:
	@norminette -R CheckForbiddenSourceHeader
	@norminette -R CheckDefine
	@norminette -R .
	@echo "$(GREEN)\n*** >>>  NORMINETTE is OK  <<< ***\n"	

.PHONY: all clean fclean re norm norm2

#.SILENT: