#include <stdio.h>

#include <stdarg.h>


void print_dcs(char *dcs, ...)

{

va_list ap;    //가변 인자 목록을 ap에 담을 것이다.

    size_t i = 0;


    va_start(ap, dcs);//dcs라는 문자열의 개수 만큼 ap가 이동할 것.


    // printf("sizeof(char): %d\n", sizeof(char));


    while (dcs[i] != '\0')

    {

    if (dcs[i] == 'd')

        printf("%d ", va_arg(ap, int));


        // gcc에서는 char 형 문자일 때 va_arg 매크로에 char 형 대신에 int를 사용해야 합니다.


        if (dcs[i] == 'c')

        printf("%c ", va_arg(ap, int)); // printf("%c ", va_arg(ap, int)) -> Is this correct?

        if  (dcs[i] == 's')

        printf("%s ", va_arg(ap, char *));

        i++;

    }

    va_end(ap);     //ap가 NULL을 가리키도록 만든다.

                    //end는 안정성을 위해 써주도록 한다.

    printf("\n");

}


int main()

{

    print_dcs("d", 10);                    // 정수

    print_dcs("dc", 10, 'a');              // 정수, 문자

    print_dcs("dcs", 10, 'a', "Hello42");  // 정수, 문자, 문자열


    return (0);

}
