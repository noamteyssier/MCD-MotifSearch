#!/usr/bin/env bash

# pipeline to search for motifs in a given input fasta set
# used to search for a motif in the input dataset

# example usage : 
# ./pipelines/motif_finder.sh results/global_enriched/motifs data/aa_seq.fa

git_dir=${HOME}/projects/UndirectedNetwork
ca_dir=${git_dir}/src/clique_analysis

motifs_dir=$1
input_db=$2


if [ ! -d ${motifs_dir} ]; then
  echo "Error... motif directory not found ${motifs_dir}";
  exit -1;
fi

if [ ! -f ${input_db} ]; then
  echo "Error... input fasta not found ${input_db}";
  exit -1;
fi


# run motif search in dataset
for clique_dir in ${motifs_dir}/*/; do
  
  clique_num=$(basename $clique_dir)

  echo "Processing... ${clique_num}"
  
  ${ca_dir}/fimo.sh ${clique_dir} ${input_db}

done


# consolidate motif search results
for i in ${motifs_dir}/*/fimo_out/fimo.tsv; do 
  name=${i/#*motifs\//}; 
  egrep "#|^$|sequence" -v  $i | sed "s|$|    ${name/\/*/}|" ; 
done > ${motifs_dir}/motif_search.tsv


