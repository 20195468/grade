#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTree {
    //���ط�����
    char name[30];
    //������������
    int data;
    //������
    struct BiTree *leftBiTree;
    //������
    struct BiTree *midBiTree;
    //������
    struct BiTree *rightBiTree;
} BiTree;

BiTree *creatBiTree(char name[30], int data) {
    BiTree *node = (BiTree *) malloc(sizeof(BiTree));
    if (node == NULL) {
        printf("���ڵ㴴��ʧ��");
        exit(1);
    }
    node->data = data;
    strcpy(node->name, name);
    node->leftBiTree = NULL;
    node->midBiTree = NULL;
    node->rightBiTree = NULL;
}

BiTree *searchNode(BiTree *bitree, char name[30]) {
    if (bitree == NULL) return bitree;
    if (strcmp(bitree->name, name) == 0) return bitree;
    BiTree *node;
    node = searchNode(bitree->leftBiTree, name);
    if (node != NULL) return node;
    node = searchNode(bitree->midBiTree, name);
    if (node != NULL) return node;
    node = searchNode(bitree->rightBiTree, name);
    if (node != NULL) return node;
    return NULL;
}

int main() {
    FILE *fp = NULL;
    fp = fopen("definitions.txt", "r");
    char name[255];//���ж�ȡ����
    int i = 0;//�ж��Ƿ�Ϊ���ڵ�
    BiTree *root;

    while (fgets(name, 255, fp) != NULL) {
        char str[3][30];//�ָ�������ַ�������
        char *result;//�ָ��Ľ��
        result = strtok(name, " ");
        // ѭ��������
        int count = 0;
        //���ո���н�ȡ
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        //�����һ���ַ�\nȥ��
        str[2][strlen(str[2]) - 1] = '\0';
        //i==0��ʾ�ڴ������ڵ�1
        if (i == 0) {
            root = creatBiTree(str[0], 0);//�������ڵ�
            root->leftBiTree = creatBiTree(str[2], atoi(str[1]));//���ڵ����֧
            i++;
        } else {
            BiTree *biTree = root;//ȡ��ͷ���
            BiTree *temp = NULL;//������Ѱ�ҽ�㱣�浱ǰֵ
            temp = searchNode(biTree, str[0]);//�ҵ���ǰ�ڵ�
            if (temp != NULL) {
                //�ж��Ƿ�Ϊ���ڵ�ķ�֧
                if (strcmp(str[0], "hospital") == 0) {
                    //���ҽڵ����ӣ���Ϊ�ʼ��ʼ���Ѿ�������ڵ�
                    temp->rightBiTree = creatBiTree(str[2], atoi(str[1]));
                } else {
                    //ͨ���� �� �� ˳������
                    if (temp->leftBiTree == NULL) {
                        temp->leftBiTree = creatBiTree(str[2], atoi(str[1]));
                    } else if (temp->rightBiTree == NULL) {
                        temp->rightBiTree = creatBiTree(str[2], atoi(str[1]));
                    } else {
                        temp->midBiTree = creatBiTree(str[2], atoi(str[1]));
                    }
                }
            }
        }

    }
    fclose(fp);

    fp = fopen("queries.txt", "r");
    int count = 0, number = 0;
    while (fgets(name, 255, fp) != NULL) {
        char str[3][30];//�ָ�������ַ�������
        char *result;//�ָ��Ľ��
        result = strtok(name, " ");
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        number++;
        if (number <= 5) {
            //�����һ���ַ�\nȥ��
            str[1][strlen(str[1]) - 1] = '\0';
            BiTree *temp = searchNode(root, str[1]);
            printf("%s subparts are: \n", temp->name);
            if (temp->leftBiTree != NULL) printf("%d  %s\n", temp->leftBiTree->data, temp->leftBiTree->name);
            if (temp->midBiTree != NULL) printf("%d  %s\n", temp->midBiTree->data, temp->midBiTree->name);
            if (temp->rightBiTree != NULL) printf("%d  %s\n", temp->rightBiTree->data, temp->rightBiTree->name);
            if (temp->leftBiTree == NULL && temp->midBiTree == NULL && temp->rightBiTree == NULL) {
                printf("NULL\n");
            }
        } else {
            //�����һ���ַ�\nȥ��
            str[2][strlen(str[2]) - 1] = '\0';
            BiTree *temp = searchNode(root, str[2]);
            BiTree *anotherTemp = searchNode(root, str[1]);
            printf("%s has %d %s\n", temp->name, anotherTemp->data, str[1]);
        }
        count = 0;
    }
    fclose(fp);
    return 0;
}
