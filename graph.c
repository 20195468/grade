#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//定义无穷大为10000
#define N 22
int distance[N];//最短路径
int path[N];//上一节点
int is[N];//是否选用该节点,0位未选用
int start = 25, end = 25;
#define Max 10000
int destination[N][N];//价格邻接矩阵
int length[N][N];//路径长度邻接矩阵
char name[22][15] = {"Lisbon", "Madrid", "Bern", "Rome", "Paris", "London", "Brussels", "Amsterdam", "Berlin", "Prague",
                     "Warsaw", "Bucharest", "Budapest", "Vienna", "Sarajevo", "Sofia", "Skopja", "Tirane", "Athens",
                     "Copenhagen", "Dublin", "Belfast"
};
int way[25];

//find函数寻找最短路径
void find() {
    //最多进行N-1次循环
    for (int k = 1; k < N; k++) {
        int min = 10000;//路径最大值
        int u = 0;//u为已经找到最短路径的节点,初始状态都为起点0
        for (int i = 0; i < N; i++) {
            if (is[i] == 0 && distance[i] < min) {
                u = i;
                min = distance[i];
            }
        }
        is[u] = 1;
        // 找出一点后更新其余点的最短路径
        for (int y = 0; y < N; y++) {
            if (is[y] == 0 && distance[u] + destination[u][y] < distance[y]) {
                distance[y] = distance[u] + destination[u][y];
                path[y] = u;
            }
        }
    }
}

int selectNumber(char place[30]) {
    for (int i = 0; i < N; ++i) {
        if (strcmp(place, name[i]) == 0) {
            return i;
        }
    }
    return 25;
}

//输出最短路径
void showpath() {

    for (int i = 0; i < N; i++) {
        if (is[i] == 1) {
            int k = i;
            int pre;//记录实际中的后一节点
            int lengthOfWay = 0;
            int circleCount = 0;//循环计数器
            //只输出开始到结束的路径，其余不输出
            if (end == k) {
                while (k != -1) {
                    way[circleCount] = k;//记录当前路径
                    circleCount++;
                    pre = k;
                    k = path[k];
                    if (k != -1) {
                        lengthOfWay = length[k][pre] + lengthOfWay;
                    }
                }//若前一节点不为起点则不断查询前一节点
                way[circleCount] = start;
                lengthOfWay = lengthOfWay + length[start][pre];
                printf("The cheapest route from %s to %s \ncosts %d euros and spans %d kilometers\n", name[start],
                       name[end], distance[i], lengthOfWay);
                //输出当前路径
                for (int j = circleCount; j >= 0; --j) {
                    if (j == 0) {
                        printf("%s\n", name[way[j]]);
                    } else {
                        printf("%s to ", name[way[j]]);
                    }
                }
                printf("\n");
            }
        } else {
            if (end==i){
                printf("%s不能到达", name[i]);
                printf("\n");
            }
        }
    }
}

//主函数起到遍历初始值的效果
int main() {

    //矩阵初始化  结点相同为0 不同为Max
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                destination[i][j] = 0;
                length[i][j] = 0;
            } else {
                destination[i][j] = Max;
                length[i][j] = Max;
            }
        }
    }
    //读取文件，建立邻接矩阵
    int n = 0;
    FILE *fp = NULL;
    char string[225];
    fp = fopen("services.txt", "r");
    while (fgets(string, 255, fp) != NULL) {
        char str[4][15];//分割后将三个字符串放入
        char *result;//分割后的结果
        result = strtok(string, " ");
        int count = 0;
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        str[3][strlen(str[3]) - 1] = '\0';
        //起始顶点
        start = selectNumber(str[0]);
        //结束顶点
        end = selectNumber(str[1]);
        destination[start][end] = atoi(str[2]);
        length[start][end] = atoi(str[3]);
    }
    fclose(fp);


    //开始时进行初始化遍历
    char startPlace[20], endPlace[20];
    printf("Enter a start and destination city: <'quit' to exit>\n");
    scanf("%s", startPlace);
    while (strcmp(startPlace, "quit") != 0) {
        scanf("%s", endPlace);

        for (int i = 0; i < 22; ++i) {
            if (strcmp(startPlace, name[i]) == 0) {
                start = i;
            }
            if (strcmp(endPlace, name[i]) == 0) {
                end = i;
            }
        }

        if (start != 25 && end != 25) {

            for (int i = 0; i < N; i++) {
                path[i] = -1;//一开始所有点的前一点为起点
                is[i] = 0;//都未选用
                distance[i] = destination[start][i];//初始时路程都为起点道该点距离
            }
            is[start] = 1;//第一个节点选用
            find();
            showpath();

        }

        if (start == 25) {
            printf("没有起点城市,请重新输入\n");
        } else if (end == 25) {
            printf("没有终点城市，请重新输入\n");
        }

        printf("Enter a start and destination city: <'quit' to exit>\n");
        scanf("%s", startPlace);
        start = 25, end = 25;
    }

}

