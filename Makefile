SRC_DIR = src
BUILD_DIR = build

.PHONY: all pack clean test doc run stddev help quote

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

parser: 
	$(MAKE) -C $(SRC_DIR) parser

pack: clean doc
	mkdir -p xkadlep01_xkovalj00_xferenj00/doc
	mkdir -p xkadlep01_xkovalj00_xferenj00/install
	mkdir -p xkadlep01_xkovalj00_xferenj00/repo
	cp -r doc/* xkadlep01_xkovalj00_xferenj00/doc/ 2>/dev/null || true
	cp IVSCalculator.deb xkadlep01_xkovalj00_xferenj00/install/IVSCalculator.deb
	cp -r . xkadlep01_xkovalj00_xferenj00/repo/ 2>/dev/null || true
	zip -r xkadlep01_xkovalj00_xferenj00.zip xkadlep01_xkovalj00_xferenj00/
	rm -rf xkadlep01_xkovalj00_xferenj00/

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
