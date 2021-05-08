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

test: LDFLAGS	+= -lcmocka --coverage
test: CFLAGS    += --coverage

TARGET   =  monkelisp
SRCS     =  $(wildcard src/*.c)
OBJS     =  $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(SRCS))

TEST_SRCS	= $(wildcard tests/*.c)
TEST_OBJS     =   $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(TEST_SRCS))


$(BUILD_DIRECTORY)/%.c.o: %.c
	$(DIRECTORY_GUARD)
	$(CC) $(CFLAGS) -r -o $@ $< 

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@ 	

build-mulib:
	$(MAKE) -C deps/mulib
	rm deps/mulib/libmu.so


test: $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	@./$@

all: build-mulib $(TARGET)

clean:
	rm -r build

	-rm monkelisp
	-rm test

	$(MAKE) -C deps/mulib clean

.PHONY: all clean test
.DEFAULT_GOAL := all
