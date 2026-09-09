#!/bin/bash
cd "$(dirname "$0")" || exit 1
[ -x ./scheduler ] || { echo "compile antes: make"; exit 1; }
P=0; F=0
chk(){ if [ "$2" = "$3" ]; then P=$((P+1)); echo "PASS: $1"; else F=$((F+1)); echo "FAIL: $1 (obteve '$2', esperava '$3')"; fi }

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

./scheduler rate voo.txt > /dev/null 2>&1
chk "rate gera saida" "$?" "0"
grep -q "LOST DEADLINES" rate_ddc.out && chk "rate tem LOST" "$?" "0"
RLOST=$(grep -A2 "LOST DEADLINES" rate_ddc.out | grep NAV | awk '{print $2}')
chk "rate NAV LOST 1" "$RLOST" "1"

./scheduler edf voo.txt > /dev/null 2>&1
ELOST=$(grep -A2 "LOST DEADLINES" edf_ddc.out | grep NAV | awk '{print $2}')
chk "edf NAV LOST 0" "$ELOST" "0"

./scheduler rate "$TMP/fantasma.txt" > /dev/null 2>&1
chk "arquivo inexistente rc 1" "$?" "1"
[ ! -f rate_ddc.out ] || rm -f rate_ddc.out
./scheduler rate "$TMP/fantasma.txt" 2> "$TMP/e.txt" > /dev/null; grep -q "nao encontrado" "$TMP/e.txt"; chk "msg arquivo inexistente" "$?" "0"

printf "100\nBAD 10 15 5\n" > "$TMP/bad.txt"
./scheduler rate "$TMP/bad.txt" > /dev/null 2>&1; chk "C>D invalido rc 1" "$?" "1"

printf "100\nBAD 20 25 5\n" > "$TMP/bad2.txt"
./scheduler rate "$TMP/bad2.txt" > /dev/null 2>&1; chk "D>P invalido rc 1" "$?" "1"

./scheduler rate > /dev/null 2>&1; chk "sem args rc 1" "$?" "1"
./scheduler errado voo.txt > /dev/null 2>&1; chk "algoritmo invalido rc 1" "$?" "1"

./scheduler rate voo.txt > "$TMP/out.txt" 2> "$TMP/err.txt"; chk "stdout vazio" "$(wc -c < "$TMP/out.txt")" "0"

echo "-----------------------------------"
echo "suite: $P PASS, $F FAIL"
[ $F -eq 0 ]
