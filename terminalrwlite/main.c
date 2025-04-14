#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ssu_setbuf(FILE *fp, char *buf) {
    size_t size;
    int fd;
    int mode;

	// 파일 포인터로부터 파일 디스크립터를 뽑아내는 함수
    fd = fileno(fp);

	// 터미널인지 확인해주는 함수
    if (isatty(fd))
		// 터미널인 경우 라인 버퍼
        mode = _IOLBF;
    else
		// 아닌 경우 풀 버퍼
        mode = _IOFBF;

	// buf 인자가 널인 경우
    if (buf == NULL) {
		// 넌 버퍼 모드
        mode = _IONBF;
        size = 0;
    }
    else
        size = BUFSIZ;

	// 버퍼 설정
    setvbuf(fp, buf, mode, size);
}

int main(int argc, char *argv[]) {
    char buf[BUFSIZ];
    FILE *fp;

	// argv[1] 에 다른 터미널의 터미널 파일 아이디를 넣을 것입니다.
    if ((fp = fopen("/dev/pts/1", "w")) == NULL) {
        fprintf(stderr, "file open error\n");
        exit(1);
    }

	// 따라서 setbuf 를 하면 isatty 에서 true로 판명되고, line buffer 로 설정됩니다.
    ssu_setbuf(fp, buf);
    fprintf(fp, "Hello, ");
    sleep(1);

    fprintf(fp, "UNIX!!");
    sleep(1);

	// line buffer 이기 때문에 3초 대기 후 Hello, UNIX!!\n가 한번에 출력
    fprintf(fp, "\n");
    sleep(1);

	// None buffer로 교체
    ssu_setbuf(fp, NULL);

	// None 버퍼기 때문에 대기 없이 바로바로 출력
    fprintf(fp, "HOW");
    sleep(1);

    fprintf(fp, " ARE");
    sleep(1);

    fprintf(fp, " YOU?");
    sleep(1);

    fprintf(fp, "\n");
    sleep(1);
    exit(0);
}

/*
int main()
{
    char buf[BUFSIZ];
    FILE *fp;

    if((fp = fopen("/dev/pts/1", "w")) == NULL){
        fprintf(stderr, "file open error\n"); // use fprintf() when return error
        exit(-1);
    }

    fprintf(fp, "Hello world!\n");
    return 0;
}
*/
