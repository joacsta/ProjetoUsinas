#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include "usinasbib.h"

/*
Este código é um programa principal que implementa um menu para
interagir com funções relacionadas a um sistema de consulta e
gerenciamento de informações sobre usinas elétricas fantasiosas do DF.

Em resumo, este programa é um menu interativo que permite ao usuário
selecionar várias operações relacionadas a um sistema de consulta e
gerenciamento de informações, como consulta de consumidores,
listagem de usinas, ordenaçao de energia, entre outros.
*/

int main()
{
    setlocale(LC_CTYPE, "Portuguese"); // Mudança de idioma
    char CCC[10];
    int subrespt, respt;

    do
    {
        menu_principal(); // void
        printf("\nPor favor, selecione uma das opçoes: ");
        fflush(stdin);
        scanf("%d", &respt);

        switch (respt)
        {
        case 0:
            limpartela();
            break;

        case 1:
            consulta_e_validacao(CCC);
            break;

        case 2:
            printf("\nOPÇAO 2, 'Consultar consumidor cadastrado' selecionada.\nAntes de realizar a operaçao, informe qual o tipo de cadastro sera digitado.\nSelecione '1', para a OPERAÇAO COM CNPJ.\nOu selecione '2', para a OPERAÇAO COM CPF.\nCNPJ |1| ou CPF |2|: ");
            scanf("%d", &subrespt);

            if (subrespt == 1)
            {
                fgets(CCC, sizeof(CCC), stdin);
                consumidor_cnpj(CCC);
            }
            else if (subrespt == 2)
            {
                fgets(CCC, sizeof(CCC), stdin);
                consumidor_cpf(CCC);
            }
            else
            {
                printf("\nOPÇAO INVALIDA.\n");
            }
            break;

        case 3:
            listagem_usina();
            break;

        case 4:
            ordenacao_energia();
            break;

        case 5:
            lista_qtdMiniusinas();
            break;

        case 6:
            lista_ra_ContratosCrescente();
            break;

        case 7:
            lista_ra_CapEnergia();
            break;

        case 8:
            porcentagem();
            break;

        case 9:
            printf("\nO sistema foi encerrado.\n");
            break;

        default:
            printf("\nOpçao invalida. Tente novamente.\n"); // caso o usuario digite um numero maior que 9 ou outro caractere
            getchar();
        }
    } while (respt != 9);

    return 0;
}
