CC := gcc
LDFLAGS := -lm
TARGETS := hw0301 hw0302 hw0303 hw0304
hw0201_OBJ := 
hw0202_OBJ := 
hw0203_OBJ := 
hw0204_OBJ := 
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