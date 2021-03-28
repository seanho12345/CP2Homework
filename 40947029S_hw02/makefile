CC := gcc
LDFLAGS := -lm
TARGETS := hw0201 hw0202 hw0203 hw0204 hw0205
hw0201_OBJ := mixed.o
hw0202_OBJ := 
hw0203_OBJ := 
hw0204_OBJ := bignum.o
hw0205_OBJ := 

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