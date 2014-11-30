all:aStar aStarDynamic

aStar: main.o Map.o List.o status.o
	-gcc main.o Map.o List.o status.o -o aStar

aStarDynamic: List.o status.o
	-gcc -fPIC -c List.c status.c
	-gcc -shared -o liblist.so List.o status.o
	-gcc main.o Map.o List.o liblist.so -lm -o aStarDynamic