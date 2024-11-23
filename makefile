result = bil
sourcefiles = $(wildcard src/*.cpp)
objectfiles = $(patsubst src/%.cpp,build/%.o,$(sourcefiles))
headerfiles = $(wildcard src/lib/*.hpp)

.PHONY: exec objects clean all validate clean

all: validate exec

exec: $(result)

$(result): $(objectfiles)
	g++ -o dest/$(result) $(objectfiles)

build/%.o: src/%.cpp $(headerfiles)
	g++ -c -o $@ $< -O4

validate:
	mkdir -p dest build

clean:
	rm -rf build/ dest/
