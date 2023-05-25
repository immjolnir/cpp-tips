
target := dynamic
subdir := v1 v2
all:
	for dir in $(subdir); do \
		$(MAKE) -C $$dir $(target) || exit 1; \
	done

.PHONY: clean
clean:
	for dir in $(subdir); do \
		$(MAKE) -C $$dir clean || exit 1; \
	done

