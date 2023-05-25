target := static 
# target := dynamic

default: all
all: deps client

SUBDIR := dynamic-lib service
deps: 
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir target=$(target) || exit 1; \
	done

.PHONY: client
client:
	g++ -std=c++14 client.cpp \
		-Idynamic-lib -Iservice \
		-Ldynamic-lib/v1 -lstudent \
		-Ldynamic-lib/v2 -lstudent \
		-Lservice -lservice \
		-o client

.PHONY: clean
clean:
	rm -rf client fixed
	for dir in $(SUBDIR); do \
		$(MAKE) -C $$dir clean; \
	done