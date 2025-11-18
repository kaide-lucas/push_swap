#!/usr/bin/env zsh
# scripts/test_limits.sh
# Gera entradas aleatórias e testa quantas operações o push_swap gera.
# Uso:
#   ./scripts/test_limits.sh 100 100   # testa 100 iterações com 100 números
#   ./scripts/test_limits.sh 500 50    # testa 50 iterações com 500 números
# Se N for 100 ou 500, o script usa os thresholds padrão (1100 e 8500).

set -euo pipefail

PROG="./push_swap"
CHECKER="./checker_linux"

if [ ! -x "$PROG" ]; then
	printf "push_swap não encontrado ou não executável. Rode 'make' na raiz do projeto primeiro.\n" >&2
	exit 1
fi

if [ "$#" -lt 1 ]; then
	echo "Usage: $0 N [TRIALS]"
	echo "  N: número de elementos (100 ou 500 suggested)"
	echo "  TRIALS: quantas entradas aleatórias testar (default: 100 for 100, 50 for 500)"
	exit 1
fi

N=$1
TRIALS=${2:-}

if [ -z "$TRIALS" ]; then
	if [ "$N" -eq 100 ]; then
		TRIALS=100
	elif [ "$N" -eq 500 ]; then
		TRIALS=50
	else
		TRIALS=50
	fi
fi

if [ "$N" -eq 100 ]; then
	THRESHOLD=1100
elif [ "$N" -eq 500 ]; then
	THRESHOLD=8500
else
	read -r -p "Digite o threshold (máximo de operações aceito): " THRESHOLD
fi

TMPDIR=$(mktemp -d /tmp/push_swap_test.XXXXXX)
FAILED=0
MAX_OPS=0
SUM=0

echo "Testando $TRIALS entradas com $N números (threshold = $THRESHOLD)." 

echo "Resultados serão guardados em: $TMPDIR"

for i in $(seq 1 $TRIALS); do
	# gerar N números únicos aleatórios no intervalo [-10000,10000]
	# usamos seq | shuf para compatibilidade com shuf range em algumas plataformas
	INPUT=$(seq -10000 10000 | shuf -n $N | tr '\n' ' ')

	# executar push_swap e contar operações (linhas)
	OPS=$($PROG $INPUT | wc -l)
	SUM=$((SUM + OPS))
	if [ $OPS -gt $MAX_OPS ]; then
		MAX_OPS=$OPS
		# guardar caso extremo
		echo "$INPUT" > "$TMPDIR/worst_input.txt"
		echo "$OPS" > "$TMPDIR/worst_ops.txt"
	fi

	if [ $OPS -gt $THRESHOLD ]; then
		FAILED=$((FAILED + 1))
		# salvar exemplo que falhou
		echo "Trial $i failed: $OPS ops" >> "$TMPDIR/fails.txt"
		echo "$INPUT" >> "$TMPDIR/fails_inputs.txt"
	fi

	# print progress simples
	echo "[$i/$TRIALS] ops=$OPS"
	done

AVG=$((SUM / TRIALS))

cat <<EOF

Resumo:
  trials:    $TRIALS
  N:         $N
  threshold: $THRESHOLD
  max ops:   $MAX_OPS
  avg ops:   $AVG
  failed:    $FAILED

Arquivos de saída em: $TMPDIR
EOF

if [ $FAILED -gt 0 ]; then
	echo "Houveram $FAILED entradas com ops > $THRESHOLD. Veja $TMPDIR/fails.txt e $TMPDIR/fails_inputs.txt"
else
	echo "Todos os testes passaram o limite de $THRESHOLD ops."
fi

exit 0
