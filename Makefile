compile:
	gcc -o prod src/main.c -lyaml
run:
	./prod source.txt output.txt
