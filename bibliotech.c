// ============================================================================
//
//  DESAFIO: SISTEMA DE BIBLIOTECA - PARTE 1
//
//  OBJETIVO PARTE 1
//  IMPLEMNTAR O CADASTRO E A LISTAGEM DE LIVROS USANDO UM ARRAY ESTÁTICO.
//  FOCO EM STRUCTS, ENTRADA/SAÍDA DE DADOS E ORGANIZAÇÃO BÁSICA.
//
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100


// --- Definição da Estrutura (Struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// --- Função para limpar buffer de entrada ---
void limparBufferEntrada() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
};


int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do {

        printf("======================================================\n");
        printf("              BIBLIOTECA - PARTE 1\n");
        printf("======================================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("-------------------------------------------------------\n");
        printf("Escolha uma opção\n");


        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
            printf("--- Cadastro de novo livro ---\n\n");

            if (totalLivros < MAX_LIVROS) {
                printf("Digite o nome do livro:");
                fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                printf("Digite o nome do autor:");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                printf("Digite a editora:");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                printf("Digite a edição:");
                scanf("%d", &biblioteca[totalLivros].edicao);


                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                totalLivros++;

                printf("Livro cadastrado com sucesso!\n");
            } else {
                printf("Biblioteca cheia! Não foi possível cadastrar mais livros.\n");
            }

            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        case 2:
            printf("--- Lista de livros cadastrados ---\n\n");

            if (totalLivros == 0) {
                printf("Nenhum livro cadastrado ainda.\n");
            } else {
                for (int i = 0; i < totalLivros; i++) {
                    printf("--------------------------------------\n");
                    printf("LIVRO %d\n", i + 1);
                    printf("Nome: %s\n", biblioteca[i].nome);
                    printf("Autor: %s\n", biblioteca[i].autor);
                    printf("Editora: %s\n", biblioteca[i].editora);
                    printf("Edição: %d\n", biblioteca[i].edicao);
                }
                printf("--------------------------------------\n");
            }

            printf("\nPressione Enter para continuar...\n\n");
            getchar();
            break;
        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção invalida! Tente novamente.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        }
    } while (opcao != 0);
    return 0;
    
}
