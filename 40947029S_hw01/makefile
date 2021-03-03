CC := gcc
LDFLAGS := -lm
TARGETS := hw0101 hw0102 hw0103 hw0104 hw0105
hw0601_OBJ :=
hw0602_OBJ := 
hw0603_OBJ := 
hw0604_OBJ := 
hw0605_OBJ := 

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