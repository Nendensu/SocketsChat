c_source_files := $(wildcard src/*.c)
c_object_files := $(patsubst src/%.c, build/obj/%.o, $(c_source_files))

server := build/server
client := build/client

.PHONY: all, clean, server, client

all: $(client) $(server)

clean:
	@echo "Cleaning all..."
	@rm -r build

server: $(server)

client: $(client)

$(client): src/client.c
	@mkdir -p $(shell dirname $@)
	@echo "Compile client part"
	@gcc $< -o $@

$(server): src/server.c
	@mkdir -p $(shell dirname $@)
	@echo "Compile server part"
	@gcc $< -o $@
