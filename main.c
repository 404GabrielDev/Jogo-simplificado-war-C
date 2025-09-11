#include <stdio.h>

struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

int main()
{
    struct Territorio territorio[5];

    printf("----Bem vindo ao war----\n para comecar, crie 5 territorios! \n");

    for (int i = 0; i <= 5; i++)
    {
        printf("\n\nInsira o nome do territorio: ");
        scanf("%29s", territorio[i].nome);

        printf("Insira a cor: ");
        scanf("%9s", territorio[i].cor);

        printf("Insira a quantidade de tropas: ");
        scanf("%d", &territorio[i].tropas);

        printf("\n -----------Territorio Criado---------- \nNome: %s | Cor: %s | Tropas: %d\n", territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }

    printf("\n=== Informacões dos Territorios ===\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Nome: %s | Cor: %s | Tropas: %d\n",
               territorio[i].nome, territorio[i].cor, territorio[i].tropas);
    }

    return 0;
}
