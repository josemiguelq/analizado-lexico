#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<conio.h>

typedef struct line {
    char line_capture[50];
    int number_line;
    bool is_code;
    struct line *next;
}Lines;

	
Lines *p_lines_p = NULL;
Lines *p_lines_f = NULL;

bool has_txt_extension(char const *name) {
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

Lines* head_lines(){
	Lines *nova = p_lines_p;
	return nova;	
}

//---------RETORNA O NOME DO ARQUIVO ESCOLHIDO

char* get_file_name() {
    DIR *dir = opendir("./");
    struct dirent *lsdir;
    char a[50];
    char* file_name;
	system("cls");
    /* lista os aquivos txt do dir current */
    printf("======= FILES IN DIRECTORY =======\n");
    while ( ( lsdir = readdir(dir) ) != NULL ) {
        if(has_txt_extension(lsdir->d_name))
        printf ("%s\n", lsdir -> d_name);
    }
    printf("========================================\n\n");
    closedir(dir);

    printf("Digite o nome do arquivo que deseja abrir: ");
    scanf("%s", file_name);
    strcat(file_name, ".txt");
system("cls");
    return file_name;
}


//-----------LIMPA
void libera()
{
	Lines *aux;
	Lines *atual = p_lines_p;
	
	while(atual != NULL) {
	aux=atual->next;
	free(atual);
	atual=aux;
	}	 
}

//---------CAPTURA AS LINHAS

void load_lines(){
 printf("\n");
	char buffer[50], copy[30];
	bool found = false;
	int indexLine=0;

    char* file_name = get_file_name();
	FILE* file = fopen(file_name, "r");
	libera();
	if(file) {
        while (!feof(file)) {
        	fgets(buffer,50,file);
        	if(strcmp(buffer,"\n")){
        		//printf("%s",buffer);
        		Lines *current = (Lines*)malloc(sizeof(Lines));
        		strcpy(current->line_capture,buffer );
        		current->number_line=indexLine;
        		//printf("%d - %s", current->number_line,current->line_capture);
        		indexLine++;        		
        		current -> next = NULL;
        		
        		if(p_lines_p==NULL){
        			p_lines_p= p_lines_f= current;
				}
				else{
					p_lines_f->next=current;
					p_lines_f=current;
				}
   			}        	
        }
	} else {
        system("clear");
        printf("\nArquivo nao encontrado!!\n\n");
	}
}

void show_all_lines(){
    int position = 0;
    Lines *nova = p_lines_p;
    printf("\n-----------Codigo fonte------------\n");
    //laço de repetição para mostrar os Data
    for (; nova != NULL; nova = nova->next) {
        position++;        
        printf("%d - %d - %s", nova->is_code, nova->number_line, nova->line_capture, nova->is_code);				
       
    }
    printf("\n--------------------------------------\n");

}
void scan_code_lines(){
    int position = 0;
    int tamLinha;
    
    Lines *nova = p_lines_p;
    
	    for (; nova != NULL; nova = nova->next) {//percorre linhas
	        //reconhecedor de comentario de linha	
			printf("%d",nova->number_line);	
	        if((nova->line_capture[0]=='/')&&(nova->line_capture[1]=='/')){        		
	        	nova->is_code=false;
	        	printf("opa %s",nova->line_capture);
			}else{
				nova->is_code=true;		
			for(int x=0;x<strlen(nova->line_capture);x++){
			if((nova->line_capture[x]=='/')&&(nova->line_capture[x+1]=='/')){        		
	        		for(int y=x;y<strlen(nova->line_capture);y++){        			
	        			nova->line_capture[y]='\0';        			
						}
					}			
			} 
			if((nova->line_capture[0]=='/')&&(nova->line_capture[1]=='*')){        		
	        	nova->is_code=false;
	        	bool fimbloco=false;
	        	while((!fimbloco)&&(nova->next!=NULL)){
	        		tamLinha = strlen(nova->line_capture);
	        		if(nova->line_capture[tamLinha-3] =='*' && nova->line_capture[tamLinha-2]=='/'){
	        			nova->is_code=false;
	        			fimbloco=true;	        			
						}else{							
							nova->is_code=false;
							fimbloco=false;
							nova = nova->next; //pula a posição
							break;						
							}
					}//while
			}else{
				 nova->is_code=true;  			
			}       			
			}//reconhecedor de comentario de linha		
			//reconhecedor de comentario de bloco
					
		}//or
		
}

void show_code_lines(){
	Lines *nova = p_lines_p;
	while(nova != NULL) {
	if(nova->is_code){
		printf("%d - %d - %s", nova->is_code, nova->number_line, nova->line_capture, nova->is_code);				
	}	
	nova = nova->next;
	}
}


void show_algorithm() {
	load_lines();
	show_all_lines();
	scan_code_lines();
	show_code_lines();
	
}
