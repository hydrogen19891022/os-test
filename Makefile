CFLAGS := -nostdinc -fno-builtin -fno-stack-protector -fno-optimize-sibling-calls -fno-asynchronous-unwind-tables -include ./include/code16gcc.h -O2
CFLAGS += -I ./include
LDFLAGS := -e start

OBJ_C := main.o print.o task.o sched.o
OBJ_S := start.o outc.o inst_irq.o irq.o

img.bin:rawimg.bin
	$(eval FILE_SIZE := $(firstword $(shell wc -c rawimg.bin)))
	$(eval SEC_CNT := $(shell echo $(FILE_SIZE)/512 | bc))
	$(eval REMAIN := $(shell echo $(FILE_SIZE)%512 | bc))
	$(eval ADD := $(shell if [ $(REMAIN) = "0" ]; then echo "0"; else echo "1"; fi))
	$(eval SEC_CNT := $(shell echo $(SEC_CNT)+$(ADD) | bc))
	dd conv=sync if=./rawimg.bin of=./img.bin ibs=512 count=$(SEC_CNT)

rawimg.bin: $(OBJ_C) $(OBJ_S)	
	ld -T link.lds $(LDFLAGS) $^ -o img
	objcopy -O binary img rawimg.bin



	
	
$(OBJ_S): %.o : %.S

$(OBJ_C): %.o : %.c

all:img.bin
clean:
	rm -f *.o
	rm -f *.bin
	rm -f img
