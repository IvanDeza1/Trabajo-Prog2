#------------------------------------------------------------------------------
# File:   Makefile
# Author: Programación II-Unizar
# Date:   mayo 2022
# Coms:   Ejemplo de Makefile (Make_mainGSenku) para el trabajo de Programación II
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -I. -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: mainGSenku
#-----------------------------------------------------------
# Compilacion
mainGSenku.o: mainGSenku.cpp
	${CC} -c mainGSenku.cpp ${CPPFLAGS}
# Linkado
mainGSenku: mainGSenku.o GSenku.o
	${CC} mainGSenku.o GSenku.o -o mainGSenku ${LDFLAGS}
GSenku.o: GSenku.cpp GSenku.hpp
	${CC} -c GSenku.cpp ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} GSenku.o mainGSenku.o mainGSenku
