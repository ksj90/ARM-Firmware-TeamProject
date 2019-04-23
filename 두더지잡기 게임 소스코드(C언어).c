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
		my_get_byte(); //����Ʈ ���� ���� �Է�  
		Uart_Printf("start!\n\n");
		
		for(count = 0; count < 30; count++) //30�� �ݺ�  
		{
			ran = rand()%4 + 1; //1���� 4���� ����(�� ��° LED�� ������ ����) 
			Uart_Printf("%d", ran);
			
			start_game(ran); //���� ���� �Լ�(�� �Լ��� ȣ��� �� ran�� ����) 
			button = go(); //�� ��° ��ư�� ���ȴ����o ���� ������� button�̶�� ������ �Է� 
			
			if(ran == button) //�������� ���� LED ��ȣ�� ���� ��ư ��ȣ�� ��ġ�ϸ� 
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
