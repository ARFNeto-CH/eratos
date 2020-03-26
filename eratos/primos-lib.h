#pragma once
#define	LIMITE_A_ALOCAR_KB	(32768)
#define UM_MEGABYTE			(1048576)

#include "limits.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

/*
	lista das funcoes ai para baixo
*/
int				compara_primos_com_crivo(unsigned int);
int				compara_primos_com_crivo_unica(unsigned int);
unsigned int	limita_memoria(unsigned int);
unsigned int	mostra_os_primos(unsigned int);
unsigned int	proximo_primo(unsigned int);
unsigned int	proximo_primo_crivo(unsigned int);
unsigned int	proximo_primo_unica(unsigned int);
int				retorna_um_se_primo(unsigned int);
int				testa_crivo_contra_funcao(unsigned int);
