#!/usr/bin/env bash

input_fa=$1
bg_model=$2
output_dir=$3

if [ ! -f ${input_fa} ]; then
  echo "error fasta not found... ${input_fa}"
  exit -1;
fi;


if [ ! -f ${bg_model} ]; then
  echo "error markov background model not found... ${bg_model}"
  exit -1;
fi;

time meme-meme \
  ${input_fa} \
  -protein \
  -oc ${output_dir} \
  -bfile ${bg_model} \
  -mod anr -nmotifs 3 -minw 6 -maxw 12 \
  -objfun classic -markov_order 0 -V

meme-meme_xml_to_html ${output_dir}/meme.xml ${output_dir}/meme.html
