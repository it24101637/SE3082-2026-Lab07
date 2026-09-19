**Summary Comparison:**
| Program | Collectives Used | Memory Allocation | Manual Summation on Root? | Where is the final result available? |
| :--- | :--- | :--- | :--- | :--- |
| **`sum_bcast`** | `MPI_Bcast`, `MPI_Send`, `MPI_Recv` | Full array on **ALL** processes | Yes | Root only |
| **`sum_scatter`** | `MPI_Scatter`, `MPI_Send`, `MPI_Recv` | Full array on **Root only** | Yes | Root only |
| **`sum_gather`** | `MPI_Scatter`, `MPI_Gather` | Full array on **Root only** | Yes | Root only |
| **`sum_reduce`** | `MPI_Scatter`, `MPI_Reduce` | Full array on **Root only** | No | Root only |
| **`sum_allreduce`**| `MPI_Scatter`, `MPI_Allreduce` | Full array on **Root only** | No | **All** processes |
| **`sum_scan`** | `MPI_Scatter`, `MPI_Scan` | Full array on **Root only** | No | Different cumulative sum per rank |

**Performance & Timings Note:**
The `sum_reduce` and `sum_allreduce` programs will run the fastest. `sum_bcast` is slow because broadcasting 1,000,000 elements across the network to every node bottlenecks the bandwidth. `sum_scatter` improves data distribution, but using Send/Recv or Gather creates an O(P) linear bottleneck at root. `MPI_Reduce` and `MPI_Allreduce` utilize tree-based network algorithms (O(log P)), minimizing both data transfer and time.

**Thinking Question: When to use MPI_Scan over MPI_Allreduce?**
We use `MPI_Scan` when we need a **parallel prefix sum to determine global offsets**. For example, if each process generates a variable number of results that need to be packed into a single, contiguous global array, `MPI_Allreduce` only tells us the total size of the final array. `MPI_Scan` tells each process exactly which index it should start writing at (`sum_before_me`), preventing processes from overwriting each other's data.
