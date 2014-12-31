waver: waver.c main.c
	gcc -o StupidSimpleCSynth waver.c main.c
clean:
	rm -rf *~*
	rm -rf StupidSimpleCSynth
	rm -rf wave.wav
install: waver.c main.c 
	gcc -o StupidSimpleCSynth waver.c main.c
