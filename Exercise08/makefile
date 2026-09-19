CC = mpicc
CFLAGS = -Wall -O2

SRCS = sum_bcast.c sum_scatter.c sum_gather.c sum_reduce.c sum_allreduce.c sum_scan.c
EXECS = $(SRCS:.c=)

all: $(EXECS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	@echo "\n--- Running sum_bcast ---"
	mpirun -np 4 ./sum_bcast
	@echo "\n--- Running sum_scatter ---"
	mpirun -np 4 ./sum_scatter
	@echo "\n--- Running sum_gather ---"
	mpirun -np 4 ./sum_gather
	@echo "\n--- Running sum_reduce ---"
	mpirun -np 4 ./sum_reduce
	@echo "\n--- Running sum_allreduce ---"
	mpirun -np 4 ./sum_allreduce
	@echo "\n--- Running sum_scan ---"
	mpirun -np 4 ./sum_scan

clean:
	rm -f $(EXECS)
