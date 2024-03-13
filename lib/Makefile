all:	game graphical

game:
	make -C arcade_snake

graphical:
	make -C arcade_ncurses

clean:
	make -C arcade_ncurses clean
	make -C arcade_snake clean

fclean:
	make -C arcade_ncurses fclean
	make -C arcade_snake fclean

re:
	make -C arcade_ncurses re
	make -C arcade_snake re

.PHONY: all game graphical clean fclean re
