#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//���������Ϊ10000
#define N 22
int distance[N];//���·��
int path[N];//��һ�ڵ�
int is[N];//�Ƿ�ѡ�øýڵ�,0λδѡ��
int start = 25, end = 25;
#define Max 10000
int destination[N][N];//�۸��ڽӾ���
int length[N][N];//·�������ڽӾ���
char name[22][15] = {"Lisbon", "Madrid", "Bern", "Rome", "Paris", "London", "Brussels", "Amsterdam", "Berlin", "Prague",
                     "Warsaw", "Bucharest", "Budapest", "Vienna", "Sarajevo", "Sofia", "Skopja", "Tirane", "Athens",
                     "Copenhagen", "Dublin", "Belfast"
};
int way[25];

//find����Ѱ�����·��
void find() {
    //������N-1��ѭ��
    for (int k = 1; k < N; k++) {
        int min = 10000;//·�����ֵ
        int u = 0;//uΪ�Ѿ��ҵ����·���Ľڵ�,��ʼ״̬��Ϊ���0
        for (int i = 0; i < N; i++) {
            if (is[i] == 0 && distance[i] < min) {
                u = i;
                min = distance[i];
            }
        }
        is[u] = 1;
        // �ҳ�һ���������������·��
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

//������·��
void showpath() {

    for (int i = 0; i < N; i++) {
        if (is[i] == 1) {
            int k = i;
            int pre;//��¼ʵ���еĺ�һ�ڵ�
            int lengthOfWay = 0;
            int circleCount = 0;//ѭ��������
            //ֻ�����ʼ��������·�������಻���
            if (end == k) {
                while (k != -1) {
                    way[circleCount] = k;//��¼��ǰ·��
                    circleCount++;
                    pre = k;
                    k = path[k];
                    if (k != -1) {
                        lengthOfWay = length[k][pre] + lengthOfWay;
                    }
                }//��ǰһ�ڵ㲻Ϊ����򲻶ϲ�ѯǰһ�ڵ�
                way[circleCount] = start;
                lengthOfWay = lengthOfWay + length[start][pre];
                printf("The cheapest route from %s to %s \ncosts %d euros and spans %d kilometers\n", name[start],
                       name[end], distance[i], lengthOfWay);
                //�����ǰ·��
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
                printf("%s���ܵ���", name[i]);
                printf("\n");
            }
        }
    }
}

//�������𵽱�����ʼֵ��Ч��
int main() {

    //�����ʼ��  �����ͬΪ0 ��ͬΪMax
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
    //��ȡ�ļ��������ڽӾ���
    int n = 0;
    FILE *fp = NULL;
    char string[225];
    fp = fopen("services.txt", "r");
    while (fgets(string, 255, fp) != NULL) {
        char str[4][15];//�ָ�������ַ�������
        char *result;//�ָ��Ľ��
        result = strtok(string, " ");
        int count = 0;
        while (result != NULL) {
            strcpy(str[count++], result);
            result = strtok(NULL, " ");
        }
        str[3][strlen(str[3]) - 1] = '\0';
        //��ʼ����
        start = selectNumber(str[0]);
        //��������
        end = selectNumber(str[1]);
        destination[start][end] = atoi(str[2]);
        length[start][end] = atoi(str[3]);
    }
    fclose(fp);


    //��ʼʱ���г�ʼ������
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
                path[i] = -1;//һ��ʼ���е��ǰһ��Ϊ���
                is[i] = 0;//��δѡ��
                distance[i] = destination[start][i];//��ʼʱ·�̶�Ϊ�����õ����
            }
            is[start] = 1;//��һ���ڵ�ѡ��
            find();
            showpath();

        }

        if (start == 25) {
            printf("û��������,����������\n");
        } else if (end == 25) {
            printf("û���յ���У�����������\n");
        }

        printf("Enter a start and destination city: <'quit' to exit>\n");
        scanf("%s", startPlace);
        start = 25, end = 25;
    }

}

