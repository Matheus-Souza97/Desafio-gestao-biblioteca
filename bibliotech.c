// ============================================================================
//
//  DESAFIO: SISTEMA DE BIBLIOTECA - PARTE 1
//
//  OBJETIVO PARTE 1
//  IMPLEMNTAR O CADASTRO E A LISTAGEM DE LIVROS USANDO UM ARRAY ESTÁTICO.
//  FOCO EM STRUCTS, ENTRADA/SAÍDA DE DADOS E ORGANIZAÇÃO BÁSICA.
//
//  OBJETIVO PARTE 2
//  ADICIONAR FUNCIONALIDADE DE EMPRESTIMO E INTRODUZIR ALOCAÇÃO DINÂMICA
//  - OS ARRAYS DE LIVRO E EMPRESTIMO SERÃO ALOCADOS COM MALLOC/CALLOC
//  - NOVA STRUCT PARA EMPRESTIMO
//  - MEMORIA LIBREADA COM FREE
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMO 50



// --- Definição da Estrutura (Struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimo {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

// --- Função para limpar buffer de entrada ---
void limparBufferEntrada() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
};


int main() {

    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = (struct Livro*) calloc(MAX_LIVROS, sizeof(struct Livro));

    emprestimos = (struct Emprestimo*) malloc(MAX_EMPRESTIMO * sizeof(struct Emprestimo));


    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }



    
    int totalEmprestimo = 0;
    int totalLivros = 0;
    int opcao;

    do {

        printf("======================================================\n");
        printf("              BIBLIOTECA - PARTE 1\n");
        printf("======================================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realiza emprestimo\n");
        printf("4 - Listar emprestimos\n");
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

                limparBufferEntrada();


                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                biblioteca[totalLivros].disponivel = 1;

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
        case 3:
            printf("--- Realizar emprestimo ---\n\n");
            if (totalEmprestimo >= MAX_EMPRESTIMO) {
                printf("Limite de emprestimos atingido!\n\n");
            } else {
                printf("Livros disponiveis:\n");
                int disponiveis = 0;
                for(int i = 0; i < totalLivros; i++) {
                    if (biblioteca[i].disponivel) {
                        printf("%d - %s\n", i + 1, biblioteca[i].nome);
                        disponiveis++;
                    }
                }

                if (disponiveis == 0) {
                    printf("Nenhum livro disponivel para emprestimo.\n");
                } else {
                    printf("\nDigite o numero do livro que deseja emprestar: ");
                    int numLivro;
                    scanf("%d", &numLivro);
                    limparBufferEntrada();

                    int indice = numLivro -1;

                    if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                        printf("Digite o nome do usuario que esta realizando o emprestimo: ");
                        fgets(emprestimos[totalEmprestimo].nomeUsuario, TAM_STRING, stdin);
                        emprestimos[totalEmprestimo].nomeUsuario[strcspn(emprestimos[totalEmprestimo].nomeUsuario, "\n")] = '\0';

                        emprestimos[totalEmprestimo].indiceLivro = indice;

                        biblioteca[indice].disponivel = 0;

                        totalEmprestimo++;
                        printf("Emprestimo realizado com sucesso!\n");
                    } else {
                        printf("Numero do livro invalido ou livro indisponivel.\n");
                    }
                }
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        case 4: 
            printf("--- Lista de Emprestimos ---\n\n");
            if (totalEmprestimo == 0) {
                printf("Nenhum emprestimo realizado.\n");
            } else {
                for(int i = 0; i < totalEmprestimo; i++) {
                    int indiceLivro = emprestimos[i].indiceLivro;
                    printf("-------------------------------------\n");
                    printf("EMPRESTIMO %d\n", i + 1);
                    printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                    printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                }
                printf("-------------------------------------\n");
            }
            printf("\nPressione Enter para continuar...");
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

    free(biblioteca);
    free(emprestimos);
    printf("Memoria liberada com sucesso!");

    return 0;
    
}
