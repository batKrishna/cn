#include <stdio.h>

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main() {
    int costmat[20][20], nodes, i, j, k, count;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter the cost matrix:\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &costmat[i][j]);
            if (i == j)
                costmat[i][j] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }

    do {
        count = 0;
        for (i = 0; i < nodes; i++) {
         for (j = 0; j < nodes; j++) {
         for (k = 0; k < nodes; k++) {
          if (rt[i].dist[j] > costmat[i][k] + rt[k].dist[j]) {
           rt[i].dist[j] = costmat[i][k] + rt[k].dist[j];
               rt[i].from[j] = k;
               count++;
                }
            }
        }
      }
    } while (count != 0);  

   
    for (i = 0; i < nodes; i++) {
        printf("\n\nFor router %d:\n", i + 1);
        for (j = 0; j < nodes; j++) {
            printf("Node %d via %d Distance %d\n", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }

    printf("\n");
    return 0;
}

