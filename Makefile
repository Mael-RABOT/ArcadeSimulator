all: submodule core graphicals games

core:
	make -C Core

games:
	make -C lib game

graphicals:
	make -C lib graphical

clean:
	make -C Core clean
	make -C lib clean

fclean:
	make -C Core fclean
	make -C lib fclean

re:
	make -C Core re
	make -C lib re

submodule:
	git submodule sync --recursive
	git submodule init ArcadeInterfaces/
	git submodule update --recursive
	cp --remove-destination ArcadeInterfaces/IDisplayModule.hpp include/IDisplayModule.hpp
	cp --remove-destination ArcadeInterfaces/IGameModule.hpp include/IGameModule.hpp
	cp --remove-destination ArcadeInterfaces/Type.hpp include/Type.hpp
