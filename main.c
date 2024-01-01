#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j,m;

void rotateTetrimino90Degrees(int tetrimino[3][3], int rotated[3][3])
{
    int temp[3][3];

    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            temp[j][i] = tetrimino[i][j];
        }
    }

    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            rotated[i][j] = temp[i][3 - j - 1];
        }
    }
    
    while(rotated[0][0] == 0 && rotated[1][0] == 0 && rotated[2][0] == 0){
    	for(i=0; i<3; i++){
    		rotated[i][0] = rotated[i][1];
    		rotated[i][1] = rotated[i][2];
    		rotated[i][2] = 0;
	
		}
			
	}
}


// Matrisi ekrana yazdýracak fonksiyon
void printTetrimino(int tetrimino[3][3]) {
    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++) {
            if(tetrimino[i][j] == 1){
				printf("%d ", tetrimino[i][j]);
        	}
        	else{
        		printf("  ");
			}
		}
        printf("\n");
    }
}


int main() {
    int i,j,k,m,choice = 0,highScore = 0, score=0;
    char nickname[20];
	
	// Tetriminolarý tanýmlama
    int tetriminos[7][3][3] = {
        {{1, 1, 1}},
        {{1, 1}, {1, 1}},
        {{1}, {1}},
        {{1}},
        {{1}, {1}, {1}},
        {{1, 0}, {1, 0}, {1, 1}},
        {{0, 1, 1}, {1, 1, 0}}
    };
    
	int currentTetrimino[3][3];
    int rotatedTetrimino[3][3];
    int control = 0;

    while (choice != 2) {
    	system("cls");
        printf("111111  222222  333333  4444444  55  666666\n");
        printf("  11    22        33    44   44  55  66    \n");
        printf("  11    22222     33    444444   55  666666\n");
        printf("  11    22        33    44   44  55      66\n");
        printf("  11    222222    33    44    44 55  666666\n");
        printf("-----------------------------------------------\n");
        printf("En Yuksek Skor: %d\n",highScore);
		printf("-----------------------------------------------\n");
        printf("1. Oyuna Basla\n");
        printf("2. Cikis\n");
        printf("-----------------------------------------------\n");
		if(control == 1){
			if(score>highScore){
    		highScore = score;
    		printf("Tebrikler %s!. En yüksek skor! ---> %d",nickname, score);
    				
			}	
			else{
				printf("Oyun bitti. Skorunuz: %d",score);
			}
		}

		printf("\n");
        scanf("%d", &choice);
        system("cls");
        

        if (choice == 1) {
        	control = 0;
            printf("Kullanici adi: ");
            scanf("%s", &nickname);
            printf("Oyun tahtasinin buyuklugunu giriniz(mxm): ");
            scanf("%d", &m);
            while(m<3){
            	printf("Oyun tahtasi en kucuk 4x4 luk olabilir!\n");
            	scanf("%d", &m);
			}
			system("cls");
            
            int board[m][m];
            
            // oyun tahtasýný 0 lama
    		for (i = 0; i < m; i++) {
        		for (j = 0; j < m; j++) {
            		board[i][j] = 0;
        		}
    		}	
            
			int game=0;
			
            
            while(game == 0 && control == 0){
            	for(i=0;i<m;i++){
            		if(board[0][i]==1){
            			control = 1;
					}
				}
				if(control == 1){
					if(score>highScore){
            		highScore = score;
            		printf("Tebrikler %s!. En yüksek skor! ---> %d",nickname, score);
            				
					}	
					else{
						printf("Oyun bitti. Skorunuz: %d",score);
					}
				}
				if(control == 0){
	
					system("cls");
					// Rastgele sayý üretme
	    			srand(time(NULL));
	
	   				// Rastgele matris seçme
					int randomIndex = (rand() % 7);
	
	    			
	    			
	    			for (i = 0; i < 3; i++)
	            	{
						for (j = 0; j < 3; j++)
	                	{
	                    currentTetrimino[i][j] = tetriminos[randomIndex][i][j];
	                	}
	            	}
	    			
	    			printTetrimino(currentTetrimino);
	    			//oyun tahtasý yazdýrma
	    			for(i=0; i<m; i++){
	    				for(j=0; j<m; j++){
	    					printf("%d ", board[i][j]);
						}
	    				printf("\n");
					}
					printf("%s",nickname);
					printf("\nScore: %d",score);
					printf("\n1.Parcayi dondur	2.Parcayi Yerlestir	 3.Ana Menu ------> ");
					scanf("%d",&game);
					
					
					while(game == 1){
						system("cls");
						rotateTetrimino90Degrees(currentTetrimino,rotatedTetrimino);
						printTetrimino(rotatedTetrimino);
						
						for (i = 0; i < 3; i++)
	                    {
	                        for (j = 0; j < 3; j++)
	                        {
	                            currentTetrimino[i][j] = rotatedTetrimino[i][j];
	                        }
	                    }
						
						for(i=0; i<m; i++){
	    					for(j=0; j<m; j++){
	    						printf("%d ", board[i][j]);
						}
	    				printf("\n");
					}
						printf("%s",nickname);
						printf("\nScore: %d",score);
						printf("\n1.Parcayi dondur	2.Parcayi Yerlestir	 3.Ana Menu	------> ");
						scanf("%d",&game);
						
						
					}
					
					while(game == 2){
						int column;
						printf("Hangi sutuna yerlestirmek istersiniz?	");
						scanf("%d",&column);
						column = column - 1;
						
						int blocked = 0, tetri_y = 2;
						//tetrimino ne kadar aþaðý inebiliyor?
						while(blocked == 0){
							for(i=0; i<3; i++){
								for(j=0; j<3; j++){
									if(currentTetrimino[i][j] == 1 && board[tetri_y - 1 + i][column + j] == 1){
										blocked = 1;
									}
									if(currentTetrimino[i][j] == 1 && tetri_y - 1 + i == m){
										blocked = 1;
									}
								}
							}
							if(blocked == 0){
								tetri_y++;
							}
						}
						//tetrimino aþaðý indirme
						for(i=0; i<3; i++){
							for(j=0; j<3; j++){
								if(currentTetrimino[i][j] == 1){
									board[tetri_y - 2 + i][column + j] = currentTetrimino[i][j];
								}
							}
						}
	
						//eðer satýr 1lenmiþse sýfýrla, score'u m kadar arttýr
						for(i=0; i<m; i++){
							int line = 1;
							for(j=0; j<m; j++){
								if(board[i][j] == 0){
									line = 0;
								}
							}
							if(line == 1){
								for(j=0; j<m; j++){
									board[i][j] = 0;
								}
								for(k = i; k>0; k--){
									for(j=0; j<m; j++){
										board[k][j] = board[k-1][j];
									}
								}
								score += m;
							}
						}
						game =0;	
					}
				}
			}
		
       	}
    }
	if(choice == 3){
		printf("\nTebrikler %s! Puaniniz: %d\n",nickname,score);
		if(score>highScore){
			highScore = score;
		}
		printf("1.Ana Menu\n");		
		printf("1.Cikis\n");
		int click;
		scanf("%d",&click);
		choice = click;
	} 
	else if (choice == 2) {
            printf("Programdan cikis yapiliyor.\n");
    } 
	else {
            printf("Gecersiz bir secim yaptiniz. Lutfen tekrar deneyin.\n");
    }

    return 0;
 }

