#include <stdio.h>
#include <time.h>

void Main()
{
	int ran, count, button, correct; 
	correct = 0; 
	Uart_Printf("Welcome to My Game\n");
	
	while(1) 
	{
		Uart_Printf("Press any key.....\n");
		my_get_byte(); //바이트 단위 문자 입력  
		Uart_Printf("start!\n\n");
		
		for(count = 0; count < 30; count++) //30번 반복  
		{
			ran = rand()%4 + 1; //1부터 4까지 난수(몇 번째 LED가 켜질지 결정) 
			Uart_Printf("%d", ran);
			
			start_game(ran); //게임 시작 함수(이 함수가 호출될 때 ran값 전달) 
			button = go(); //몇 번째 버튼이 눌렸는지엗 대한 결과값을 button이라는 변수에 입력 
			
			if(ran == button) //랜덤으로 켜진 LED 번호와 누른 버튼 번호가 일치하면 
			{
				Uart_Printf("Right!\n");
				correct += 1;
			}
			else
			{
				Uart_Printf("Wrong!\n");
			}
			Uart_Printf("correct : %d , Wrong : %d\n", correct, 30 - correct);
		}
	}	
} 
