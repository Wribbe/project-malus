
DEPS := \
	glfw/src/libglfw3.a \
	glad/libglad.a \
	cglm/libcglm.a \


INCLUDES := \
	glfw/include \
	glad/include \
	lib \


DIR_BIN := bin
DIR_SRC := src


LIB_SRC := $(wildcard lib/*.c)
BINS := $(foreach p,$(wildcard ${DIR_SRC}/*.c),${DIR_BIN}/$(notdir ${p:.c=}))


all: ${BINS}


INCLUDES := $(foreach i,${INCLUDES},-I$i)


FLAGS = $(filter-out -lglfw3,\
	$(shell pkg-config --cflags ./glfw/src/glfw3.pc) \
	$(shell pkg-config --static --libs ./glfw/src/glfw3.pc) \
)
FLAGS := ${FLAGS} -Wall -pedantic -g


${DIR_BIN}/% : ${DIR_SRC}/%.c | ${DIR_BIN}
	gcc ${INCLUDES} $(filter %.c %.a,$^) -o $@ ${FLAGS}


${BINS} : ${DEPS} Makefile ${LIB_SRC}


glfw/%:
	git clone https://github.com/glfw/glfw
	cd glfw && git checkout latest && cmake . && make


glad/%:
	git clone https://github.com/Dav1dde/glad
	cd glad && git checkout v0.1.33 && cmake . && make


cglm/%:
	git clone https://github.com/recp/cglm
	cd cglm && git checkout v0.7.8 && cmake -DCGLM_STATIC=ON . && make


${DIR_BIN} :
	mkdir $@
