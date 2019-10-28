compile: t1.cc
	g++ -o simula-vm t1.cc
test1: compile teste1
	./simula-vm 3 < teste1
test2: compile teste1
	./simula-vm 4 < teste2
test3: compile teste1
	./simula-vm 4 < teste3
simpleTests: test1 test2 test3

complexTests: compile teste4.txt
	./simula-vm 64 < teste4.txt

