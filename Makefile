

DEPS := \
	glfw/src/libglfw3.a \
	glad/libglad.a \

INCLUDES := \
	glfw/include \
	glad/include \
	glfw/deps \


DIR_BIN := bin
DIR_SRC := src

BINS := $(foreach p,$(wildcard ${DIR_SRC}/*.c),${DIR_BIN}/$(notdir ${p:.c=}))


FLAGS := \
	$(shell pkg-config --cflags ./glfw/src/glfw3.pc) \
	$(shell pkg-config --static --libs ./glfw/src/glfw3.pc) \

FLAGS := $(filter-out -lglfw3,${FLAGS})

all: ${BINS}


${BINS} : ${DEPS} Makefile
INCLUDES := $(foreach i,${INCLUDES},-I$i)


${DIR_BIN}/% : ${DIR_SRC}/%.c | ${DIR_BIN}
	gcc ${FLAGS} ${INCLUDES} $(filter %.c %.h %.a,$^) -o $@


glfw/%:
	git clone https://github.com/glfw/glfw
	cd glfw && git checkout latest && cmake . && make


glad/%:
	git clone https://github.com/Dav1dde/glad
	cd glad && git checkout v0.1.33 && cmake . && make


${DIR_BIN} :
	mkdir $@
