#include <stdio.h>
#include <stdbool.h>

void dfs(int quantity, int *start, int *fin, int s, bool *visited) {
    visited[s] = true;
    for (int i = 0; i < quantity; ++i) {
        if (start[i] == s && !visited[fin[i]])
            dfs(quantity, start, fin, fin[i], visited);
    }
}

bool *find_states(int quantity_state, int quantity_trans, int *start, int *fin, int start_state, bool *visited) {
    for(int i = 0; i < quantity_state; i++) {
        visited[i] = false;
    }
    dfs(quantity_trans, start, fin, start_state, visited);
}

int main() {
    FILE *file;
    int A, S, s0, F_len;

    file = fopen("a3.txt", "r");

    if (NULL == file) {
        printf("File can't be opened.\n");
        return 0;
    }

    fscanf(file, "%d%d%d", &A, &S, &s0);
    fscanf(file, "%d", &F_len);
    int F[F_len];
    for (int i = 0; i < F_len; i++) {
        fscanf(file, "%d", &F[i]);
    }

    int j = 0;
    int start[100], fin[100];
    char sym[100];
    while (fscanf(file, "%d %c %d", &start[j], &sym[j], &fin[j]) == 3) {
        j++;
    }

    bool result[S];
    find_states(S, j, start, fin, s0, result);

    bool reverse_result[S];
    for(int i = 0; i < S; i++) {
        reverse_result[i] = false;
    }

    bool reverse_visited_states[S];
    for (int k = 0; k < F_len; k++) {
        find_states(S, j, fin, start, F[k], reverse_visited_states);

        for(int i = 0; i < S; i++) {
            if (!reverse_result[i] && reverse_visited_states[i])
                reverse_result[i] = 1;
        }
    }

    for(int i = 0; i < S; i++) {
        if (result[i] && !reverse_result[i])
            result[i] = 0;
    }

    bool result_exist = false;
    printf("%s ", "Result:");
    for(int i = 0; i < S; i++) {
        if (!result[i]) {
            printf("%d ", i);
            result_exist = true;
        }
    }

    if (!result_exist) {
        printf("%s", "no states.");
    }

    fclose(file);
    return 0;
}
