#   Universidade Federal da Fronteira Sul
# 
#                TRABALHO II
#   
#	Disciplina: Computação gráfica
#   Professor: José Carlos Bins Filho
#    
#   Renderização da Bandeira da Netherlands(Holanda) 
# 	
#
#   Alunos : Edson Lemes da Silva & Lucas Cezar Parnoff
#
#
#  --- MAKEFILE DE COMPILAÇÃO E EXECUÇAO ---
all: flag

flag: *.cpp
	g++ snow.cpp bmp.cpp android.h  -o  main -lGL -lGLU -lglut
	./main
   
