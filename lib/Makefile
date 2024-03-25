all:	game graphical

game:
	make -C arcade_snake
	make -C arcade_menu
	make -C arcade_name_selector
	make -C arcade_pacman

graphical:
	make -C arcade_ncurses
	make -C arcade_sfml
	make -C arcade_sdl

clean:
	make -C arcade_ncurses clean
	make -C arcade_snake clean
	make -C arcade_menu clean
	make -C arcade_sfml clean
	make -C arcade_sdl clean
	make -C arcade_pacman clean
	make -C arcade_name_selector clean

fclean:
	make -C arcade_ncurses fclean
	make -C arcade_snake fclean
	make -C arcade_menu fclean
	make -C arcade_sfml fclean
	make -C arcade_sdl fclean
	make -C arcade_pacman fclean
	make -C arcade_name_selector fclean

re:
	make -C arcade_ncurses re
	make -C arcade_snake re
	make -C arcade_menu re
	make -C arcade_sfml re
	make -C arcade_sdl re
	make -C arcade_pacman re
	make -C arcade_name_selector re

.PHONY: all game graphical clean fclean re
