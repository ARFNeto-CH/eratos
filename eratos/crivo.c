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
unsigned int	limita_memoria(unsigned int);
unsigned int	mostra_os_primos(unsigned int);
unsigned int	proximo_primo(unsigned int);
int				retorna_um_se_primo(unsigned int);
int				testa_crivo_contra_funcao(unsigned int);


int	compara_primos_com_crivo(unsigned int n)
{
	proximo_primo(n);	// prepara crivo
	for (unsigned int i = 2; i <= n; i++)
	{
		int r = retorna_um_se_primo(i);
		if (r == 1)
		{	// primo. então deve ser o proximo d lista
			int s = proximo_primo(0);
			if (i != s) return 0;
		}	// end if
	}	// end for
	return 1;	// tudo ok: valores indenticos
}	// end compara_primos_com_crivo()


unsigned int	limita_memoria(unsigned int n)
{
	unsigned limite = (LIMITE_A_ALOCAR_KB * 512) + 1;
	unsigned int t_b = n + n - 2;
	unsigned int r;
	r = (t_b > limite) ? (limite+2)/2 : n;
	return r;

}	// end limita_memoria()


unsigned int	proximo_primo(unsigned int n)
{
	static unsigned int*	valores;
	static unsigned int		proximo, limite, indice, tamanho;
	unsigned int			j, k;
	////////////////////////////////// prepara tudo e retorna
	unsigned int i = 0;
	static int	 eraDois;

	if (n == 1) return (-1);
	if (n > 0)
	{	// chamada inicial: prepara tudo
		if (n == 2)
		{
			eraDois = 1;
			return 0;
		}
		else
		{
			eraDois = 0;
			if (valores != NULL) free(valores);				// se chamou de novo apaga tudo
			tamanho = ((n - 1) / 2);						// so os impares
			i = tamanho * sizeof(unsigned int);
			valores = malloc(i);		// aloca o necessario
			if (valores == NULL) return -1;
			for (j = 0; j < tamanho; j++) valores[j] = 3 + j + j;
			limite = n;
			proximo = 2;
			indice = 0;
		}
		return 0;
	}	//	end if
	////////////////////////////////// devolve o proximo primo
	if (eraDois == 1)
	{
		proximo = 0;
		eraDois = 0;
		return (2);
	}
	if (proximo == 0)	 return( 0);
	if (valores == NULL) return(-2);
	if (proximo == 2)
	{
		proximo = 3;
		return 2;		// unico primo par
	}
	k = proximo;		// a partir de 3
	for (j = indice + k; j < tamanho; j += k)valores[j] = 0;	// marca os multiplos
	for (j = indice + 1; j<tamanho; j++)
	{
		if (valores[j] <= 0) continue;
		proximo = valores[j];
		indice = j;
		return k;
	}	// end for
	proximo = 0;
	return k;
}	// end proximo_primo()


unsigned int	mostra_os_primos(unsigned int n)
{
	unsigned int l = limita_memoria(n);
	if (l < n)
	{	// nao deu: o valor foi limitado
		printf(	"Limite de memoria %dKB: o maior primo foi limitado de %u para %u",
			LIMITE_A_ALOCAR_KB, n, l		);
	}
	unsigned int r = proximo_primo(l);
	if (r < 0)
	{
		printf("Erro ao iniciar sequencia: %d\n", r);
		return(r);
	}
	printf("\n\nPrimos ate %u (inclusive)\n\n", n);
	unsigned int i = 0;
	while ((r = proximo_primo(0)) != 0)
	{
		printf("%10u ", r);
		i += 1;
		if (i % 10 == 0) printf("\n");
	} while (r > 0);
	return i;
}	// end mostra_os_primos()


int				retorna_um_se_primo(unsigned int n)
{
	if (n < 2)		return 0;
	if (n == 2)		return(1);
	if (n % 2 == 0) return(0);
	unsigned int maior = (unsigned int) sqrt( (double) n);
	unsigned int fator = 3;
	while (fator <= maior)
	{
		if (n % fator == 0) return 0;
		fator += 2;
	}	// end while
	return 1;
}	// end retorna_zero_se_primo()


int				testa_crivo_contra_funcao(unsigned int n)
{
	unsigned int r = proximo_primo(n);	// prepara crivo
	
	if (r != 0) return 1;	// deu erro
	unsigned int i = 0;
	while ((r = proximo_primo(0)) != 0)
	{
		i = retorna_um_se_primo(r);
		if (i != 1)
		{
			return 0;	// deu pau: no crivo diz que e primo mas a funcao nao
		}	// end if
	}	// end while
	return 1;
}	//	end testa_crivo_contra_funcao()


int main(int argc, char** argv)
{
	unsigned int n;
	if (argc > 1)	n = strtoul(argv[1], 0, 0);
	else
		n = 900;
	unsigned int	i = 0;
	unsigned int	lim = limita_memoria(n);

	printf("\n\nTestando com n=%u\n", lim);
	if (lim < n)
	{
		printf("Valor original %u truncado por falta de memoria para o crivo\n", n);
		printf("Memoria reservada = %uKB\n", LIMITE_A_ALOCAR_KB );
	}	// end if

	i = mostra_os_primos(lim);
	printf("\n\nEncontrados %u primos\n", i);
	// agora testa a funcao e compara com os valores obtidos do crivo de eratostenes
	i = compara_primos_com_crivo(lim);
	if (i == 1)
		printf("Testando primos contra os marcados no crivo: sem surpresas. Todos os valores coincidem\n");
	else
		printf("Testando primos contra os marcados no crivo: Algo errado!\n");
	// agora testa o crivo e com a funcao verifica se todos sao primos
	i = testa_crivo_contra_funcao(lim);
	if (i == 1)	printf("Testando os valores do crivo com a funcao: sem surpresas. todos os valores confirmados\n");
	else
		printf("Testando os valores do crivo com a funcao: Algo errado\n");

	i = retorna_um_se_primo(UINT_MAX);
	printf("\n\n retorna_um_se_primo(UINT_MAX=%u) retornou %u\n", UINT_MAX, i);
	return 0;

}	// end main()