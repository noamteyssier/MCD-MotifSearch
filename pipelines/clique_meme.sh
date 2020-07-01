#!/usr/bin/env bash

# pipeline to run a clique set through meme and discover motifs

## Requires input directory to be structured in the format
## previous pipelines output: ie

## {prefix}.[conv.txt, fa]
## cliques/

## MUST be in input directory.

git_dir=${HOME}/projects/UndirectedNetwork/
ca_dir=${git_dir}/src/clique_analysis

input_dir=$1
prefix=$2

clique_dir=${input_dir}/cliques
conv_fn=${input_dir}/${prefix}.conv.txt
fasta_fn=${input_dir}/${prefix}.fa

output_dir=${input_dir}/motifs
bg_model=${output_dir}/${prefix}.markov.bg


# checks if clique dir is in directory
if  [ ! -d ${clique_dir} ]; then
  echo "error clique path not found : ${clique_dir}"
  exit -1;
fi

# checks if conversion table is in directory
if [ ! -f ${conv_fn} ]; then
  echo "error conversion table not found : ${conv_fn}"
  exit -1;
fi

# checks if fasta file is in directory
if [ ! -f ${fasta_fn} ]; then
  echo "error input fasta not found : ${fasta_fn}"
  exit -1;
fi

# overwrites existing ouput directory
if [ -d ${output_dir} ]; then
  echo "Overwriting existing output directory..."
  rm -rfv ${output_dir}
fi
mkdir -v ${output_dir}


# create custom background model for the clique set using the input fasta
meme-fasta-get-markov -m 0 -protein ${fasta_fn} > ${bg_model}


# iterate through cliques and run meme on each
for clique_fn in ${clique_dir}/clique_*.tab; do

  clique_idx=$(basename ${clique_fn} .tab)
  clique_outdir=${output_dir}/${clique_idx}
  clique_fa=${clique_dir}/${clique_idx}.fa

  mkdir -v $clique_outdir

  python3 ${ca_dir}/clique_to_fasta.py \
    -i ${clique_fn} -c ${conv_fn} -f ${fasta_fn} -o ${clique_fa}

  bash ${ca_dir}/run_meme.sh \
    ${clique_fa} ${bg_model} ${clique_outdir}


done;
