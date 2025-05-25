NAME = hotrace

CFLAGS = -Wall -Wextra -Werror -g #-O3 -march=native -mtune=native -flto -funroll-loops -ffast-math

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
# @echo "Generating test data..."
# @rm -f gen test.txt
# cc gen.c -o gen
# ./gen > test.txt
# @echo "Running program with profiling enabled..."
	./$(NAME) < test.txt
	@echo "Generating profiling report..."
	gprof -lb $(NAME) > profile_report.txt
	@echo "Profile report generated as profile_report.txt"
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png && \
		echo "Visual profile generated as profile.png"; \
	fi
	@echo "Profiling complete!"

TEST_FILE = test_files/1_empty.txt

# Add sanitizer targets
asan: CFLAGS += -fsanitize=address -g
asan: LDFLAGS += -fsanitize=address
asan: re

ubsan: CFLAGS += -fsanitize=undefined -g
ubsan: LDFLAGS += -fsanitize=undefined
ubsan: re

# Combined sanitizers
san: CFLAGS += -fsanitize=address,undefined -g
san: LDFLAGS += -fsanitize=address,undefined
san: re

# Run with sanitizers enabled
test-san: san
	@echo "Running with sanitizers..."
	./$(NAME) < $(TEST_FILE) > /dev/null 2>san_errors.txt

# Memory leak sanitizer (can be run standalone from ASan)
lsan: CFLAGS += -fsanitize=leak -g
lsan: LDFLAGS += -fsanitize=leak
lsan: re

# Memory sanitizer (detects uninitialized reads)
# Note: Requires all code including libraries to be built with MSan
msan: CFLAGS += -fsanitize=memory -g -fPIE -fno-omit-frame-pointer
msan: LDFLAGS += -fsanitize=memory -fPIE
msan: re

# Thread sanitizer (for multi-threaded code)
# Note: Your code seems single-threaded so this is for completeness
tsan: CFLAGS += -fsanitize=thread -g
tsan: LDFLAGS += -fsanitize=thread
tsan: re

# Profile-guided optimization - step 1: generate profile
pgo-gen: CFLAGS += -fprofile-generate -g
pgo-gen: LDFLAGS += -fprofile-generate
pgo-gen: re
	./$(NAME) < $(TEST_FILE) > /dev/null

# Profile-guided optimization - step 2: use profile data
pgo-use: CFLAGS += -fprofile-use -g
pgo-use: LDFLAGS += -fprofile-use
pgo-use: re

# Thorough analysis with multiple tools in sequence
analyze: clean
	@echo "Running Address Sanitizer..."
	@make asan
	@./$(NAME) < $(TEST_FILE) > /dev/null 2>asan_errors.txt || true
	@echo "Running Undefined Behavior Sanitizer..."
	@make ubsan
	@./$(NAME) < $(TEST_FILE) > /dev/null 2>ubsan_errors.txt || true
	@echo "Running Leak Sanitizer..."
	@make lsan
	@./$(NAME) < $(TEST_FILE) > /dev/null 2>lsan_errors.txt || true
	@echo "Running Memory Sanitizer..."
	@make msan
	@./$(NAME) < $(TEST_FILE) > /dev/null 2>msan_errors.txt || true
	@echo "Analysis complete. Check *_errors.txt files for details."


# Profile each hash function
profile-hash-functions: profile
	@echo "Generating test data..."
	@rm -f gen $(TEST_FILE)
	cc gen.c -o gen
	./gen > $(TEST_FILE)
		
	@echo "==== Profiling MurmurHash3 (64-bit) ===="
	@rm -f gmon.out
	./$(NAME) -hash 0 < $(TEST_FILE) > /dev/null
	gprof -lp $(NAME) > murmur64_profile.txt
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof murmur64_profile.txt | dot -Tpng -o murmur64_profile.png && \
		echo "Visual profile generated as murmur64_profile.png"; \
	fi
		
	@echo "==== Profiling FNV-1a ===="
	@rm -f gmon.out
	./$(NAME) -hash 1 < $(TEST_FILE) > /dev/null
	gprof -lp $(NAME) > fnv1a_profile.txt
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof fnv1a_profile.txt | dot -Tpng -o fnv1a_profile.png && \
		echo "Visual profile generated as fnv1a_profile.png"; \
	fi
		
	@echo "==== Profiling djb2 ===="
	@rm -f gmon.out
	./$(NAME) -hash 2 < $(TEST_FILE) > /dev/null
	gprof -lp $(NAME) > djb2_profile.txt
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof djb2_profile.txt | dot -Tpng -o djb2_profile.png && \
		echo "Visual profile generated as djb2_profile.png"; \
	fi
		
	@echo "==== Profiling MurmurHash3 (128-bit) ===="
	@rm -f gmon.out
	./$(NAME) -hash 3 < $(TEST_FILE) > /dev/null
	gprof -lp $(NAME) > murmur128_profile.txt
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof murmur128_profile.txt | dot -Tpng -o murmur128_profile.png && \
		echo "Visual profile generated as murmur128_profile.png"; \
	fi
		
	@echo "All hash functions profiled! Check *_profile.txt and *_profile.png files"