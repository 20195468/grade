#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
typedef struct {
    char date[STACK_INIT_SIZE];
    int top;
} OperatorStack;     //�������ṹ��

typedef struct {
    double date[STACK_INIT_SIZE];
    int top;
} OperandStack;     //�������ṹ��

//��������ز���
OperatorStack *Init_OperatorStack();    //��ջ��
int Empty_OperatorStack(OperatorStack *s);//�п�ջ
int Push_OperatorStack(OperatorStack *s, char x);//��ջ(ע�⣺�ж�ջ�Ƿ�����)
char Pop_OperatorStack(OperatorStack *s, char x);//��ջ(ע�⣺�ж�ջ�Ƿ��ѿ�)
char GetTop_OperatorStack(OperatorStack *s, char x);//ȡջ��Ԫ�أ����п�

//��������ز���
OperandStack *Init_OperandStack();//��ջ��
int Empty_OperandStack(OperandStack *t);//�п�ջ
int Push_OperandStack(OperandStack *t, double y);//��ջ(ע�⣺�ж�ջ�Ƿ�����)
double Pop_OperandStack(OperandStack *t, double y);//��ջ(ע�⣺�ж�ջ�Ƿ��ѿ�)
double GetTop_OperandStack(OperandStack *t, double y);//ȡջ��Ԫ��

//���ʽ��ֵ����
void Error(char *s);                  //��������
int Judge_operator(char top);              //�����ж��ַ�ch�Ƿ��������
double Operate(double b, double a, char top);  //���ڼ��㵱ǰ��ֵ��������ֵ����
void Jsbds_operate(char str[]);        //����һ�����������ʽ��ֵ

//����������ʵ�ֲ���
OperatorStack *Init_OperatorStack() {
    OperatorStack *s;
    s = (OperatorStack *) malloc(sizeof(OperatorStack));
    s->top = -1;
    return s;
}

int Empty_OperatorStack(OperatorStack *s)//�п�ջ
{
    if (s->top != -1)
        return 1;
    else
        return 0;
}

int Push_OperatorStack(OperatorStack *s, char x)//��ջ(ע�⣺�ж�ջ�Ƿ�����)
{
    if (s->top == (STACK_INIT_SIZE - 1)) {
        return 0;
    } else
        s->date[++s->top] = x;
    return 1;

}

char Pop_OperatorStack(OperatorStack *s, char x)//��ջ(ע�⣺�ж�ջ�Ƿ��ѿ�)
{
    if (!Empty_OperatorStack(s)) {
        return 0;
    } else
        x = s->date[s->top];
    s->top--;
    return x;
}

char GetTop_OperatorStack(OperatorStack *s, char x)//ȡջ��Ԫ�أ����п�
{
    if (!Empty_OperatorStack(s)) {
        return 0;
    } else
        x = s->date[s->top];
    return x;
}

//����������ʵ�ֲ���
OperandStack *Init_OperandStack()//��ջ��
{
    OperandStack *t;
    t = (OperandStack *) malloc(sizeof(OperandStack));
    t->top = -1;
    return t;
}

int Empty_OperandStack(OperandStack *t)//�п�ջ
{
    if (t->top != -1)
        return 1;
    else
        return 0;
}

int Push_OperandStack(OperandStack *t, double y)//��ջ(ע�⣺�ж�ջ�Ƿ�����)
{
    if (t->top == (STACK_INIT_SIZE - 1)) {
        return 0;
    } else
        t->date[++t->top] = y;
    return 1;
}

double Pop_OperandStack(OperandStack *t, double y)//��ջ(ע�⣺�ж�ջ�Ƿ��ѿ�)
{
    if (!Empty_OperandStack(t)) {
        return 0;
    } else
        y = t->date[t->top];
    t->top--;
    return y;
}

double GetTop_OperandStack(OperandStack *t, double y)//ȡջ��Ԫ��
{
    if (!Empty_OperandStack(t)) {
        return 0;
    }
    y = t->date[t->top];
    return y;
}

//���ʽ��ֵ����ʵ��
void Error(char *s)   //��������
{
    printf("%s\n", s);
    exit(1);
}

int Judge_operator(char top)//�����ж��ַ�ch�Ƿ��������
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

double Operate(double b, double a, char top)  //���ڼ��㵱ǰ��ֵ��������ֵ����
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
                printf("��ĸΪ��!\n");
                return 0;
            } else
                c = b / a;
            break;
        default:
            printf("������ַ��Ƿ�!\n");
            break;
    }
    return c;
}

void Jsbds_operate(char str[])             //����һ�����������ʽ,�������������ص�������
{
    OperatorStack *operator = Init_OperatorStack();     //��ʼ��������ջ
    OperandStack *operand = Init_OperandStack();     //��ʼ��������ջ
    int i, j;                               //i,jΪѭ��������a,b���մӲ�����ջ�г�ջ��Ԫ��
    double f;                               //���ս��ַ���ת��Ϊ��������ֵ
    double a = 0;
    double b = 0;
    double c = 0;
    char d[100];                           //�����ַ����������ġ�����
    char top = 0;                          //���մӲ�����ջ�г�ջ��Ԫ��
    for (i = 0; str[i]; i++)               //���ַ����е�Ԫ�ذ�˳���뵽ջ��
    {
        switch (str[i]) {
            case '+':
            case '-':
                /*���жϵ�ǰ������������ջջ��Ԫ�ص����ȼ����������ջ��Ԫ�أ�����ջ��
                С��ջ��Ԫ�أ���Ӳ�����ջ�����γ�������������������ջ��ջ��Ԫ�س�ջ��
                �ٽ��Ӳ�����ջ�г��������������Ӳ�����ջջ�г�����������㣬
                �������ѹ�������ջ�У��ٽ���ǰ�Ĳ�����ѹ�������ջ�С�*/
                if (!Empty_OperatorStack(operator))  //��������ջΪ�յ�ʱ��ѹջ����,��ʱ����Ҫ�ж�˭�����ȼ��Ƚϴ�
                {
                    Push_OperatorStack(operator, str[i]);
                } else {
                    a = Pop_OperandStack(operand, a); //���մӲ�����ջ�г�ջ��Ԫ��
                    b = Pop_OperandStack(operand, b); //���մӲ�����ջ�г�ջ��Ԫ��
                    top = Pop_OperatorStack(operator, top);//���մӲ�����ջ�г�ջ��Ԫ��
                    c = Operate(b, a, top);
                    Push_OperandStack(operand, c);
                    //��������ֵѹ�������ջ��
                    Push_OperatorStack(operator, str[i]);
                }
                break;
            case '*':
            case '/':
                if ((!Empty_OperatorStack(operator)) || (Judge_operator(str[i]) > Judge_operator(
                        GetTop_OperatorStack(operator, top)))) { //��������ջΪ�ջ��߸ò����������ȼ�����ջ��Ԫ�ص����ȼ�����ջ����
                    Push_OperatorStack(operator, str[i]);
                } else {
                    a = Pop_OperandStack(operand, a);//���մӲ�����ջ�г�ջ��Ԫ��
                    b = Pop_OperandStack(operand, b);//���մӲ�����ջ�г�ջ��Ԫ��
                    top = Pop_OperatorStack(operator, top);//���մӲ�����ջ�г�ջ��Ԫ��
                    c = Operate(b, a, top);
                    Push_OperandStack(operand, c);
                    //��������ֵѹ�������ջ��
                    Push_OperatorStack(operator, str[i]);
                }
            case '\0':
                break;
            default:
                j = 0;
                do {
                    d[j++] = str[i];
                    i++;
                } while (str[i] >= '0' && str[i] <= '9');  //�ɴ���һ�����������ַ�
                d[j] = '\0';                  //�������������������ַ�ƴ�����ַ���
                i--;
                f = atof(d);                //���ÿ⺯��atoi()���ַ���ת��Ϊ������
                Push_OperandStack(operand, f);    //��ת�������ѹ�������ջ��
                break;
        }
    }
    while (Empty_OperatorStack(operator))  //��������ջ��Ϊ�յ�ʱ��ִ��
    {
        a = Pop_OperandStack(operand, a);//���մӲ�����ջ�г�ջ��Ԫ��
        b = Pop_OperandStack(operand, b);//���մӲ�����ջ�г�ջ��Ԫ��
        top = Pop_OperatorStack(operator, top);//���մӲ�����ջ�г�ջ��Ԫ��
        c = Operate(b, a, top);
        Push_OperandStack(operand, c);
        //��������ֵѹ�������ջ��
    }
    printf("�ñ��ʽ�ļ�����Ϊ��\n");
    printf("%lf", GetTop_OperandStack(operand, c));//��������ջ�е�Ԫ��(�����ʽ�����ս��)��ӡ����
}

int main() {
    char str[100]="2*8+3";
    printf("�������������ʽ(���ܣ�+��-��*��/)\n");
    printf("%s", str);
    Jsbds_operate(str);
    return 0;
}
