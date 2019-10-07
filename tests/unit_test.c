#include "../header/headers.h"

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
    char* test1;
    char* test2;

    test1 =  malloc(sizeof(char) * 1024);
    test2 =  malloc(sizeof(char) * 128);


    // char* test[1000];
    // int i;
    //
    // for (i = 0; i < 998; ++i) {
    //     printf("\n %d \n", i);
    //     test[i] = malloc(sizeof(char) * 14);
    //
    //     strcat(test[i], "14 characters");
    //     // printf(" test[%d] = %s", i, test[i]);
    // }
    //
    // for (i = 0; i < 998; ++i) {
    //     free(test[i]);
    // }
    free(test1);
    free(test2);

    test1 =  malloc(sizeof(char) * 16);

    free(test1);

    //test2 =  malloc(sizeof(char) * 128);

    char* test3 =  malloc(sizeof(char) * 5);
    free(test3); //invalid pointer

    char* test31 =  malloc(sizeof(char) * 16);
    char* test32 =  malloc(sizeof(char) * 16);
    char* test33 =  malloc(sizeof(char) * 8);

    free(test31);
    free(test33);

    test32 =  malloc(sizeof(char) * 16);
    test33 =  malloc(sizeof(char) * 16);

    char* test4 =  malloc(sizeof(char) * 889);
    char* test5 =  malloc(sizeof(char) * 124);
    char* test6 =  malloc(sizeof(char) * 1024);
    char* test7 =  malloc(sizeof(char) * 22);
    char* test8 =  malloc(sizeof(char) * 502);
    char* test9 =  malloc(sizeof(char) * 105);
    char* test10 =  malloc(sizeof(char) * 78);
    char* test11 =  malloc(sizeof(char) * 128);
    char* test12 =  malloc(sizeof(char) * 2021);
    test6 =  malloc(sizeof(char) * 14);
    char* test13 =  malloc(sizeof(char) * 4);
    free(test13);
    test6 =  malloc(sizeof(char) * 15);
    free(test6);
    return 0;
}
