# Compiler and flags
CC = gcc
CFLAGS = -fopenmp -O2 -pg  # OpenMP support, optimization, and profiling flag

# Target executable
TARGET = secondq

all: $(TARGET)

# Compile the program
$(TARGET): secondq.c
	$(CC) $(CFLAGS) -o $(TARGET) secondq.c -lm

# Run the program with different numbers of threads and save the output and profiling results
run: $(TARGET)
	@echo "Running with 1 thread..."
	OMP_NUM_THREADS=1 ./$(TARGET)
	gprof $(TARGET) gmon.out > profile_1_thread.txt
	mv gmon.out gmon_1_thread.out

	@echo "Running with 2 threads..."
	OMP_NUM_THREADS=2 ./$(TARGET)
	gprof $(TARGET) gmon.out > profile_2_threads.txt
	mv gmon.out gmon_2_threads.out

	@echo "Running with 4 threads..."
	OMP_NUM_THREADS=4 ./$(TARGET)
	gprof $(TARGET) gmon.out > profile_4_threads.txt
	mv gmon.out gmon_4_threads.out

	@echo "Running with 8 threads..."
	OMP_NUM_THREADS=8 ./$(TARGET)
	gprof $(TARGET) gmon.out > profile_8_threads.txt
	mv gmon.out gmon_8_threads.out

	@echo "Profiling results saved in profile_1_thread.txt, profile_2_threads.txt, profile_4_threads.txt, and profile_8_threads.txt."

# Clean up the generated files
clean:
	rm -f $(TARGET) results_*.txt profile_*.txt gmon_*.out
