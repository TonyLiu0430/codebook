# codebook
cloned from NCTU_Tmprry
last version: 2021/3/3

## PDF syntax highlighting

`scripts/highlight_code.py` extends Pygments for C++ types (including `using`
aliases), function calls, keywords, numbers, strings, comments and preprocessor
directives. Python snippets use the Python lexer; `.txt` snippets stay plain.

Install Pygments (`python -m pip install Pygments`) and XeLaTeX, then run `make`.
Alternatively:

```sh
python scripts/highlight_code.py
xelatex -interaction=nonstopmode -halt-on-error codebook.tex
xelatex -interaction=nonstopmode -halt-on-error codebook.tex
```

Tectonic also works after generating the highlights:
`tectonic -X compile codebook.tex`.
No shell escape or minted installation is needed. Generated files live in
`.codebook-cache/`. Customize the palette in `CodebookStyle`.
Required fonts: Consolas and Noto Sans CJK TC. On Windows, Microsoft JhengHei
is used when Noto Sans CJK TC is unavailable (Noto Sans TC is the last fallback).
