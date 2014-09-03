CC = gcc
CFLAGS = -g 
LIBS=

APP = setuid_script_helper

all:$(APP)
	@echo "done"

setuid_script_helper: setuid_script_helper.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

clean:
	rm -f $(APP)
