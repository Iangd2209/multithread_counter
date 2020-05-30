#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t trava;
int vetor_primos[15], vetor[15];
int tam, k;

//retorna 1 se o número é primo, 0 se não
int primo (int N){
	int aux=1, div;

	if(N==0 || N==1){
		aux=0;
	} else if(N!=2) {
		for(div=2; div<N; div++){
			if(N%div==0){ aux=0; break;}
		}
	}

	return aux;
}

void* worker(void *arg) {
	int x, aux=0;
	
	pthread_mutex_lock(&trava);

	x=vetor[k];
	aux=primo(x);
	vetor_primos[k]=aux;
		
	k++;
	
	pthread_mutex_unlock(&trava);
				
	return NULL;
}

int main() {

	pthread_t threads[4];
	int thread_id[4];

	int x, i=0, contador=0;
	char verifier;

	for(i=0; i<4; i++){
		thread_id[i]=i;
	}
	
	while(verifier!='\n'){
		scanf("%d", &x);
		vetor[tam]=x;
		tam++;
		scanf("%c", &verifier);
	}
	
	while(k<tam)
		for(i=0; i<4; i++){
			if(k<=tam){
				pthread_create(&(threads[i]), NULL, worker, (void*) (&thread_id[i]));
				pthread_join(threads[i], NULL);
			}
		}		

	for(i=0; i<tam; i++){
		if(vetor_primos[i]==1) contador++;
	}
		
	printf("%d\n", contador);
	
	return 0;
}
