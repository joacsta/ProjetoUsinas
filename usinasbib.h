/*Criacao de uma biblioteca que compoe o codigo principal*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //inclusao de bibliotecas
#include <locale.h>
#include <ctype.h>

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H // Definicoes de biblioteca

#define OPCAO1_CONSULTAR_MINIUSINA 1
#define OPCAO2_CONSULTAR_CONSUMIDOR 2
#define OPCAO3_LISTAGEM_MINIUSINAS 3
#define OPCAO4_LISTAGEM_MINIUSINAS_OPERACAO_DECRESCENTE 4
#define OPCAO5_LISTAGEM_RAS_ORDEM_DESCRESCENTE_QUANTIDADE_MINIUSINAS 5
#define OPCAO6_LISTAGEM_RAS_ORDEM_CRESCENTE_CONTRATOS 6 // opcoes do menu
#define OPCAO7_LISTAGEM_RAS_ORDEM_DESCRESCENTE_CAPACIDADE_GERACAO 7
#define OPCAO8_LISTAGEM_RAS_ORDEM_DESCRESCENTE_PERCENTUAL_ENERGIA_DISPONIVEL 8
#define OPCAO9_SAIR 9

#define TAM_CNPJ 20
#define TAM_CPF 15
#define TAM_NOME_MINIUSINA 100   // tamanho permitido de caracteres
#define TAM_ENERGIA_MINIUSINA 20 // OPCAO1_CONSULTAR_MINIUSINA
#define TAM_RA_MINIUSINA 10
#define TAM_STATUS_MINIUSINA 30

#define TAM_ID_CONTRATO 20    // tamanho permitido de caracteres
#define TAM_ID_CONSUMIDOR 20 // OPCAO1_CONSULTAR_MINIUSINA e OPCAO2_CONSULTAR_CONSUMIDOR
#define TAM_DATA_CONTRATO 20

#define TAM_NOME_CONSUMIDOR 100 // OPCAO2_CONSULTAR_CONSUMIDOR

struct raopcao7
{
    int id_ra;
    char nome_ra[100];
    float capacidade_geracao_energia;
    float capacidade_total;
};
struct contrato_float
{
    char idcontrato[TAM_ID_CONTRATO];
    char idconsumidor[TAM_ID_CONSUMIDOR];
    char energia[TAM_ENERGIA_MINIUSINA];
    char cnpj[TAM_CNPJ];
    char datacontrato[TAM_DATA_CONTRATO];
    float energia_contratada;
};
struct ra_com_int
{
    char idra[TAM_RA_MINIUSINA];
    char nome_ra[TAM_NOME_CONSUMIDOR];
    int quantidade;
    int id_ra;
    int quantidade_contratos;
    float capacidade_total;
    float percentual_energia_disponivel;
};
struct consumidor_int
{
    char id_consumidor[TAM_ID_CONSUMIDOR];
    char nome[100];
    int id_ra;
};
struct usina // struct destinado a primeira opcao;
{
    char cnpj[TAM_CNPJ];
    char nome[TAM_NOME_MINIUSINA];
    char energia[TAM_ENERGIA_MINIUSINA];
    char idra[TAM_RA_MINIUSINA];
    char status[TAM_STATUS_MINIUSINA];
};
struct contrato // struct destinada para a primeira opcao, se estiver disponivel nos arquivos;
{
    char idcontrato[TAM_ID_CONTRATO];
    char idconsumidor[TAM_ID_CONSUMIDOR];
    char cnpj[TAM_CNPJ];
    char inicio_data[TAM_DATA_CONTRATO];
    char energiacontratada[TAM_ENERGIA_MINIUSINA];
};
struct consumidor1 // struct destinado para opcao 2 caso o usuario selecione a opcao CNPJ;
{
    char cnpj[TAM_CNPJ];
    char nome[TAM_NOME_CONSUMIDOR];
    char idra[TAM_RA_MINIUSINA];
};
struct consumidor2 // struct destinado para opcao 2 caso o usuario selecione a opcao CPF;
{
    char cpf[TAM_CPF];
    char nome[TAM_NOME_CONSUMIDOR];
    char idra[TAM_RA_MINIUSINA];
};
struct lista_usina
{
    char cap_energia[TAM_ENERGIA_MINIUSINA];
    char nome[TAM_NOME_MINIUSINA];
    char cnpj[TAM_CNPJ];
    char idra[TAM_RA_MINIUSINA];
    char status[TAM_STATUS_MINIUSINA];
    float capacidade_total;
    float percentual;
};
struct num_RA
{
    char idra[99];
    char cidade[30];
};
struct RA_Quantidade
{
    int id;
    int quantidade;
};
struct Regioes_Adm
{
    int id;
    char nomeRA[100];
    int quantidadeContratos;
};

/// VOIDS "AUXILIARES" (COMPOEM OS PRINCIPAIS)

void limpartela()
{
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void RA(const char *entrada_id)
{
    FILE *arquivo_RA;
    struct num_RA RA_cad;

    arquivo_RA = fopen("ra.csv", "r");

    if (arquivo_RA != NULL)
    {
        int encontrou = 0;

        while (fscanf(arquivo_RA, " %[^,],%[^\n]\n", RA_cad.idra, RA_cad.cidade) == 2)
        {
            if (strcmp(RA_cad.idra, entrada_id) == 0)
            {
                printf("N° Regiao Administrativa: %s\n", RA_cad.idra);
                printf("Cidade: %s\n", RA_cad.cidade);
                encontrou = 1;
            }
        }

        if (!encontrou)
        {
            printf("Nenhuma correspondencia encontrada para a ID: %s\n", entrada_id);
        }

        fclose(arquivo_RA);
    }
    else
    {
        printf("Erro ao abrir o arquivo.\n");
    }
}
void validacao_cnpj(const char *str)
{
    char cnpj[TAM_CNPJ];
    int tamanho = strlen(str);
    int j = 0; // DECLARACAO DE VARIAVEIS PARA A VALIDACAO DE CNPJ
    int icnpj[TAM_CNPJ];
    int i, digito1, digito2, result1, result2, valor, somador = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (isdigit(str[i])) // extracao de numeros do CNPJ removendo pontos, barras e traços
        {
            cnpj[j] = str[i];
            j++;
        }
    }
    cnpj[j] = '\0';

    for (i = 0; i < 14; i++)
    {
        icnpj[i] = cnpj[i] - '0'; //"conversao" de string para inteiro.
    }

    // Calculo do primeiro digito
    somador = icnpj[0] * 5 + icnpj[1] * 4 + icnpj[2] * 3 + icnpj[3] * 2 +
              icnpj[4] * 9 + icnpj[5] * 8 + icnpj[6] * 7 + icnpj[7] * 6 +
              icnpj[8] * 5 + icnpj[9] * 4 + icnpj[10] * 3 + icnpj[11] * 2;

    result1 = somador % 11;
    digito1 = (result1 < 2) ? 0 : 11 - result1;

    // Calculo do segundo digito
    somador = icnpj[0] * 6 + icnpj[1] * 5 + icnpj[2] * 4 + icnpj[3] * 3 +
              icnpj[4] * 2 + icnpj[5] * 9 + icnpj[6] * 8 + icnpj[7] * 7 +
              icnpj[8] * 6 + icnpj[9] * 5 + icnpj[10] * 4 + icnpj[11] * 3 + icnpj[12] * 2;
    valor = (somador / 11) * 11;
    result2 = somador - valor;
    digito2 = (result2 < 2) ? 0 : 11 - result2;

    if (digito1 == icnpj[13] && digito2 == icnpj[14])
    {
        printf("\nCNPJ VALIDO");
    }
    else
    {
        printf("\nCNPJ INVALIDO");
    }
}

void validacao_cpf(const char *str)
{
    char cpf[TAM_CPF];
    int tamanho = strlen(str);
    int j = 0;
    int icpf[TAM_CPF];
    int i, digito1, digito2, somador = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (isdigit(str[i]))
        {
            cpf[j] = str[i]; /// EXTRACCAO DE NUMEROS DA STRING
            j++;
        }
    }
    cpf[j] = '\0';

    for (i = 0; i < TAM_CPF; i++) //"conversao" para inteiros
    {
        icpf[i] = cpf[i] - '0';
    }

    // Calculo do primeiro digito
    somador = icpf[0] * 10 + icpf[1] * 9 + icpf[2] * 8 + icpf[3] * 7 +
              icpf[4] * 6 + icpf[5] * 5 + icpf[6] * 4 + icpf[7] * 3 + // algoritmo de validacao
              icpf[8] * 2;

    digito1 = (somador % 11) < 2 ? 0 : 11 - (somador % 11); // '?' e uma condicao de verdadeiro e falso com duas alternativas
    //'0' e a priemira alternativa
    //'11-(somador %11)' e a segunda

    // Calculo do segundo digito
    somador = icpf[0] * 11 + icpf[1] * 10 + icpf[2] * 9 + icpf[3] * 8 +
              icpf[4] * 7 + icpf[5] * 6 + icpf[6] * 5 + icpf[7] * 4 +
              icpf[8] * 3 + digito1 * 2;

    digito2 = (somador % 11) < 2 ? 0 : 11 - (somador % 11);

    if (digito1 == icpf[9] && digito2 == icpf[10]) // verificador de digitacao com os dois ultimos digitos
    {
        printf("\nCPF VALIDO");
    }
    else
    {
        printf("\nCPF INVALIDO");
    }
}
void selectionSort_contratos(struct ra_com_int *ras, int quantidade_ras)
{
    int i, j, minIndex;
    struct ra_com_int temp;

    for (i = 0; i < quantidade_ras - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < quantidade_ras; j++)
        {
            if (ras[j].quantidade_contratos < ras[minIndex].quantidade_contratos)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            temp = ras[i];
            ras[i] = ras[minIndex];
            ras[minIndex] = temp;
        }
    }
}
void selectionSort_capacidade(struct raopcao7 *ras, int quantidade_ras)
{
    // Adicionar a capacidade de energia das miniusinas pertencentes e mesma RA
    for (int i = 0; i < quantidade_ras; i++)
    {
        for (int j = i + 1; j < quantidade_ras; j++)
        {
            if (ras[i].id_ra == ras[j].id_ra)
            {
                ras[i].capacidade_geracao_energia += ras[j].capacidade_geracao_energia;
                // Zerar a capacidade de energia da miniusina adicionada
                ras[j].capacidade_geracao_energia = 0;
            }
        }
    }

    // Ordenar as RAs por capacidade de geracao de energia em ordem decrescente
    for (int i = 0; i < quantidade_ras - 1; i++)
    {
        for (int j = i + 1; j < quantidade_ras; j++)
        {
            if (ras[i].capacidade_geracao_energia < ras[j].capacidade_geracao_energia)
            {
                // Trocar as posicoes das RAs
                struct raopcao7 temp = ras[i];
                ras[i] = ras[j];
                ras[j] = temp;
            }
        }
    }

    // Exibir as RAs em ordem decrescente de capacidade de geracao de energia
    for (int i = 0; i < quantidade_ras; i++)
    {
        if (ras[i].capacidade_geracao_energia > 0)
        {
            char str1[99];
            sprintf(str1, "%d", ras[i].id_ra);
            RA(str1);
            printf("Capacidade de Geracao de Energia: %.2f\n\n", ras[i].capacidade_geracao_energia);
        }
    }
}
void selectionSort_energia(struct lista_usina usinas[], int n)
{
    int i, j, max_idx;
    struct lista_usina temp;

    for (i = 0; i < n - 1; i++)
    {
        max_idx = i;
        for (j = i + 1; j < n; j++)
        {
            int cap1 = atoi(usinas[j].cap_energia);
            int cap2 = atoi(usinas[max_idx].cap_energia);
            if (cap1 < cap2)
            {
                max_idx = j;
            }
        }
        if (max_idx != i)
        {
            temp = usinas[i];
            usinas[i] = usinas[max_idx];
            usinas[max_idx] = temp;
        }
    }
}
void selectionSort_energia_total(struct lista_usina usinas[], int n)
{
    // Calcula a capacidade de energia total para cada RA
    for (int i = 0; i < n; i++)
    {
        float capacidade_total = 0.0;

        // Procura apenas as usinas com o mesmo ID da RA atual
        for (int j = 0; j < n; j++)
        {
            if (strcmp(usinas[i].idra, usinas[j].idra) == 0)
            {
                capacidade_total += atof(usinas[j].cap_energia);
            }
        }

        // Armazena a capacidade de energia total na estrutura usina
        usinas[i].capacidade_total = capacidade_total;
    }

    // Ordena as usinas pela capacidade de energia total em ordem decrescente usando o algoritmo de bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (usinas[j].capacidade_total < usinas[j + 1].capacidade_total)
            {
                // Troca as posicoes das usinas
                struct lista_usina temp = usinas[j];
                usinas[j] = usinas[j + 1];
                usinas[j + 1] = temp;
            }
        }
    }

    // Imprime a capacidade de energia total em ordem decrescente
    printf("\nOPCAO 7, Capacidade de energia total em ordem decrescente:\n\n");
    char ra_anterior[10] = "";
    for (int i = 0; i < n; i++)
    {
        if (strcmp(usinas[i].idra, ra_anterior) != 0)
        {
            RA(usinas[i].idra);
            printf("Capacidade de Energia Total: %.1fkW\n\n", usinas[i].capacidade_total);
        }
    }
}
void selectionSort_percentual(struct lista_usina usinas[], int n)
{
    // Calcula a capacidade de energia total para cada RA
    for (int i = 0; i < n; i++)
    {
        float capacidade_total = 0.0;

        // Procura apenas as usinas com o mesmo ID da RA atual
        for (int j = 0; j < n; j++)
        {
            if (strcmp(usinas[i].idra, usinas[j].idra) == 0)
            {
                capacidade_total += atof(usinas[j].cap_energia);
            }
        }

        // Armazena a capacidade de energia total na estrutura usina
        usinas[i].capacidade_total = capacidade_total;
    }

    // Calcula a capacidade total de energia de todas as usinas
    float capacidade_total_usinas = 0.0;
    for (int i = 0; i < n; i++)
    {
        capacidade_total_usinas += atof(usinas[i].cap_energia);
    }

    // Calcula o percentual de energia para cada RA
    for (int i = 0; i < n; i++)
    {
        float percentual = (usinas[i].capacidade_total / capacidade_total_usinas) * 100;
        usinas[i].percentual = percentual;
    }

    // Ordena as RAs pelo percentual de energia em ordem decrescente usando o algoritmo de ordenacao bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (usinas[j].percentual < usinas[j + 1].percentual)
            {
                // Troca as posicoes das RAs
                struct lista_usina temp = usinas[j];
                usinas[j] = usinas[j + 1];
                usinas[j + 1] = temp;
            }
        }
    }

    // Imprime o percentual de energia total em ordem decrescente
    printf("\nOPCAO 8, Percentual de energia disponivel em ordem decrescente:\n\n");
    printf("Calculo do percentual de energia disponivel para cada Regiao Administrativa em relacao a capacidade total de energia de todas as usinas.\n\n");
    char ra_anterior[10] = "";
    for (int i = 0; i < n; i++)
    {
        if (strcmp(usinas[i].idra, ra_anterior) != 0)
        {
            RA(usinas[i].idra);
            printf("Percentual de Energia Disponivel: %.2f%%\n\n", usinas[i].percentual);
        }
    }
}

/// VOIDS "PRINCIPAIS"

void consulta_e_validacao(const char *str) {
    setlocale(LC_CTYPE, "Portuguese"); // Definir localidade
    struct usina usina_cadastrada;     // Declaração da struct usina
    struct contrato contrato_cadastrado; // Declaração da struct contrato
    char cnpj_consulta[TAM_CNPJ];      // Variável para armazenar o CNPJ de consulta
    int encontrei_usina = 0;           // Variável para indicar se a usina foi encontrada
    int encontrei_contrato = 0;        // Variável para indicar se o contrato foi encontrado
    FILE *arquivo_usina;               // Ponteiro para o arquivo de usinas
    FILE *arquivo_contrato;            // Ponteiro para o arquivo de contratos

    arquivo_usina = fopen("miniusinas.csv", "r");
    arquivo_contrato = fopen("contratos.csv", "r");

    printf("\nOPCAO 1, 'Consultar miniusina cadastrada' selecionada.\n");
    printf("Por favor, digite um CNPJ para realizar a operação.\nCNPJ: ");
    scanf(" %[^\n]", cnpj_consulta); // Leitura do CNPJ
    getchar(); // Limpeza do buffer do teclado

    if (arquivo_usina != NULL) {
        while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", 
                      usina_cadastrada.cnpj, usina_cadastrada.nome, usina_cadastrada.energia, 
                      usina_cadastrada.idra, usina_cadastrada.status) != EOF) 
        {
            if (strcmp(cnpj_consulta, usina_cadastrada.cnpj) == 0) {
                printf("\nINFORMACOES DA USINA:\n");
                validacao_cnpj(cnpj_consulta);
                printf(" | %s\n", usina_cadastrada.cnpj);
                printf("Nome da Usina: %s\n", usina_cadastrada.nome);
                printf("Capacidade de energia: %s\n", usina_cadastrada.energia);
                RA(usina_cadastrada.idra);
                printf("Status: %s\n", usina_cadastrada.status);
                encontrei_usina = 1;
            }
        }
        if (encontrei_usina == 0) {
            printf("\nAVISO!");
            validacao_cnpj(cnpj_consulta);
            printf("\nNao foi encontrada nenhuma usina com o CNPJ: %s.", cnpj_consulta);
        }
        fclose(arquivo_usina);
    } else {
        printf("ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO.\n");
    }

    if (arquivo_contrato != NULL) {
        while (fscanf(arquivo_contrato, "%19[^,],%19[^,],%19[^,],%19[^,],%19[^\n]\n", 
                      contrato_cadastrado.idcontrato, contrato_cadastrado.idconsumidor, 
                      contrato_cadastrado.cnpj, contrato_cadastrado.inicio_data, 
                      contrato_cadastrado.energiacontratada) != EOF) 
        {
            if (strcmp(cnpj_consulta, contrato_cadastrado.cnpj) == 0) {
                printf("\nID |Contrato: %s\n", contrato_cadastrado.idcontrato);
                printf("ID|Consumidor: %s\n", contrato_cadastrado.idconsumidor);
                printf("Data: %s\n\n", contrato_cadastrado.inicio_data);
                encontrei_contrato = 1;
            }
        }
        if (encontrei_contrato == 0) {
            printf("\nNenhum contrato identificado com o CNPJ: %s.\n", cnpj_consulta);
        }
        fclose(arquivo_contrato);
    } else {
        printf("\nERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO.\n");
    }
}
void consumidor_cpf(const char *str) // opcao 2 destinada a operacao com CPF
{
    /// Declaracao de variaveis
    setlocale(LC_CTYPE, "Portuguese");
    struct consumidor2 consumidor_cad2; // Declaracao da struct para armazenar os dados
    char cpf_consulta[TAM_CPF];         // variavel para armazenar a entrada
    int encontrei_consumidor = 0;
    FILE *arquivo_consumidor; // Ponteiro para o arquivo de consumidores

    printf("\nConsultar consumidor cadastrado com CPF, selecionado.\n");
    printf("Por favor, digite um CPF para realizar a operacao.\nCPF: ");
    scanf(" %[^\n]", cpf_consulta); // Leitura do CPF digitado pelo usuario
    getchar();                      // Pausa o programa para aguardar uma acao do usuario

    arquivo_consumidor = fopen("consumidores.csv", "r"); // Abertura do arquivo de consumidores no modo leitura
    if (arquivo_consumidor != NULL)                      // Verifica se o arquivo de consumidores foi aberto corretamente
    {
        while (!feof(arquivo_consumidor)) // Loop para percorrer o arquivo de consumidores
        {
            fscanf(arquivo_consumidor, "%[^,],%[^,],%[^\n]\n", consumidor_cad2.cpf, // Escaneamento dos dados separados por ponto e virgula
                   consumidor_cad2.nome,
                   consumidor_cad2.idra);
            if (strcmp(cpf_consulta, consumidor_cad2.cpf) == 0) // Verifica se o CPF digitado coincide com o CPF do consumidor atual
            {
                printf("\nINFORMACOES DO(A) CONSUMIDOR(A)");
                validacao_cpf(cpf_consulta);                // funcao para validar e formatar a exibicao do CPF
                printf(": %s\n", consumidor_cad2.cpf);      // Imprime o CPF do consumidor
                printf("Nome: %s\n", consumidor_cad2.nome); // Imprime o nome do consumidor
                RA(consumidor_cad2.idra);                   // Imprime o ID da regiao administrativa do consumidor
                encontrei_consumidor = 1;                   // Marca que o consumidor foi encontrado
            }
        }
        if (encontrei_consumidor == 0) // Verifica se o consumidor nao foi encontrado
        {
            printf("\nAVISO!\nNao foi encontrado(a) nenhum(a) consumidor(a) com o CPF: %s.\n", cpf_consulta);
        }
    }
    else
    {
        printf("ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO.\n"); // Imprime uma mensagem de erro caso o arquivo de consumidores nao possa ser aberto
    }
}

void consumidor_cnpj(const char *str) // opcao 2 destinada a operacao com CNPJ
{
    setlocale(LC_CTYPE, "Portuguese");
    struct consumidor1 consumidor_cad; // Declaracao da struct para armazenar os dados do consumidor
    char cnpj_consulta[TAM_CNPJ];      // variavel para armazenar o CNPJ digitado pelo usuario
    int encontrei_consumidor = 0;
    FILE *arquivo_consumidor; // Ponteiro para o arquivo de consumidores

    printf("\nConsultar consumidor cadastrado com CNPJ, selecionado.\n");
    printf("Por favor, digite um CNPJ para realizar a operacao.\nCNPJ: ");
    scanf(" %[^\n]", cnpj_consulta); // Leitura do CNPJ digitado pelo usuario
    getchar();                       // Pausa o programa para aguardar uma acao do usuario

    arquivo_consumidor = fopen("consumidores.csv", "r"); // Abertura do arquivo de consumidores no modo leitura
    if (arquivo_consumidor != NULL)                      // Verifica se o arquivo de consumidores foi aberto corretamente
    {
        while (!feof(arquivo_consumidor)) // Loop para percorrer o arquivo de consumidores
        {
            fscanf(arquivo_consumidor, "%[^,],%[^,],%[^\n]\n", consumidor_cad.cnpj, // Escaneamento dos dados separados por ponto e virgula
                   consumidor_cad.nome,
                   consumidor_cad.idra);
            if (strcmp(cnpj_consulta, consumidor_cad.cnpj) == 0) // Verifica se o CNPJ digitado coincide com o CNPJ do consumidor atual
            {
                printf("\nINFORMACOES DO(A) CONSUMIDOR(A)");
                validacao_cnpj(cnpj_consulta);             // funcao para validar e formatar a exibicao do CNPJ
                printf(": %s\n", consumidor_cad.cnpj);     // Imprime o CNPJ do consumidor
                printf("Nome: %s\n", consumidor_cad.nome); // Imprime o nome do consumidor
                RA(consumidor_cad.idra);                   // Imprime o ID da regiao administrativa do consumidor
                encontrei_consumidor = 1;                  // Marca que o consumidor foi encontrado
            }
        }
        if (encontrei_consumidor == 0) // Verifica se o consumidor nao foi encontrado
        {
            printf("\nAVISO!\nNao foi encontrado(a) nenhum(a) consumidor(a) com o CNPJ: %s.\n", cnpj_consulta);
        }

        fclose(arquivo_consumidor); // Fecha o arquivo de consumidores
    }
    else
    {
        printf("ERRO, NAO FOI POSSIVEL ABRIR O ARQUIVO.\n"); // Imprime uma mensagem de erro caso o arquivo de consumidores nao possa ser aberto
    }
}

void listagem_usina() // opcao 3
{
    struct usina usina_cad; // Declaracao da struct usina para armazenar os dados da usina
    FILE *arquivo_usina;    // Ponteiro para o arquivo de miniusinas

    arquivo_usina = fopen("miniusinas.csv", "r"); // Abertura do arquivo de miniusinas no modo leitura
    if (arquivo_usina == NULL)                    // Verifica se o arquivo de miniusinas foi aberto corretamente
    {
        printf("Nao foi possivel abrir o arquivo.\n"); // Imprime uma mensagem de erro caso o arquivo nao possa ser aberto
        return;                                        // Encerra a funcao
    }

    printf("\nOPCAO 3, 'Listar miniusinas cadastradas', selecionada.\n");
    printf("Por favor, aguarde...\n");
    getchar();
    printf("\n");

    while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usina_cad.cnpj, // Leitura dos dados separados por ponto e virgula
                  usina_cad.nome,
                  usina_cad.energia,
                  usina_cad.idra,
                  usina_cad.status) != EOF) // Loop para percorrer o arquivo de miniusinas ate o final do arquivo (EOF - End Of File)
    {
        printf("CNPJ: %s\n", usina_cad.cnpj);                       // Imprime o CNPJ da usina
        printf("Nome: %s\n", usina_cad.nome);                       // Imprime o nome da usina
        printf("Capacidade de Energia: %skW\n", usina_cad.energia); // Imprime a capacidade de energia da usina// Imprime o ID da regiao administrativa da usina
        RA(usina_cad.idra);
        printf("Status: %s\n", usina_cad.status); // Imprime o status da usina
        printf("\n");
    }

    fclose(arquivo_usina); // Fecha o arquivo de miniusinas

    printf("Deseja continuar? Se sim, por favor, digite outra opcao.\n"); // Pergunta se o usuario deseja continuar
}

void ordenacao_energia() // opcao 4
{
    setlocale(LC_CTYPE, "Portuguese");
    struct lista_usina usinas[100]; // Declaracao de um array de struct lista_usina para armazenar as informacoes das usinas
    FILE *arquivo_usina;            // Ponteiro para o arquivo de miniusinas

    arquivo_usina = fopen("miniusinas.csv", "r"); // Abertura do arquivo de miniusinas no modo leitura
    if (arquivo_usina == NULL)                    // Verifica se o arquivo de miniusinas foi aberto corretamente
    {
        printf("Nao foi possivel abrir o arquivo.\n"); // Imprime uma mensagem de erro caso o arquivo nao possa ser aberto
        return;                                        // Encerra a funcao
    }

    printf("\nOPCAO 4, 'Listar as miniusinas em operacao por ordem decrescente de capacidade de geracao de energia', selecionada.\n");
    printf("Por favor, aguarde...\n");
    getchar();

    int count = 0;
    while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usinas[count].cnpj,
                  usinas[count].nome,
                  usinas[count].cap_energia,
                  usinas[count].idra,
                  usinas[count].status) != EOF) // Loop para ler as informacoes das usinas do arquivo e armazena-las na estrutura usinas
    {
        count++; // Incrementa o contador de usinas
    }

    // Aplica o algoritmo de ordenacao selection sort para ordenar as usinas pela capacidade de geracao de energia
    selectionSort_energia(usinas, count);

    printf("Miniusinas ordenadas por ordem decrescente de capacidade de geracao de energia:\n\n");
    for (int i = count - 1; i >= 0; i--) // Loop para percorrer as usinas do maior para o menor valor de capacidade de geracao de energia
    {
        printf("Capacidade de Energia: %skW\n", usinas[i].cap_energia); // Imprime a capacidade de energia da usina
        printf("Nome: %s\n", usinas[i].nome);                           // Imprime o nome da usina
        printf("CNPJ: %s\n", usinas[i].cnpj);                           // Imprime o CNPJ da usina
        RA(usinas[i].idra);                                             // Imprime o ID da regiao administrativa da usina
        printf("Status: %s\n", usinas[i].status);                       // Imprime o status da usina
        printf("\n");
    }

    fclose(arquivo_usina); // Fecha o arquivo de miniusinas

    printf("Deseja continuar? Se sim, por favor, digite outra opcao.\n"); // Pergunta se o usuario deseja continuar
}

void lista_qtdMiniusinas() // opcao 5
{
    setlocale(LC_CTYPE, "Portuguese");
    struct lista_usina usinas[100]; // Suponha que haja no maximo 100 usinas
    int qtdUsinasPorID[100] = {0};  // Array para armazenar a quantidade de usinas por ID (considerando ate 100 IDs)
    FILE *arquivo_usina;

    arquivo_usina = fopen("miniusinas.csv", "r");
    if (arquivo_usina == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    printf("\nOpcao 5, 'Listar as RAs por ordem decrescente de quantidade de miniusinas', selecionada.\n");
    getchar();
    printf("\n");

    int count = 0;
    while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usinas[count].cnpj,
                  usinas[count].nome,
                  usinas[count].cap_energia,
                  usinas[count].idra,
                  usinas[count].status) != EOF)
    {
        int id = atoi(usinas[count].idra); // Considerando que o ID e um numero inteiro
        qtdUsinasPorID[id]++;              // Incrementa a quantidade de usinas para o ID correspondente

        count++;
    }

    // Criar um array de RA_Quantidade para armazenar os IDs e quantidades de miniusinas
    struct RA_Quantidade ids_quantidades[20];
    int numIDs = 0;

    // Preencher o array ids_quantidades com os IDs e quantidades de miniusinas
    for (int i = 0; i < 100; i++)
    {
        if (qtdUsinasPorID[i] > 0)
        {
            ids_quantidades[numIDs].id = i;
            ids_quantidades[numIDs].quantidade = qtdUsinasPorID[i];
            numIDs++;
        }
    }

    // Aplicar um algoritmo de ordenacao para ordenar os IDs por quantidade de miniusinas em ordem decrescente
    for (int i = 0; i < numIDs - 1; i++)
    {
        for (int j = i + 1; j < numIDs; j++)
        {
            if (ids_quantidades[j].quantidade > ids_quantidades[i].quantidade)
            {
                // Trocar a posicao dos elementos
                struct RA_Quantidade temp = ids_quantidades[i];
                ids_quantidades[i] = ids_quantidades[j];
                ids_quantidades[j] = temp;
            }
        }
    }

    // Imprimir os IDs das RAs por ordem decrescente de quantidade de miniusinas
    for (int i = 0; i < numIDs; i++)
    {
        char str1[99];
        sprintf(str1, "%d", ids_quantidades[i].id);
        printf("\nQuantidade: %d || ", ids_quantidades[i].quantidade);
        RA(str1);
    }

    // Fechar o arquivo
    fclose(arquivo_usina);

    printf("\nDeseja continuar? Se sim, por favor, digite outra opcaoo.\n");
}

void lista_ra_ContratosCrescente() // opcao 6
{
    setlocale(LC_CTYPE, "Portuguese"); // Define a localizacao para "Portuguese"

    // Declaracao das variaveis e estruturas
    FILE *arquivo_consumidores;              // Ponteiro para o arquivo de consumidores
    FILE *arquivo_contratos;                 // Ponteiro para o arquivo de contratos
    FILE *arquivo_ra;                        // Ponteiro para o arquivo de RAs
    struct consumidor_int consumidores[100]; // Array de consumidores
    struct contrato_float contratos[100];    // Array de contratos
    struct ra_com_int ras[100];              // Array de RAs
    int qtd_consumidor = 0;                  // Contador de consumidores
    int qtd_contrato = 0;                    // Contador de contratos
    int qtd_ra = 0;                          // Contador de RAs

    // Abertura dos arquivos
    arquivo_consumidores = fopen("consumidores.csv", "r"); // Abre o arquivo de consumidores no modo leitura
    arquivo_contratos = fopen("contratos.csv", "r");       // Abre o arquivo de contratos no modo leitura
    arquivo_ra = fopen("ra.csv", "r");                     // Abre o arquivo de RAs no modo leitura

    // Verifica se os arquivos foram abertos corretamente
    if (arquivo_consumidores == NULL || arquivo_contratos == NULL || arquivo_ra == NULL)
    {
        printf("ERRO AO ABRIR OS ARQUIVOS!.\n");
        return; // Sai da função se qualquer arquivo não for aberto
    }

    // Leitura dos consumidores
    char linha_c[1000];
    fscanf(arquivo_consumidores, "%[^\n]\n", linha_c); // Lê a primeira linha e ignora

    // Le os dados dos consumidores do arquivo
    while (fscanf(arquivo_consumidores, "%[^,],%[^,],%d\n",
                  consumidores[qtd_consumidor].id_consumidor,
                  consumidores[qtd_consumidor].nome,
                  &consumidores[qtd_consumidor].id_ra) == 3)
    {
        qtd_consumidor++;
    }

    // Verificação da leitura de consumidores
    printf("Consumidores lidos: %d\n", qtd_consumidor);
    for (int i = 0; i < qtd_consumidor; i++)
    {
        printf("ID: %s, Nome: %s, ID RA: %d\n", consumidores[i].id_consumidor, consumidores[i].nome, consumidores[i].id_ra);
    }

    // Leitura dos contratos
    char linha_cont[1000];
    fscanf(arquivo_contratos, "%[^\n]\n", linha_cont); // Lê a primeira linha e ignora

    // Le os dados dos contratos do arquivo
    while (fscanf(arquivo_contratos, "%[^,],%[^,],%[^,],%[^,],%f\n",
                  contratos[qtd_contrato].idcontrato,
                  contratos[qtd_contrato].idconsumidor,
                  contratos[qtd_contrato].cnpj,
                  contratos[qtd_contrato].datacontrato,
                  &contratos[qtd_contrato].energia_contratada) == 5)
    {
        qtd_contrato++;
    }

    // Verificação da leitura de contratos
    printf("Contratos lidos: %d\n", qtd_contrato);
    for (int j = 0; j < qtd_contrato; j++)
    {
        printf("ID Contrato: %s, ID Consumidor: %s\n", contratos[j].idcontrato, contratos[j].idconsumidor);
    }

    // Leitura das RAs
    char linha_ra[1000];
    fscanf(arquivo_ra, "%[^\n]\n", linha_ra); // Lê a primeira linha e ignora

    // Le os dados das RAs do arquivo
    while (fscanf(arquivo_ra, "%d;%[^\n]\n",
                  &ras[qtd_ra].id_ra,
                  ras[qtd_ra].nome_ra) == 2)
    {
        ras[qtd_ra].quantidade_contratos = 0;
        qtd_ra++;
    }

    // Verificação da leitura de RAs
    printf("RAs lidas: %d\n", qtd_ra);
    for (int k = 0; k < qtd_ra; k++)
    {
        printf("ID RA: %d, Nome RA: %s\n", ras[k].id_ra, ras[k].nome_ra);
    }

    // Verificação dos contratos para cada consumidor
    for (int i = 0; i < qtd_consumidor; i++)
    {
        for (int j = 0; j < qtd_contrato; j++)
        {
            // Verifica se o ID do consumidor coincide com o ID do contrato
            if (strcmp(consumidores[i].id_consumidor, contratos[j].idconsumidor) == 0)
            {
                printf("Consumidor %s corresponde ao contrato %s\n", consumidores[i].id_consumidor, contratos[j].idconsumidor);
                // Procura a RA correspondente ao consumidor e incrementa a quantidade de contratos
                for (int k = 0; k < qtd_ra; k++)
                {
                    if (consumidores[i].id_ra == ras[k].id_ra)
                    {
                        ras[k].quantidade_contratos++;
                        break;
                    }
                }
                break;
            }
        }
    }

    // Ordenacao das RAs por quantidade de contratos
    selectionSort_contratos(ras, qtd_ra); // funcao para ordenar as RAs

    // Exibicao das RAs
    printf("RAs com quantidade de contratos em ordem crescente:\n");
    for (int i = 0; i < qtd_ra; i++)
    {
        char str1[99];
        sprintf(str1, "%d", ras[i].id_ra); // Converte o ID da RA para string
        RA(str1);                          // funcao para exibir a RA
        printf("Quantidade de Contratos: %d\n\n", ras[i].quantidade_contratos);
    }

    // Fechamento dos arquivos
    fclose(arquivo_consumidores);
    fclose(arquivo_contratos);
    fclose(arquivo_ra);
}

void lista_ra_CapEnergia() // opcao 7
{
    struct lista_usina usinas[100]; // Declaracao de um array de struct lista_usina para armazenar as informacoes das usinas
    FILE *arquivo_usina;            // Ponteiro para o arquivo de miniusinas

    arquivo_usina = fopen("miniusinas.csv", "r"); // Abertura do arquivo de miniusinas no modo leitura
    if (arquivo_usina == NULL)                    // Verifica se o arquivo de miniusinas foi aberto corretamente
    {
        printf("nao foi possivel abrir o arquivo.\n");
        return;
    }

    getchar(); // Aguarda a entrada do usuario para prosseguir

    int count = 0; // variavel para contar o numero de usinas lidas
    while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usinas[count].cnpj,
                  usinas[count].nome,
                  usinas[count].cap_energia,
                  usinas[count].idra,
                  usinas[count].status) != EOF) // Loop para ler as informacoes das usinas do arquivo e armazena-las na estrutura usinas
    {
        count++; // Incrementa o contador de usinas
    }

    fclose(arquivo_usina); // Fecha o arquivo de miniusinas

    selectionSort_energia_total(usinas, count); // Chama a funcao para ordenar as usinas por capacidade de energia total em ordem decrescente

    printf("Deseja continuar? Se sim, por favor, digite outra opcaoo.\n"); // Mensagem para solicitar a entrada do usuario
}

void porcentagem() // opcao 8
{
    struct lista_usina usinas[100]; // Declaracao de um array de struct lista_usina para armazenar as informacoes das usinas
    FILE *arquivo_usina;            // Ponteiro para o arquivo de miniusinas

    arquivo_usina = fopen("miniusinas.csv", "r"); // Abertura do arquivo de miniusinas no modo leitura
    if (arquivo_usina == NULL)                    // Verifica se o arquivo de miniusinas foi aberto corretamente
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    getchar(); // Aguarda a entrada do usuario para prosseguir

    int count = 0; // variavel para contar o numero de usinas lidas
    while (fscanf(arquivo_usina, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usinas[count].cnpj,
                  usinas[count].nome,
                  usinas[count].cap_energia,
                  usinas[count].idra,
                  usinas[count].status) != EOF) // Loop para ler as informacoes das usinas do arquivo e armazena-las na estrutura usinas
    {
        count++; // Incrementa o contador de usinas
    }

    fclose(arquivo_usina); // Fecha o arquivo de miniusinas

    selectionSort_percentual(usinas, count); // Chama a funcao para ordenar as RAs por percentual de energia disponivel em ordem decrescente

    printf("Deseja continuar? Se sim, por favor, digite outra funcao.");
}

void menu_principal()
{
    printf("\n|ESCOLHA UMA DAS OPCOES A SEGUIR|\n| PARA LIMPAR A TELA, DIGITE '0'|\n\n");
    printf("1] Consultar miniusina cadastrada\n");
    printf("2] Consultar consumidor cadastrado\n");
    printf("3] Listar miniusinas cadastradas\n");
    printf("4] Listar as miniusinas em operacao por ordem descrescente de capacidade de geracao de energia\n");
    printf("5] Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
    printf("6] Listar as RAs por ordem crescente de numeros de contratos\n");
    printf("7] Listar as RAs por ordem decrescente de capacidade de geracao\n");
    printf("8] Listar as RAs por ordem decrescente de percentual de energia disponivel\n");
    printf("9] Sair do programa\n");
}

#endif // 231012254_H
