CORE = core/Case.cpp core/Competence.cpp core/Donjon.cpp core/Ennemi.cpp core/Etage.cpp core/Jeu.cpp core/Joueur.cpp core/ListeCases.cpp core/ListeCompetences.cpp core/ListeDonjons.cpp core/ListeObjets.cpp core/ListeTypesEnnemis.cpp core/Objet.cpp core/random.cpp core/Stats.cpp core/TypeEnnemi.cpp core/TypeJoueur.cpp

SRCS_REGRESSION = $(CORE) core/mainTestRegression.cpp
FINAL_TARGET_REGRESSION = test

SRCS_TXT = $(CORE) txt/Jeu_txt.cpp txt/main_txt.cpp
FINAL_TARGET_TXT = yajugo_txt

SRCS_SFML = $(CORE) sfml/Jeu_sfml.cpp sfml/main_sfml.cpp
FINAL_TARGET_SFML = yajugo_sfml

INCLUDE_DIR_SFML = -I/extern/Linux/SFML-2.5.1/include/SFML
LIBS_SFML = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

CC			= g++
LD			= g++
LDFLAGS 		=
CPPFLAGS		= -Wall -g -std=c++11
OBJ_DIR 		= obj
SRC_DIR 		= src
BIN_DIR 		= bin
INCLUDE_DIR		= -Isrc/core -Isrc/txt -Isrc/sfml

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_REGRESSION) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SFML)

make_dir:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sfml $(OBJ_DIR)/core
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(FINAL_TARGET_REGRESSION): $(SRCS_REGRESSION:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_SFML): $(SRCS_SFML:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SFML)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR) $(INCLUDE_DIR_SFML) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

