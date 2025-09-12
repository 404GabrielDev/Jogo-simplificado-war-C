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
    char *missao;
} Jogador;

// ---------------- Cadastro de Territórios ----------------
Territorio *cadastrarTerritorios(int n)
{
    Territorio *mapa = (Territorio *)malloc(n * sizeof(Territorio));
    if (!mapa)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("Território %d nome: ", i + 1);
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do jogador: ");
        scanf(" %9s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// ---------------- Exibição de Territórios ----------------
void exibirTerritorios(Territorio *mapa, int n)
{
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ---------------- Função de Ataque ----------------
void atacar(Territorio *atacante, Territorio *defensor)
{
    int dados_atacante = rand() % 6 + 1;
    int dados_defensor = rand() % 6 + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dados_atacante, dados_defensor);

    if (dados_atacante > dados_defensor)
    {
        printf("Atacante venceu!\n");
        defensor->tropas = atacante->tropas / 2; // exemplo simples
        strcpy(defensor->cor, atacante->cor);
    }
    else
    {
        printf("Defensor resistiu!\n");
        atacante->tropas /= 2;
    }
}

// ---------------- Missões ----------------
void atribuirMissao(char *destino, char *missoes[], int totalMissoes)
{
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

Jogador criarJogador(char *cor)
{
    Jogador j;
    strcpy(j.cor, cor);
    j.missao = (char *)malloc(100 * sizeof(char));
    if (!j.missao)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    return j;
}

int verificarMissao(char *missao, Territorio *mapa, int n)
{
    // Exemplo simples: missão de "10 tropas"
    if (strstr(missao, "10 tropas") != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            if (mapa[i].tropas >= 10)
                return 1;
        }
        return 0;
    }
    // Missão de "territórios vermelhos"
    if (strstr(missao, "vermelhas") != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0)
                return 0; // ainda existe território vermelho, não cumpriu
        }
        return 1; // missão cumprida
    }
    return 0; // default
}

// ---------------- Main ----------------
int main()
{
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio *mapa = cadastrarTerritorios(n);
    exibirTerritorios(mapa, n);

    // Missões pré-definidas
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Ter pelo menos 20 tropas em um territorio",
        "Controlar todos os territorios de cor azul",
        "Ter um territorio com mais de 10 tropas"};
    int totalMissoes = 5;

    // Jogadores
    Jogador jogador1 = criarJogador("vermelho");
    Jogador jogador2 = criarJogador("azul");

    // Atribuindo missões
    atribuirMissao(jogador1.missao, missoes, totalMissoes);
    atribuirMissao(jogador2.missao, missoes, totalMissoes);

    printf("\nMissao do Jogador 1: %s\n", jogador1.missao);
    printf("Missao do Jogador 2: %s\n", jogador2.missao);

    // Exemplo de ataque
    int atk, def;
    printf("\nEscolha o território atacante (número): ");
    scanf("%d", &atk);
    printf("Escolha o território defensor (número): ");
    scanf("%d", &def);

    atacar(&mapa[atk - 1], &mapa[def - 1]);
    exibirTerritorios(mapa, n);

    // Verificação de missão
    if (verificarMissao(jogador1.missao, mapa, n))
        printf("Jogador 1 cumpriu a missao!\n");
    if (verificarMissao(jogador2.missao, mapa, n))
        printf("Jogador 2 cumpriu a missao!\n");

    // Liberar memória
    free(jogador1.missao);
    free(jogador2.missao);
    free(mapa);

    return 0;
}
