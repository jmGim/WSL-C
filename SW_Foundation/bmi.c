#include <stdio.h>

int main()
{
	int cm = 0;
	double kg = 0.0;
       	double bmi = 0.0;
	printf("체중(oo.okg) : ");	
	scanf("%lf", &kg);
		
	printf("키(cm) : ");
	scanf("%d",&cm);
	
	bmi = kg / (cm*cm) * 10000;
	printf("bmi : %lf \n", bmi);

	if (bmi >= 20 && bmi < 25) {
		printf("표준입니다.");
	}
	else printf("체중관리가 필요합니다.");
	

	return 0;

}
