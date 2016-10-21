#   Universidade Federal da Fronteira Sul
# 
#                TRABALHO I
#   
#   Disciplina: Computação gráfica
#   Professor: José Carlos Bins Filho
#    
#   Renderização do Android andando de Skate 
# 	
#
#   Aluno : Edson Lemes da Silva
#
#
#  --- MAKEFILE DE COMPILAÇÃO E EXECUÇAO ---
all: android

android: *.cpp
	g++ snow.cpp bmp.cpp android.h  -o  main -lGL -lGLU -lglut
	./main


clean:
	rm main   
