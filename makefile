all: aicos

aicos: aicos.c
	gcc -o aicos aicos.c -lm

clean:
	rm -f aicos output.csv
	

