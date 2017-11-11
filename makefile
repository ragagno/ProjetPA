CC = g++
CCFLAGS = -Wall -Wextra
CCFLAGS_LK =
CCFLAGS_CP =

OUT = build/
EX = ProximaCentauri

_TITLE_SCREEN = view/menu/TitleScreenView.cpp model/menu/TitleScreenModel.cpp controller/menu/TitleScreenController.cpp
_MAP_SELECTION = view/menu/MapSelectionView.cpp model/menu/MapSelectionModel.cpp controller/menu/MapSelectionController.cpp
_OPTIONS = view/menu/OptionsView.cpp model/menu/OptionsModel.cpp controller/menu/OptionsController.cpp
_GAME = view/game/GameView.cpp model/game/GameModel.cpp controller/game/GameController.cpp
_MAP = model/game/map/Map.cpp
_OTHERS = ProximaCentauri.cpp view/menu/MenuView.cpp

SOURCE = main.cpp ${_OTHERS} ${_MAP} ${_TITLE_SCREEN} ${_MAP_SELECTION} ${_OPTIONS} ${_GAME}
LIBS = mingw32 SDL2main SDL2 SDL2_ttf SDL2_image

#----------------

OBJS = $(addprefix obj/,$(SOURCE:.cpp=.o))
LDFLAGS = ${addprefix -l,${LIBS}}

all: proxima-centauri

proxima-centauri: $(OBJS)
	@echo Linking...
	@${CC} ${CCFLAGS} ${CCFLAGS_LK} $^ ${LDFLAGS} -o ${OUT}${EX}
	@echo Done.

obj/%.o: src/%.cpp
	@echo Compling ${notdir $<}...
	@${CC} ${CCFLAGS} ${CCFLAGS_CP} -c $< -o $@