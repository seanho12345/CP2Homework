CC := gcc
LDFLAGS := -lm -lcurl
TARGETS := hw0501 hw0502 hw0503
hw0501_OBJ := 
hw0502_OBJ := 
hw0503_OBJ :=

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