#first makefile ever
build:
	gcc src/player.c src/team.c src/lan_party.c src/match.c -o ./src/lanParty -lm
run:
	./src/lanParty src/ioFiles/c.in src/ioFiles/d.in src/ioFiles/r.out
checker:
	 ./checker/checker.sh
clean:
	rm -f src/lanParty