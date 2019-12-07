#ifndef _H_tp1
#define _H_tp1

typedef long unsigned int *lista_primos;

/*lista_primos get_primos();*/

int raiz_inteira(long unsigned int num);

void fatorar(long unsigned int num);
void mostrar_fatores(FILE *input);
void mostrar_vetor(int *vetor, int tamanho);

int comb(int q);
int cont_fatores(long unsigned int num);
int soma_xulamb(int primos);

int get_parametros(char **entrada, char **saida, int argc, char** argv);
void divisores_xulamb(FILE *input, FILE *output);
void tabela(FILE *input, FILE *output);

double time_start();
double time_end(double tempo);

double system_time_start();
double user_time_start();
double system_time_end(double tempo);
double user_time_end(double tempo);

void run(int argc, char **argv);
void teste_tempo();

#endif