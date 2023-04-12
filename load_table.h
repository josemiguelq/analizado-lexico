typedef struct analyzer_lexico {
    char algorithm[15], token[15], tipo[15];
    struct analyzer_lexico *next;
}Data;

Data *table_lexica = NULL;

Data* head_table(){
	return table_lexica;
}
void load_table(){
    FILE *f;
    f = fopen("tabela.txt","r");

    while(!feof(f)){
    	Data *current = (Data*)malloc(sizeof(Data));
        fscanf(f, "%s %s %s\n", current->algorithm, current->token, current->tipo);
        current -> next = table_lexica;
        //table_lexica volta a ser a current
        table_lexica = current;
    }
}
//---------MOSTRA A TABELA PRIMEIRA
void show_table(){
    int position = 0;
    Data *nova = table_lexica;
    printf("*-------------------------------------*");
    printf("\n \t \t TABLE\n");
    printf("--------------------------------------\n");
    printf("algoritmo \t\t| token \t| tipo\n");
    printf("--------------------------------------\n");

    //la�o de repeti��o para mostrar os Data
    for (; nova != NULL; nova = nova->next) {
        position++;
        printf("%s \t\t| %s \t\t| %s\n", nova->algorithm, nova->token, nova->tipo);
    }
    printf("--------------------------------------");

}
