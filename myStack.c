#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_INIT_SIZE 100
typedef struct operatorStack {
    char data[STACK_INIT_SIZE];
    int top;
} operatorStack;

typedef struct operandStack {
    double data[STACK_INIT_SIZE];
    int top;
} operandStack;

operatorStack *Init_operatorStack();//初始化运算符栈
int operatorIsEmpty(operatorStack *operator);//判断运算符栈是否为空
int Push_operatorStack(operatorStack *operator, char data);//将运算符推入栈中
char Pop_operatorStack(operatorStack *operator);//将栈顶元素推出
char Top_operatorStack(operatorStack *operator);//获取栈顶元素

operandStack *Init_operandStack();//初始化运算数栈
int operandIsEmpty(operandStack *operand);//判断运算数栈是否为空
int Push_operandStack(operandStack *operand, double data);//将运算符推入栈中
double Pop_operandStack(operandStack *operand);//将栈顶元素推出
double Top_operandStack(operandStack *operand);//获取栈顶元素

double operation(double a, double b, char operator);//两个操作数进行运算
int Judge_operator(char top);//判断两个字母的优先级
void start(operatorStack *operator, operandStack *operand, char str[]);//运算开始

int main() {
    char str[100] = "2/2";
    operatorStack *operator = Init_operatorStack();
    operandStack *operand = Init_operandStack();
    start(operator, operand, str);

}

//初始化栈
operatorStack *Init_operatorStack() {
    operatorStack *operator = (operatorStack *) malloc(sizeof(operatorStack));
    if (operator == NULL) {
        printf("运算符栈创建失败，程序停止运行");
        exit(1);
    }
    operator->top = 0;
    return operator;
}

//判断运算符栈是否为空
int operatorIsEmpty(operatorStack *operator) {
    if (operator->top == 0) return 1;
    else return 0;
}

//将运算符推入栈中（先判断栈是否已满）
int Push_operatorStack(operatorStack *operator, char data) {
    if (operator->top == STACK_INIT_SIZE) return 0;
    else operator->data[operator->top++] = data;
    return 1;
}

//将栈顶元素推出
char Pop_operatorStack(operatorStack *operator) {
    char aimChar;
    if (operatorIsEmpty(operator)) {
        printf("运算符栈已空，程序停止运行");
        exit(1);
    } else {
        aimChar = operator->data[--operator->top];
    }
    return aimChar;
}

//获取栈顶元素
char Top_operatorStack(operatorStack *operator) {
    char aimChar;
    if (operatorIsEmpty(operator)) {
        printf("栈已空");
        exit(1);
    } else {
        aimChar = operator->data[operator->top - 1];
    }
    return aimChar;
}

//初始化运算符栈
operandStack *Init_operandStack() {
    operandStack *operand = (operandStack *) malloc(sizeof(operandStack));
    if (operand == NULL) {
        printf("创建失败");
        exit(1);
    }
    operand->top = 0;
    return operand;
}

//判断运算数栈是否为空
int operandIsEmpty(operandStack *operand) {
    if (operand->top == 0) return 1;
    else return 0;
}

//将运算符推入栈中
int Push_operandStack(operandStack *operand, double data) {
    if (operand->top == STACK_INIT_SIZE) {
        printf("栈已满无法添加");
        return 0;
    }
    operand->data[operand->top++] = data;
    return 1;
}

//将栈顶元素推出
double Pop_operandStack(operandStack *operand) {
    double aimData;
    if (operandIsEmpty(operand)) {
        printf("运算数栈为空，程序停止运行");
        exit(1);
    }
    aimData = operand->data[--operand->top];
    return aimData;
}

//获取栈顶元素
double Top_operandStack(operandStack *operand) {
    double aimData;
    if (operandIsEmpty(operand)) {
        printf("栈为空");
        exit(1);
    }
    aimData = operand->data[operand->top - 1];
    return aimData;
}

//计算两个操作数
double operation(double a, double b, char operator) {
    double c = 0;
    switch (operator) {
        case '+':
            c = b + a;
            break;
        case '-':
            c = b - a;
            break;
        case '*':
            c = b * a;
            break;
        case '/':
            if (a == 0) {
                printf("分母为零!\n");
                return 0;
            } else
                c = b / a;
            break;
        default:
            printf("输入的字符非法!\n");
            break;
    }
    return c;
}

//判断两个运算符的优先级
int Judge_operator(char top) {
    int x = 0;
    switch (top) {
        case '(':
            x = 0;
            break;
        case '+':
        case '-':
            x = 1;
            break;
        case '*':
        case '/':
            x = 2;
            break;
        case ')':
            x = 3;
            break;
    }
    return x;
}

//运算开始
void start(operatorStack *operator, operandStack *operand, char str[]) {
    double a = 0, b = 0, c = 0, d = 0;
    char aChar, operandChar[strlen(str)];
    int count;
    for (int i = 0; str[i]; ++i) {
        switch (str[i]) {
            case '(':
                Push_operatorStack(operator, str[i]);
                break;
            case '+':
            case '-':
                //这里运算符级别相等的话按照后面的低级进行运算
                if (operatorIsEmpty(operator) || Judge_operator(Top_operatorStack(operator)) <
                                                 Judge_operator(str[i])) {
                    Push_operatorStack(operator, str[i]);
                } else {
                    //取出两个运算数
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //取出运算符
                    aChar = Pop_operatorStack(operator);
                    //二者相加
                    a = operation(b, c, aChar);
                    //将相加结果推入栈中
                    Push_operandStack(operand, a);
                    //将低级的运算符压入栈中
                    Push_operatorStack(operator, str[i]);
                }
                break;
            case '*':
            case '/':
                if (operatorIsEmpty(operator) || Judge_operator(Top_operatorStack(operator)) <
                                                 Judge_operator(str[i])) {
                    Push_operatorStack(operator, str[i]);
                } else {
                    //取出两个运算数
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //取出运算符
                    aChar = Pop_operatorStack(operator);
                    //二者相加
                    a = operation(b, c, aChar);
                    //将相加结果推入栈中
                    Push_operandStack(operand, a);
                    //将低级的运算符压入栈中
                    Push_operatorStack(operator, str[i]);
                }
                break;
            case ')':
                aChar = Pop_operatorStack(operator);
                while (aChar != '(') {
                    //取出两个运算数
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //二者相加
                    a = operation(b, c, aChar);
                    //将相加结果推入栈中
                    Push_operandStack(operand, a);
                    aChar = Pop_operatorStack(operator);
                }
                break;
            case '\0':
                break;
            default:
                count = 0;
                do {
                    operandChar[count++] = str[i++];
                } while (str[i] >= '0' && str[i] <= '9');
                operandChar[count] = '\0';
                i--;
                d = strtod(operandChar, NULL);
                Push_operandStack(operand, d);
                break;
        }
    }
    while (!operatorIsEmpty(operator)) {
        //取出两个运算数
        b = Pop_operandStack(operand);
        c = Pop_operandStack(operand);
        //取出运算符
        aChar = Pop_operatorStack(operator);
        //二者相加
        a = operation(b, c, aChar);
        //将相加结果推入栈中
        Push_operandStack(operand, a);
    }
    printf("运算结果为：%.2lf", Pop_operandStack(operand));
}