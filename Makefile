all: core graphicals games

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
