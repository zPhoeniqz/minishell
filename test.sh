#!/usr/bin/env bash
set -euo pipefail

BIN="${BIN:-./tokenizer}"

if [[ ! -x "$BIN" ]]; then
  echo "ERROR: tokenizer binary not found/executable at: $BIN"
  echo "Run: BIN=./your_binary_name $0"
  exit 1
fi

pass=0
fail=0

run_case() {
  local name="$1"
  local input="$2"
  shift 2
  local -a expected=("$@")

  mapfile -t got < <("$BIN" "$input")

  local ok=1
  if [[ "${#got[@]}" -ne "${#expected[@]}" ]]; then
    ok=0
  else
    for i in "${!expected[@]}"; do
      if [[ "${got[$i]}" != "${expected[$i]}" ]]; then
        ok=0
        break
      fi
    done
  fi

  if [[ $ok -eq 1 ]]; then
    printf "✅ %-35s\n" "$name"
    pass=$((pass+1))
  else
    printf "❌ %-35s\n" "$name"
    echo "  input:    $input"
    echo "  expected: (${#expected[@]})"
    for t in "${expected[@]}"; do echo "    [$t]"; done
    echo "  got:      (${#got[@]})"
    for t in "${got[@]}"; do echo "    [$t]"; done
    echo
    fail=$((fail+1))
  fi
}

run_fail_case() {
  local name="$1"
  local input="$2"

  if "$BIN" "$input" >/dev/null 2>&1; then
    printf "❌ %-35s\n" "$name"
    echo "  input:    $input"
    echo "  expected: non-zero exit"
    fail=$((fail+1))
  else
    printf "✅ %-35s\n" "$name"
    pass=$((pass+1))
  fi
}

# -------------------------
# Core parentheses behavior
# -------------------------
run_case "paren spaced" \
  "echo ( test )" \
  "echo" "(" "test" ")"

run_case "paren adjacent word" \
  "echo (test)" \
  "echo" "(" "test" ")"

run_case "paren adjacent both sides" \
  "a(b)c" \
  "a" "(" "b" ")" "c"

run_case "nested parens" \
  "((test))" \
  "(" "(" "test" ")" ")"

run_case "only parens" \
  "()()(" \
  "(" ")" "(" ")" "("

run_case "paren with tabs/spaces" \
  $'echo\t(test)\t( x )' \
  "echo" "(" "test" ")" "(" "x" ")"

# -------------------------
# Quotes shield parentheses
# -------------------------
run_case "double quotes keep parens" \
  'echo "(test)"' \
  "echo" "\"(test)\""

run_case "single quotes keep parens" \
  "echo '(test)'" \
  "echo" "'(test)'"

run_case "quotes with spaces + parens" \
  'echo "a ( b ) c"' \
  "echo" "\"a ( b ) c\""

run_case "mix quoted + unquoted" \
  'x"(y)"z (a) "b(c)d"' \
  "x\"(y)\"z" "(" "a" ")" "\"b(c)d\""

# -------------------------
# Error behavior
# -------------------------
run_fail_case "unclosed quote should fail" \
  'echo "unterminated'

# -------------------------
# Delimiters + parentheses
# -------------------------
run_case "multiple spaces" \
  "  (  test )  " \
  "(" "test" ")"

run_case "no spaces around parens" \
  "(a)(b)" \
  "(" "a" ")" "(" "b" ")"

run_case "parens near delimiters" \
  $'cmd\t(\targ\t)\n' \
  "cmd" "(" "arg" ")"

# -------------------------
# Summary
# -------------------------
echo
echo "Passed: $pass"
echo "Failed: $fail"
[[ $fail -eq 0 ]]
