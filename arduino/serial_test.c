#include <stdio.h>
#include <string.h>
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h>  // UNIX standard function definitions

int main() {
    // 1. 포트 열기 (O_RDWR: 읽기/쓰기, O_NOCTTY: 터미널 제어 안함)
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("포트 열기 실패: %s\n", strerror(errno));
        return -1;
    }

    // 2. 시리얼 포트 설정
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        printf("tcgetattr 에러: %s\n", strerror(errno));
        return -1;
    }

    // 통신 속도 설정 (Baudrate: 115200)
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    // 8N1 설정
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_cflag &= ~PARENB;                     // No parity
    tty.c_cflag &= ~CSTOPB;                     // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                    // No hardware flow control
    tty.c_cflag |= (CLOCAL | CREAD);            // Enable receiver, ignore modem control lines

    // Raw 모드 설정 (특수 문자 처리 비활성화)
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;

    // 타임아웃 설정 (1초 대기 후 리턴)
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 10; 

    // 설정 적용
    tcsetattr(fd, TCSANOW, &tty);

    // 3. 데이터 쓰기 (Tx)
    char msg[] = "Hello Serial from WSL!\r\n";
    write(fd, msg, sizeof(msg) - 1);

    // 4. 데이터 읽기 (Rx)
    char buf[256];
    memset(&buf, '\0', sizeof(buf));
    int n = read(fd, &buf, sizeof(buf));
    
    if (n > 0) {
        printf("수신된 데이터: %s\n", buf);
    } else if (n < 0) {
        printf("읽기 에러: %s\n", strerror(errno));
    } else {
        printf("수신 대기 시간 초과.\n");
    }

    // 5. 포트 닫기
    close(fd);
    return 0;
}
