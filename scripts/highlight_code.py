"""Generate custom print-friendly highlights before TeX runs; no shell escape."""
from pathlib import Path
import re

from pygments import format as format_tokens, lex
from pygments.formatters import LatexFormatter
from pygments.lexers import CppLexer, PythonLexer, TextLexer
from pygments.style import Style
from pygments.token import Comment, Error, Keyword, Name, Number, Operator, String, Text

ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / ".codebook-cache"


class CodebookStyle(Style):
    default_style = "#263238"
    styles = {
        Text: "", Keyword: "#7C2DCE", Keyword.Type: "#008577",
        Keyword.Constant: "#B85C00", Name: "#263238", Name.Class: "#008577",
        Name.Function: "#005FCC", Name.Namespace: "#008577",
        Name.Builtin: "#005FCC", Name.Constant: "#B85C00",
        Name.Decorator: "#7C2DCE", Number: "#B85C00", String: "#C52A4A",
        String.Escape: "#7C2DCE", Comment: "#478148",
        Comment.Preproc: "#7C2DCE", Comment.PreprocFile: "#C52A4A",
        Operator: "#46515E", Error: "#263238",
    }


STL_TYPES = set("""
array bitset complex deque forward_list function initializer_list list map
multimap multiset optional pair priority_queue queue set span stack string
string_view tuple unordered_map unordered_multimap unordered_multiset
unordered_set vector variant mt19937 mt19937_64 uniform_int_distribution
ordered_set pairing_heap uint32_t uint64_t int32_t int64_t __int128 __uint128_t
size_t ptrdiff_t FILE
""".split())


def cpp_tokens(source):
    """Recognize aliases, user types, macros and calls; preserve source exactly.

    This is lexical highlighting, not a C++ parser. Comments and strings are
    excluded from declaration detection. Incomplete snippets are supported.
    """
    tokens = list(lex(source, CppLexer(ensurenl=False, stripnl=False)))
    code = "".join(" " * len(v) if t in Comment or t in String else v for t, v in tokens)
    types = STL_TYPES | set(re.findall(r"\busing\s+(\w+)\s*=", code))
    types.update(re.findall(r"\b(?:class|struct|union|enum(?:\s+class)?)\s+(\w+)", code))
    types.update(re.findall(r"\btypedef\b[^;]*?\b(\w+)\s*;", code))
    macros = set(re.findall(r"^\s*#\s*define\s+(\w+)", source, re.MULTILINE))
    significant = [i for i, (_, v) in enumerate(tokens) if v.strip()]
    following = {i: tokens[j][1] for i, j in zip(significant, significant[1:])}
    for i, (token, value) in enumerate(tokens):
        if token in Name:
            if value in types:
                token = Name.Class
            elif value in macros:
                token = Name.Constant
            elif following.get(i) == "(":
                token = Name.Function
            elif following.get(i) == ":" and i + 2 < len(tokens):
                if tokens[i + 1][1] == tokens[i + 2][1] == ":":
                    token = Name.Namespace
        yield token, value


def main():
    CACHE.mkdir(exist_ok=True)
    formatter = LatexFormatter(
        style=CodebookStyle, commandprefix="CB",
        verboptions="fontsize=\\footnotesize,tabsize=2,breaklines=true,"
        "breakanywhere=true,breaksymbolleft={},breaksymbolright={},"
        "breakindent=1em,breakautoindent=true,baselinestretch=1,"
        "formatcom=\\color{CodeText}",
    )
    (CACHE / "style.tex").write_text(formatter.get_style_defs(), encoding="utf-8")
    content = (ROOT / "content.tex").read_text(encoding="utf-8")
    files = re.findall(r"\\lstinputlisting(?:\[[^\]]*\])?\{([^}]+)\}", content)
    for filename in files:
        path = ROOT / filename
        source = path.read_text(encoding="utf-8-sig")
        if path.suffix in {".cpp", ".h", ".hpp"}:
            tokens = cpp_tokens(source)
        else:
            lexer = PythonLexer if path.suffix == ".py" else TextLexer
            tokens = lex(source, lexer(ensurenl=False, stripnl=False))
        # Plain whitespace lets fvextra see indentation when wrapping a line.
        tokens = ((Text, value) if token in Text else (token, value)
                  for token, value in tokens)
        destination = CACHE / (filename + ".tex")
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(format_tokens(tokens, formatter), encoding="utf-8")
    print(f"Highlighted {len(files)} snippets in {CACHE.name}/")


if __name__ == "__main__":
    main()
