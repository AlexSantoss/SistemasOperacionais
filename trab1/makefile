compile:
	g++ -o simula-vm t1.cc
test1: compile
	./simula-vm 3 < teste1
test2: compile
	./simula-vm 4 < teste2
test3: compile
	./simula-vm 4 < teste3
test4: compile
	./simula-vm 64 < teste4
test5: compile
	./simula-vm 256 < teste4
test6: compile
	./simula-vm 1024 < teste4
test7: compile
	./simula-vm 4096 < teste4

simpleTests: test1 test2 test3
complexTests: test4 test5 test6 test7

allTests: simpleTests complexTests




