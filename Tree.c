#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTree {
    //各地方名称
    char name[30];
    //所属部分数据
    int data;
    //左子树
    struct BiTree *leftBiTree;
    //中子数
    struct BiTree *midBiTree;
    //右子树
    struct BiTree *rightBiTree;
} BiTree;

BiTree *creatBiTree(char name[30], int data) {
    BiTree *node = (BiTree *) malloc(sizeof(BiTree));
    if (node == NULL) {
        printf("树节点创建失败");
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
    char name[255];//整行读取容器
    int i = 0;//判断是否为根节点
    BiTree *root;

    while (fgets(name, 255, fp) != NULL) {
        char str[3][30];//分割后将三个字符串放入
        char *result;//分割后的结果
        result = strtok(name, " ");
        // 循环计数器
        int count = 0;
        //按空格进行截取
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        //将最后一个字符\n去掉
        str[2][strlen(str[2]) - 1] = '\0';
        //i==0表示在创建根节点1
        if (i == 0) {
            root = creatBiTree(str[0], 0);//创建根节点
            root->leftBiTree = creatBiTree(str[2], atoi(str[1]));//根节点左分支
            i++;
        } else {
            BiTree *biTree = root;//取出头结点
            BiTree *temp = NULL;//从树中寻找结点保存当前值
            temp = searchNode(biTree, str[0]);//找到当前节点
            if (temp != NULL) {
                //判断是否为根节点的分支
                if (strcmp(str[0], "hospital") == 0) {
                    //将右节点连接，因为最开始初始化已经连接左节点
                    temp->rightBiTree = creatBiTree(str[2], atoi(str[1]));
                } else {
                    //通过左 右 中 顺序连接
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
        char str[3][30];//分割后将三个字符串放入
        char *result;//分割后的结果
        result = strtok(name, " ");
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        number++;
        if (number <= 5) {
            //将最后一个字符\n去掉
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
            //将最后一个字符\n去掉
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
