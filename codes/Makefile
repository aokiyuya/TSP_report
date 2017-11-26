default: main.cpp 10.dat
	gcc main.cpp -o main.out
	./main.out ./10.dat II
	rm *.out

all: II SA CM comb

II: main.cpp 10.dat 11.dat 12.dat 13.dat  225.dat
	gcc main.cpp -o main.out
	ls | grep -e '1..dat' -e '5.dat' | xargs -I@ ./main.out @ II
	rm *.out

SA: main.cpp  10.dat 11.dat 12.dat 13.dat  225.dat
	gcc main.cpp -o main.out
	ls | grep -e '1..dat' -e '5.dat' | xargs -I@ ./main.out @ SA
	rm *.out

CM: main.cpp 10.dat 11.dat 12.dat 13.dat  225.dat
	gcc main.cpp -o main.out
	ls | grep -e '1..dat' -e '5.dat' | xargs -I@ ./main.out @ CM
	rm *.out

comb: combination.c 10.dat 11.dat 12.dat 13.dat
	gcc combination.c -o main.out
	ls | grep -e '^5.dat' -e '1..dat' | xargs -I@ ./main.out @
	rm *.out

clean:
	rm *.out

