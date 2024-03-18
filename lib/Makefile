all:	game graphical

game:
	make -C arcade_snake
	make -C arcade_menu

graphical:
	make -C arcade_ncurses
	make -C arcade_menu

clean:
	make -C arcade_ncurses clean
	make -C arcade_snake clean
	make -C arcade_menu clean
	make -C arcade_sfml clean

fclean:
	make -C arcade_ncurses fclean
	make -C arcade_snake fclean
	make -C arcade_menu fclean
	make -C arcade_sfml fclean

re:
	make -C arcade_ncurses re
	make -C arcade_snake re
	make -C arcade_menu re
	make -C arcade_sfml re

.PHONY: all game graphical clean fclean re
