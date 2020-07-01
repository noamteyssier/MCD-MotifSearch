#!/usr/bin/env python3

import argparse
import sys
import os


def build_dict(conv_fn):
    f = open(conv_fn, "r+")

    conv_dict = {}
    for line in f:
        idx, name = line.strip().split(" ")
        conv_dict[idx] = name

    return conv_dict

def main(args):

    conv_dict = build_dict(args.conv)

    f_in = open(args.input, "r+")

    if not args.output:
        f_out = sys.stdout
    else:
        f_out = open(args.output, "w+")

    out_str = "{}\t{}\n"
    for line in f_in:
        u, v  = line.strip().split("\t")
        f_out.write(
            out_str.format(
                conv_dict[u], conv_dict[v]
            )
        )


def get_args():
    p = argparse.ArgumentParser()
    p.add_argument(
        "-i", "--input", required=True,
        help="clique file to convert back to original names"
    )
    p.add_argument(
        "-c", "--conv", required=True,
        help="Conversion file to convert index back to name"
    )
    p.add_argument(
        "-o", "--output", required=False,
        help="Output file to write to, defaults to stdout"
    )

    args = p.parse_args()

    assert os.path.exists(args.input)
    assert os.path.exists(args.conv)
    return args

if __name__ == '__main__':
    args = get_args()
    main(args)
