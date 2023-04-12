		#include<stdio.h>
		#include<stdlib.h>
		#include<string.h>
		#include<dirent.h>
		#include<conio.h>
		
		#include"load_table.h"
		#include"load_lines.h"
		
		
/*-----------------------------------------------------------------------
Autor: José Miguel		|  RA:6059010150

Esta biblioteca faz leitura das linhas de codigo carregadas pela load_lines e cria strutura de nós para cada token
-----------------------------------------------------------------------
						-> Funcoes
** lexico: Faz todas as funcoes abaixo
* append_token: Anexa um token já existente na tabela lexica inicial ou se é um token já anexando aanteriormente na tabela;
* add_token: Adiciona um novo token;
* clear_tokens_table: Limpa toda a tabela de tokens;
* search_tokens: procura na tabela de tokens já adicionados
* search_table: procura na tabela lexica inicial

-----------------------------------------------------------------------	
							->Estrutura
---	|algoritmo		|-|token	|-|tipo		|-|linha	|---|coluna		|-
	|				|			|			|			|				|
	|				|			|			|			|				|
	|				|			|			|			|				|
	
Documentação
Configurações para o compilador: TDM-GCC 4.9.2 64-bit Release
Bibliotecas Necessárias:
load_lines.h
load_table.h
-----------------------------------------------------------------------
load_lines: Funcoes que carrega o arquivo texto contendo o codigo para ser compilado na memoria
-----------------------------------------------------------------------
load_table: Carrega a tabela lexica inicial na memoria
-----------------------------------------------------------------------*/		
		typedef struct token {
			int line, column;
		    char algorithm[45], token[15], tipo[15];
		    struct token *next;
		}Tokens_table;
		
		Tokens_table *p_tokens_p = NULL;
		Tokens_table *p_tokens_f = NULL;
		
		Data *table_head;
		Lines *p_lines = NULL;
		
		int auxint=0;
		char c;
		
		void append_token(char *buffer,char *tok, char *tipo, int line, int column){
			Tokens_table *current = (Tokens_table*)malloc(sizeof(Tokens_table));			
		    strcpy(current->token,tok);
		    strcpy(current->algorithm,buffer);
		    strcpy(current->tipo,tipo);
		    current->line=line;
		    current->column=column;
		    printf("\nAdicionou token %s da tabela %s\n.",current->token, current->algorithm);
		    
		    current -> next = NULL;
		    if(p_tokens_p==NULL){
		   		p_tokens_p= p_tokens_f= current;
			}else{
					p_tokens_f->next=current;
					p_tokens_f=current;
				}
		}
		
		int add_token(char *buffer, int line, int column){
		if((buffer[0]!=32)&&(buffer[0]!=00)){		//NAO ACEITA ESPAÇOS E SIMBOLOS NAO PERTENCENTES A LINGUAGEM
		
		if(((buffer[0]>47)&&(buffer[0]<58))&&(buffer[1]>97))	{
				//printf("Não é permitido comecar uma variavel com um inteiro");
			return 0;
			
		}else{
			Tokens_table *current = (Tokens_table*)malloc(sizeof(Tokens_table));
		char varaux[]="varx";
		varaux[3]=auxint+'0';
		auxint++;
		    strcpy(current->token,varaux);
		    strcpy(current->algorithm ,buffer);
		    current->line=line;
		    current->column=column;
		    printf("\nAdicionou token NOVO: %s\n.", current->algorithm);
		    
		    current -> next = NULL;
		    if(p_tokens_p==NULL){
		   		p_tokens_p= p_tokens_f= current;
			}else{
					p_tokens_f->next=current;
					p_tokens_f=current;
				}
				return 1;
		}
		}else{//DIf de 00 e Espaco
			return 1;
		}
			
		}
		
		void show_tokens_table(){
			Tokens_table *atual = p_tokens_p;
			for (; atual != NULL; atual = atual->next) {	 	
			printf("algo: %s- \t\t| token %s \tlinha: %d\n", atual->algorithm,atual->token,atual->line);
			}
		}
		
		void clear_tokens_table(){
			Tokens_table *aux;
			Tokens_table *atual = p_tokens_p;
			while(atual != NULL) {	 	
			aux=atual->next;
			free(atual);
			atual=aux;
			}
		}
		
		Tokens_table* search_token(char *buffer){
			printf("Procura Token");
			Tokens_table *atual = p_tokens_p;
			int a=strlen(buffer);
			printf("\nTAM:%d",a);
			for(int e=0;e<a;e++){
				printf("\nPOS:%d",e);
				printf("\nChar:%c",buffer[e]);
				printf("\nChar:%d",buffer[e]);
			}
			if(buffer[a-1]==10){
				buffer[a-1]='\0';
			}
			 for (; atual != NULL; atual = atual->next) {	 		 
			 printf("\nProcura Token %s com %s",buffer,atual->algorithm);
					if(!strcmp(buffer,atual->algorithm)){
					//add_token(buffer,1,1);
					printf("\nachou na tebela de tokens: %s\n", atual->algorithm);				
				return atual;
					}		else{
						printf("\nNAO achou na tebela de tokens\n");				
					}				
				}//for
		}
		
		void receives(){	
			table_head=head_table();
			for (; table_head != NULL; table_head = table_head->next) {		
			printf("%s \t\t| %s \t\t| %s\n", table_head->algorithm, table_head->token, table_head->tipo);
			}
		}
		
		Data* search_table(char *buffer){	
		printf("Procura Tabela |%s|",buffer);
			table_head=head_table();
						 for (; table_head != NULL; table_head = table_head->next) {	 							 
							if(!strcmp(buffer,table_head->algorithm)){
								//append_token(buffer,table_head->token,table_head->tipo, 1,0);
								printf("achou: %s\n", buffer);	
								
				return table_head;
								}
								
							}//for
		}
		
		
			
			int lexico(){				
			p_lines=head_lines();
			char buffer[50];
			int ref=0, posicoes=1;
			clear_tokens_table();	
					for (; p_lines != NULL; p_lines = p_lines->next) {
					//LIMPA BUFFER
					for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					//RESETA PARA POSICAO INICIAL DA LINHA
					posicoes=1;
					ref=0;
					if(p_lines->is_code){//confere se a linha é código
					//VAMOS ANDAR POSICAO POR POSICAO DENTRO DA LINHA, COPIANDO OS VALORES DA LINHA PARA O BUFFER SEMPRE VENDO O PROXIMO CARACTER	
						for(int i=1;i<=strlen(p_lines->line_capture);i++){
						if((p_lines->line_capture[i-1]!=35)&&(p_lines->line_capture[i-1]!=36)&&(p_lines->line_capture[i-1]!=126))	{						
						//COPIA PARA O BUFFER A LINHA DA POSICAO REF ATÉ 
						strncpy(buffer,p_lines->line_capture+ref,posicoes);
						printf("\n\nPALAVRA: %s", buffer);
				printf("\nDECIMAL I: %d", i);
				printf("\nREF: %d", ref);
				printf("\nPOSICOES: %d", posicoes);
		
						if((buffer[0]==44)||(buffer[0]==58)){
							printf("\n\nVIRGULA");
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								if(!add_token(buffer,p_lines->number_line,ref)){
									clear_tokens_table();
								return 0;
								}
							}
							}
							//Busca
							for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					posicoes=0;
					ref=i+1;
						}
						if((buffer[0]==40)||(buffer[0]==41)){
							printf("\n\nPARENTESES");
							printf("\nPALAVRA NO: %s", buffer);
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i+1;
						}
						//---------------						
						if((buffer[0]=='>')&&(buffer[1]=='=')){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i+1;
						}
						//---------------------------------------
						if((buffer[0]=='<')&&(buffer[1]=='=')){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i+1;
						}							
						//--------------------------------------	
						if((buffer[0]=='=')&&(buffer[1]=='=')){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i+1;
						}
						//----------------------
						if((buffer[0]=='=')&&(buffer[1]>62||buffer[1]<59)){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i+1;
						}
						//----------------------
						if((buffer[0]=='<')&&(buffer[1]>62||buffer[1]<59)){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i;
						}
						//----------------------
						if((buffer[0]=='>')&&(buffer[1]>62||buffer[1]<59)){
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca
							for(int a=0;a<49;a++){
						buffer[a]='\0';			
							}
							posicoes=0;
							ref=i;
						}
						//----------------------
						
						if(p_lines->line_capture[i]==32){
							printf("\n\nESPACO");
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{							
							if(search_token(buffer)){
								
							}else{
								add_token(buffer,p_lines->number_line,ref);															
							}
							
							}
							for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					posicoes=0;
					ref=i+1;
						}		
						//--------------------------------------	
						if(p_lines->line_capture[i]==34){
							printf("\n\nASPAS");	
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								add_token(buffer,p_lines->number_line,ref);
							}
							}
							//Busca						
							for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					i++;
					int aux=0;
					while(p_lines->line_capture[i]!=34){
						printf("\nLetra %c",p_lines->line_capture[i]);
					i++;
					aux++;
					}					
					strncpy(buffer,p_lines->line_capture+ref+1,aux);
					char tok[10]="String";
					append_token(buffer,tok,"",p_lines->number_line,ref);
							for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					posicoes=0;
					ref=i+1;
					
						}		
						//--------------------------------------
						if((p_lines->line_capture[i+1]==44)||(p_lines->line_capture[i+1]==58)){
							printf("\n\n Separadores");
							//Busca
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
								if(!add_token(buffer,p_lines->number_line,ref)){
									printf("Não é permitido comecar uma variavel com um inteiro, linha: %d coluna: %d", p_lines->number_line, ref);
									clear_tokens_table();
									return 0;
								}																
							}
							}
							//Busca
							for(int a=0;a<49;a++){
					buffer[a]='\0';			
					}
					posicoes=0;
					ref=i+1;
						}
						//--------------------------------------			
						
						if((p_lines->line_capture[i]=='\n')||(p_lines->line_capture[i]<10)){
							printf("\n\nQUEBRA");
							if (search_table(buffer)){
								table_head=search_table(buffer);
								append_token(buffer,table_head->token,"",p_lines->number_line,ref);
							}else{
							if(search_token(buffer)){
								Tokens_table *atual = search_token(buffer);
								append_token(buffer,atual->token,"",p_lines->number_line,ref);
							}else{
								if(!add_token(buffer,p_lines->number_line,ref)){
									printf("Não é permitido comecar uma variavel com um inteiro, linha: %d coluna: %d", p_lines->number_line, ref);
									clear_tokens_table();
									return 0;
								}
							}
							}
							for(int a=0;a<49;a++){
							buffer[a]='\0';			
							}
					break;
						}		
					posicoes++;
				}else{
					printf("\nSimbolo nao pertencente a linguagem na linha %d coluna %d",p_lines->number_line,i);
					return 0;
				}
					}//FOR PERCORRE CHAR POR CHAR
		
					}
			//FINAL DA LINHA RESETA OS VALORES
			ref=0;
			posicoes=1;
			}
		}
