#!/usr/bin/env bash

num_records=$1


cat ../aa_seq.fa | paste - - | shuf | head -n $num_records | tr "\t" "\n"

