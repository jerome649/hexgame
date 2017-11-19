bin/main.app: obj/hex_board.o obj/hex_node.o obj/hex_ai.o main.cpp
	g++ -std=c++11 -Wall main.cpp obj/hex_board.o obj/hex_node.o obj/hex_ai.o -o bin/main.app

obj/hex_board.o: hex_board.cpp hex_board.hpp hex_node.hpp
	g++ -std=c++11 -Wall -c hex_board.cpp -o obj/hex_board.o

obj/hex_node.o: hex_node.cpp hex_node.hpp
	g++ -std=c++11 -Wall -c hex_node.cpp -o obj/hex_node.o

obj/hex_ai.o: hex_ai.cpp hex_ai.hpp hex_board.hpp hex_node.hpp
	g++ -std=c++11 -Wall -c hex_ai.cpp -o obj/hex_ai.o

clean: cleans.o cleans.app

cleans.o:
	rm obj/*.o

cleans.app:
	rm bin/*.app
