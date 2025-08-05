#include <stdlib.h>
#include <stdio.h>

void matrixSum(int bScale);
int** inputMatrix(int width, int height);
void printMatrix(int** matrix, int height, int width);

// linha / height primeiro

int main(){
    int nextOperation = 10;

    while (nextOperation > 0){
        printf(
            "Insira o numero da operacao\n"
            "1 - Adicao\n"
            "2 - Subtracao\n"
            "3 - Multiplicacao escalar\n"
            "4 - Multiplicacao matricial\n\n"
            "0 - Sair\n"
        );

        scanf("%d",&nextOperation);

        switch (nextOperation) {
        case 0: break; //Nao faz nada e cai no proximo while
        case 1:
            matrixSum(1);
            break;
        case 2:
            matrixSum(-1);
            break;
        default:
            printf("Operacao %d e invalida, tente de novo\n",nextOperation);
            break;
        }
    }
    printf("o/\n");
    return 0;
}

void matrixSum(int bSignal){
    bSignal = bSignal > 0 ? 1 : -1; //bSignal eh so um atalho para a implementacao de subtracao
    
    // A + B = C, todos tem o mesmo tamanho
    int height, width;
    int **A, **B, **C;
    
    printf("Insira o numero de linhas das matrizes:\n"); scanf("%d",&height);
    printf("Insira o numero de colunas das matrizes:\n"); scanf("%d",&width);
    
    printf("\n--- Input para a matriz A ---\n");
    A = inputMatrix(height,width);
    printf("\n--- Input para a matriz B ---\n");
    B = inputMatrix(height,width);

    C = malloc(height * sizeof(int*));
    for(int y = 0; y < height; ++y){
        C[y] = malloc(width * sizeof(int));
        for(int x = 0; x < height; ++x){
            C[y][x] = A[y][x] + B[y][x] * bSignal;
        }
    }

    printf("RESULTADO:\n");
    printMatrix(C, height, width);
    printf("\n");

    return;
}

// como varias funcoes pedem pra colocar a matriz
// isso deixa o codigo um pouco menos verbose
int** inputMatrix(int height, int width){
    int** matrix = malloc(height * sizeof(int*));
    for(int y = 0; y < height; ++y){
        matrix[y] = malloc(width * sizeof(int));
        for(int x = 0; x < height; ++x){
            printf("\nInsira o valor na linha %d coluna %d\n",y+1,x+1);
            scanf("%d",&matrix[y][x]);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int height, int width){
    for(int y = 0; y < height; ++y){
        printf("[");
        for(int x = 0; x < height; ++x){
            printf(" %d",matrix[y][x]);
        }
        printf(" ]\n");
    }
}