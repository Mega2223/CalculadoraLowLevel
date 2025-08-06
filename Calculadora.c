#include <stdlib.h>
#include <stdio.h>

void matrixSum(int bScale);
void scalarProduct();
void matrixProduct();
void transpose();
void isSquare();
void isSymetric();
int** inputMatrix(int width, int height);
int** getTranspose(int** matrix, int height, int width);
void printMatrix(int** matrix, int height, int width);

// linha / height primeiro

int main(){
    int nextOperation = 10;

    while (nextOperation != 0){
        printf(
            "Insira o numero da operacao\n"
            "1 - Adicao\n"
            "2 - Subtracao\n"
            "3 - Multiplicacao escalar\n"
            "4 - Multiplicacao matricial\n"
            "5 - Transposicao\n"
            "6 - Verificar se eh quadrada\n"
            "7 - Verificar se eh simetrica\n"
            "\n0 - Sair\n"
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
        case 3:
            scalarProduct();
            break;
        case 4:
            matrixProduct();
            break;
        case 5:
            transpose();
            break;
        case 6:
            isSquare();
            break;
        case 7:
            isSymetric();
            break;
        default:
            printf("Operacao %d nao existe, tente de novo\n",nextOperation);
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
        for(int x = 0; x < width; ++x){
            C[y][x] = A[y][x] + B[y][x] * bSignal;
        }
    }
    
    printf("A:\n");
    printMatrix(A, height, width);
    printf("\nB:\n");
    printMatrix(B, height, width);

    printf("\nRESULTADO:\n");
    printMatrix(C, height, width);
    printf("\n");

    // nao podemos gerar vazamento de memoria hehehe
    for(int y = 0; y < height; ++y){
        free(A[y]); free(B[y]); free(C[y]);
    }
    free(A); free(B); free(C);
    return;
}

void scalarProduct(){
    int height, width, scalar, **matrix, **result;

    printf("Insira o escalar que vai multiplicar a matriz:\n"); scanf("%d",&scalar);
    printf("Insira o numero de linhas da matriz:\n"); scanf("%d",&height);
    printf("Insira o numero de colunas da matriz:\n"); scanf("%d",&width);
    
    printf("\n--- Insira a matriz ---\n");
    matrix = inputMatrix(height,width);

    result = malloc(height * sizeof(int*));
    for(int y = 0; y < height; ++y){
        result[y] = malloc(width * sizeof(int));
        for(int x = 0; x < width; ++x){
            result[y][x] = matrix[y][x] * scalar;
        }
    }
    
    printf("A:\n");
    printMatrix(matrix, height, width);

    printf("\nRESULTADO:\n");
    printMatrix(result, height, width);
    printf("\n");

    for(int y = 0; y < height; ++y){
        free(matrix[y]); free(result[y]);
    }
    free(matrix); free(result);
    return;
}


void matrixProduct(){
    // A x B = C
    int heightA, widthA, heightB, widthB;
    int **A, **B, **C;
    
    printf("Insira o numero de linhas da matriz A:\n"); scanf("%d",&heightA);
    printf("Insira o numero de colunas da matriz A:\n"); scanf("%d",&widthA);
    printf("Insira o numero de linhas da matriz B:\n"); scanf("%d",&heightB);
    printf("Insira o numero de colunas da matriz B:\n"); scanf("%d",&widthB);
    
    if(widthA != heightB){
        printf("Essas matrizes nao se multiplicam (largura de A eh diferente da altura de B)\n");
        return;
    }

    printf("\n--- Input para a matriz A ---\n");
    A = inputMatrix(heightA,widthA);
    printf("\n--- Input para a matriz B ---\n");
    B = inputMatrix(heightB,widthB);

    C = malloc(heightA * sizeof(int*));
    for(int y = 0; y < heightB; ++y){
        C[y] = malloc(widthB * sizeof(int));
        for(int x = 0; x < widthB; ++x){
            C[y][x] = 0;
            for (int i = 0; i < widthA; i++) {
                C[y][x] += A[y][i] * B[i][x];
            }
        }
    }

    printf("A:\n");
    printMatrix(A, heightA, widthA);
    printf("\nB:\n");
    printMatrix(B, heightB, widthB);

    printf("\nA x B:\n");
    printMatrix(C, heightA, widthB);
    printf("\n");

    for(int y = 0; y < heightA; ++y){ free(A[y]); }
    for(int y = 0; y < heightB; ++y){ free(C[y]); free(B[y]); }

    free(A); free(B); free(C);
    return;
}

void transpose(){
    int height, width, **matrix, **result;

    printf("Insira o numero de linhas da matriz:\n"); scanf("%d",&height);
    printf("Insira o numero de colunas da matriz:\n"); scanf("%d",&width);

    printf("\n--- Input ---\n");
    matrix = inputMatrix(height,width);
    printf("Input:\n");
    printMatrix(matrix, height, width);

    result = getTranspose(matrix,height,width);
    printf("\nTRANSPOSE:\n");
    printMatrix(result, width, height);
}

void isSquare(){
    int width, height;
    // Eu acabei fazendo o codigo de tal modo que ele sempre pede a altura e largura antecipadamente.
    printf("Insira o numero de linhas da matriz:\n"); scanf("%d",&height);
    printf("Insira o numero de colunas da matriz:\n"); scanf("%d",&width);

    if(height == width){
        printf("\nEh quadrada\n");
    } else {
        printf("\nNao eh quadrada\n");
    }       
}

void isSymetric(){
    int width, height, **matrix, **transpose;

    printf("Insira o numero de linhas da matriz:\n"); scanf("%d",&height);
    printf("Insira o numero de colunas da matriz:\n"); scanf("%d",&width);

    matrix = inputMatrix(height,width);

    printf("Input:\n");
    printMatrix(matrix, height, width);

    if(height == width){
        transpose = getTranspose(matrix, height, width);
        for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){
                if(transpose[y][x] != matrix[y][x]){
                    printf("\nNao eh simetrica\n");
                    return;
                }
            }
        }
        printf("\nEh simetrica\n");
    } else {
        printf("\nNao eh simetrica\n");
    }       
}

// como varias funcoes pedem pra colocar a matriz
// isso deixa o codigo um pouco menos verbose
int** inputMatrix(int height, int width){
    int** matrix = malloc(height * sizeof(int*));
    for(int y = 0; y < height; ++y){
        matrix[y] = malloc(width * sizeof(int));
        for(int x = 0; x < width; ++x){
            printf("\nInsira o valor na linha %d coluna %d\n",y+1,x+1);
            scanf("%d",&matrix[y][x]);
        }
    }
    return matrix;
}

int** getTranspose(int** matrix, int height, int width){
    int** transposed;
    transposed = malloc(width * sizeof(int*));
    
    for(int x = 0; x < width; ++x){
        transposed[x] = malloc(width * sizeof(int));
        for(int y = 0; y < height; ++y){
            transposed[x][y] = matrix[y][x];
        }
    }

    return transposed;
}

/*int equals(){

}*/

void printMatrix(int** matrix, int height, int width){
    for(int y = 0; y < height; ++y){
        printf("[");
        for(int x = 0; x < width; ++x){
            printf(" %d",matrix[y][x]);
        }
        printf(" ]\n");
    }
}