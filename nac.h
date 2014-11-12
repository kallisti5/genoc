/*
 * Copyright 2014, Alexander von Gluck IV
 * Released under the terms of the GPLv3
 */

/* IUPAC nucleic acid codes */

const struct codon_matrix {
	char		code;
	const char* name;
} kCodonMatrix[] = {
	{'A', "Adenine"},
	{'C', "Cytosine"},
	{'G', "Guanine"},
	{'T', "Thymine"},
	{'?', "UNKNOWN"},
};

const struct amino_matrix {
	char		code;
	const char*	name;
} kAminoMatrix[] = {
	{'A', "Alanine"},
	{'C', "Cysteine"},
	{'D', "Aspartic Acid"},
	{'E', "Glutamic Acid"},
	{'F', "Phenylalanine"},
	{'G', "Glycine"},
	{'H', "Hisitidine"},
	{'I', "Isoleucine"},
	{'K', "Lysine"},
	{'L', "Leucine"},
	{'M', "Methionine"},
	{'N', "Asparagine"},
	{'P', "Proline"},
	{'Q', "Glutamine"},
	{'R', "Arginine"},
	{'S', "Serine"},
	{'T', "Threonine"},
	{'V', "Valine"},
	{'W', "Tryptophan"},
	{'Y', "Tyrosine"},
	{'?', "**UNKNOWN**"},
};
