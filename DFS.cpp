#include <iostream>
#include <vector>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void dfs_serial(int start, int* arr, int n, int visited[]) {
    for(int i = 0; i < n; i++) {
        if((*(arr + (start * n) + i) == 1) && (!visited[i])) {
            visited[i] = 1;
            cout << i << " ";
            dfs_serial(i, (int*)arr, n, visited);
        }
    }
}

void dfs_parallel(int start, int* arr, int n, int visited[]) {
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        if((*(arr + (start * n) + i) == 1) && (!visited[i])) {
            #pragma omp critical
            {
                visited[i] = 1;
                cout << i << " ";
            }
            dfs_parallel(i, (int*)arr, n, visited);
        }
    }
}


int main() {
    cout << "Enter the number of vertices: ";
    int n;
    cin >> n;

    int arr[n][n] = {0};

    cout << "Enter the number of edges: ";
    int edges;
    cin >> edges;

    for(int j = 0; j < edges; j++) {
        int a, b;
        cout << "Enter the two edges:" << endl;
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    int visited[n] = {0};

    cout << "Enter the start vertex: ";
    int start;
    cin >> start;

    // Serial execution
    clock_t strt_serial = clock();
    cout << start << " ";
    visited[start] = 1;
    dfs_serial(start, (int *)arr, n, visited);
    clock_t stop_serial = clock();

    cout << "\nTime required (serial): " << (double)(stop_serial - strt_serial) << " ms" << endl;

    // Parallel execution
    clock_t strt_parallel = clock();
    memset(visited, 0, sizeof(visited)); // Reset visited array for parallel execution
    cout << start << " ";
    visited[start] = 1;
    dfs_parallel(start, (int *)arr, n, visited);
    clock_t stop_parallel = clock();

    cout << "\nTime required (parallel): " << (double)(stop_parallel - strt_parallel) << " ms" << endl;

    return 0;
}
