GCC= gcc 

build: browser.c functions.c functions.h
	$(GCC) -o browser $^ -lncurses
clean: 
	rm browser