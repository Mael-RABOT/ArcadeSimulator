all:	game graphical

game:
	make -C arcade_snake
	make -C arcade_pacman
	make -C arcade_menu
	make -C arcade_pacman

graphical:
	make -C arcade_ncurses
	make -C arcade_sfml
	make -C arcade_sdl2

clean:
	make -C arcade_snake clean
	make -C arcade_pacman clean
	make -C arcade_menu clean
	make -C arcade_ncurses clean
	make -C arcade_sfml clean
	make -C arcade_sdl2 clean
	make -C arcade_pacman clean

fclean:
	make -C arcade_snake fclean
	make -C arcade_pacman fclean
	make -C arcade_menu fclean
	make -C arcade_ncurses fclean
	make -C arcade_sfml fclean
	make -C arcade_sdl2 fclean
	make -C arcade_pacman fclean

re:
	make -C arcade_snake re
	make -C arcade_pacman re
	make -C arcade_menu re
	make -C arcade_ncurses re
	make -C arcade_sfml re
	make -C arcade_sdl2 re
	make -C arcade_pacman re

.PHONY: all game graphical clean fclean re
