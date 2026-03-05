NAME = game
SRC = src/client/main.cpp src/client/Player.cpp src/client/Background.cpp src/client/Level.cpp src/client/PlaneSelector.cpp src/client/MainMenu.cpp src/client/Enemy.cpp src/client/GameOverMenu.cpp src/client/Bullet.cpp src/client/MissionObjective.cpp src/client/WinMenu.cpp src/client/HelpMenu.cpp src/client/Sounds.cpp src/client/SettingsMenu.cpp src/client/GravityBubble.cpp src/client/Weapon.cpp src/client/BlasterWeapon.cpp src/client/GravityLauncherWeapon.cpp src/client/SettingsPersistence.cpp
OBJ = $(SRC:.cpp=.o)
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Iinclude -Iinclude/client
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
