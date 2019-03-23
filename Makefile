c_source_files := $(wildcard src/*.c)
c_object_files := $(patsubst src/%.c, build/obj/%.o, $(c_source_files))

server := build/server
client := build/client

.PHONY: all, clean, run, server, client

all: $(client) $(server)

clean:
	@echo "Cleaning all..."
	@rm -r build

run: $(client) $(server)
	@build/server 1337
	@build/client 127.0.0.1 1337

$(client): client.c
	@mkdir -p $(shell dirname $@)
	@echo "Compile client par"
	@gcc $< -o $@

$(server): server.c
	@mkdir -p $(shell dirname $@)
	@echo "Compile server part"
	@gcc $< -o $@
