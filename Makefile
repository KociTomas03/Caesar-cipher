ceasar: compile
	@ceasar
compile:
	@gcc -std=c99 -Wall -Wextra -Werror Ceasar-Cipher.c -o ceasar -lm