all: core games graphicals

core:
	make -C Core
	mv Core/arcade .

games:
	make -C Games

graphicals:
	make -C Graphicals

clean:
	make -C Core clean
	make -C Games clean
	make -C Graphicals clean

fclean:
	make -C Core fclean
	make -C Games fclean
	make -C Graphicals fclean
