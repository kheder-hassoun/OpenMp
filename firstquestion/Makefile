CC = gcc
CFLAGS = -fopenmp -O2          
PROF_FLAGS = -pg                

TARGET = firstq

all: $(TARGET)

$(TARGET): firstq.c
	$(CC) $(CFLAGS) -o $(TARGET) firstq.c -lm

profile_build: firstq.c
	$(CC) $(CFLAGS) $(PROF_FLAGS) -o $(TARGET) firstq.c -lm

run: $(TARGET)
	@echo "Running program without profiling..."
	./$(TARGET)

profile: profile_build
	@echo "Running program with profiling enabled..."
	./$(TARGET)                     # Run the program to generate gmon.out
	@echo "Generating gprof report..."
	gprof $(TARGET) gmon.out > gprof_report.txt
	@echo "gprof report saved to gprof_report.txt"

clean:
	rm -f $(TARGET) gmon.out gprof_report.txt
