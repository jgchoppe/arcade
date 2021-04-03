NAMELIB	=	lib_arcade_sdl2.so

DIRLIB = src/Lib

SRCLIB	=	SDL.cpp		\

LIBS	= -lSDL2 -lSDL2_ttf -lSDL2_image

CC	=	g++ -g

RM	=	rm -f

OBJSARC	=	$(SRCLIB:.cpp)

%.o: %.c
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(CC) -c -o $(NAMELIB) $(SRCLIB) $@ $< $(CFLAGS) $(LDFLAGS) $(LIBS) -std=c++14 -fpic -shared

all:		sdl

sdl:		$(NAMELIB)

$(NAMELIB):	$(OBJSARC)
		@$(CC) -o $(NAMELIB) $(SRCLIB) $(LIBS) -std=c++14 -fPIC -shared
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
