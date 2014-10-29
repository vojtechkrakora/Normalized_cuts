# VR FIT segmenter makefile

all:	segmenter
segmenter:	main.cpp Segmenter.cpp
	@echo
	@echo VR FIT Segmenter building.
	@echo
	g++ -O -Wall -o segmenter main.cpp Segmenter.cpp -Ivr_fit -Lvr_fit -lvr_fit -lm -ldl
	@echo Compilation successfully finished.
	@echo
