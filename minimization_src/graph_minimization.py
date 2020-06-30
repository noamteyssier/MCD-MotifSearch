#!/usr/bin/env python3

import subprocess
import itertools
import argparse
import shutil
import sys
import os
import re

def run_cliquer(dimacs_fn):
    """
    Run cliquer on a given dimacs file
    """
    arguments = (
        "cl", "-s", "-x", "-u", dimacs_fn
    )

    popen = subprocess.Popen(arguments, stdout=subprocess.PIPE)
    popen.wait()

    output = popen.stdout.read().decode("UTF-8")
    return output

def parse_cl(cl_output):
    literal = cl_output.strip().split(' ')

    size_val = 0
    weight_val = 0
    node_list = list()

    for entry in literal:
        if size_val == 0:
            size_val = int(entry.split("=")[-1].strip(','))
        elif weight_val == 0:
            weight_val = int(entry.strip(':').split("=")[-1])
        elif entry != '':
            node_list.append(int(entry))

    return size_val, weight_val, node_list

def log_result(iter, size):
    print(
        "Size at iter {} : {}".format(iter, size),
        file = sys.stderr
        )

def prepare_regex(regex_fn, node_list):
    exp = "^e {} [0-9]+$|^e [0-9]+ {}$\n"
    f = open(regex_fn, "w+")
    for n in node_list:
        f.write(
            exp.format(n, n)
        )
    f.close()

def prepare_outdir(outdir):
    if os.path.exists(outdir) and os.path.isdir(outdir):
        shutil.rmtree(outdir)

    os.mkdir(outdir)

def filter_dimacs(dimacs_fn, regex_fn):
    """
    remove nodes from dimacs file
    """
    tmp_fn = "{}.f".format(dimacs_fn)

    arguments = (
        "egrep -f {} -v {} > {} && mv -v {} {}".format(
            regex_fn, dimacs_fn, tmp_fn,
            tmp_fn, dimacs_fn
            )
    )

    popen = subprocess.Popen(arguments, stdout = subprocess.PIPE, shell=True)
    popen.wait()

    return

def write_clique(base_name, iter, node_list):

    f = open(base_name.format(iter), "w+")
    for n1, n2 in itertools.combinations(node_list, 2):
        f.write("{}\t{}\n".format(n1, n2))

def main(args):
    original_fn = args.input
    outdir = args.outdir
    prepare_outdir(outdir)

    regex_fn = os.path.join(outdir, "current.regex")
    dimacs_fn = os.path.join(outdir, "current.dimacs")
    base_name = os.path.join(outdir, "clique_{}.tab")
    shutil.copyfile(original_fn, dimacs_fn)

    iter = 0
    while True:

        cl_output = run_cliquer(dimacs_fn)
        size, weight, node_list = parse_cl(cl_output)
        if size > 1:
            log_result(iter, size)
            prepare_regex(regex_fn, node_list)
            filter_dimacs(dimacs_fn, regex_fn)
            write_clique(base_name, iter, node_list)
            iter+=1

        else:
            break

def get_args():
    p = argparse.ArgumentParser()
    p.add_argument(
        "-i", "--input", required=True,
        help="dimacs formatted file to minimize"
        )
    p.add_argument(
        "-o", "--outdir", default="results", type = str,
        help="output directory to write files to"
    )

    args = p.parse_args()

    if not os.path.exists(args.input):
        sys.exit(
            "Error : File does not exist :\n\n\t{}".format(args.input)
		)

    return args

if __name__ == '__main__':
    args = get_args()
    main(args)
