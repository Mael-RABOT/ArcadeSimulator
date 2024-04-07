FILE_SRC    :=    $(shell find . -type f -name '*.cpp')

FILE_OBJ    =   $(FILE_SRC:.cpp=.o)

CXX    		=   g++

UNUSED   	=   -Wno-unused-parameter -Wno-unused-function
CXXFLAGS    =	-Wall -Wextra $(UNUSED) -std=c++20 -fpic -I../../include -I../../ExceptionClass
LDFLAGS 	= 	-lSDL2 -lSDL2_ttf -lSDL2_image
SAN			=	-g3

EXE    		=	../arcade_sdl2.so

all:    	$(EXE)

%.o:    	%.cpp
			$(CXX) $(CXXFLAGS)   -c -o $@ $<

$(EXE):    $(FILE_OBJ)
			$(CXX) --shared -o $(EXE) $^ $(LDFLAGS)

clean:
			rm -rf $(FILE_OBJ)
        	$(shell find * -name "vgcore.*" -delete)

fclean:		clean
			rm -rf $(EXE)
			rm -rf $(TEST_EXE)

re:			fclean all

.PHONY: 	all clean re fclean
