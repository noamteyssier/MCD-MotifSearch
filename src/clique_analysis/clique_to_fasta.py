#!/usr/bin/env python3

import argparse
import sys
import os
import gzip


def seqReader(fn):
    """
    iterate through sequences and yield as generator
    """
    def openSeq(fn):
        if 'gz' in fn:
            return gzip.open(fn, 'rt')
        else:
            return open(fn, 'r')

    def num_iter(fn):
        if 'fastq' in fn or 'fq' in fn:
            return 4
        else:
            return 2

    n = num_iter(fn)

    with openSeq(fn) as f:
        while True:
            try:
                yield [next(f).strip('\n') for _ in range(n)]
            except StopIteration:
                break

def conv_to_dict(conv_fn):
    """
    creates a lookup table for idx to target name
    """

    conv_dict = dict()
    f = open(conv_fn, "r+")
    for line in f:
        idx, name = line.strip().split(" ")
        conv_dict[idx] = name

    return conv_dict

def edgelist_to_nodeset(conv_dict, edgelist_fn):
    """
    convert an edgelist of node indices to a set of target names using
    a provided lookup table
    """

    nodeset = set()
    f = open(edgelist_fn, "r+")
    for line in f:
        node_indices = line.strip().split("\t")[:2]
        node_names = [conv_dict[idx] for idx in node_indices]
        [nodeset.add(n) for n in node_names]

    return nodeset

def fasta_to_dict(fasta_fn):
    """
    moves fasta to memory for lookup with header
    * doesn't scale well with large fasta files *
    """

    fasta_dict = {
        h : s for h,s in seqReader(fasta_fn)
    }

    return fasta_dict

def main(args):

    conv_dict = conv_to_dict(args.conv)
    nodeset = edgelist_to_nodeset(conv_dict, args.edgelist)
    fasta_dict = fasta_to_dict(args.fasta)

    if not args.output:
        f_out = sys.stdout
    else:
        f_out = open(args.output, "w+")


    target_lookup = ">{}"
    fasta_format = "{}\n{}\n"
    for n in nodeset:
        node_header = target_lookup.format(n)
        node_seq = fasta_dict[node_header]
        f_out.write(
            fasta_format.format(node_header, node_seq)
        )

    pass

def get_args():
    p = argparse.ArgumentParser()
    p.add_argument(
        "-i", '--edgelist', required=True,
        help='input clique to create fasta from as edgelist'
        )
    p.add_argument(
        "-c", "--conv", required=True,
        help="conversion file to convert target idx to target name"
        )
    p.add_argument(
        "-f", "--fasta", required=True,
        help="input fasta to scrape target names from"
    )
    p.add_argument(
        "-o", "--output", required=False, type=str,
        help="output fasta to write to (default = stdout)"
    )

    args = p.parse_args()

    assert os.path.exists(args.edgelist)
    assert os.path.exists(args.conv)
    assert os.path.exists(args.fasta)

    return args

if __name__ == '__main__':
    args = get_args()
    main(args)
