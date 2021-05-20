CC := gcc
LDFLAGS := -lm -lcurl
TARGETS := hw0502 hw0503
hw0401_OBJ := 
hw0402_OBJ := 
hw0403_OBJ :=
hw0404_OBJ := 
hw0405_OBJ := 

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