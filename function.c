#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>
#include "function.h"



/*long unsigned int* get_primos(){
	FILE* fp;
	long unsigned int* lista = malloc(10000000*sizeof(int));
	int i = 0;

	fp = fopen("primos.txt", "r");
	if(fp != NULL){

		while(fscanf(fp, "%lu", &lista[i])> 0){
			i++;
		}
		
	}
 	return lista;
}

void crivo(){
	FILE* primos;
	unsigned long int i, max = 10000000;
	primos = fopen("primos.txt","w");
	char *vetor = calloc(max, 1);
	long int  divisor;

	divisor = 2;
	
	int limite = raiz_inteira(max);

	while(divisor <= limite){
		for (i = divisor+1; i <= max; i++){
			if(vetor[i] == 1){
				continue;
			}
			if(i % divisor == 0)
				vetor[i] = 1;
		}
		divisor++;
	}
	i = 2;
	while(i < max){
		if (vetor[i] == 0)
			fprintf(primos, "%lu\n", i);

		i++;
	}	
	fclose(primos);
}*/

int raiz_inteira(long unsigned int num){  /*Função que encontra a raiz inteira de um número*/
	float x, y;
	x = num;
	y = 1;

	while(x - y > 1){
		x = (x + y)/2;
		y = num / x;
	}
	return x;
}


void fatorar(long unsigned int valor){
	long unsigned int divisor = 2;
	long unsigned int r = raiz_inteira(valor);
	while(valor != 1){
		if (divisor >= r)
			divisor = valor;
		if(valor % divisor == 0){
			printf(" %-12lu | %lu\n", valor, divisor);
			valor = valor/divisor;
		}
		else{
			divisor++;
			
		}
	}
	printf(" %-12lu | \n",valor);
}

void mostrar_vetor(int *vetor, int tamanho){
	int i = 0;
	for (i = 0; i < tamanho; i++){
		if (vetor[i] == -1){
			printf("\n");
			return;
		}
		
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

void mostrar_fatores(FILE *input){
	unsigned long int num, u_time, s_time, tempo;
	
	while(fscanf(input, "%lu", &num) == 1){
		tempo = time_start();
		u_time = user_time_start();
		s_time = system_time_start();
		fatorar(num);
		tempo = time_end(tempo);
		u_time = user_time_end(u_time);
		s_time = system_time_end(s_time);
		printf(" Tempo de usuário: %lu us\n Tempo de sistema: %lu us\n Tempo de Execução: %lu us\n ____________________________________________________\n", u_time, s_time, tempo/1000);
	}
}


int comb(int q){	/* 2^n - (n+1)) cálculo do número de xulambs atraves da tabela verdade*/
		return (2<<(q-1))-q-1;
}

int cont_fatores(long unsigned int num){
	int cont = 0;

	long unsigned int divisor = 2;
	long unsigned int ultimo = 0;
	if(num % divisor == 0){
		cont ++;
		ultimo = 2;
		while (num % divisor == 0){
			num = num /divisor;
		}
	}
	
	divisor++;
	
	while (num != 1){
		if(num % divisor == 0){
			num = num / divisor;
			if(divisor != ultimo){
				ultimo = divisor;
				cont ++;
			}
		}
		else
		divisor = divisor+2;
	}
	return cont;
}

int soma_xulamb(int num){
	
	return comb(num);	
}


int get_parametros(char **entrada, char **saida, int argc, char **argv){
	int opt;
	while ((opt = getopt(argc, argv, "i:o:df")) > 0){
		switch (opt){
			case 'i':
				*entrada = optarg;
				break;

			case 'o':
				*saida = optarg;
				break;

			case 'd':
				return 1;

			case 'f':
				return 2;

			default: printf("Diretiva não reconhecida.\n");
		}
	}
	return 0;
}	

void divisores_xulamb(FILE *input, FILE *output){
	long unsigned int num;
	/*long unsigned int *lista = get_primos();*/
	if (input == NULL){
		printf("Arquivo de entrada não encontrado.\n");
		return;
	}
	
	while(fscanf(input, "%lu", &num) == 1){
		fprintf(output, "%d\n", soma_xulamb(cont_fatores(num)));
	}
}

void tabela(FILE *input, FILE *output){
	int fatores;
	int xulambs;
	long unsigned int num;
	double s_time, u_time, tempo;
	/*long unsigned int* lista;*/
	/*lista = get_primos();*/

	if (input == NULL){
		printf("Arquivo de entrada não encontrado.\n");
		return;
	}
	fprintf(output, "               |                Fatores              |                 Tempos em microssegundos\n");
	fprintf(output, "Número         |      Primos       |     Xulambs     |        Usuário       |        Sistema        |      Execução\n");
	while(fscanf(input, "%lu", &num) == 1){
		u_time = user_time_start();
		s_time = system_time_start();

		tempo = time_start();
		fatores = cont_fatores(num);
		xulambs = soma_xulamb(fatores);
		tempo = time_end(tempo);

		u_time = user_time_end(u_time);
		s_time = system_time_end(s_time);

		fprintf(output, "%-13lu  |        %-10d |        %-8d |        %-13f |        %-13f  |      %f\n", num, fatores, xulambs, u_time, s_time, tempo/1000);
	}
}


double time_start(){
	struct timespec tempo;
	clock_gettime(CLOCK_MONOTONIC, &tempo);
	return ((double)tempo.tv_nsec /1000 ) + ((double)tempo.tv_sec * 1000000); 
}

double time_end(double tempo_inicial){
	struct timespec tempo_final;
	clock_gettime(CLOCK_MONOTONIC, &tempo_final);
	return ((double)tempo_final.tv_nsec /1000 ) + ((double)tempo_final.tv_sec * 1000000) - tempo_inicial;
}


double system_time_start(){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return (double)use.ru_stime.tv_usec + ((double)use.ru_stime.tv_sec * 1000000);
}

double user_time_start(){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return (double)use.ru_utime.tv_usec + ((double)use.ru_utime.tv_sec * 1000000);	
}


double system_time_end(double tempo){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return use.ru_stime.tv_usec + (use.ru_stime.tv_sec * 1000000) - tempo;
}

double user_time_end(double tempo){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return use.ru_utime.tv_usec + (use.ru_utime.tv_sec * 1000000) - tempo;	
}


void run(int argc, char **argv){

	FILE *input, *output;
	char *entrada = NULL, *saida = NULL;
	int detalhes;
	/*teste_tempo();*/
	if(argc >= 2){
		if (argc >6){
			printf("Erro. Excesso de parâmetros.\n");
			return;
		}
		detalhes = get_parametros(&entrada, &saida, argc, argv);
		input = fopen(entrada, "r");
		output = fopen(saida, "w");

		if (detalhes == 1)
			tabela(input, output);

		else{
			if (detalhes == 2){
				mostrar_fatores(input);
			}
			else divisores_xulamb(input, output);
		}
		fclose(input);
		fclose(output);
	}
}

void teste_tempo(){
	FILE *time_cont = fopen("tempo.txt","w");
	srand(time(NULL));
	long unsigned int x;
	double u_time, s_time, tempo;
	int fatores, qtd;
	
	x = 9; 
	fprintf(time_cont, "                                            Contagem de Tempo                           \n");
	fprintf(time_cont, "               |                Fatores              |                 Tempos em microssegundos\n");
	fprintf(time_cont, "Número         |      Primos       |     Xulambs     |        Usuário       |        Sistema        |      Execução\n");
	while (x <= 100000000000){
		tempo = time_start();
		u_time = user_time_start();
		s_time = system_time_start();

		fatores = cont_fatores(x);
		qtd = soma_xulamb(fatores);
		
		tempo = time_end(tempo);
		u_time = user_time_end(u_time);
		s_time = system_time_end(s_time);

		fprintf(time_cont, "%-13lu  |        %-10d |        %-8d |        %-13f |        %-13f  |      %f\n", x, fatores, qtd, u_time, s_time, tempo/1000);
		x = x+(rand() % x) + raiz_inteira(x);
	}
	
	fclose(time_cont);
	return;

}
