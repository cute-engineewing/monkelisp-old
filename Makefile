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

test: CFLAGS	+=  -Iinc --coverage
test: LDFLAGS	+= -lcmocka --coverage
test: CC	= gcc

TARGET   =  monkelisp
SRCS     =  $(wildcard src/*.c)
OBJS     =  $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(SRCS))

TEST_SRCS	= test.c
TEST_OBJS     =  $(addprefix tests/, $(TEST_SRCS:.c=.o))


$(BUILD_DIRECTORY)/%.c.o: %.c
	$(DIRECTORY_GUARD)
	$(CC) $(CFLAGS) -r -o $@ $< 

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ 	

build-mulib:
	$(MAKE) -C deps/mulib
	rm deps/mulib/libmu.so


test: $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	@./$@

all: build-mulib $(TARGET)

clean:
	@-rm -r build
	@-rm $(TEST_OBJS:.o=.gcno)
	@-rm $(TEST_OBJS:.o=.d)
	@-rm $(TEST_OBJS)

	@-rm monkelisp
	$(MAKE) -C deps/mulib clean

.PHONY: all clean
.DEFAULT_GOAL := all
