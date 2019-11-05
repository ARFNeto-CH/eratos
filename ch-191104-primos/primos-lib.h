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
unsigned int	calcula_mmc(int a, int b, int c);
unsigned int	proximo_primo(unsigned int);
int				retorna_um_se_primo(unsigned int);
