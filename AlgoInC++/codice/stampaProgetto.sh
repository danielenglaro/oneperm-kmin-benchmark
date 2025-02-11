#!/bin/bash

# Nome del file di output
OUTPUT_FILE="progetto_completo.txt"

# Controllo se esiste già un file di output
if [ -f "$OUTPUT_FILE" ]; then
    echo "Il file $OUTPUT_FILE esiste già. Verrà sovrascritto."
    rm "$OUTPUT_FILE"
fi

# Cerca i file .cpp e .h e concatenali nel file di output
echo "Unendo i file .cpp e .h in $OUTPUT_FILE..."
find . \( -name "*.cpp" -o -name "*.h" \) -exec cat {} \; > "$OUTPUT_FILE"

# Verifica del risultato
if [ $? -eq 0 ]; then
    echo "Unione completata con successo! I file sono stati salvati in $OUTPUT_FILE."
else
    echo "Si è verificato un errore durante l'unione dei file."
fi
