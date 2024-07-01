CC = gcc 
CFLAGS = -Wall -Wextra -pedantic -std=gnu99 -g 
INCLUDE = -I/local/courses/csse2310/include -I.
LDFLAGS = -L/local/courses/csse2310/lib -lcsse2310a1 
OBJFILES = strings.o arrays.o exit.o uqunscramble.o 
TARGET = uqunscramble

all : $(TARGET)

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(INCLUDE) $(LDFLAGS)

uqunscramble.o : uqunscramble.c /local/courses/csse2310/include 
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $<

strings.o : strings.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $<

arrays.o : arrays.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $<

exit.o : exit.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $<

clean : 
	rm -f $(OBJFILES) $(TARGET) *~
