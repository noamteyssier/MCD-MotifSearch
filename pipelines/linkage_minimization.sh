#!/usr/bin/env bash

# Convenience script to take a fasta file to a full minimized clique set

#git_dir=${HOME}/projects/UndirectedNetwork
git_dir=$1
min_dir=${git_dir}/src/minimization
link_dir=${git_dir}/src/linkage

input_fa=$2
base_name=$3
outdir=$4

linkage_fn=${outdir}/${base_name}.edgelist
dimacs_fn=${outdir}/${base_name}.dimacs
conv_fn=${outdir}/${base_name}.conv.txt
min_outdir=${outdir}/cliques
merged_cliques=${min_outdir}/merged_cliques.tab
final_cliques=${outdir}/${base_name}.cliques.edgelist


# checks if input fasta exists
if [ -f $input_fa ]; then
  echo "Processing : ${input_fa}";
else
  echo "file : (${input_fa}) does not exist"
  exit;
fi
echo

# creates output directory
if [ -d $outdir ]; then
  rm -rfv $outdir
  echo
fi
mkdir $outdir

# copies input fasta to outdir
cp -v ${input_fa} ${outdir}/${base_name}.fa

# calculates linkages on fasta
${link_dir}/bin/distance_network ${input_fa} ${linkage_fn} 1

# creates dimacs and conversion table from edgelist
${min_dir}/edgelist_to_dimacs.py -i ${linkage_fn} -n ${outdir}/${base_name}

# runs minimization on dimacs
${min_dir}/graph_minimization.py -i ${dimacs_fn} -o ${min_outdir}

# concatenates all cliques
cat ${min_outdir}/clique*tab > ${merged_cliques}

# converts idx to original names
${min_dir}/convert_names.py -i ${merged_cliques} -c ${conv_fn} -o ${final_cliques}
