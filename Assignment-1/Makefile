FLAGS = -g -fno-stack-protector -z execstack  -m32

EXES = testme myinfo exploit

all: $(EXES) 


$(EXES):
	gcc $(FLAGS) $@.c -o $@

clean:
	rm -f $(EXES)

