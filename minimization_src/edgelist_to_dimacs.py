#!/usr/bin/env python3

import argparse
import sys
import os

def reader(fn, skiprows):
	"""
	read from a given filename and create :

		- dict : vertex_to_idx
			node name to index mapping

		- set : edges
			a set of edges to write to a file

	"""
	f = open(fn, "r+")


	vertex_to_idx = dict()
	edges = set()

	current_v = 1
	num_skipped = 0
	for line in f:
		if num_skipped < skiprows:
			num_skipped += 1
			continue

		if "---" in line:
			continue
			
		e1, e2 = line.strip().split('\t')[:2]

		if e1 not in vertex_to_idx:
			vertex_to_idx[e1] = current_v
			current_v += 1

		if e2 not in vertex_to_idx:
			vertex_to_idx[e2] = current_v
			current_v += 1


		edges.add(
			(vertex_to_idx[e1], vertex_to_idx[e2])
		)



	return vertex_to_idx, edges

def write_dimacs(prefix, n_vertices, n_edges, edges):
	"""
	write a dimacs file with a given edge list
	"""

	f = open("{}.dimacs".format(prefix), "w+")
	f.write(
		"p EDGE {} {}\n".format(n_vertices, n_edges)
	)

	for edge in sorted(edges):
		u, v = edge
		f.write(
			"e {} {}\n".format(u, v)
		)

	f.close()

def write_conversion(prefix, vertex_to_idx):
	"""
	write conversion table for vertices to indices
	"""

	f = open("{}.conv.txt".format(prefix), "w+")

	for v in vertex_to_idx:
		f.write(
			"{} {}\n".format(vertex_to_idx[v], v)
		)

	f.close()

def main(args):

	vertex_to_idx, edges = reader(args.input, args.skiprows)
	n_vertices = len(vertex_to_idx)
	n_edges = len(edges)

	write_dimacs(args.name, n_vertices, n_edges, edges)
	write_conversion(args.name, vertex_to_idx)

def get_args():
	p = argparse.ArgumentParser()

	p.add_argument(
		"-i", '--input', required=True, type=str,
		help = "edgelist to convert to dimacs",
		)
	p.add_argument(
		"-n", "--name", required=True, type=str,
		help = "prefix to write output files"
		)
	p.add_argument(
		"-s", "--skiprows", required=False, type=int, default=1,
		help = "number of rows to skip in input file (default = 1)"
	)

	args = p.parse_args()

	if not os.path.exists(args.input):
		sys.exit(
			"Error : File does not exist :\n{}".format(args.input)
			)

	return args

if __name__ == '__main__':
	args = get_args()
	main(args)
