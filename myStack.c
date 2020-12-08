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

operatorStack *Init_operatorStack();//��ʼ�������ջ
int operatorIsEmpty(operatorStack *operator);//�ж������ջ�Ƿ�Ϊ��
int Push_operatorStack(operatorStack *operator, char data);//�����������ջ��
char Pop_operatorStack(operatorStack *operator);//��ջ��Ԫ���Ƴ�
char Top_operatorStack(operatorStack *operator);//��ȡջ��Ԫ��

operandStack *Init_operandStack();//��ʼ��������ջ
int operandIsEmpty(operandStack *operand);//�ж�������ջ�Ƿ�Ϊ��
int Push_operandStack(operandStack *operand, double data);//�����������ջ��
double Pop_operandStack(operandStack *operand);//��ջ��Ԫ���Ƴ�
double Top_operandStack(operandStack *operand);//��ȡջ��Ԫ��

double operation(double a, double b, char operator);//������������������
int Judge_operator(char top);//�ж�������ĸ�����ȼ�
void start(operatorStack *operator, operandStack *operand, char str[]);//���㿪ʼ

int main() {
    char str[100] = "2/2";
    operatorStack *operator = Init_operatorStack();
    operandStack *operand = Init_operandStack();
    start(operator, operand, str);

}

//��ʼ��ջ
operatorStack *Init_operatorStack() {
    operatorStack *operator = (operatorStack *) malloc(sizeof(operatorStack));
    if (operator == NULL) {
        printf("�����ջ����ʧ�ܣ�����ֹͣ����");
        exit(1);
    }
    operator->top = 0;
    return operator;
}

//�ж������ջ�Ƿ�Ϊ��
int operatorIsEmpty(operatorStack *operator) {
    if (operator->top == 0) return 1;
    else return 0;
}

//�����������ջ�У����ж�ջ�Ƿ�������
int Push_operatorStack(operatorStack *operator, char data) {
    if (operator->top == STACK_INIT_SIZE) return 0;
    else operator->data[operator->top++] = data;
    return 1;
}

//��ջ��Ԫ���Ƴ�
char Pop_operatorStack(operatorStack *operator) {
    char aimChar;
    if (operatorIsEmpty(operator)) {
        printf("�����ջ�ѿգ�����ֹͣ����");
        exit(1);
    } else {
        aimChar = operator->data[--operator->top];
    }
    return aimChar;
}

//��ȡջ��Ԫ��
char Top_operatorStack(operatorStack *operator) {
    char aimChar;
    if (operatorIsEmpty(operator)) {
        printf("ջ�ѿ�");
        exit(1);
    } else {
        aimChar = operator->data[operator->top - 1];
    }
    return aimChar;
}

//��ʼ�������ջ
operandStack *Init_operandStack() {
    operandStack *operand = (operandStack *) malloc(sizeof(operandStack));
    if (operand == NULL) {
        printf("����ʧ��");
        exit(1);
    }
    operand->top = 0;
    return operand;
}

//�ж�������ջ�Ƿ�Ϊ��
int operandIsEmpty(operandStack *operand) {
    if (operand->top == 0) return 1;
    else return 0;
}

//�����������ջ��
int Push_operandStack(operandStack *operand, double data) {
    if (operand->top == STACK_INIT_SIZE) {
        printf("ջ�����޷����");
        return 0;
    }
    operand->data[operand->top++] = data;
    return 1;
}

//��ջ��Ԫ���Ƴ�
double Pop_operandStack(operandStack *operand) {
    double aimData;
    if (operandIsEmpty(operand)) {
        printf("������ջΪ�գ�����ֹͣ����");
        exit(1);
    }
    aimData = operand->data[--operand->top];
    return aimData;
}

//��ȡջ��Ԫ��
double Top_operandStack(operandStack *operand) {
    double aimData;
    if (operandIsEmpty(operand)) {
        printf("ջΪ��");
        exit(1);
    }
    aimData = operand->data[operand->top - 1];
    return aimData;
}

//��������������
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

//�ж���������������ȼ�
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

//���㿪ʼ
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
                //���������������ȵĻ����պ���ĵͼ���������
                if (operatorIsEmpty(operator) || Judge_operator(Top_operatorStack(operator)) <
                                                 Judge_operator(str[i])) {
                    Push_operatorStack(operator, str[i]);
                } else {
                    //ȡ������������
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //ȡ�������
                    aChar = Pop_operatorStack(operator);
                    //�������
                    a = operation(b, c, aChar);
                    //����ӽ������ջ��
                    Push_operandStack(operand, a);
                    //���ͼ��������ѹ��ջ��
                    Push_operatorStack(operator, str[i]);
                }
                break;
            case '*':
            case '/':
                if (operatorIsEmpty(operator) || Judge_operator(Top_operatorStack(operator)) <
                                                 Judge_operator(str[i])) {
                    Push_operatorStack(operator, str[i]);
                } else {
                    //ȡ������������
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //ȡ�������
                    aChar = Pop_operatorStack(operator);
                    //�������
                    a = operation(b, c, aChar);
                    //����ӽ������ջ��
                    Push_operandStack(operand, a);
                    //���ͼ��������ѹ��ջ��
                    Push_operatorStack(operator, str[i]);
                }
                break;
            case ')':
                aChar = Pop_operatorStack(operator);
                while (aChar != '(') {
                    //ȡ������������
                    b = Pop_operandStack(operand);
                    c = Pop_operandStack(operand);
                    //�������
                    a = operation(b, c, aChar);
                    //����ӽ������ջ��
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
        //ȡ������������
        b = Pop_operandStack(operand);
        c = Pop_operandStack(operand);
        //ȡ�������
        aChar = Pop_operatorStack(operator);
        //�������
        a = operation(b, c, aChar);
        //����ӽ������ջ��
        Push_operandStack(operand, a);
    }
    printf("������Ϊ��%.2lf", Pop_operandStack(operand));
}