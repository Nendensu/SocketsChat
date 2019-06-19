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

$(server): src/server/server.c
	@mkdir -p $(shell dirname $@)
	@echo "Compile server part"
	@gcc -pthread $< -o $@
