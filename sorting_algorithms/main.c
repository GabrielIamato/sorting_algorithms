#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>
long long int comp_chaves, mov_registros;
/*Bubble Sort, Insertion Sort, Shell Sort, Quick Sort, Selection Sort, Heap Sort, Merge Sort*/
void swap (int *a, int *b){
    int aux = (*a);
    (*a) =(*b);
    (*b) = aux;
}

void bubble_sort_aprimorado(int *vetor, int tamanho_vetor){
    int i, j;
    bool troca = true;
    // Se não for feita nenhuma troca, retorna
    for(i = 0; i<tamanho_vetor && troca; i++){
        troca = false;
        // Para em tamanho_vetor -i - 1. O -i refere-se aos elementos já ordenados
        for(j = 0; j<tamanho_vetor-i-1; j++){
            comp_chaves++;
            if(vetor[j]>vetor[j+1]){
                mov_registros++;
                swap(&vetor[j], &vetor[j+1]);
                troca  = true;
            }
        }
    }
}
//Acha pivo como mediana de 3 elementos
int achar_pivo(int *vector, int ini, int fim) {
    int meio = ini + (fim - ini) / 2;

    int a = vector[ini];
    int b = vector[meio];
    int c = vector[fim];

    // Verifica a mediana entre *a, *b e *c
    if ((a > b) != (a > c))
        return a;
    else if ((b > a) != (b > c))
        return b;
    else
        return c;
}
void quick_sort(int *v, int ini, int fim){
    // Define-se pivo como elemento do meio, i como primeiro elemento e j como último elemento
    int i =ini, j = fim;
    int pivo = achar_pivo(v, ini, fim);
    //int pivo = v[(ini+fim)/2];
   // Primeira etapa, percorre enquanto i<j
    do{
        // percorre i e j até que um elemento da esquerda pertença à direita
        while(v[i]<pivo){ i++; comp_chaves++;}
        while(v[j]>pivo){ j--; comp_chaves++;}
        comp_chaves+=2; // critério de parada
        // Não é estavel (realiza troca de elementos iguais)
        if(i<=j){
            mov_registros++;
            swap(&v[i], &v[j]);
            i++;
            j--;
        }
    } while(i<j);
    // Continua iterações
    if(j>ini){
        quick_sort(v, ini, j);
    }
    if(i<fim){
        quick_sort(v, i, fim);
    }
}

void insertion_sort(int *vector, int tamanho_vetor){
    int i, j, elem;
    // vai percorrer o vetor inteiro , começando em 1 (começa em 1 pois o elemento 0 já está ordenado)
    for(i = 1; i<tamanho_vetor; i++){
        // pega o elemento
        elem = vector[i];
        // para os elementos para trás de elem (Já ordenados), enquanto o "elem<vector[j]", realiza-se shift right
        // Note que se eu considerar elem<=vector[j] , o algoritmo é instável (pois vai realizar a troca de 2 e 2)
        // se eu considerar elem<vector[j] , o algoritmo é estável (pois não vai realizar a troca de 2 e 2)
        for(j = i-1; j>=0 && elem<vector[j];j--){
            comp_chaves++;
            mov_registros++;
            vector[j+1] = vector[j];
        }
        comp_chaves++;
        // se o elemento for maior que o da posição vector[j], ele deve ser inserido ali, pois a iteração acabou
        // portanto, insere-se o elemento naquela posição
        mov_registros++;
        vector[j+1] = elem;
    }
}


void shell_sort(int *vector, int tamanho){
    // No sheel sort, o algoritmo divide em sublistas(gaps) e aplica o insertion sort, até que o gap seja 1 e aplique-se o insertion sort no vetor inteiro
    int gap = tamanho / 2; 
    int j;
    int elemento_aux;
    while(gap>0){
        // começa o loop a partir do gap e vai até o final do array
        for(int i = gap; i <tamanho; i++){
            elemento_aux = vector[i]; // variável auxiliar para pegar o elemento atual
            j = i;
            // faz a verificação se o elemento_aux é maior que o elemento comparado pelo gap. Se for maior, atribui ao elemento j o elemento da distância de gap.
            while((j>=gap) && ((elemento_aux > vector[j-gap]) )){
                comp_chaves++;
                mov_registros++;
                vector[j] = vector[j-gap];
                j -= gap;
              }
            comp_chaves++;
            mov_registros++;
            //Atribui-se o elemento original a sua posição correta (para que ele não seja perdido)
        vector[j]= elemento_aux;
        }
    //repete-se esse processo
    gap /= 2;
    }
} 

void selection_sort(int *vector, int tamanho_vetor){
    int menor_elemento_posicao;
    for(int i = 0; i<tamanho_vetor-1; i++){
        menor_elemento_posicao = i;
        for(int j = i+1;j<tamanho_vetor; j++){
            comp_chaves++;
            if(vector[j]<vector[menor_elemento_posicao]){
                menor_elemento_posicao = j;
            }
        }
        comp_chaves++;
        if(i != menor_elemento_posicao){
            mov_registros++;
            swap(&(vector[i]), &(vector[menor_elemento_posicao]));
        }
}
}

void intercala(int *v, int ini, int meio, int fim) {
    int i, j, k, n1, n2;

    // tamanhos dos dois subarranjos a serem intercalados
    n1 = meio - ini + 1;
    n2 = fim - meio;

    // Aloca-se dinamicamente espaço para os arrays
    int *L = (int *) malloc((n1 + 1) * sizeof(int));
    int *R = (int *) malloc((n2 + 1) * sizeof(int));

    // Caso haja problema na alocação
    if (L == NULL || R == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    // Inicia-se os dois subarranjos 
    for (i = 0; i < n1; i++)
        L[i] = v[ini + i];
    L[n1] = INT_MAX; 

    for (j = 0; j < n2; j++)
        R[j] = v[meio + j + 1];
    R[n2] = INT_MAX;

   // Intercala-se os dois arranjos
    i = j = 0;
    for (k = ini; k <= fim; k++) {
        // Verificando prioridades
        comp_chaves++;
        mov_registros++;
        if (L[i] < R[j]) {
            v[k] = L[i];
            i++;
        }      
        else {
            v[k] = R[j];
            j++;
        }
    }
    // Libera-se memória alocada
    free(L);
    free(R);
}

// Separa o array no meio repetidas vezes , até que So início seja menor que o fim (podemos considerar que cada subarray tem tamanho 1)
// Faz esse processo recursivamente e depois intercala (ordenando) os subarrays, totalizando complexidade de O(n*log(n))
void mergesort(int *v, int ini, int fim) {
    int meio;
    if (ini < fim) {
        meio = (ini + fim) / 2; //metade do subarray
        mergesort(v, ini, meio); // metade inferior do subarray
        mergesort(v, meio + 1, fim); // metade superio do subarray
        intercala(v, ini, meio, fim); // intercala os subarrays ordenando-os
    }
}

// Complexidade: O(logn) , 
//arrumar a heap depois que a raiz passa para o final do vetor
void rearranjar_heap(int *vector, int posicao, int tam_heap){
    // esq, dir e maior recebem indices
    int esq, dir, maior, aux;
    // elementos da esquerda e da direita
    esq = 2* posicao + 1;
    dir = 2 * posicao +2;
    maior = posicao;

    // encontra o maior elemento entre o pai e dois filhos
    comp_chaves++;
    if(esq < tam_heap && vector[esq] > vector[maior]){
        maior = esq;
    }
    else if(dir < tam_heap && vector[dir] > vector[maior]){
        maior = dir;
    }

    // se o elemento da esq ou direita é maior que o pai (posicao)
    // então troca-se os dois elementos
    if(maior != posicao){
        mov_registros++;
        swap(&(vector[maior]), &(vector[posicao]));
        //chama por maior (o elemento achado)
        rearranjar_heap(vector, maior, tam_heap);
    }

}

// Complexidade : O(n)
//Objetivo: pegar vetor inicial e construir heap máximo
void construir_heap(int *vector, int tam_heap){
    int i;
    // tam_heap/2 -1 é o último nó que não é folha
    // O(n)
    for(i = tam_heap/2 -1 ; i>=0; i--){
        //Rearranjar heap
        rearranjar_heap(vector, i, tam_heap);
    }
}

// Ordenação por Heap sort 
// Ordenação O(nlogn)
// Melhor que o Shell Sort
// Heap Sort é estável
void heap_sort(int *vector, int tamanho_vetor){
    int i;
    // constroi a heap
    construir_heap(vector, tamanho_vetor);
    // troca a raiz com o último elemento do vetor
    int tam_heap = tamanho_vetor;
    for(i = 0; i<tamanho_vetor; i++){
        mov_registros++;
        swap(&(vector[0]), &(vector[tam_heap-1]));
        // diminui o tamanho da heap, pois já colocamos o elemento 0 na posição correta
        tam_heap--;
        // rearranja a heap
        rearranjar_heap(vector, 0, tam_heap);
    }
}  

/*Contagem dos Menores
    Ideia: se soubermos quantos elementos são menores que X, sabemos a posição de x
    Usa-se um array auxiliar para manter a contagem e outro para montar o arranjo
    Complexidade de tempo: O(n²), 2 for aninhados que percorrem em N
    COmplexidade de espaço: O(3n) , o vetor original + 2 vetores auxiliares
*/

void contagem_dos_menores(int *vector, int tamanho){
    int vet_auxiliar[tamanho], vet_final[tamanho], i, j;
    //inicialização do vetor
    for(i = 0; i<tamanho;i++){
        vet_auxiliar[i] = 0;
    }

    //Contagem dos menores
    //Começa do segundo elemento, vai até o fim
    for(i = 1;i<tamanho;i++){
        for(j = i-1; j>=0;j--){
            comp_chaves++;
            if(vector[i]<vector[j])
                vet_auxiliar[j]++;
            else vet_auxiliar[i]++;
        }
    }
    //Monta-se arranjo final
    for(i = 0;i<tamanho;i++){
        vet_final[vet_auxiliar[i]] = vector[i];
    }

    // Copia-se o array para o array final
    for(i = 0; i<tamanho; i++){
        vector[i] = vet_final[i];
    }

}

/*
    Ordenação de Raízes ou Radix-Sort
    Ideia: comparar os dígitos menos significativos para mais significativos  
*/

void radixSort(int *v, int n) {
    int maior = 0;
    for (int i = 1; i < n; i++) {
        comp_chaves++;
        if (v[i] > maior)
            maior = v[i];
    }

    for (int base = 1; maior/base > 0; base *= 10 ) {
        int *aux = (int*)malloc(sizeof(int)*n);
        int b[10] = {0}; 

        for (int i = 0; i < n; i++) {
            mov_registros++;
            int indice = (v[i]/base) % 10;
            b[indice]++;
        }

        for (int i = 1; i < 10; i++)
            //mov_registros++;?? comp_chaves++;??
            b[i] += b[i-1];

        for (int i = n-1; i >= 0; i--) {
            mov_registros++;
            int ind = ( v[i]/base )  % 10;
            aux[b[ind]-1] = v[i];
            b[ind]--;
        }

        for (int i = 0; i < n; i++) {
            mov_registros++;
            v[i] = aux[i];
        }
            
        free(aux);
    }
}

// Compilação Script
// chmod +x medir_tempo.sh
// Rodando script
// ./medir_tempo.sh
int main(){
    int tamanho;
    scanf("%d", &tamanho);
    int* v = (int *) malloc (tamanho * sizeof(int));
    mov_registros = 0, comp_chaves = 0;
    for(int i=0; i<tamanho; i++){
        scanf(" %d", &v[i]);
    }
    //quick_sort(v, 0, tamanho-1);
    //contagem_dos_menores(v, tamanho);
    //radixSort(v, tamanho);
    //heap_sort(v,tamanho);
    //shell_sort(v,tamanho);
    insertion_sort(v, tamanho);
    //selection_sort(v, tamanho);
   //bubble_sort_aprimorado(v, tamanho);
    //mergesort(v, 0, tamanho-1);
    /*printf("\n");
    for(int i=0; i<tamanho; i++){
        printf("%d ", v[i]);
    }*/
    printf("%d\n", tamanho);
    printf("com_chaves=%lld\n", comp_chaves);
    printf("mov_registros=%lld\n", mov_registros);
    return 0;
}
