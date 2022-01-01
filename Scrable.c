#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

//Constantes neccessárias
#define ESCAPE 0x1B
#define FONT_BLACK 0x1E
#define FONT_WHITE 0x25

#define BG_BLACK 0x28
#define BG_RED 0x29
#define BG_YELLOW 0x2B
#define BG_BLUE 0x2C
#define BG_MAGENTA 0x2D
#define BG_CYAN 0x2E
#define BG_WHITE 0x2F

#define WHT 100
#define RED 101
#define LBL 102
#define PNK 103
#define BLU 104
#define YEL 105

#define MAX_ROWS 17
#define MAX_COLS 17
#define BOARD_SIZE 15

#define NUMBER_OF_PIECES 115
#define DICTIONARY_SIZE 27718

typedef struct Word
	{
		char name[16];
		char orientation;
		int row;
		char col;
		int player;
		int points;
	}WORD;

typedef struct Piece
	{
		char letter;
		int points;
	}PIECE;

typedef struct Player
	{
		char name[20];
		int points;
		PIECE hand[7];
	}PLAYER;

typedef struct Game
	{
		WORD words[50];
		PLAYER players[2];
		PIECE pool[NUMBER_OF_PIECES];
		char board[15][15];
		char dictionary[DICTIONARY_SIZE][16];
		char turn;
		int word_count;
	}GAME;


void show_board(GAME game){	
	
	int i,j,row,col,orient;
	int colour,letter1,letter2;
	int board[17][17] = {{-1,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,-1},
						 {1,RED,WHT,WHT,LBL,WHT,WHT,WHT,RED,WHT,WHT,WHT,LBL,WHT,WHT,RED,1},
						 {2,WHT,PNK,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,PNK,WHT,2},
						 {3,WHT,WHT,PNK,WHT,WHT,WHT,LBL,WHT,LBL,WHT,WHT,WHT,PNK,WHT,WHT,3},
						 {4,LBL,WHT,WHT,PNK,WHT,WHT,WHT,LBL,WHT,WHT,WHT,PNK,WHT,WHT,LBL,4},
						 {5,WHT,WHT,WHT,WHT,PNK,WHT,WHT,WHT,WHT,WHT,PNK,WHT,WHT,WHT,WHT,5},
						 {6,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,6},
						 {7,WHT,WHT,LBL,WHT,WHT,WHT,LBL,WHT,LBL,WHT,WHT,WHT,LBL,WHT,WHT,7},
						 {8,RED,WHT,WHT,LBL,WHT,WHT,WHT,YEL,WHT,WHT,WHT,LBL,WHT,WHT,RED,8},
						 {9,WHT,WHT,LBL,WHT,WHT,WHT,LBL,WHT,LBL,WHT,WHT,WHT,LBL,WHT,WHT,9},
						 {10,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,10},
						 {11,WHT,WHT,WHT,WHT,PNK,WHT,WHT,WHT,WHT,WHT,PNK,WHT,WHT,WHT,WHT,11},
						 {12,LBL,WHT,WHT,PNK,WHT,WHT,WHT,LBL,WHT,WHT,WHT,PNK,WHT,WHT,LBL,12},
						 {13,WHT,WHT,PNK,WHT,WHT,WHT,LBL,WHT,LBL,WHT,WHT,WHT,PNK,WHT,WHT,13},
						 {14,WHT,PNK,WHT,WHT,WHT,BLU,WHT,WHT,WHT,BLU,WHT,WHT,WHT,PNK,WHT,14},
						 {15,RED,WHT,WHT,LBL,WHT,WHT,WHT,RED,WHT,WHT,WHT,LBL,WHT,WHT,RED,15},
						 {-1,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,-1}};	

	char game_board[BOARD_SIZE][BOARD_SIZE];
	for(i=0;i<BOARD_SIZE;i++)
	{
		for(j=0;j<BOARD_SIZE;j++)
			game_board[i][j] = ' ';
	}

	for(i=0;i < game.word_count;i++)
	{
		row = game.words[i].row - 1;
		col = game.words[i].col - 'A';
		orient = game.words[i].orientation;	

		for(j=0;game.words[i].name[j] != '\0';j++)
		{
			game_board[row][col] = game.words[i].name[j];
			if(orient == 'v')
				row++;
			else if(orient == 'h')
				col++;
		}		
	}	
	
	for(row = 0;row < MAX_ROWS;row++)
	{
		for(col = 0;col < MAX_COLS;col++)
		{
			switch(board[row][col]){	
				case WHT: colour = BG_WHITE;break;
				case RED: colour = BG_RED;break;
				case LBL: colour = BG_CYAN;break;
				case PNK: colour = BG_MAGENTA;break;
				case BLU: colour = BG_BLUE;break;
				case YEL: colour = BG_YELLOW;break;
				default: colour = BG_BLACK;break;
			}
			if((row == 0 &&  col == 0) || row == 0 &&  col == 16 || row == 16 &&  col == 0 || row == 16 &&  col == 16){
				printf("%c[%d;%dm %c%c %c[%dm",ESCAPE,FONT_WHITE,colour,' ',' ', ESCAPE, 0);	
			}else if((row == 0 || row == 16) && (col!= 0 || col!= 16)){
				letter1 = board[row][col];		
				printf("%c[%d;%dm %c %c[%dm",ESCAPE,FONT_WHITE,colour,letter1, ESCAPE, 0);
			}else if((col == 0 || col == 16) && (row != 0 || row != 16)){				
				if(board[row][col] > 9)
				{
					letter1 = 1 + '0';
					letter2 = board[row][col]%10;
					letter2 = letter2 + '0';
				}else{
					letter2 = board[row][col] + '0';
					letter1 = ' ';
				}									
				printf("%c[%d;%dm %c%c %c[%dm",ESCAPE,FONT_WHITE,colour,letter1,letter2, ESCAPE, 0);							
			}else{
				letter1 = ' ';
				if(game_board[row-1][col-1]!=' '){
					letter1 = game_board[row-1][col-1];
				}		
				if(letter1 != ' ')
					colour = BG_YELLOW;		
				printf("%c[%d;%dm %c %c[%dm",ESCAPE,FONT_BLACK,colour,letter1, ESCAPE, 0);	
			}			
		}
		putchar('\n');		
	}	
	putchar('\n');	
}

void show_hand(GAME *jogo){
	int i, j;
	if(jogo->turn==49)
		i=0;
	else {
		if(jogo->turn==50)
			i=1;
		else
			printf("Erros nos turnos, na função show_hand");
	}
	printf("A Mão do/a %s é: ", jogo->players[i].name);
	for(j=0; j<7;j++){
		printf(" %c", jogo->players[i].hand[j].letter);
	}
	printf(" \n");
}

char hand(GAME *jogo){
	int i, j=0, k;
	i=(jogo->turn -'0'-1);
	for(k=0; k<7 ; k++)
		if(jogo->players[i].hand[k].letter >= 'A' && jogo->players[i].hand[k].letter <= 'Z')
			j++;
	for(;j<7;j++){
		jogo->players[i].hand[j].letter = jogo->pool[rand()%115].letter;
	}
}


void get_hand(GAME *jogo){
	int i, j;
	for(i=0;i<2;i++){
		for(j=0;j<7;j++){
			jogo->players[i].hand[j].letter = jogo->pool[rand()%115].letter;
		}
	}
}



void novo_jogo(GAME *jogo){
	int i, j;
	jogo->word_count = 0;
	jogo->turn = '1';
	get_hand(jogo);
	getchar();
	for(i=0; i<2; i++){
		jogo->players[i].points=0;
		if(i==0)
			printf("Introduza o Nome do jogador 1: ");
		else
			printf("Introduza o Nome do jogador 2: ");
		for(j=0;j<20;j++){
			jogo->players[i].name[j] = getchar();
			if(jogo->players[i].name[j] == '\n'){
				jogo->players[i].name[j]= '\0';
				break;
			}
		}
	
	}
	for(i=0; i<16;i++){
		for(j=0; j<16;j++){
			jogo->board[i][j]=' ';
		}
	}
	system("clear");
}

void carregar_jogo(GAME *jogo){
	FILE *load_game = fopen("saveGame0.txt", "r");/*porque se encontra na mesma pasta*/
	int i=0, j=0, k=0,n, l, h=0, mudanca, word=0, letra, palavra, x, contador_1, contador_2, pontos_jogador, c;
	char ch, s[40], carregar[60][40], pontos[3],  contador[2], linha[2], nome[20], hand[7] ;
	if (load_game == NULL)
		printf("Impossível abrir o ficheiro\n");
	while((fscanf(load_game, "%s", carregar[i])!=EOF)){
	i++;
	}
	for(i=0; i<2; i++){
		l=0;
		n=0;
		h=0;
		for(j=0; j<strlen(carregar[i]);j++){
			if(carregar[i][j]!=';' && l==0){
				jogo->players[i].name[j]=carregar[i][j];
			}
			else{
				if(carregar[i][j]==';' && l==0)
					l++;
				else{
					if(carregar[i][j]!=';' && carregar[i][j]<'9'&& carregar[i][j]>'0'){
						for(k=0; k<2; k++){
							pontos[k] =carregar[i][j];
							j++;
						}
					}
					else{
						if(carregar[i][j]==';' && n==0)
							n++;
						else{
							if(carregar[i][j]!=';'){
								jogo->players[i].hand[h].letter=carregar[i][j];
								h++; 
							}
						}
					}
				}
			
			}	
			jogo->players[i].points=atoi(pontos);
		}
	}
	for(j=0; j<strlen(carregar[i]);j++){
			contador[j]=carregar[i][j];
			jogo->word_count= atoi(contador);/*A função atoi devolve o valor inteiro correspondente a uma string.(vetor de caracteres)*/
	}
	i++;
	for(; i<(jogo->word_count+3); i++){
		contador_1=0;
		contador_2=0;
		letra=0;
		palavra=0;
		k=0;	
		if(i!=3)
			word++;
		for(j=0; j<strlen(carregar[i]); j++){
			if(carregar[i][j]!=';' && palavra==0){
				jogo->words[word].name[letra]=carregar[i][j];			
				letra++;
			}
			else{
				if(carregar[i][j]==';'&& palavra==0)
					palavra++;
				else{
					if(carregar[i][j]!=';' && palavra==1)
						jogo->words[word].orientation=carregar[i][j];
					else{
						if(carregar[i][j]==';'&& palavra==1)
							palavra++;
						else{
							if(carregar[i][j]!=';' && palavra==2){
								if(contador_1==0){
									x=j;
									for(k=0; k<2; k++){
										linha[k] =carregar[i][j];
										j++;
									}
									j=x;
								}
								contador_1+=1;
								if(linha[1]== ';')
									jogo->words[word].row = ( linha[0] - '0');
								else
									jogo->words[word].row = ((linha[0] - '0')*10 + (linha[1] -'0')*1);
							}/*atribuir valores inteiros ao parâmetro row, visto que pode ter 2 caractéres*/	
							else{
								if(carregar[i][j]==';' && palavra==2){
									palavra++;
								}
								else{
									if(carregar[i][j]!= ';' && palavra ==3){
										jogo->words[word].col=carregar[i][j];
									}
									else{
										if(carregar[i][j]==';' && palavra ==3)
											palavra++;
										else{
											if(carregar[i][j]!=';' && palavra ==4){
												if(k==3){
													pontos[1]=carregar[i][j];
													k++;
												}
												if(k==2){
													pontos[0]=carregar[i][j];
													k++;
												}				}					
											else{
												if(carregar[i][j]==';' && palavra ==4)
													palavra++;
												else{
													if(carregar[i][j]!=';' && palavra==5)
														jogo->words[word].player=carregar[i][j]-'0'-1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if(k==3)/*vetor só tem 1 caracter*/
				jogo->words[word].points= (pontos[0] -'0');
			if(k==4)/*vetor tem 2 caracteres*/
				jogo->words[word].points= (pontos[0] - '0')*10 + (pontos[1] - '0')*1;
			
		}
	}
	jogo->turn=carregar[i][0];
	for(l=0; l<BOARD_SIZE; l++){  /*inicializar o tabuleiro com espaços em branco, a board de 15x15*/
		for(c=0;c<BOARD_SIZE;c++)
			jogo->board[l][c] = ' ';
	}

	for (j = 0; j < jogo->word_count; j++){ /*envia dados para board de 15x15*/
		for(x = 0; x < strlen(jogo->words[j].name) ; x++){
			if(jogo->words[j].orientation == 'h'){
				jogo->board[jogo->words[j].row][(jogo->words[j].col - 'A') + x+1] = jogo->words[j].name[x];
			}
			if(jogo->words[j].orientation == 'v'){
				jogo->board[jogo->words[j].row + x][(jogo->words[j].col - 'A')+1] = jogo->words[j].name[x];
			}
		}
	}
	fclose(load_game);
	
}

void guardar_jogo(GAME *jogo){
	FILE *save_game = fopen("save.txt", "w");/*porque se encontra na mesma pasta*/
	int i, j, k, l, contador;
	if (save_game == NULL){
		printf("Erro na escrita do ficheiro.\n");
		exit(1);
	}
	for(k=0, i=0;k<2;k++){
		fprintf(save_game, "%s;%d;", jogo->players[i].name, jogo->players[i].points);
		for(j=0;j<7;j++){
			fprintf(save_game, "%c", jogo->players[i].hand[j].letter);
		}
		fprintf(save_game, "\n");
		i++;
	}
	if (k == 2){
		fprintf(save_game, "%d", jogo->word_count);
		fprintf(save_game, "\n");
	}
	contador= jogo->word_count +3;
	i=0;
	for(k=3;k<contador; k++){
		fprintf(save_game, "%s;%c;%d;%c;%d;%d\n", jogo->words[i].name, jogo->words[i].orientation, jogo->words[i].row, jogo->words[i].col, jogo->words[i].points, jogo->words[i].player);
		i++;
	} 
	if (k == contador){
		fprintf(save_game, "%c", jogo->turn);
		fprintf(save_game, "\n");
	}
	fclose(save_game);
}


int menu_jogo(){
	int escolha, y=0;
	printf("\n\n\t\t\t*********************MENU DE PAUSA*********************\n\t\t\t\t\t1) Guardar Jogo\n\t\t\t\t\t2) Continuar Jogo Corrente\n\t\t\t\t\t3) Voltar ao Menu Principal\n\t\t\t\t\t4) Sair do Jogo\n\t\t\t*******************************************************\n\n\n");
	
	while(y==0){
		scanf(" %d", &escolha);
		switch(escolha){
			case 1: return 1; 
			case 2: return 2;
			case 3: return 3;
			case 4: exit(0);
			default: printf("Opção Introduzida está incorreta. Insira outra vez.");continue ;
		}	
	}
}

void eliminar_letra(GAME *jogo, char ch){
	int i, j, k=0, contador =0;
	for(i=0; jogo->players[jogo->words[jogo->word_count].player].hand[i].letter != '\0' ; i++){
		for(j=0; j<7; j++){
			if(jogo->words[jogo->word_count].name[j] == jogo->players[jogo->words[jogo->word_count].player].hand[i].letter){
				contador = i;
				break;
			}
		}
		printf(" \ni= %d and j= %d and contador = %d", i, j, contador);
		if( contador!= 0) 
			break;
	}
	printf("  contador é tal tal = %d", contador);
	for(i=0, j=0; jogo->players[jogo->words[jogo->word_count].player].hand[i].letter != '\0';i++){
		if(i==contador){
			continue;
		}
		jogo->players[jogo->words[jogo->word_count].player].hand[j++].letter = jogo->players[jogo->words[jogo->word_count].player].hand[i].letter;
	}
	printf(" j = %d \n", j);
	jogo->players[jogo->words[jogo->word_count].player].hand[j].letter = '\0';
	for(i=0; i<10; i++){
		printf(" %c", jogo->players[jogo->words[jogo->word_count].player].hand[i].letter);
	}	
		
} /* nao consegui acabar o trabalho, mas esta função era utilizada para eliminar as letras da mao utilizada pela palavra introduzida, e depois eram repostas estas letras na função hand */

int encadeamento(GAME *jogo, int a){

	int word_size = strlen(jogo->words[a].name);
	int l = jogo->words[a].row-2;
	int c = (jogo->words[a].col - 'A'-1);
	int i, x = 0, k;

	for(i=0; i < word_size; i++){
		if(jogo->words[a].orientation == 'h'){
			if(jogo->board[l][c+i] != ' '){
				x++; 
				if(jogo->words[a].name[i] != jogo->board[l][c+i])
					return 0;
				else
					if((jogo->board[l][c-1] != ' ') || (jogo->board[l][c+word_size] != ' ')){					
						return 0;
					}
			}
		}
		else if (jogo->words[a].orientation == 'v'){
			if(jogo->board[l+i][c] != ' '){
				x++;
				if(jogo->words[a].name[i] != jogo->board[l+i][c])
					return 0;
                else
					if((jogo->board[l-1][c] != ' ') || (jogo->board[l+word_size][c] != ' '))	 					
						return 0;
			}	
		}
	}
	if(strlen(jogo->words[a].name) == x)
		return 0;
	if(x == 0)
		return 0;
	return 1;
}

void mostrar_board(GAME *jogo){
    int c, l;
    printf("    ");
    for(c=0; c<15; c++)
        printf("%d ", c);
    putchar('\n');
    for (l=0; l<15; l++){
        printf("%2d |", l);
        for (c=0; c<15; c++){
            printf ("%c ", jogo->board[l][c]);
        }
        putchar('\n');
    }
}

void menu_jogo_print(){
	printf("\n\n\n\n************************SCRABBLE************************\n\tH - Histórico\n\tT - Trocar Letra\n\tP - Passar Turno\n\tM - Voltar ao menu Principal\n\tS - Sair\n********************************************************\n\n\n");
}

void jogar(GAME *jogo){
	int i, j, x, o=0, r=0, c=0, k, l=0, escolha, pontos, y=0, letra, ANALISE, TESTE, historico; 
	char turno, caracter, letra_trocar;
	i=(jogo->word_count);
	do{
		if(jogo->turn == '2')
			jogo->words[i].player=1;
		if(jogo->turn == '1')
			jogo->words[i].player=0;
		o=0, r=0, c=0;
		while(1){
			show_board(*jogo);
			menu_jogo_print();
			printf("\nÉ a vez do/a %s.\n", jogo->players[jogo->words[i].player].name);
			show_hand(jogo);
			printf("Os pontos são: %d\n", jogo->players[jogo->words[i].player].points);
			printf("Introduza a palavra: ");
			while(1){
				while(1){
					l=0;
					scanf(" %s", jogo->words[i].name);
					for(x=0;x<strlen(jogo->words[i].name);x++){
						jogo->words[i].name[x] = toupper(jogo->words[i].name[x]);
					}
					break;
				}

				k=0;
				for(x=0; x<DICTIONARY_SIZE; x++){
					if(strstr(jogo->dictionary[x], jogo->words[i].name))
						k=1;
				}	
				if(k==1)
					break;
				else
					printf("Palavra inválida. Não existe no dicionário. Por favor introduza uma nova Palavra.\n");		
			}
			k=0;
			if(jogo->words[i].name[0] == 'S' && jogo->words[i].name[1] == '\0'){
				printf("\n\nObrigado por Jogar até à próxima =)\n\n\n\n\n\n");
				exit(1);
			}
			if(jogo->words[i].name[0] == 'H' && jogo->words[i].name[1] == '\0'){
				for(historico=0; historico<i; historico++){
					printf("Palavra: %s Jogador: %s Pontos: %d\n", jogo->words[historico].name, jogo->players[jogo->words[historico].player].name, jogo->words[historico].points);
				}
			}
			if(jogo->words[i].name[0] == 'T' && jogo->words[i].name[1] == '\0'){
				printf("\nQual é a letra que deseja trocar? :");
				while(1){
					scanf(" %c", &letra_trocar);
					toupper(letra_trocar);
					for(x=0;x<7;x++){
						if(jogo->players[jogo->words[i].player].hand[x].letter == letra_trocar){
							jogo->players[jogo->words[i].player].hand[x].letter = jogo->pool[rand()%115].letter;
							break;
						}
					}
					if(x==7)
						printf("\nLetra inválida( Não se encontra na mão)");
					else
						break;
				}
				printf("\nA Sua nova letra é %c \n", jogo->players[jogo->words[i].player].hand[x].letter);
			}
			if(jogo->words[i].name[0] == 'M' && jogo->words[i].name[1]=='\0'){
				escolha = menu_jogo();
				if(escolha==1){
					guardar_jogo(jogo);
					printf("\n\nJogo Guardado com Sucesso !\n\n");
					continue;
				}
				if(escolha==2)
					continue;
				if(escolha==3)
					main();
					
			}
			break;
		}
		
		
		while(1){
			if((jogo->words[i].name[0] == 'P' && jogo->words[i].name[1]=='\0') || (jogo->words[i].name[0] == 'T' && jogo->words[i].name[1]=='\0'))
				break;	/*passar o turno, quando o jogador pede ou quando trocou letra.*/	
			x=0;
			printf("\nIntroduza agora a orientação, linha e coluna(da primeira letra da palavra), respetivamente:   ");
			while(1){
				/*verificar se as orientações estão bem introduzidas*/
				while(1){
					x=0;
					scanf(" %c %d %c", &jogo->words[i].orientation, &jogo->words[i].row, &jogo->words[i].col);
				
					if(jogo->words[i].orientation == 'h' || jogo->words[i].orientation == 'v')
						x++;
					else
						x=0;
					if(jogo->words[i].row > 0 && jogo-> words[i].row <16)
						x++;
					else
						x=0;
					if(jogo->words[i].col >= 'a' && jogo->words[i].col <= 'o' || jogo->words[i].col >= 'A' && jogo->words[i].col <= 'O')
						x++;
					else
						x=0;
					if(x==3)
						break;
					else
						printf("\nAlgum dos parâmetros foi introduzido incorretamente.\nPor favor introduza novamente: ");
					
				}
				/*verificar se a primeira palavra está na casa do meio*/
				if(jogo->word_count == 0){
					if(jogo->words[i].orientation== 'v'){
						l=0;
						for(x=jogo->words[i].row;x<(strlen(jogo->words[i].name)+jogo->words[i].row);x++){
							jogo->board[x][(jogo->words[i].col-'a'+1)]=jogo->words[i].name[l];
							l++;
						}
					}
					else{
						l=0;
						for(x=(jogo->words[i].col - 'a'+1); x<(strlen(jogo->words[i].name)+(jogo->words[i].col - 'a'+1));x++){
							jogo->board[jogo->words[i].row][x]=jogo->words[i].name[l];
							l++;
						}
					}
					if(jogo->board[8][8]!= ' ')
						;
					else{
						printf("\nA casa do meio não foi preenchida, por favor introduza de novo os parâmetros: ");
		                continue;
		            }
				}
				/*verificar se as palavras estão encadeadas, excluindo a primeira palavra introduzida*/
				if (jogo->word_count > 0){		
					while (!(((jogo->words[i].orientation == 'v') || (jogo->words[i].orientation == 'h')) && ((jogo->words[i].col >= 'a') && (jogo->words[i].col <= 'o')) && ((jogo->words[i].row >= 1) && (jogo->words[i].row <= 15))) || (encadeamento(jogo, i) == 0)){
						if(!(((jogo->words[i].orientation == 'v') || (jogo->words[i].orientation == 'h')) && ((jogo->words[i].col >= 'a') && (jogo->words[i].col <= 'o')) && ((jogo->words[i].row >= 1) && (jogo->words[i].row <= 15)))){
							printf ("Os dados que introduziu estão errados. Por favor, tente novamente.\n");
							if(encadeamento(jogo, i) == 0)
								printf ("A palavra introduzida não utiliza peças de palavras anteriores.\n");
						}
						else if(encadeamento(jogo, i) == 0)
							printf ("A palavra introduzida não utiliza peças de palavras anteriores.\n");
						printf("\nIntroduza a orientação, linha e coluna(da primeira letra da palavra), respetivamente:   ");
						scanf(" %c %d %c", &jogo->words[i].orientation, &jogo->words[i].row, &jogo->words[i].col);
					}
			    }
                break;
			}
			/*atribuir pontos ás palavras e depois aos jogadores*/
			jogo->words[i].row-=2;
			jogo->words[i].col-=2;
			for(letra=0; letra<strlen(jogo->words[i].name);letra++){
				for(y=0; y<115;y++){
					if(jogo->pool[y].letter == jogo->words[i].name[letra]){
						jogo->words[i].points += jogo->pool[y].points;
						break;
					}
				}
			}
          	for(x = 0; x < strlen(jogo->words[i].name); x++){
				if(jogo->words[i].orientation == 'h')
					jogo->board[jogo->words[i].row][(jogo->words[i].col - 'A') + x+1] = jogo->words[i].name[x];
				if(jogo->words[i].orientation == 'v')
					jogo->board[jogo->words[i].row + x][(jogo->words[i].col - 'A')+1] = jogo->words[i].name[x];
			}
			jogo->players[jogo->words[i].player].points += jogo->words[i].points;
			system("clear");
			printf("\n\n\n\n\n\n\n\n\nOs pontos do/a %s agora são %d\n", jogo->players[jogo->words[i].player].name, jogo->players[jogo->words[i].player].points);
			jogo->word_count+=1;
			hand(jogo);
			i++;
			break;
		}
		if(jogo->turn== '2')
				jogo->turn= '1';
			else{
				if(jogo->turn== '1')
					jogo->turn= '2';
			}
		if(jogo->players[jogo->words[i].player].points >=100){
			printf("Parabéns %s ! \nGanhaste o Jogo com uma Pontuação de %d. %s Ficou com %d pontos =)\n\n", jogo->players[0].name, jogo->players[0].points, jogo->players[1].name, jogo->players[1].points);
			printf("Muito Obrigado por Jogar!\n\n");
			exit(0);
		}
	}
	while(1);
}



void menu(){
	printf("\n\n\n\n\t\t\t************************SCRABBLE************************\n\t\t\t\t\t1) Novo Jogo\n\t\t\t\t\t2) Carregar Jogo\n\t\t\t\t\t3) Sair do Jogo\n\t\t\t********************************************************\n\n\n");
}


int choose(){
	int y=0;
	char menu_escolha;
	menu();
	do{
		scanf(" %c", &menu_escolha);
		switch(menu_escolha){
			case '1': return y=1;
			case '2': return y=2;
			case '3': return y=3;
			case '4': return y=4;
			default:printf("Opção Introduzida é Inválida.\n\n"); menu();
		}
	}	
	while(y==0);
}



void inic_random(){
	long ultime;
	time (&ultime);
	srand((unsigned) ultime);
}
	
main(){
	GAME jogo;
	FILE *dictionary_pool, *piece_pool;	
	int opcao, i=0, j=0, k=0, contou=0, v=0, pontos, total=0, quantidade, x;	
	char ch[16], piscina_pieces[26][40], letra;
	inic_random();
	dictionary_pool = fopen("words.txt", "r");
	piece_pool = fopen("letters.txt", "r");
	if(dictionary_pool==NULL)
		printf("Impossível abrir o ficheiro words.txt");
	while((fscanf(dictionary_pool, "%s", jogo.dictionary[i])!=EOF)){
		i++;
	}
	i=0;
	if(piece_pool == NULL)
		printf("Impossível abrir o ficheiro letters.txt");
	while((fscanf(piece_pool, " %d;%c;%d\n", &quantidade, &letra, &pontos)!=EOF)){
		for(i=0; i<quantidade; i++){
			jogo.pool[j].letter=letra;
			jogo.pool[j].points=pontos;
			j++;
		}
	}
	do{
		opcao = choose();
		if(opcao==3){
			printf("Obrigado Por Jogar. Adeus =)\n");
			exit(0);
		}
		if(opcao==1){
			novo_jogo(&jogo);
			jogar(&jogo);
		}
		else{
			if(opcao==2){
				carregar_jogo(&jogo);
				jogar(&jogo);
			}
		}
	}
	while(opcao!=3);
	
}












