#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char nome[MAX_LEN];
    float nota1;
    float nota2;
} Aluno;

void calcularSituacao(Aluno aluno, FILE *saida) {
    float media = (aluno.nota1 + aluno.nota2) / 2.0;

    fprintf(saida, "%s, %.2f, %s\n", aluno.nome, media, (media >= 7.0) ? "APROVADO" : "REPROVADO");
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    char cabecalho[MAX_LEN];
    fgets(cabecalho, MAX_LEN, entrada);

    Aluno aluno;
    char nota1Str[MAX_LEN], nota2Str[MAX_LEN];
    while (fscanf(entrada, "%[^,],%*[^,],%[^,],%[^,],%*s\n", aluno.nome, nota1Str, nota2Str) == 3) {
        aluno.nota1 = atof(nota1Str);
        aluno.nota2 = atof(nota2Str);
        calcularSituacao(aluno, saida);
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo SituacaoFinal.csv gerado com sucesso!\n");

    return 0;
}
