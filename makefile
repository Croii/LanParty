#first makefile ever
build:
	gcc -Wunused-function src/player.c src/team.c src/lanParty.c src/match.c src/trees.c -o ./src/lanParty -lm
	
run:
	./src/lanParty src/ioFiles/c.in src/ioFiles/d.in src/ioFiles/r.out

checker:
	 ./checker/checker.sh

clean:
	rm -f src/lanParty

valgr:
	make build
	clear
#	valgrind --leak-check=full --show-leak-kinds=alloc,free src/lanParty src/ioFiles/c.in src/ioFiles/d.in src/ioFiles/r.out
	valgrind --leak-check=full --show-leak-kinds=definite --trace-children=no src/lanParty src/ioFiles/c.in src/ioFiles/d.in src/ioFiles/r.out 2>&1 | grep -E "total heap usage"
