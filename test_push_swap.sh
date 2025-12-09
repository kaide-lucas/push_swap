shell

# Quantidade de números
ARG_SIZE=5

# Caminho do push_swap e checker
PUSH_SWAP=./push_swap
CHECKER=./checker_linux  # ajuste se necessário

# Gera os 100 números aleatórios
ARG=$(shuf -i 0-999 -n $ARG_SIZE | tr '\n' ' ')

echo "📌 Testando com 100 números..."
echo "Args:"
echo "$ARG"
echo "--------------------------------"

# Executa o push_swap + checker
RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
OPS=$($PUSH_SWAP $ARG | wc -l)

echo "Checker: $RESULT"
echo "Número de operações: $OPS"