OBJDIR = obj
BINDIR = bin
SEARCH = $(shell pwd)
CC = gcc
CCFLAGS =
CCFLAGS1 := $(CCFLAGS) -c
.PHONY : release
release: dirs $(BINDIR)/slbot
.PHONY : debug
debug: CCFLAGS := $(CCFLAGS) -g
debug: release
.PHONY : clean
clean:
	rm -rf $(OBJDIR)
.PHONY : clean-all
clean-all: clean
	rm -rf $(BINDIR)
dirs: $(BINDIR) $(OBJDIR)
$(BINDIR):
	@echo "[MKDIR] $(BINDIR)"
	@mkdir $(BINDIR)
$(OBJDIR):
	@echo "[MKDIR] $(OBJDIR)"
	@mkdir $(OBJDIR)
$(OBJDIR)/parsing.o: parsing.c
	@echo "[CC]    parsing.o"
	@$(CC) $(CCFLAGS1) -I$(SEARCH) -o $@ parsing.c
$(OBJDIR)/processing.o: processing.c
	@echo "[CC]    processing.o"
	@$(CC) $(CCFLAGS1) -I$(SEARCH) -o $@ processing.c
$(OBJDIR)/slbot.o: slbot.c
	@echo "[CC]    slbot.o"
	@$(CC) $(CCFLAGS1) -I$(SEARCH) -o $@ slbot.c
$(BINDIR)/slbot: $(OBJDIR)/parsing.o $(OBJDIR)/processing.o $(OBJDIR)/slbot.o
	@echo "[LD]    slbot"
	@$(CC) $(CCFLAGS) -I$(SEARCH) -o $@ $(OBJDIR)/slbot.o $(OBJDIR)/parsing.o $(OBJDIR)/processing.o
	@echo "[STRIP] slbot"
	@strip $@
