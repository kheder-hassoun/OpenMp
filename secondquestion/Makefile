CC = gcc
CFLAGS = -fopenmp -O2         
PROF_FLAGS = -pg               

TARGET = secondq

all: $(TARGET)

$(TARGET): secondq.c
	$(CC) $(CFLAGS) -o $(TARGET) secondq.c -lm

run: $(TARGET)
	@echo "Running without profiling..."
	@echo "Running with 1 thread..."
	OMP_NUM_THREADS=1 ./$(TARGET) > results_1_thread.txt
	@echo "Running with 2 threads..."
	OMP_NUM_THREADS=2 ./$(TARGET) > results_2_threads.txt
	@echo "Running with 4 threads..."
	OMP_NUM_THREADS=4 ./$(TARGET) > results_4_threads.txt
	@echo "Running with 8 threads..."
	OMP_NUM_THREADS=8 ./$(TARGET) > results_8_threads.txt
	@echo "Results saved in results_1_thread.txt, results_2_threads.txt, results_4_threads.txt, results_8_threads.txt."

profile_build: secondq.c
	$(CC) $(CFLAGS) $(PROF_FLAGS) -o $(TARGET) secondq.c -lm

profile: profile_build
	@echo "Running with profiling enabled..."
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

clean:
	rm -f $(TARGET) results_*.txt profile_*.txt gmon_*.out
