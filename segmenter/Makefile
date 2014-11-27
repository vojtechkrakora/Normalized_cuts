# VR FIT segmenter makefile

all:	segmenter
segmenter:	main.cpp Segmenter.cpp
	@mkdir -p results	
	@echo
	@echo VR FIT Segmenter building.
	@echo
	g++ -O -Wall -o segmenter main.cpp Segmenter.cpp NCut.cpp -Ivr_fit -Lvr_fit -lvr_fit -lm -ldl
	@echo Compilation successfully finished.
	@echo

clean: 
	@rm -f segmenter
	@rm -rf results
