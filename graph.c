#include <stdio.h>
#include "string.h"
//定义无穷大为10000
#define N 22
int distance[N];//最短路径
int path[N];//上一节点
int is[N];//是否选用该节点,0位未选用
int start = 25, end = 25;
int destination[N][N] = {
        {0,     75,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {55,    0,     15,    10000, 100,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 45,    0,     75,    15,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 75,    0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 100,   35,    10000, 0,     110,   135,   10000, 10000, 10000, 10000, 10000, 10000, 75,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 110,   0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 225,   10000, 0,     185,   65,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 125,   0,     45,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 45,    10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 35,    75,    0,     45,    35,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 55,    0,     35,    10000, 10000, 45,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 35,    25,    0,     25,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    0,     25,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    0,     25,    15,    10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 75,    10000, 10000, 10000, 10000, 10000, 45,    10000, 10000, 45,    0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 25,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    10000, 0,     15,    15,    10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    0,     15,    10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 15,    15,    0,     15,    10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 35,    0,     55,    10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 55,    0,     10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 45,    10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 0,     10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 0,     25},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 25,    0}

};//路程矩阵
int length[N][N] = {
        {0,     450,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {450,   0,     1500,  10000, 1300,  10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 1500,  0,     900,   600,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1100,  10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 900,   0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 1300,  600,   10000, 0,     450,   300,   10000, 10000, 10000, 10000, 10000, 10000, 1300,  10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 450,   0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 300,   10000, 0,     200,   800,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 200,   0,     700,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 800,   10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 800,   700,   0,     350,   900,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 350,   0,     850,   10000, 10000, 300,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 900,   850,   0,     1700,  10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1700,  0,     900,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 900,   0,     300,   600,   10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 1300,  10000, 10000, 10000, 10000, 10000, 1300,  10000, 10000, 300,   0,     10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 1100,  10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 600,   10000, 0,     600,   500,   10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 600,   0,     200,   10000, 10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 500,   200,   0,     200,   10000, 10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 200,   0,     700,   10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 700,   0,     10000, 10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 800,   10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 0,     10000, 10000},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 0,     167},
        {10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 167,   0}
};
char name[22][15] = {"Lisbon", "Madrid", "Bern", "Rome", "Pairs", "London", "Brussels", "Amsterdam", "Berlin", "Prague",
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

