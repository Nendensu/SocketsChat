server_source_files := $(wildcard src/server/*.c)

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

$(server): $(server_source_files)
	@mkdir -p $(shell dirname $@)
	@echo "Compile server part"
	@gcc -pthread $(server_source_files) -o $@
