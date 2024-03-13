SRC		 :=	$(shell find ./src -type f -name '*.cpp')

OBJ		 = $(SRC:.cpp=.o)

CXX		 = g++
CFLAGS	 = -std=c++20 -Wall -Wextra
V_FLAG   = --leak-check=full --show-leak-kinds=all --track-origins=yes
EXE		 = ../arcade
SAN		 = -g3

all:	$(EXE)

%.o:	%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(SAN)

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $^

clean:
	@rm -rf $(OBJ)
	@rm -rf vgcore*
	@find . -type f -name '*.gcda' -delete
	@find . -type f -name '*.gcno' -delete

fclean:	clean
	@rm -rf $(EXE)

re:	fclean all
