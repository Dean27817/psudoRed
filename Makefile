test:
	gcc -o prod src/main.c -lyaml
	./prod source.txt output.red
	rm prod
	./src/asm output.red
	rm output.red
	./src/corewar output.
compile:
	gcc -o prod src/main.c -lyaml
run:
	./prod source.txt output.red
	rm prod
	./src/asm output.red
	rm output.red
	./src/corewar output.
