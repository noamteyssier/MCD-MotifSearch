#!/usr/bin/env bash

input_fa=$1
input_db=$2
output_tab=$3

if [ ! -f ${input_fa} ]; then
  echo "Input fasta not found : ${input_fa}";
  exit -1;
fi


if [ ! -f ${input_db} ]; then
  echo "Input database not found : ${input_db}";
  exit -1;
fi

# create header for output file
echo "qseqid sseqid pident length mismatch gapopen qstart qend sstart send evalue bitscore" | \
  sed "s/ /\t/g" > ${output_tab}

# run blast
time blastp -db ${input_db} -query ${input_fa} -outfmt 6 \
  >> ${output_tab}
