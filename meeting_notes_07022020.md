# meeting notes w/ Bryan (07-02-2020)


## Go over pipeline

- take enriched peptide set (around 2.7k peptides)

- create background markov model from peptide set
	- essentially an amino acid frequency table

- iteratively select maximum maximal clique

- search for 3 Motifs using MEME and the enriched set background

- blast all clique motifs against entire falciparum epitope set


## Questions 

- What number of motifs are already known?
	- 54.95% of 293 total cliques have at least 1 known motif

- Of the motifs that are unknown:

	- is there correlation with node membership?

		slightly, but the medians of the groups are 3 and [4, 4.5, 5]

	- is there correlation with patient response? 

		more of a correlation, medians are 26 and [31, 36, 38]

		but still found in a nontrivial amount of patients. 


	- What do the unknown motifs/cliques look like?

		- chemically textured 

		- high inter- and intra- repeat regions in clique

		- involved in virulence pathways / surface protein / or exported

## Takeaways

- method provides a way to accurately find known and validated epitopes
- method also finds many plausible novel epitopes


## Where to go with this

- clique differentiation by strata
	- agecat
	- location/agecat


- clique differentiation with immunity
	- don't know how much power this will have
	- don't know exactly how to run a regression for this


- compare with different minimum fractions of clique recovery


- could do an analysis modeled after a minimum spanning tree 
	
	i.e. take a motif and explore how many branches away is required before recognition is lost


	[hit] [nohit]  [hit]-[nohit]
      |     |       | 
	[k1] [k2] [k3] [k4] [k5] 
					|
				   [hit]-[hit]



## How to present this?



## Notes 

- finding a way to normalize membership size by input library
- correlating strain specific sequence diversity with inclusion in library
- increase number of motifs returned 
- what proportion of the peptides in the full set have the motif 