#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<ctype.h>

#define VAZIO 10
#define BOMBA -1
#define DUVIDA 12
#define BANDEIRA 11
#define TAM_MAX 20

// Variáveis globais:
char nome_jogador[31];
int num_bombas=10, num_casas=10;
int campo_invisivel[TAM_MAX][TAM_MAX];//gabarito
int campo[TAM_MAX][TAM_MAX];
int qt_bandeira=0;

// Variavel para pontuação:
int PONTUACAO=0;

// Variável para registro de tempo
int tempo_inicial=0, tempo_final=0;

// Assinaturas:
int inicializacao(int num_bombas, int num_casas);
void mostra_campo();
int numero_bombas(int i,int j);
int abre_casa(int l,int c);
void leitura();
void abre_zeros(int i , int j);
void campo_minado();

// Principal:
int main(void){
	
	setlocale(LC_ALL, "portuguese");
	srand(time(NULL));
	int linha, coluna;
	char opcao_menu;
	
	while(opcao_menu!='c'){
    campo_minado();
		printf("\n\t(a) Jogar\n\t(b) Configurações\n\t(c) Sair\n\n");
		scanf(" %c", &opcao_menu);
		
		// Opção: JOGAR
		if(opcao_menu=='a'){
			system("cls");
			//Nome do jogador 
			printf("Insira seu nome: ");
			scanf(" %s", nome_jogador);
			//Chamdo das finçãoes
			inicializacao(num_bombas, num_casas);
			leitura();
		}
		
		// Opção: CONFIGURAÇÕES
		else if(opcao_menu=='b'){
			system("cls");
			char opcao_configuracoes;
			printf("\n\t*CONFIGURAÇÃOES*\n\n\t\n(a) Fácil\n\t\t-Tabuleiro 10 x 10\n\t\t-Quantidade de Bombas: 10\n\t\n(b) Intermediário\n\t\t-Tabuleiro 15 x 15\n\t\t-Quantidade de Bombas: 40\n\t\n(c) Difícil\n\t\t-Tabuleiro 20 x 20\n\t\t-Quantidade de Bombas: 90\n\t");
    		scanf(" %c", &opcao_configuracoes);
			switch(opcao_configuracoes){
    			//Facil
				case 'a':
    				num_bombas=10;
    				num_casas=10;
    				printf("\nDificuldade alterada para fácil.\n\n");
    				system("pause");
            system("cls");
			      //Nome do jogador 
			      printf("Insira seu nome: ");
			      scanf(" %s", nome_jogador);
			      //Chamdo das finçãoes 
			      inicializacao(num_bombas, num_casas);
			      leitura();
    				break;
    			//intermediário
				case 'b':
    				num_bombas=40;
    				num_casas=15;
    				printf("\nDificuldade alterada para intermediário.\n\n");
    				system("pause");
            system("cls");
			      //Nome do jogador 
			      printf("Insira seu nome: ");
			      scanf(" %s", nome_jogador);
			      //Chamdo das finçãoes 
			      inicializacao(40, 15);
			      leitura();
					break;
    			//Difícil
				case 'c':
    				num_bombas=99;
    				num_casas=20;
    				printf("\nDificuldade alterada para difícil.\n\n");
    				system("pause");
            system("cls");
			      //Nome do jogador 
			      printf("Insira seu nome: ");
			      scanf(" %s", nome_jogador);
			      //Chamdo das finçãoes 
			      inicializacao(99, 20);
			      leitura();
    				break;
    			//Valor invalidado
				default:
    				printf("\nVALOR INVÁLIDO!\n\n");
    				system("pause");
    				break;
			}
		}
		system("cls");
	}
	printf("\n\t[MENSAGEM DESPEDIDA]\n");
	return 0;
}

// O que eu vou precisar "antes" do usuario começae a jogar 
int inicializacao(int num_bombas, int num_casas){
	
	//DISTRUBUI AS BOMBAS 	
	int i=0, j=0;
	// Cria a matriz:
	for(i=0; i<num_casas; i++){
		for(j=0; j<num_casas; j++){
			campo_invisivel[i][j]=0; 
			campo[i][j] = VAZIO;
		}
	}
	// Destribui as bombas:
	int cont=0, a=0, b=0;
	while(cont<num_bombas){
		a=rand()%num_casas;
		b=rand()%num_casas;
		if(campo_invisivel[a][b]!= BOMBA){
			campo_invisivel[a][b]= BOMBA;
			cont++;
		}
	}

	//CALCULAR O NUMERO DE CASAS AO REDOR DA CASA I,J
	for(i = 0;i<num_casas;i++){
		for(j=0;j<num_casas;j++){
			
			if(campo_invisivel[i][j] != BOMBA){
				campo_invisivel[i][j] = numero_bombas(i,j);//numero_bomabas(i,j); chamado para a função
			}
			//printf("%3d", campo_invisivel[i][j]);
		}
		//printf("\n");	//iniciar uma nova linha da matriz
	}
	//printf("\n");	

}

//o campo que vai ser mostrado para o usuario
void mostra_campo(){
	int i,j;
	//Imprime a matriz
	for( i=0; i<num_casas; i++){
		for(j=0; j<num_casas; j++){
				
			if(campo[i][j] == VAZIO){
				printf(" - ");
			} else if(campo[i][j] == DUVIDA){
        printf(" ? ");
      } else if(campo[i][j] == BANDEIRA){
        printf(" B ");
        
      } else if(campo[i][j] ==  campo[i][j]){
        printf(" %d ",campo[i][j]);
      }
		}
		printf("\n");
	}
}

//calculara o numero de bombas ao redor de cada casa i ,j
int numero_bombas(int i , int j){
	
	int qt_bombas = 0;

	//chegcar a casa Superior
	if(i-1 >= 0 && j-1>= 0){
		if(campo_invisivel[i-1][j-1] == BOMBA)
			qt_bombas++;
	}
	//chegcar a casa Superior Centro
	if(i-1 >= 0){
		if(campo_invisivel[i-1][j] == BOMBA)
			qt_bombas++;
	}
	//chegcar a casa inferior direiro 
	if(i+1 < num_casas && j+1 < num_casas){
		if(campo_invisivel[i+1][j+1] == BOMBA)
			qt_bombas++;
	}
	//chegcar a casa superior direito		
	if(i-1 >= 0 && j+1 < num_casas){
		if(campo_invisivel[i-1][j+1] == BOMBA)
			qt_bombas++;
	}		
	//chegcar a casa inferior centro		
	if(i+1 < num_casas ){	
		if(campo_invisivel[i+1][j] == BOMBA)
			qt_bombas++;
	}
		
	//chegcar a casa inferior esquerdo
	if(i+1 < num_casas && j-1>=0 ){		
		if(campo_invisivel[i+1][j-1] == BOMBA)
			qt_bombas++;
	}
	//chegcar a casa esquerdo
	if(j-1>=0 ){		
		if(campo_invisivel[i][j-1] == BOMBA)
			qt_bombas++;
	}
	//chegcar a casa esquerdo
	if(j+1< num_casas){		
		if(campo_invisivel[i][j+1] == BOMBA)
			qt_bombas++;
	}

	return qt_bombas;
}

void leitura(){
	
  int linha, coluna;
  int FIM_DE_JOGO;
  int opcao;
  
 tempo_inicial=time(NULL);

  do{

    system("cls");
    
    printf("Pontuação: %d\nBombas restantes: %d\n\n", (PONTUACAO), (num_bombas-qt_bandeira));

    mostra_campo();
    //Linha e coluna
	  printf("\nLinha: ");
	  scanf("%d",&linha);
	  printf("Coluna: ");
	  scanf("%d",&coluna);
    linha = linha - 1;
    coluna  = coluna - 1;
    //opçoesten
    printf("\n\t*Opções*\n\n\t\n(1) Abrir casa:\n\t\t-Você vê oque tem dentro da casa\n\t\n(2) Marcar bandeira:\n\t\t-Você pode marcar o lugar em que acredita ter uma bomba\n\t\n(3) Marcar dúvida:\n\t\t-Você pode marcar com uma '?' a casa que não sabe o que tem dentro\n\n");
    scanf("%d", &opcao);
    switch(opcao){
      //abrir casa
      case 1:
         FIM_DE_JOGO = abre_casa(linha,coluna);
         campo[linha][coluna] =  campo[linha][coluna];
      break;
      //maracar bandeira
      case 2:
        campo[linha][coluna] = BANDEIRA;
        qt_bandeira++;
      break;
      //marcar duvida
      case 3:
      campo[linha][coluna] = DUVIDA;
      break;
    }

  } while((FIM_DE_JOGO != -1||(PONTUACAO==((num_casas*num_casas)-num_bombas))));

  tempo_final=time(NULL);

  // Mensagem de despedida.
  if(FIM_DE_JOGO==-1){
  	
  	system("cls");
    
	printf("%s, VOCÊ PERDEU!!\n\nTempo: %d segundos\nPontuação final: %d\n\nPosição das bombas:\n", nome_jogador, (tempo_final-tempo_inicial), PONTUACAO);

	int i,j;
	for(i=0; i<num_casas; i++){
	  	for(j=0; j<num_casas; j++){
  
        if(campo_invisivel[i][j] == BOMBA){
          printf(" * ");
        } else if(campo[i][j] == campo_invisivel[i][j]){
        printf(" %d ", campo[i][j]);
        }else if(campo[i][j] == VAZIO){
          printf(" - ");
        }
  	  }
    printf("\n");
  }
	
  printf("\n");

  } else {
  	system("cls");
    printf("%s, VOCÊ GANHOU!!\nTempo: %d segundos\nPontuação final: %d\n", nome_jogador, (tempo_final-tempo_inicial), PONTUACAO);
  }

  system("pause");

  PONTUACAO=0;
}

int abre_casa(int l, int c){
	if(campo_invisivel[l][c] == BOMBA)
		return -1;//Fim de jogo

  PONTUACAO++;
  
  campo[l][c] = campo_invisivel[l][c];

	if(campo_invisivel[l][c] == 0){
    abre_zeros(l,c);
  }
  return 0;
}


void abre_zeros(int i , int j){

	//chegcar a casa Superior
  //testar se a casa já esta aberta
  //campo != VAZIO
   if(i-1 >= 0 && j-1>= 0){
      if(campo[i-1][j-1] == VAZIO){
        campo[i-1][j-1] = campo_invisivel[i-1][j-1];
        PONTUACAO++;
     }
    }
	//chegcar a casa Superior Centro
  if(i-1>= 0){
		if(campo[i-1][j] == VAZIO){
        campo[i-1][j] = campo_invisivel[i-1][j];
        PONTUACAO++;
      }		
	}
	//chegcar a casa inferior direiro
	if(i+1 < num_casas && j+1 < num_casas){
		if(campo[i+1][j+1] == VAZIO){
        campo[i+1][j+1] = campo_invisivel[i+1][j+1];
        PONTUACAO++;
      }
	}
	//chegcar a casa superior direito		
	if(i-1 >= 0 && j+1 < num_casas){
		if(campo[i-1][j+1] == VAZIO){
        campo[i-1][j+1] = campo_invisivel[i-1][j+1];
        PONTUACAO++;
      }
	}		
	//chegcar a casa inferior centro		
	if(i+1 < num_casas ){	
		if(campo[i+1][j] == VAZIO){
        campo[i+1][j] = campo_invisivel[i+1][j];
        PONTUACAO++;
      }
	}
	//chegcar a casa inferior esquerdo
	if(i+1 < num_casas && j-1>=0 ){		
		if(campo[i+1][j-1] == VAZIO){
        campo[i+1][j-1] = campo_invisivel[i+1][j-1];
        PONTUACAO++;
      }
	}
	//chegcar a casa esquerdo
	if(j-1>=0){
    if(campo[i][j-1] == VAZIO){
        campo[i][j-1] = campo_invisivel[i][j-1];
        PONTUACAO++;
      }
	}
	//chegcar a casa esquerdo
	if(j+1<num_casas){
    if(campo[i][j+1] == VAZIO){
        campo[i][j+1] = campo_invisivel[i][j+1];
        PONTUACAO++;
      }
	}
}

void campo_minado(){

  puts("");       
	puts("      .--.                               .-..-. _                 .-.      "); 
	puts("     : .--'                              : `' ::_;                : :      "); 
	puts("     : :    .--.  ,-.,-.,-..---.  .--.   : .. :.-.,-.,-. .--.   .-' : .--. "); 
	puts("     : :__ ' .; ; : ,. ,. :: .; `' .; :  : :; :: :: ,. :' .; ; ' .; :' .; :"); 
	puts("     `.__.'`.__,_;:_;:_;:_;: ._.'`.__.'  :_;:_;:_;:_;:_;`.__,_;`.__.'`.__.'"); 
	puts("                           : :                                        ");      
	puts("                           :_;                                    ");
  
}
