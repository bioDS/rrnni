# setting RECIPEPREFIX to plus sign:
# tabs are bad as they are invisible
.RECIPEPREFIX = +

# compile with warnings
LDFLAGS = -Wall -Wextra

# include the ../ dir with .h files
INCLUDE = -I../

LIBS =

LD = gcc

test: tests
+ ./tests

tests: tests.c ../tree.c ../dist.c
+ $(LD) $(LDFLAGS) $(INCLUDE) $(LIBS) $^ -o $@

clean:
+ rm tests
