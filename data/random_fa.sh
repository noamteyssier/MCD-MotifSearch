#!/usr/bin/env bash

num_records=$1


cat aa_seq.fa | paste - - | shuf | head -n $num_records | tr "\t" "\n"

#for i in {1..10}; do 
#	cat aa_seq.fa | paste - - | shuf | head -n 20 | tr "\t" "\n" > random_20_${i}.fa; done
