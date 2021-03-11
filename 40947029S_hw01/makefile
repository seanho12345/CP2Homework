CC := gcc
LDFLAGS := -lm
TARGETS := hw0101 hw0102 hw0103 hw0104 hw0105
hw0101_OBJ :=
hw0102_OBJ := 
hw0103_OBJ := 
hw0104_OBJ := 
hw0105_OBJ := mystring.o

.PHONY:all
all:$(TARGETS)

.SECONDEXPANSION:

$(TARGETS):$$($$@_OBJ)
	$(CC) $@.c $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@


.PHONY:clean
clean:
	rm -rf $(TARGETS) $(foreach targ,$(TARGETS),$(foreach obj, $($(targ)_OBJ), $(obj)))