#ifndef GRADE_QUEUE_H
#define GRADE_QUEUE_H

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int QelemType;
typedef struct {
    QelemType *base;
    int front;
    int rear;
} squene;

//初始化队列
squene *InitQuene() {
    squene *s = NULL;
    s->base = (QelemType *) malloc(MAXSIZE * sizeof(QelemType));
    if (!s->base) {
        printf("队列初始化创建失败\n");
        exit(-1);
    }
    s->front = 0;
    s->rear = 0;
}

//进入队列
void enQuene(squene *s, QelemType e) {
    //队尾指针加一对最大值取余 若和队头指针相等则队已满
    if ((s->rear + 1) % MAXSIZE == s->front) {
        printf("队列已满\n");
        exit(1);
    }
    s->base[s->rear] = e;
    s->rear = (s->rear + 1) % MAXSIZE;
}

//出队列
void deQuene(squene *s, QelemType e) {
    //队尾和对头相等则为空
    if (s->rear == s->front) {
        printf("栈空");
        exit(-1);
    }
    e = s->base[s->front];
    s->front = (s->front + 1) % MAXSIZE;
}

//队列当前长度
int length(squene *s) {
    //避免队尾指针在对头前
    return (s->rear - s->front + MAXSIZE) % MAXSIZE;
}

int main() {
    squene *s = NULL;
    s = InitQuene();
    int m, n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        enQuene(s, m);
    }
    printf("%d", length(s));
    return 0;
}


#endif //GRADE_QUEUE_H
