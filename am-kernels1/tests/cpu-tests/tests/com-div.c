#include <trap.h>
#include <stdio.h>//头文件 

/* 最大公约数和最小公倍数 */
static const  int ans_table[] =
{
1000,
1,
2,
1,
4,
5,
2,
1,
8,
1,
10,
1,
4,
1,
2,
5,
8,
1,
2,
1,
20,
1,
2,
73,
8,
25,
2,
1,
4,
1,
10,
1,
8,
1,
2,
5,
4,
1,
2,
1,
40,
1,
2,
1,
4,
5,
2,
1,
8,
1,
50,
1,
4,
1,
2,
5,
8,
1,
2,
1,
20,
1,
2,
1,
8,
5,
2,
1,
4,
1,
10,
1,
8,
1,
2,
25,
4,
1,
2,
1,
40,
1,
2,
1,
4,
5,
2,
1,
8,
1,
10,
1,
4,
1,
2,
5,
584,
1,
2,
1
};

int calculate(int num1, int num2) {
    int temp;
    while (num2 != 0) // 余数不为0，继续相除，直到余数为0 
    {
        temp = num1 % num2;
        num1 = num2;
        num2 = temp;
    }
    return num1;
}

#define COUNT 100

void gendata(void) {
    int a = 5000;
    int b = 3000;
    printf("static const  int ans_table[] =\n{\n");
    for (int i = 0; i < COUNT; i++) {
        int t = calculate(a, b);
        printf("%d", t);
        if (i + 1 < COUNT)
            putchar(',');
        putchar('\n');
        a = a + 100;
        b = b + 133;
    }
    printf("};\n");
}

void testdata(void) {
    int a = 5000;
    int b = 3000;
    int i;
    for (i = 0; i < COUNT; i++) {
        int t = calculate(a, b);
        check(t == ans_table[i]);
        // if (t == ans_table[i]) {
        //     printf("ok\n");
        // }
        // else {
        //     printf("err\n");
        // }
        a = a + 100;
        b = b + 133;
    }
    check(i == COUNT);
}

int main()//主函数 
{
    testdata();
    //gendata();
}