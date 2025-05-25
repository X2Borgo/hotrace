NAME = hotrace

CFLAGS = -Wall -Wextra -Werror -O3

SRCS = \
main.c \
parsing.c \
ft_strchr.c \
ft_strdup.c \
ft_strlen.c \
ft_memset.c \
ft_memcpy.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_strncmp.c \
ft_write.c

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
