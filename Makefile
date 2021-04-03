SRC	=	src/Main.cpp					\
		src/Core/Core.cpp				\
		src/Utils/RingBufferString.cpp	\
		src/Clock/Clock.cpp				\
		src/Menu/Menu.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=            arcade

CXXFLAGS	+=	-ISources-W -Wall -Wextra -std=c++14 -lstdc++ -O3 -ldl

CC	 =	g++ -o

RM	=	rm -f

ALL	=	all

CLEAN	=	clean

FCLEAN	=	fclean

RE	=	re

CORE	=	mcore

GAMES	=	mgames

GRAPHICALS	=	mgraphicals

core: $(NAME)

games: $(GAMES)

graphicals: $(GRAPHICALS)

all:	$(NAME) $(GRAPHICALS) $(GAMES)

$(GAMESCLEAN):
			@make fclean --no-print-directory -C src/Games

$(GRAPHICALS):
			@make --no-print-directory -C src/Lib/Graphic

$(GAMES):
			@make --no-print-directory -C src/Games

$(NAME):	$(OBJ)
			$(CC) $(NAME) $(OBJ) $(CXXFLAGS)
clean:
			$(RM) $(OBJ)
			@make clean --no-print-directory -C src/Lib/Graphic
			@make clean --no-print-directory -C src/Games

fclean:
		$(RM) $(OBJ)
		$(RM) $(NAME)
		@make fclean --no-print-directory -C src/Lib/Graphic
		@make fclean --no-print-directory -C src/Games

re:	$(FCLEAN) $(ALL)

.PHONY:	$(RE) $(FCLEAN) $(CLEAN) $(ALL)