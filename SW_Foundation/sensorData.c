#include <stdio.h>

int main()
{
        char SDR[30] = "=== Sensor Data Report ===";
	char LINE[30] = "===========================";
	char ID[10];
	char TEMP[10];
	char HUMI[10];
	char INPUT[40] = "ID:101;TEMP:25;HUMI:60";

	int id = 0 , temp = 0, humi = 0;


	sscanf(INPUT, "%*[^:]:%d;%*[^:]:%d;%*[^:]:%d", &id, &temp,&humi );

	printf("%s\n", SDR);
	printf("Device ID : %d\n", id);
	printf("Temperature : %d C \n", temp);
	printf("Humidity : %d %% \n", humi);
	printf("%s\n", LINE);
	
        return 0;

}                           
