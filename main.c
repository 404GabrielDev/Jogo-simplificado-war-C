#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

typedef struct
{
    char cor[10];
    // char *missao; resultados instáveis
} Jogador;

// Cadastro de territorios
Territorio *cadastrarTerritorios(int n)
{
    Territorio *mapa = (Territorio *)malloc(n * sizeof(Territorio));

    if (!mapa)
    {
        printf("Erro ao alocar o espaço em memoria\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("Territorio %d nome: ", i + 1);
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do jogador: ");
        scanf(" %9s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

//-----exibir territorios--------//

void exibirTerritorios(Territorio *mapa, int n)
{

    printf("\n <<< Territorios >>> \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// --- função de ataque --- //

void atacar(Territorio *atacante, Territorio *defensor)
{
    int dados_atacante = rand() % 6 + 1;
    int dados_defensor = rand() % 6 + 1;

    printf("\n Ataque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dados_atacante, dados_defensor);

    if (dados_atacante > dados_defensor)
    {
        printf("Atacante venceu!\n");
        defensor->tropas = atacante->tropas / 2;
        strcpy(defensor->cor, atacante->cor);
    }
    else
    {
        printf("Defensor resistiu!\n");
        atacante->tropas /= 2;
    }
}

Jogador criarJogador(char *cor)
{
    Jogador j;
    strcpy(j.cor, cor);
    return j;
}

int main()
{
    srand(time(NULL));

    int n;
    printf("Quantos territorios deseja cadastrar?");
    scanf("%d", &n);

    Territorio *mapa = cadastrarTerritorios(n);
    exibirTerritorios(mapa, n);

    Jogador jogador1 = criarJogador("Vermelho");
    Jogador jogador2 = criarJogador("azul");

    int atk, def;
    printf("\nEscolha o terrtorio atacante (numero): ");
    scanf("%d", &atk);
    printf("Escolha o territorio defensor (numero): ");
    scanf("%d", &def);

    atacar(&mapa[atk - 1], &mapa[def - 1]);
    exibirTerritorios(mapa, n);

    // limpa memoria
    free(mapa);
}
