CC = g++
CCFLAGS = -Wall -Wextra
CCFLAGS_LK =
CCFLAGS_CP =

OUT = build/
EX = ProximaCentauri

SOURCE = main.cpp Controller/Game.cpp Model/Level.cpp View/View.cpp View/TitleScreen.cpp
LIBS = mingw32 SDL2main SDL2

#----------------

OBJS= $(addprefix obj/,$(SOURCE:.cpp=.o))
LDFLAGS = ${addprefix -l,${LIBS}}

all: proxima-centauri

proxima-centauri: $(OBJS)
	@echo Linking...
	@${CC} ${CCFLAGS} ${CCFLAGS_LK} $^ ${LDFLAGS} -o ${OUT}${EX}
	@echo Done.

obj/%.o: src/%.cpp
	@echo Compling ${notdir $<}...
	@${CC} ${CCFLAGS} ${CCFLAGS_CP} -c $< -o $@