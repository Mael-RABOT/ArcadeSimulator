SRC			=	$(shell find src/ -type f -name "*.cpp")

OBJ			=	$(SRC:.cpp=.o)

CXX			=	g++

UNUSED		=	-Wno-unused-parameter -Wno-unused-function
CXXFLAGS	=	-Wall -Wextra $(UNUSED) -std=c++20 -fpic -I../../include -I../../ExceptionClass

EXE			=	../arcade_pacman.so

all:		$(EXE)

%.o:		%.cpp
			$(CXX) $(CXXFLAGS)   -c -o $@ $<

$(EXE):		$(OBJ)
			$(shell cp --remove-destination assets/pacman_* ../assets/)
			$(CXX) --shared -o $(EXE) $^ $(LDFLAGS)

clean:
			rm -rf $(OBJ)
			$(shell find * -name "vgcore.*" -delete)

fclean:		clean
			rm -rf ../assets/pacman_*
			rm -rf $(EXE)

re:			fclean all

.PHONY: 	all clean re fclean
