CXX = g++-5
CXXFLAGS = -std=c++14 -MMD -g -Werror=vla
OBJECT = main.o controller.o board.o ai.o move.o piece.o king.o queen.o bishop.o knight.o rook.o pawn.o graphics.o window.o
DEPENDS = ${OBJECT:.o=.d}

a4q4: ${OBJECT}
	${CXX} ${CXXFLAGS} ${OBJECT} -o chess -lX11

-include ${DEPENDS}

.PHONY: clean
clean:
	rm *.o *.d chess

