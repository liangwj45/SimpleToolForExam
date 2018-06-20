main : *.cpp
	g++ *.cpp -I. -o main
	./main
run :
	./main