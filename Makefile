CC ?= gcc
PKG = gtk+-3.0
CFLAGS = -Wall -Wextra -std=c11 -Isrc $(shell pkg-config --cflags $(PKG))
LDFLAGS = $(shell pkg-config --libs $(PKG))

BUILD = build
SRC = \
	src/main.c \
	src/processors/directories.c \
	src/ui/window/window.c \
	src/ui/mainbox.c \
	src/ui/toolbar.c \
	src/ui/filearea.c \
	src/ui/scrolledwindow.c \
	src/ui/fileitem.c \
	src/ui/window/menu.c \
	src/ui/window/menu_actions.c \
	src/ui/actionBar.c

OBJ = $(patsubst src/%.c,$(BUILD)/%.o,$(SRC))
BIN = edens

.PHONY: all clean run

all: $(BIN) compile_commands.json

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

compile_commands.json: $(SRC) Makefile
	@SRC="$(SRC)" CC="$(CC)" PKG="$(PKG)" python3 -c 'import json,os,pathlib,subprocess; cflags=subprocess.check_output(["pkg-config","--cflags",os.environ["PKG"]],text=True).split(); root=pathlib.Path.cwd().resolve(); cc=os.environ["CC"]; db=[]; \
[db.append({"directory":str(root),"arguments":[cc,"-Wall","-Wextra","-std=c11","-Isrc",*cflags,"-c",src,"-o","build/"+str(pathlib.Path(src.removeprefix("src/")).with_suffix(".o"))],"file":str(root/src)}) for src in os.environ["SRC"].split()]; \
(root/"compile_commands.json").write_text(json.dumps(db,indent=2)+"\n")'

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BUILD) $(BIN)
