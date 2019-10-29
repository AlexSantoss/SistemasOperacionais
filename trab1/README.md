# Trabalho 1 - Simular algoritmos de substituição de páginas

### Para Executar
No terminal:
```
make compile
./simula-vm n < input
```
Onde n = numero de quadros e input = arquivo de entrada

### Para usar os testes prontos
No terminal:
```
make testX
```
Onde X pode ser de 1 ate 7, sendo:
- 1: Referente ao exemplo do livro do Maziero
- 2: Referente ao Arquivo 1 do site do trabalho
- 3: Referente ao Arquivo 2 do site do trabalho
- 4-7: Referentes ao Arquivo 3 do site do trabalho, variando apenas o numero de paginas (64, 256, 1024, 4096)

Para executar os testes de 1 a 3:
```
make simpleTests
```

Para executar os testes de 4 a 7:
```
make complexTests
```

Para executar todos os testes:
```
make allTests
```
