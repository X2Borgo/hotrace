NAME = hotrace

CFLAGS = -Wall -Wextra -Werror -O3

SRCS = \
main.c \
core_hash.c \
memory_ops.c \
parsing_core.c \
parsing_utils.c \
io_memory.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all


gen_file: gen.c
	rm -f gen
	$(CC) $(CFLAGS) -o gen gen.c
	rm -f test.txt
	./gen > test.txt


# Added prof target as an alias to profile
prof: profile

exec: gen_file
	@echo "Executing the program..."
	./$(NAME) < test.txt

profile: CFLAGS += -pg
profile: LDFLAGS += -pg
profile: re

gprof-report: 
	@if [ -f gmon.out ]; then \
		gprof -lb -v $(NAME) > profile_report.txt; \
		echo "Detailed profile report generated as profile_report.txt"; \
	else \
		echo "Error: gmon.out not found. Run the program with 'make profile' first."; \
	fi

gprof-visual: gprof-report 
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png; \
		echo "Visual profile generated as profile.png"; \
	else \
		echo "Please install gprof2dot with: pip3 install --user gprof2dot"; \
		exit 1; \
	fi

# Complete profiling workflow in a single command
profile-all: profile
	@echo "Generating test data..."
	@rm -f gen test.txt
	cc gen.c -o gen
	./gen > test.txt
	@echo "Running program with profiling enabled..."
	./$(NAME) < test.txt
	@echo "Generating profiling report..."
	gprof -lb $(NAME) > profile_report.txt
	@echo "Profile report generated as profile_report.txt"
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png && \
		echo "Visual profile generated as profile.png"; \
	fi
	@echo "Profiling complete!"



# VTune profiling with Docker
vtune-build: CFLAGS += -g -O2
vtune-build: re

vtune-pull:
	docker pull intel/oneapi-vtune

vtune-run: vtune-build gen_file
	@echo "Running VTune profiling with Docker..."
	docker run --rm \
		--privileged \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -collect hotspots -result-dir ./vtune_results_user -- ./$(NAME) < test.txt

vtune-report:
	docker run --rm \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -report summary -result-dir ./vtune_results_user

# Complete VTune workflow
vtune: vtune-pull vtune-build gen_file vtune-run vtune-report
	@echo "VTune profiling complete! Results in ./vtune_results_user directory"

vtune-help:
	docker run --rm intel/oneapi-vtune vtune -help collect

# Alternative VTune collection types for restricted environments

vtune-memory: vtune-build gen_file
	@echo "Running VTune memory consumption analysis..."
	docker run --rm \
		--privileged \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -collect memory-consumption -result-dir ./vtune_memory -- ./$(NAME) < test.txt

vtune-threading: vtune-build gen_file
	@echo "Running VTune threading analysis..."
	docker run --rm \
		--privileged \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -collect threading -result-dir ./vtune_threading -- ./$(NAME) < test.txt

vtune-snapshot: vtune-build gen_file
	@echo "Running VTune performance snapshot..."
	docker run --rm \
		--privileged \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -collect performance-snapshot -result-dir ./vtune_snapshot -- ./$(NAME) < test.txt

# Report targets for each collection type
vtune-memory-report:
	docker run --rm \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -report summary -result-dir ./vtune_memory

vtune-threading-report:
	docker run --rm \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -report summary -result-dir ./vtune_threading

vtune-snapshot-report:
	docker run --rm \
		-v $(shell pwd):/app \
		-w /app \
		intel/oneapi-vtune \
		vtune -report summary -result-dir ./vtune_snapshot