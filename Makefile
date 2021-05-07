DIRECTORY_GUARD=@mkdir -p $(@D)
BUILD_DIRECTORY ?= build

CC		?=	tcc
CFLAGS	+=  -pedantic						\
			-Wpedantic						\
			-Wall							\
			-Wextra							\
			-Werror							\
			-ggdb							\
			-MD								\
			-fsanitize=undefined		 	\
			-fsanitize=address  			\
			-Ideps/mulib/inc				\

LDFLAGS	+=  -lreadline						\
			-lm 							\
			-Ldeps/mulib					\
			-lmu							\
			-fsanitize=undefined			\
			-fsanitize=address

TARGET   =  monkelisp
SRCS     =  $(wildcard src/*.c)
OBJS     =  $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(SRCS))

$(BUILD_DIRECTORY)/%.c.o: %.c
	$(DIRECTORY_GUARD)
	$(CC) $(CFLAGS) -r -o $@ $< 

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ 	

build-mulib:
	$(MAKE) -C deps/mulib
	rm deps/mulib/libmu.so

all: build-mulib $(TARGET)

clean:
	rm -r build 
	rm monkelisp
	$(MAKE) -C deps/mulib clean

.PHONY: all clean
.DEFAULT_GOAL := all
