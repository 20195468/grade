#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
typedef struct {
    char date[STACK_INIT_SIZE];
    int top;
} OperatorStack;     //操作符结构体

typedef struct {
    double date[STACK_INIT_SIZE];
    int top;
} OperandStack;     //操作数结构体

//操作符相关操作
OperatorStack *Init_OperatorStack();    //置栈空
int Empty_OperatorStack(OperatorStack *s);//判空栈
int Push_OperatorStack(OperatorStack *s, char x);//入栈(注意：判断栈是否已满)
char Pop_OperatorStack(OperatorStack *s, char x);//出栈(注意：判断栈是否已空)
char GetTop_OperatorStack(OperatorStack *s, char x);//取栈顶元素，先判空

//操作数相关操作
OperandStack *Init_OperandStack();//置栈空
int Empty_OperandStack(OperandStack *t);//判空栈
int Push_OperandStack(OperandStack *t, double y);//入栈(注意：判断栈是否已满)
double Pop_OperandStack(OperandStack *t, double y);//出栈(注意：判断栈是否已空)
double GetTop_OperandStack(OperandStack *t, double y);//取栈顶元素

//表达式求值函数
void Error(char *s);                  //错误处理函数
int Judge_operator(char top);              //用于判断字符ch是否是运算符
double Operate(double b, double a, char top);  //用于计算当前的值，并将该值返回
void Jsbds_operate(char str[]);        //读入一个简单算术表达式的值

//操作符函数实现部分
OperatorStack *Init_OperatorStack() {
    OperatorStack *s;
    s = (OperatorStack *) malloc(sizeof(OperatorStack));
    s->top = -1;
    return s;
}

int Empty_OperatorStack(OperatorStack *s)//判空栈
{
    if (s->top != -1)
        return 1;
    else
        return 0;
}

int Push_OperatorStack(OperatorStack *s, char x)//入栈(注意：判断栈是否已满)
{
    if (s->top == (STACK_INIT_SIZE - 1)) {
        return 0;
    } else
        s->date[++s->top] = x;
    return 1;

}

char Pop_OperatorStack(OperatorStack *s, char x)//出栈(注意：判断栈是否已空)
{
    if (!Empty_OperatorStack(s)) {
        return 0;
    } else
        x = s->date[s->top];
    s->top--;
    return x;
}

char GetTop_OperatorStack(OperatorStack *s, char x)//取栈顶元素，先判空
{
    if (!Empty_OperatorStack(s)) {
        return 0;
    } else
        x = s->date[s->top];
    return x;
}

//操作数函数实现部分
OperandStack *Init_OperandStack()//置栈空
{
    OperandStack *t;
    t = (OperandStack *) malloc(sizeof(OperandStack));
    t->top = -1;
    return t;
}

int Empty_OperandStack(OperandStack *t)//判空栈
{
    if (t->top != -1)
        return 1;
    else
        return 0;
}

int Push_OperandStack(OperandStack *t, double y)//入栈(注意：判断栈是否已满)
{
    if (t->top == (STACK_INIT_SIZE - 1)) {
        return 0;
    } else
        t->date[++t->top] = y;
    return 1;
}

double Pop_OperandStack(OperandStack *t, double y)//出栈(注意：判断栈是否已空)
{
    if (!Empty_OperandStack(t)) {
        return 0;
    } else
        y = t->date[t->top];
    t->top--;
    return y;
}

double GetTop_OperandStack(OperandStack *t, double y)//取栈顶元素
{
    if (!Empty_OperandStack(t)) {
        return 0;
    }
    y = t->date[t->top];
    return y;
}

//表达式求值函数实现
void Error(char *s)   //错误处理函数
{
    printf("%s\n", s);
    exit(1);
}

int Judge_operator(char top)//用于判断字符ch是否是运算符
{
    int x;
    switch (top) {
        case '+':
        case '-':
            x = 1;
            break;
        case '*':
        case '/':
            x = 2;
            break;
    }
    return x;
}

double Operate(double b, double a, char top)  //用于计算当前的值，并将该值返回
{
    double c = 0;
    switch (top) {
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

void Jsbds_operate(char str[])             //读入一个简单算术表达式,并将计算结果返回到主函数
{
    OperatorStack *operator = Init_OperatorStack();     //初始化操作符栈
    OperandStack *operand = Init_OperandStack();     //初始化操作数栈
    int i, j;                               //i,j为循环变量，a,b接收从操作数栈中出栈的元素
    double f;                               //接收将字符数转换为浮点数的值
    double a = 0;
    double b = 0;
    double c = 0;
    char d[100];                           //储存字符串中连续的‘数’
    char top = 0;                          //接收从操作符栈中出栈的元素
    for (i = 0; str[i]; i++)               //将字符串中的元素按顺序入到栈中
    {
        switch (str[i]) {
            case '+':
            case '-':
                /*先判断当前运算符与操作符栈栈顶元素的优先级，如果高于栈顶元素，则入栈；
                小于栈顶元素，则从操作数栈中依次出两个数，并将操作符栈中栈顶元素出栈，
                再将从操作数栈中出的两个数，按从操作符栈栈中出的运算符运算，
                并将结果压入操作数栈中，再将当前的操作符压入操作符栈中。*/
                if (!Empty_OperatorStack(operator))  //当操作符栈为空的时候压栈保存,此时不需要判断谁的优先级比较大
                {
                    Push_OperatorStack(operator, str[i]);
                } else {
                    a = Pop_OperandStack(operand, a); //接收从操作数栈中出栈的元素
                    b = Pop_OperandStack(operand, b); //接收从操作数栈中出栈的元素
                    top = Pop_OperatorStack(operator, top);//接收从操作符栈中出栈的元素
                    c = Operate(b, a, top);
                    Push_OperandStack(operand, c);
                    //将计算后的值压入操作数栈中
                    Push_OperatorStack(operator, str[i]);
                }
                break;
            case '*':
            case '/':
                if ((!Empty_OperatorStack(operator)) || (Judge_operator(str[i]) > Judge_operator(
                        GetTop_OperatorStack(operator, top)))) { //当操作符栈为空或者该操作符的优先级大于栈顶元素的优先级是入栈保存
                    Push_OperatorStack(operator, str[i]);
                } else {
                    a = Pop_OperandStack(operand, a);//接收从操作数栈中出栈的元素
                    b = Pop_OperandStack(operand, b);//接收从操作数栈中出栈的元素
                    top = Pop_OperatorStack(operator, top);//接收从操作符栈中出栈的元素
                    c = Operate(b, a, top);
                    Push_OperandStack(operand, c);
                    //将计算后的值压入操作数栈中
                    Push_OperatorStack(operator, str[i]);
                }
            case '\0':
                break;
            default:
                j = 0;
                do {
                    d[j++] = str[i];
                    i++;
                } while (str[i] >= '0' && str[i] <= '9');  //可存入一个或多个数字字符
                d[j] = '\0';                  //将输入的连续多个数字字符拼成了字符串
                i--;
                f = atof(d);                //调用库函数atoi()将字符数转换为浮点数
                Push_OperandStack(operand, f);    //将转换后的数压入操作数栈中
                break;
        }
    }
    while (Empty_OperatorStack(operator))  //当操作符栈不为空的时候执行
    {
        a = Pop_OperandStack(operand, a);//接收从操作数栈中出栈的元素
        b = Pop_OperandStack(operand, b);//接收从操作数栈中出栈的元素
        top = Pop_OperatorStack(operator, top);//接收从操作符栈中出栈的元素
        c = Operate(b, a, top);
        Push_OperandStack(operand, c);
        //将计算后的值压入操作数栈中
    }
    printf("该表达式的计算结果为：\n");
    printf("%lf", GetTop_OperandStack(operand, c));//将操作数栈中的元素(即表达式的最终结果)打印出来
}

int main() {
    char str[100]="2*8+3";
    printf("请输入算术表达式(功能：+，-，*，/)\n");
    printf("%s", str);
    Jsbds_operate(str);
    return 0;
}
