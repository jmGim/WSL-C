# 주소값 출력 error 
## %x -> %p
- printf("  %x\n\n", *(ppArr2D + i));
-- wsl 포인터 크기 : 8byte 
-- %x 자료형 크기 : 4byte(정수 32bit)
-- 자료형을 다르게 판단하여 warning 출력
- printf("  %p\n\n", (void *)*(ppArr2D + i));
