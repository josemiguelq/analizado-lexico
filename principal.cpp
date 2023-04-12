#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<conio.h>

#include"var_tokens.h"

/*-----------------------------------------------------------------------
Autor: José Miguel		|  RA:6059010150

-----------------------------------------------------------------------
Documentação
Configurações para o compilador: TDM-GCC 4.9.2 64-bit Release
-----------------------------------------------------------------------
				Arquivos Necessarios:
-----------------------------------------------------------------------
- tabela.txt
- codigo.txt
-----------------------------------------------------------------------
				Bibliotecas Necessárias:
-----------------------------------------------------------------------
- load_lines.h
- load_table.h
- var_tokens.h

-----------------------------------------------------------------------
load_lines: Funcoes que carrega o arquivo texto contendo o codigo para ser compilado na memoria
-----------------------------------------------------------------------
load_table: Carrega a tabela lexica inicial na memoria
-----------------------------------------------------------------------
var_tokens: Faz leitura das linhas de codigo carregadas pela load_lines e cria strutura de nós para cada token
-----------------------------------------------------------------------*/


void menu() {
    int option = NULL;

    do {    	
        printf("\nMENU =====================\n\n");
        printf("1.\t Ler arquivo \n");
        printf("2.\t Ver tabela lexica \n");
        printf("3.\t Lexico \n");
        printf("4.\t Tabela de Tokens \n\n");
        printf("5.\t Sair \n\n");
        fflush(stdout);
        scanf("%d", &option);

        switch (option) {
            case 1:
            	clear_tokens_table();
                show_algorithm();
                break;
            case 2:
                  show_table();
                break;
        	case 3:
              lexico();
                break;    
            case 4:
              show_tokens_table();
                break;    
            default:
                printf("\n\nOpcao Invalida \n\n");
                break;
        }
    } while(option != 5);
}

main() {
    load_table();
    menu();

    getchar();
}
