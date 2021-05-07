DIRECTORY_GUARD=@mkdir -p $(@D)
BUILD_DIRECTORY ?= build

CC		=	gcc
CFLAGS	+=	-ansi	 					\
			-pedantic					\
			-Wpedantic					\
			-Wall						\
			-Wextra						\
			-Werror						\
			-ggdb						\
			-MD							\
			-fsanitize=undefined	 	\
			-fsanitize=address  		\
			-Ideps/mulib/inc		

LDFLAGS	+=	-fsanitize=undefined	\
			-fsanitize=address		\
			-Ldeps/mulib			\
			-l:libmu.a

TARGET   =  monkelisp
SRCS     =  $(wildcard src/*.c)
OBJS     =  $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(SRCS))

$(BUILD_DIRECTORY)/%.c.o: %.c
	$(DIRECTORY_GUARD)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -lm -o $@ $(LDFLAGS)	

build-mulib:
	$(MAKE) -C deps/mulib

all: build-mulib $(TARGET)

.PHONY: all
.DEFAULT_GOAL := all