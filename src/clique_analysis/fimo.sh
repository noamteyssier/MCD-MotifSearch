#!/usr/bin/env bash

input_dir=$1
query_db=$2
bg_file=$3

if [ ! -d ${input_dir} ]; then
  echo "Error... input dir not found ${input_dir}"
  exit -1;
fi;

if [ ! -f ${input_dir}/minimal_meme.txt ]; then
  echo "Minimal meme not found ${input_dir}/minimal_meme.txt"
  exit -1;
fi;

if [ ! -f ${query_db} ]; then
  echo "Error... input db not found ${query_db}"
  exit -1;
fi;

if [ ! -f ${bg_file} ]; then
  echo "Error... background file not found ${bf_file}"
  exit -1;
fi

time meme-fimo \
  --thresh 1e-10 \
  --oc ${input_dir}/fimo_out \
  --bfile ${bg_file} \
  ${input_dir}/minimal_meme.txt \
  ${query_db}
