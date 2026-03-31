SRC_DIR = src
BUILD_DIR = build

.PHONY: all pack clean test doc run stddev help

all:
	$(MAKE) -C $(SRC_DIR)

stddev:
	$(MAKE) -C $(SRC_DIR) stddev

run: all
	./$(BUILD_DIR)/calculator

test:
	$(MAKE) -C $(SRC_DIR) test

doc:
	doxygen $(SRC_DIR)/Doxyfile

pack: clean
	zip -r xlogin01_xlogin02_xlogin03_xlogin04.zip \
		src/ mockup/ plan/ profiling/ manual.pdf \
		README.md hodnoceni.txt skutecnost.txt \
		debugging.png screenshot.png Makefile .gitignore

clean:
	$(MAKE) -C $(SRC_DIR) clean
	rm -rf $(BUILD_DIR) *.zip

quote:
	@echo "===================================="
	@echo "     BEAR TOGETHER STROOOOOOONK!    "
	@echo "     BEAR TOGETHER SMAAAAAAAART!    "
	@echo "   -- Bear_Together_Stronk (2026)   "
	@echo "===================================="
help:
	@echo " Requirements: g++, make, doxygen"
	@echo " "
	@echo "   make         - Build calculator + stddev"
	@echo "   make run     - Run the calculator"
	@echo "   make stddev  - Build stddev program"
	@echo "   make test    - Run math library tests"
	@echo "   make doc     - Generate Doxygen docs"
	@echo "   make pack    - Create submission zip"
	@echo "   make clean   - Remove build files"
