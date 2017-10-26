CC = g++
CCFLAGS = -Wall -Wextra
CCFLAGS_LK =
CCFLAGS_CP =

OUT = build/
EX = ProximaCentauri

_TITLE_SCREEN = view/menu/TitleScreenView.cpp model/menu/TitleScreenModel.cpp controller/menu/TitleScreenController.cpp
_START_GAME = view/menu/StartGameView.cpp model/menu/StartGameModel.cpp controller/menu/StartGameController.cpp
_OPTIONS = view/menu/OptionsView.cpp model/menu/OptionsModel.cpp controller/menu/OptionsController.cpp
_IN_GAME = view/game/InGameView.cpp model/game/InGameModel.cpp controller/game/InGameController.cpp
_OTHERS = controller/GameController.cpp model/game/data/Level.cpp view/menu/MenuView.cpp

SOURCE = main.cpp ${_OTHERS} ${_TITLE_SCREEN} ${_START_GAME} ${_OPTIONS} ${_IN_GAME}
LIBS = mingw32 SDL2main SDL2 SDL2_ttf SDL2_image

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

.PHONY: clean

clean: