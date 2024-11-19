#!/bin/bash

# Arquivo de saída CSV
output_file="tempos_execucao.csv"

# Cabeçalho do CSV
echo "Diretório,Arquivo,TempoReal,NumCasos,ComChaves,MovRegistros" > "$output_file"

# Função para medir o tempo de execução dos arquivos .in
medir_tempo() {
  local dir=$1
  local file=$2

  # Extrai o nome da última pasta do diretório
  dir_name=$(basename "$dir")

  # Marca o início e o fim da execução para calcular o tempo real
  start_time=$(date +%s.%N)
  # Captura a saída do programa
  output=$(./main < "$dir/$file")
  end_time=$(date +%s.%N)
  
  # Calcula o tempo real com precisão máxima
  tempo_real=$(echo "$end_time - $start_time" | bc -l)

  # Extrai o número de casos de teste (primeiro número da saída)
  num_casos=$(echo "$output" | head -n 1 | grep -oP "^\d+")

  # Extrai os valores de com_chaves e mov_registros da saída
  com_chaves=$(echo "$output" | grep -oP "(?<=com_chaves=)[0-9]+")
  mov_registros=$(echo "$output" | grep -oP "(?<=mov_registros=)[0-9]+")

  # Escreve os dados no CSV
  echo "$dir_name,$file,$tempo_real,$num_casos,$com_chaves,$mov_registros" >> "$output_file"
}

# Loop para cada diretório
for dir in "tests/decrescente" "tests/crescente" "tests/aleatorio"; do
  # Verifica se o diretório existe
  if [ -d "$dir" ]; then
    # Loop para cada arquivo .in no diretório
    for file in "$dir"/*.in; do
      # Verifica se há arquivos .in
      if [ -f "$file" ]; then
        medir_tempo "$dir" "$(basename "$file")"
      fi
    done
  else
    echo "Diretório $dir não encontrado."
  fi
done

echo "Execução concluída. Resultados salvos em $output_file."
