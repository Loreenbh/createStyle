NAME		=	findStyle

CC			=	c++

CFLAGS		=	-Wall -Werror -Wextra -I/usr/include/SFML

# Drapeaux SFML pour lier les bibliothèques
LIBS 		= -L./SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#================SRC=================

SRC			=	main.cpp initGame.cpp
#================OBJ=================

OBJ			=	${SRC:.cpp=.o}

#================COULEURS============

RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RESET		=	\033[0m
BOLD		=	\033[1m

#================BACKGROUND==========

REDB		=	\033[41m
GREENB		=	\033[42m
YELLOWB		=	\033[43m
BLUEB		=	\033[44m
RESETB		=	\033[0m

#================RULES===============

all	: ${NAME}
	@echo "${GREENB}  ./${NAME}  : Projet compilé  ${RESETB}"

%.o	:	%.cpp
	@${CC} ${CFLAGS} -o $@ -c $^

${NAME}	:	${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME} ${LIBS}

clean		:
	@rm -rf ${OBJ}
	@echo "${REDB}   ${OBJ} : .O surppimé ${RESETB}"

fclean		:	clean
	@rm -rf ${NAME}
	@rm -rf ${OBJ}
	@echo "${BLUEB}  ./${NAME}  : Nettoyage complet  ${RESETB}"

re			:	fclean all

.PHONY		:	all clean fclean re