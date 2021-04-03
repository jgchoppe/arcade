NAMELIB	=	lib_arcade_sfml.so

DIRLIB = src/Lib

SRCLIB	=	SFML.cpp		\

LIBS	= -std=c++14 -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window

CC	=	g++

RM	=	rm -f

OBJSARC	=	$(SRCLIB:.cpp)

%.o: %.c
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(CC) -c -o $(NAMELIB) $(SRCLIB) $@ $< $(CFLAGS) $(LDFLAGS) $(LIBS) -fpic -shared

all:		sfml

sfml:		$(NAMELIB)

$(NAMELIB):	$(OBJSARC)
		@$(CC) -o $(NAMELIB) $(SRCLIB) $(LIBS) -fPIC -shared
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAMELIB) | tr ' ' '.'
		@cp $(NAMELIB) ../../../../lib

clean:
		@$(RM) $(OBJSARC)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(SRCLIB) | tr ' ' '.'

fclean:		clean
		@$(RM) $(NAMELIB)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAMELIB) | tr ' ' '.'

re:		fclean all

.PHONY:		all clean fclean re
