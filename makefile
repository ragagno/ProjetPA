CC = g++
CCFLAGS = -Wall -Wextra
CCFLAGS_LK =
CCFLAGS_CP =

OUT = build/
EX = ProximaCentauri

SOURCE = main.cpp controller/GameController.cpp model/Level.cpp view/menu/MenuView.cpp view/menu/TitleScreenView.cpp model/menu/TitleScreenModel.cpp controller/menu/TitleScreenController.cpp view/menu/TitleScreenView.cpp model/menu/TitleScreenModel.cpp controller/menu/TitleScreenController.cpp view/menu/StartGameView.cpp model/menu/StartGameModel.cpp controller/menu/StartGameController.cpp view/menu/OptionsView.cpp model/menu/OptionsModel.cpp controller/menu/OptionsController.cpp
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