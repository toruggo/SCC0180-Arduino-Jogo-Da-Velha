int current_line = 0, current_column = 0, current_player = 1, chosen, winner = -1;
int board[3][3], display_board[3][3];

int scrollButton = 2;
int selectButton = 4;

int lowerRow = 8;
int middleRow = 12;
int upperRow = 13;

int redLeft = 11;
int redCenter = 9;
int redRight = 5;

int blueLeft = 10;
int blueCenter = 6;
int blueRight = 3;

int scrollState;
int selectState;

int lastscrollState = HIGH;
int lastselectState = HIGH;

void clearLed(int position){
  if(position == 0){
  	digitalWrite(blueLeft, LOW);
  	digitalWrite(redLeft, LOW);
  }
  else if(position == 1){
  	digitalWrite(blueCenter, LOW);
  	digitalWrite(redCenter, LOW);
  }
  else if(position == 2){
  	digitalWrite(blueRight, LOW);
  	digitalWrite(redRight, LOW);
  }
}

void lineSwapper(int x0, int x1, int x2)
{
  if(x0)
  {
  	digitalWrite(upperRow, LOW);
  }
  else
  {
  	digitalWrite(upperRow, HIGH);
  }
  if(x1)
  {
  	digitalWrite(middleRow, LOW);
  }
  else
  {
  	digitalWrite(middleRow, HIGH);
  }
  if(x2)
  {
  	digitalWrite(lowerRow, LOW);
  }
  else
  {
  	digitalWrite(lowerRow, HIGH);
  }
}
  
void updateLed(int row, int led0, int led1, int led2){
  if(row == 0) lineSwapper(1,0,0);
  else if(row == 1) lineSwapper(0,1,0);
  else if(row == 2) lineSwapper(0,0,1);
  
  if(led0 == 0){
   	// nao liga
    clearLed(0);
  }
  else if(led0 == 1){
   	// liga player 1
    digitalWrite(redLeft, LOW);
    digitalWrite(blueLeft, HIGH);
  }
  else if(led0 == 2){
   	 // liga player 1
    digitalWrite(redLeft, HIGH);
    digitalWrite(blueLeft, LOW);
  }
  else if(led0 == 3){
    digitalWrite(redRight, HIGH);
    digitalWrite(blueRight, HIGH);
  }
  
  if(led1 == 0){
   	// nao liga
    clearLed(1);
  }
  else if(led1 == 1){
   	// liga player 1
    digitalWrite(redCenter, LOW);
    digitalWrite(blueCenter, HIGH);
  }
  else if(led1 == 2){
   	 // liga player 2
    digitalWrite(redCenter, HIGH);
    digitalWrite(blueCenter, LOW);
  }
  else if(led1 == 3){
    digitalWrite(redRight, HIGH);
    digitalWrite(blueRight, HIGH);
  }
  
  if(led2 == 0){
   	// nao liga
    clearLed(2);
  }
  else if(led2 == 1){
   	// liga player 1
    digitalWrite(redRight, LOW);
    digitalWrite(blueRight, HIGH);
  }
  else if(led2 == 2){
   	 // liga player 2
    digitalWrite(redRight, HIGH);
    digitalWrite(blueRight, LOW);
  }
  else if(led2 == 3){
    digitalWrite(redRight, HIGH);
    digitalWrite(blueRight, HIGH);
  }
  
  delay(200);
  
  clearLed(0);
  clearLed(1);
  clearLed(2);
}

void clearBoard(){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
    	board[i][j] = 0;
      	display_board[i][j] = 0;
    }
  }
}

void resetGame(){
 	clearBoard();
  	chosen = 9;
   	winner = -1;
}

int check_for_wins(int board[][3]){
	int ans = -1;

	// linhas 
	if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != 0)
	{	
		ans = board[0][0];
		clearBoard();
		display_board[0][0] = ans;
		display_board[0][1] = ans;
		display_board[0][2] = ans;
	}
	if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != 0)
	{
		ans = board[1][0];
		clearBoard();
		display_board[1][0] = ans;
		display_board[1][1] = ans;
		display_board[1][2] = ans;
	}
	if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != 0)
	{
		ans = board[2][0];
		clearBoard();
		display_board[2][0] = ans;
		display_board[2][1] = ans;
		display_board[2][2] = ans;
	}

	// colunas
	if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != 0)
	{
		ans = board[0][0];
		clearBoard();
		display_board[0][0] = ans;
		display_board[1][0] = ans;
		display_board[2][0] = ans;
	}
	if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != 0)
	{
		ans = board[0][1];
      	clearBoard();
		display_board[0][1] = ans;
		display_board[1][1] = ans;
		display_board[2][1] = ans;
	}
	if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != 0)
	{
		ans = board[0][2];
		clearBoard();
		display_board[0][2] = ans;
		display_board[1][2] = ans;
		display_board[2][2] = ans;
	}

	// diagonais
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0)
	{
		ans = board[0][0];
		clearBoard();
		display_board[0][0] = ans;
		display_board[1][1] = ans;
		display_board[2][2] = ans;
	}
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0){
		ans = board[0][2];
		clearBoard();
		display_board[0][2] = ans;
		display_board[1][1] = ans;
		display_board[2][0] = ans;
	}
	return ans;
}

void setup()
{
  Serial.begin(9600);
  chosen = 9;
  winner = 0;
  clearBoard();

  
  pinMode(scrollButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  
  pinMode(lowerRow, OUTPUT);
  pinMode(middleRow, OUTPUT);
  pinMode(upperRow, OUTPUT);
}

void loop()
{
  
  scrollState = digitalRead(scrollButton);
  selectState = digitalRead(selectButton);
  
  if(lastscrollState == 0 && scrollState == 1)
  {
    display_board[current_line][current_column] = 0;
    do{
      current_column++;
      Serial.println(current_column);
      if(current_column > 2){
        current_line++;
        current_column = 0;
      }
      if(current_line > 2){
        current_line = 0;
      }
    }
    while(board[current_line][current_column] != 0);
    
  }
  
  if(lastselectState == 0 && selectState == 1)
  {
   board[current_line][current_column] = current_player;
   
   current_player = (current_player == 1 ? 2 : 1);    
    
    do{
      current_column++;
      Serial.println(current_column);
      if(current_column > 2){
        current_line++;
        current_column = 0;
      }
      if(current_line > 2){
        current_line = 0;
      }
    }
    while(board[current_line][current_column] != 0);
  }
  
  Serial.println(current_line);
  Serial.println(current_column);
  
  winner = check_for_wins(board);
  
  if(winner == -1) display_board[current_line][current_column] = current_player;
  
	if(winner != -1){
		if(winner == 1){
			Serial.println("Jogador 1 venceu!\n");
			while(1)
			{
			     updateLed(0, display_board[0][0], display_board[0][1], display_board[0][2]);
				 updateLed(1, display_board[1][0], display_board[1][1], display_board[1][2]);
				 updateLed(2, display_board[2][0], display_board[2][1], display_board[2][2]);
			}
			resetGame();
		}
		else if(winner == 2){
			Serial.println("Jogador 2 venceu!\n");
			while(1)
			{
			     updateLed(0, display_board[0][0], display_board[0][1], display_board[0][2]);
				 updateLed(1, display_board[1][0], display_board[1][1], display_board[1][2]);
				 updateLed(2, display_board[2][0], display_board[2][1], display_board[2][2]);
			}
			resetGame();
		}
	}
	else if(chosen == 0){
		Serial.println("Empate!\n");
		while(1)
		{
			 updateLed(0, display_board[0][0], display_board[0][1], display_board[0][2]);
			 updateLed(1, display_board[1][0], display_board[1][1], display_board[1][2]);
			 updateLed(2, display_board[2][0], display_board[2][1], display_board[2][2]);
		}
		resetGame();
	}
  
  lastscrollState = scrollState;
  lastselectState = selectState;
  updateLed(0, display_board[0][0], display_board[0][1], display_board[0][2]);
  updateLed(1, display_board[1][0], display_board[1][1], display_board[1][2]);
  updateLed(2, display_board[2][0], display_board[2][1], display_board[2][2]);
  
}