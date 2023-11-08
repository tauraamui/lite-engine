SRCFILES != find src -name '*.c'
OBJFILES := ${SRCFILES:%.c=build/obj/%.o} 
INCDIR := include
LIBS := -lSDL2 -ldl -lm
MODE ?= DEBUG

LDFLAGS := -Wall -Wno-missing-braces -std=c11 
CFLAGS := -Wall -Wno-missing-braces -std=c11
LDFLAGS_DEBUG := -g3
CFLAGS_DEBUG := -g3
LDFLAGS_RELEASE := -flto
CFLAGS_RELEASE := -O2 -flto
LDFLAGS += ${LDFLAGS_${MODE}}
CFLAGS += ${CFLAGS_${MODE}}

default: all

all: clearscreen run

clearscreen:
	clear

run: build/bin/test
	./build/bin/test
build/bin/test: ${OBJFILES};
	@mkdir -p build/bin
	clang ${OBJFILES} -I ${INCDIR} ${LIBS} ${LDFLAGS} -o build/bin/test

${OBJFILES}: ${@:build/obj/%.o=%.c}
	@mkdir -p ${dir ${@}}
	clang -c ${@:build/obj/%.o=%.c} ${CFLAGS} ${INCDIR:%=-I%} -o ${@}
clean: 
	rm build/bin/test

