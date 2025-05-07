#include <stdio.h>

#include <stdarg.h>


void print_digit(int args, ...)

{

    va_list ap;                     // 가변 변수들을 가리킬 포인터이다.


    va_start(ap, args);             // ap라는 포인터가 args만큼

                                    // 가변 변수들을 차례로 가리키게 만듬

    for (int i = 0 ; i < args; i++)

    {

        int num = va_arg(ap, int);

        // 윗줄에서 va_arg는 int byte만큼 포인터를 이동시키면서 읽은 정보를 반환함.


        printf("%d ", num); // 이 함수는 인자로 들어온 정수를 출력한다.

    }

    va_end(ap);

    printf("\n");

}


int main()

{

    print_digit(1, 10);

    print_digit(2, 10, 20);

    print_digit(3, 10, 20, 30);


    return (0);

}
