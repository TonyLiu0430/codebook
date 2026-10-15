PYTHON ?= $(shell command -v python3 2>/dev/null || echo python)
XELATEX ?= xelatex
SOURCES := $(wildcard Basic/* DarkCode/* Geometry/* Flow/* Math/* Graph/* Graph/Matching/* DataStructure/* String/* Other/*)

codebook.pdf: codebook.tex content.tex scripts/highlight_code.py $(SOURCES)
	$(PYTHON) scripts/highlight_code.py
	$(XELATEX) -interaction=nonstopmode -halt-on-error codebook.tex
	$(XELATEX) -interaction=nonstopmode -halt-on-error codebook.tex
	# third pass: the filled TOC shifts pages, so record them again
	$(XELATEX) -interaction=nonstopmode -halt-on-error codebook.tex
	$(RM) codebook.aux codebook.log codebook.toc

clean:
	$(RM) codebook.pdf
