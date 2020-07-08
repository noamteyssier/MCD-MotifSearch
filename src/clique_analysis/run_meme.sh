#!/usr/bin/env bash

git_dir=${HOME}/projects/UndirectedNetwork
ca_src=${git_dir}/src/clique_analysis

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
  -mod anr \
  -nmotifs 50 -minw 7 -maxw 12 \
  -evt 1e-05 \
  -objfun classic -markov_order 0 -V

# create visualization html from xml
meme-meme_xml_to_html ${output_dir}/meme.xml ${output_dir}/meme.html

# extract meme motif information
meme-meme-get-motif -all ${output_dir}/meme.txt > ${output_dir}/minimal_meme.txt

# create motif fasta
${ca_dir}/motif_parser \
  -i ${output_dir}/minimal_meme.txt \
  -o ${output_dir}/motif.fa
  
# fgrep "MOTIF" ${output_dir}/minimal_meme.txt | \
#   awk 'OFS="\n"{print ">"$3,$2}' \
#   > ${output_dir}/motif.fa
