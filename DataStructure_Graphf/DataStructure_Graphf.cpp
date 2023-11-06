#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 50

typedef int QueueType;
QueueType queue[MAX_VERTICES];
int front = -1, rear = -1;

void enqueue(QueueType value) {
    if (rear == MAX_VERTICES - 1) {
        fprintf(stderr, "Queue is full.\n");
        exit(1);
    }
    queue[++rear] = value;
}

QueueType dequeue() {
    if (front == rear) {
        fprintf(stderr, "Queue is empty.\n");
        exit(1);
    }
    return queue[++front];
}


typedef struct GraphType {
    int n;	// ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
int visited[MAX_VERTICES];
void init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}
void insert_vertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}


void dfs_mat(GraphType* g, int v)
{
    int w;
    visited[v] = true;		// ���� v�� �湮 ǥ�� 
    printf("%d ", v);		// �湮�� ���� ���
    for (w = 0; w < g->n; w++) 		// ���� ���� Ž��
        if (g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, w);	//���� w���� DFS ���� ����
}
void bfs_mat(GraphType* g, int start) {
    int v;
    enqueue(start);
    visited[start] = true;

    while (front != rear) {
        v = dequeue();
        printf("%d ", v);

        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                enqueue(w);
                visited[w] = true;
            }
        }
    }
}

int visited_count(GraphType* g) {
    int count = 0;
    for (int i = 0; i < g->n; i++) {
        if (visited[i]) {
            count++;
        }
    }
    return count;
}

int main(void)
{
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        return 1;
    }

    init(g);
    for (int i = 0; i < 11; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 1, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    insert_edge(g, 8, 10);

    int menu = 0;
    printf("1:  ���� �켱 Ž��\n");
    printf("2:  �ʺ� �켱 Ž��\n");
    printf("3:  ����\n");

    while (menu != 3) {
        printf("�޴� �Է�: ");
        scanf_s(" %d", &menu);

        switch (menu) {
        case 1:
            int start, value;

            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &value);

            if (start < 0 || start >= g->n || value < 0 || value >= g->n) {
                printf("�߸��� ���� ��ȣ �Ǵ� Ž�� ���Դϴ�.\n");
                break;
            }

            for (int i = 0; i < g->n; i++) {
                visited[i] = false; // �湮 ��� �ʱ�ȭ
            }

            dfs_mat(g, start);
            printf("\n");

            if (visited[value] == 1) {
                printf("Ž�� ����! �湮�� ����� ����: %d\n", visited_count(g));
            }
            else {
                printf("Ž�� ����! \n");
            }
            break;
        case 2:
            int bfs_start, search_value;

            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &bfs_start, &search_value);

            if (bfs_start < 0 || bfs_start >= g->n || search_value < 0 || search_value >= g->n) {
                printf("�߸��� ���� ��ȣ �Ǵ� Ž�� ���Դϴ�.\n");
                break;
            }

            for (int i = 0; i < g->n; i++) {
                visited[i] = false; // �湮 ��� �ʱ�ȭ
            }

            bfs_mat(g, bfs_start);
            printf("\n");

            if (visited[search_value]) {
                printf("Ž�� ����! �湮�� ����� ����: %d\n", visited_count(g));
            }
            else {
                printf("Ž�� ����!\n");
            }
            break;
        case 3:
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    free(g);
    return 0;
}
