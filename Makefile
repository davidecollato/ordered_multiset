FLAGS = #-DNDEBUG

main.exe: main.o element_not_found.o
	g++ $(FLAGS) main.o element_not_found.o -o main.exe
	
main.o: main.cpp multiset.h
	g++ $(FLAGS) -c main.cpp -o main.o
	
element_not_found.o: element_not_found.cpp
	g++ $(FLAGS) -c element_not_found.cpp -o element_not_found.o
	
.PHONY: clean

clean:
	rm -f *.exe *.o