CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
RM			= rm -f
SRC			= tests/main_eval.cpp
SRC_SUB		= tests/main_org.cpp
SRC_VAL		= tests/main_valfun.cpp tests/AAnimal.cpp tests/Brain.cpp tests/Cat.cpp
OBJ			= $(SRC:%.cpp=%.o)
OBJ_SUB		= $(SRC_SUB:%.cpp=%.o)
OBJ_VAL		= $(SRC_VAL:%.cpp=%.o)
NAME		= ft_containers
UNAME		:= $(shell uname)


.cpp.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	${OBJ}
			@$(CC) $(CFLAGS) -D LIB=1 $(SRC) -o $(NAME)
			@./ft_containers 1 > std
			@$(CC) $(CFLAGS) -D LIB=0 $(SRC) -o $(NAME)
			@./ft_containers 1 > ft
			@diff std ft > diff

ifeq ($(UNAME), Linux)
valfun:	${OBJ_VAL}
			$(CC) $(CFLAGS) -D LIB=0 $(SRC_VAL) -o $(NAME)
			valgrind ./ft_containers 42
endif

ifeq ($(UNAME), Darwin)
valfun:	${OBJ_VAL}
			$(CC) $(CFLAGS) -D LIB=0 $(SRC_VAL) -o $(NAME)
			leaks --atExit -- ./ft_containers 42
endif

subject:	${OBJ_SUB}
			@$(CC) $(CFLAGS) -D LIB=1 $(SRC_SUB) -o $(NAME)
			@./ft_containers 1 > std
			@$(CC) $(CFLAGS) -D LIB=0 $(SRC_SUB) -o $(NAME)
			@./ft_containers 1 > ft
			@diff std ft > diff

all:		${NAME}

clean:		
			@${RM} ${OBJ}
			@${RM} ${OBJ_SUB}
			@${RM} ${OBJ_VAL}
			@${RM} diff
			@${RM} std
			@${RM} ft

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re valfun subject