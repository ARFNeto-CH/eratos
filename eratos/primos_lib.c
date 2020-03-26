#define _CRT_SECURE_NO_WARNINGS
#include "primos-lib.h"

int				compara_primos_com_crivo(unsigned int n)
{
	proximo_primo_crivo(n);	// prepara crivo
	for (unsigned int i = 2; i <= n; i++)
	{
		int r = retorna_um_se_primo(i);
		if (r == 1)
		{	// primo. então deve ser o proximo d lista
			int s = proximo_primo_crivo(0);
			if (i != s) return 0;
		}	// end if
	}	// end for
	return 1;	// tudo ok: valores indenticos
}	// end compara_primos_com_crivo()

int				compara_primos_com_crivo_unica(unsigned int n)
{
	proximo_primo_crivo(n);	// prepara crivo
	for (unsigned int i = 11; i <= n; i++)
	{
		int r = retorna_um_se_primo(i);
		if (r == 1)
		{	// primo. então deve ser o proximo d lista
			int s = proximo_primo_unica(i);
			if (i != s)
			{
				printf("Falhou para %d: nova funcao retornou %d\n", i, s);
				return 0;
			}
		}	// end if
	}	// end for
	return 1;	// tudo ok: valores indenticos
}	// end compara_primos_com_crivo_unica()

unsigned int	limita_memoria(unsigned int n)
{
	unsigned limite = (LIMITE_A_ALOCAR_KB * 512) + 1;
	unsigned int t_b = n + n - 2;
	unsigned int r;
	r = (t_b > limite) ? (limite + 2) / 2 : n;
	return r;

}	// end limita_memoria()

unsigned int	mostra_os_primos(unsigned int n)
{
	unsigned int l = limita_memoria(n);
	if (l < n)
	{	// nao deu: o valor foi limitado
		printf("Limite de memoria %dKB: o maior primo foi limitado de %u para %u",
			LIMITE_A_ALOCAR_KB, n, l);
	}
	unsigned int r = proximo_primo_crivo(l);
	if (r < 0)
	{
		printf("Erro ao iniciar sequencia: %d\n", r);
		return(r);
	}
	printf("\n\nPrimos ate %u (inclusive)\n\n", n);
	unsigned int i = 0;
	while ((r = proximo_primo_crivo(0)) != 0)
	{
		printf("%10u ", r);
		i += 1;
		if (i % 10 == 0) printf("\n");
	} while (r > 0);
	return i;
}	// end mostra_os_primos()

unsigned int	proximo_primo(unsigned int n)
{
	static int	 iniciado = 0;
	static int	 proximo = 0;

	if (n == 0)						// inicia a serie
	{
		iniciado = 1;
		proximo = 2;
		return 1;
	}	// end if

	if (iniciado == 0) return 0;		// erro: tem que chamar com 0 antes

	if (proximo == 2)
	{
		proximo = 1;
		return 2;
	}	// end if

	// normal: a a partir daqui retorna o proximo primo
	for (int i = proximo + 2;; i += 2)
		if (retorna_um_se_primo(i))
		{
			proximo = i;
			return proximo;
		}	// end if
}	// end proximo_primo()

unsigned int	proximo_primo_crivo(unsigned int n)
{
	static unsigned int* valores;
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
	if (proximo == 0)	 return(0);
	if (valores == NULL) return(-2);
	if (proximo == 2)
	{
		proximo = 3;
		return 2;		// unico primo par
	}
	k = proximo;		// a partir de 3
	for (j = indice + k; j < tamanho; j += k)valores[j] = 0;	// marca os multiplos
	for (j = indice + 1; j < tamanho; j++)
	{
		if (valores[j] <= 0) continue;
		proximo = valores[j];
		indice = j;
		return k;
	}	// end for
	proximo = 0;
	return k;
}	// end proximo_primo_crivo()

unsigned int	proximo_primo_unica(unsigned int next)
{
	//
	// atencao: retorna os primos a partir de 11
	//
	int FALSE = 0;
	int TRUE = 1;
	static int p4 = 7;
	// p4 e o ultimo primo
	// nas proximas linhas vamos definir next como
	// sendo... o proximo primo depois de p4
	int achou_proximo = FALSE;
	next = 0;
	for (int i = p4 + 2; !achou_proximo; i = i + 2)
	{
		//int smaior = (int)sqrt((double)i); era isso
		int  maior = 0;
		for (maior = 7; (maior * maior) < i; maior += 1);
		// passou 1 da conta se nao for um quadrado perfeito
		if (maior * maior != i) maior = maior - 1;
		int  fator = 3;
		while (fator <= maior)
		{
			if (i % fator == 0)
			{	// entao 'i' nao e primo
				// forca sair do loop
				fator = 100000000L; // tanto faz
			}
			else
			{
				fator = fator + 2;
			}
		}	// end while
		if (fator != (100000000L))
		{
			next = i;
			achou_proximo = TRUE;
		};	// if()
	};	// for()
	// saindo daqui temos o primo depois de p4 em next
	p4 = next;
	return next;
};	// proximo_primo_unica()

int				retorna_um_se_primo(unsigned int n)
{
	if (n < 2)		return 0;
	if (n == 2)		return(1);
	if (n % 2 == 0) return(0);
	unsigned int maior = (unsigned int)sqrt((double)n);
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
	unsigned int r = proximo_primo_crivo(n);	// prepara crivo

	if (r != 0) return 1;	// deu erro
	unsigned int i = 0;
	while ((r = proximo_primo_crivo(0)) != 0)
	{
		i = retorna_um_se_primo(r);
		if (i != 1)
		{
			return 0;	// deu pau: no crivo diz que e primo mas a funcao nao
		}	// end if
	}	// end while
	return 1;
}	//	end testa_crivo_contra_funcao()

// fim do texto