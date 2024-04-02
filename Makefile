all: core graphicals games

core: submodule
	make -C Core

games: submodule
	make -C lib game

graphicals: submodule
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
	git submodule init include/
	git submodule update --recursive
