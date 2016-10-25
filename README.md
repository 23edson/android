	Universidade Federal da Fronteira Sul.
 
	TRABALHO I
   
	Disciplina: Computação gráfica;
	Professor: José Carlos Bins Filho;
    
	Renderização do Android andando de Skate; 
 	

	Aluno : Edson Lemes da Silva.


**Compilação**
Para compilar é necessário digitar na linha de comando "make".

Compilado e executado no LINUX.

O arquivo Makefile se encarrega de iniciar a execução do arquivo compilado.
Alternativamente, para remover o executável gerado basta digitar no terminal: make clean.

**Execução**

a tecla 'ESC' pode ser utilizada para o encerramento do programa.

a tecla 'w' muda a visão da câmera para cima;
a tecla 's'  muda a visão da câmera para baixo;
as teclas direcionais : UP, DOWN, LEFT e RIGHT podem ser usadas para
controlas  a livre movimentação da câmera no cenário. 

Inicialmente, o ponto de visão é definido como : 0.0, assim ao apertar 'w', o
ponto de visão é incrementado, e ao apertar 's', o ponto é decrementado. A cada
evento de teclado destas duas teclas, o ponto de visão atual é mostrado no terminal.

No terminal, também é impresso a quantidade de quadros por segundo da aplicação.

*Obs: O movimento dos braços do boneco é irregular, isto é, um braço
movimento mais que o outro. A intenção disso é fazer com que os movimentos
se tornem o mínimo real possível. 