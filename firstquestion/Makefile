# Compiler and flags
CC = gcc
CFLAGS = -fopenmp -O2          # OpenMP support and optimization flag
PROF_FLAGS = -pg               # Profiling flag for gprof

# Target executable
TARGET = firstq

all: $(TARGET)

# Compile with profiling enabled
$(TARGET): firstq.c
	$(CC) $(CFLAGS) $(PROF_FLAGS) -o $(TARGET) firstq.c -lm

# Run the program with profiling and generate a gprof report
run: $(TARGET)
	@echo "Running program with profiling enabled..."
	./$(TARGET)                     # Run the program to generate gmon.out
	@echo "Generating gprof report..."
	gprof $(TARGET) gmon.out > gprof_report.txt
	@echo "gprof report saved to gprof_report.txt"

# Clean up the compiled files and profiling data
clean:
	rm -f $(TARGET) gmon.out gprof_report.txt
