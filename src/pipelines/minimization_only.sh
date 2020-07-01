#!/usr/bin/env bash

# Convenience script to take an edgelist to a full minimized clique set

git_dir=${HOME}/projects/UndirectedNetwork
min_dir=${git_dir}/src/minimization
link_dir=${git_dir}/src/linkage

linkage_fn=$1
base_name=$2
outdir=$3

# linkage_fn=${outdir}/${base_name}.edgelist
dimacs_fn=${outdir}/${base_name}.dimacs
conv_fn=${outdir}/${base_name}.conv.txt
min_outdir=${outdir}/results
merged_cliques=${min_outdir}/merged_cliques.tab
final_cliques=${outdir}/${base_name}.cliques.edgelist


# creates output directory
if [ -d $outdir ]; then
  rm -rfv $outdir
  echo
fi
mkdir $outdir

# checks if input fasta exists
if [ -f $linkage_fn ]; then
  echo "Processing : ${input_fa}";
  cp -v $linkage_fn ${outdir}/
  linkage_fn=${outdir}/$(basename $linkage_fn)

else
  echo "file : (${input_fa}) does not exist"
  exit;
fi
echo

# calculates linkages on fasta
# ${link_dir}/bin/distance_network ${input_fa} ${linkage_fn} 1

# creates dimacs and conversion table from edgelist
${min_dir}/edgelist_to_dimacs.py -i ${linkage_fn} -n ${outdir}/${base_name}

# runs minimization on dimacs
${min_dir}/graph_minimization.py -i ${dimacs_fn} -o ${min_outdir}

# concatenates all cliques
cat ${min_outdir}/clique*tab > ${merged_cliques}

# converts idx to original names
${min_dir}/convert_names.py -i ${merged_cliques} -c ${conv_fn} -o ${final_cliques}
