all:	game graphical

game:
	make -C arcade_snake
	make -C arcade_menu

graphical:
	make -C arcade_ncurses

clean:
	make -C arcade_ncurses clean
	make -C arcade_snake clean
	make -C arcade_menu clean

fclean:
	make -C arcade_ncurses fclean
	make -C arcade_snake fclean
	make -C arcade_menu fclean

re:
	make -C arcade_ncurses re
	make -C arcade_snake re
	make -C arcade_menu re

.PHONY: all game graphical clean fclean re
