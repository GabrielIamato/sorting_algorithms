#!/bin/bash

# Arquivo de saída CSV
output_file="tempos_execucao.csv"

# Cabeçalho do CSV
echo "Diretório,Arquivo,TempoReal,TempoUsuario,TempoSistema" > "$output_file"

# Função para medir o tempo de execução dos arquivos .in
medir_tempo() {
  local dir=$1
  local file=$2
  
  # Mede o tempo de execução e captura a saída do tempo
  tempo=$( (/usr/bin/time -f "%e,%U,%S" ./main < "$dir/$file") 2>&1 )
  
  # Escreve os dados no CSV
  echo "$dir,$file,$tempo" >> "$output_file"
}

# Loop para cada diretório
for dir in "tests/aleatorio" "tests/crescente" "tests/decrescente"; do
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
