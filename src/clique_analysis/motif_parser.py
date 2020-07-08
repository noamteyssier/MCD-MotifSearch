#!/usr/bin/env python3

import argparse
import sys
import os
import re


def pull_required_lines(fn):

    regex_motif = re.compile("^MOTIF")

    f = open(fn, "r+")

    motif_list = []

    while True:

        try:

            line = next(f).strip()

            if regex_motif.match(line):

                # strip motif
                motif = line.split(" ")[1]

                # strip evalue
                _, eval_line = [next(f) for _ in range(2)]
                eval = eval_line.strip().split(" ")[-1]

                motif_list.append((motif, eval))

        except StopIteration:
            break

    return motif_list

def main(args):
    motif_list = pull_required_lines(args.input_motif)

    if not args.output_fn:
        f = sys.stdout
    else:
        f = open(args.output_fn, "w+")

    fasta_output = ">MEME-{}_{}\n{}\n"
    for idx, tup in enumerate(motif_list):
        motif, eval = tup

        f.write(
            fasta_output.format(idx, eval, motif)
        )



def get_args():
    p = argparse.ArgumentParser()
    p.add_argument(
        "-i", "--input_motif", required=True,
        help="minimal motif format text file"
        )
    p.add_argument(
        "-o", "--output_fn", required=False,
        help="output fasta to write to (default stdout)"
    )

    args = p.parse_args()

    assert os.path.exists(args.input_motif)

    return args

if __name__ == '__main__':
    args = get_args()
    main(args)
