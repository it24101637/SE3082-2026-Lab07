#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size = N / size;
    int *array = NULL;
    int *local_chunk = (int *)malloc(chunk_size * sizeof(int));

    if (rank == 0) {
        array = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) array[i] = i + 1;
    }

    MPI_Scatter(array, chunk_size, MPI_INT, local_chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    long long local_sum = 0;
    for (int i = 0; i < chunk_size; i++) local_sum += local_chunk[i];

    long long total_sum = 0;
    
    // Allreduce makes the total available to all ranks
    MPI_Allreduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

    double percent = ((double)local_sum / (double)total_sum) * 100.0;
    printf("Rank %d: local_sum = %lld, total_sum = %lld, contributed %.2f%%\n", rank, local_sum, total_sum, percent);

    if (rank == 0) free(array);
    free(local_chunk);
    MPI_Finalize();
    return 0;
}
