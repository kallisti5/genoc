/*
 * Copyright 2014, Alexander von Gluck IV
 * Released under the terms of the GPLv3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nac.h"


#define COUNT_OF(a) (sizeof(a) / sizeof(a[0]))


struct codon_triplet {
	char a;
	char b;
	char c;
} kTriplets[4096];


static int
load_file(char* filename)
{
	FILE* fh;
	fh = fopen(filename, "rb");
	if (fh == NULL)
		return -1;

	fseek(fh, 0, SEEK_END);
	off_t length = ftell(fh);
	rewind(fh);

	char* buffer = (char*)calloc(1, length + 1);
	if (!buffer) {
		printf("Out of memory\n");
		fclose(fh);
		return -1;
	}

	int tripletIndex = 0;
	while (tripletIndex < length / (sizeof(char) * 3)) {
		size_t read = fread(&kTriplets[tripletIndex], sizeof(char), 3, fh);
		if (read != 3) {
			printf("Error reading triplet\n");
		}
		tripletIndex++;
	}
	printf("Read in %d codon triplets.\n", tripletIndex);
	fclose(fh);

	return tripletIndex;
}


static int
decode_codon(char codon)
{
	for (int i = 0; i < COUNT_OF(kCodonMatrix); i++) {
		if (kCodonMatrix[i].code == codon)
			return i;
	}
	return -1;
}


static int
decode_amino(char amino)
{
	for (int i = 0; i < COUNT_OF(kAminoMatrix); i++) {
		if (kAminoMatrix[i].code == amino)
			return i;
	}
	return -1;
}


static char
translate_amino(struct codon_triplet* t)
{
	switch(t->a) {
		case 'T':
			switch(t->b) {
				case 'T':
					switch (t->c) {
						case 'T':
						case 'C':
							return 'F';
							break;
						case 'A':
						case 'G':
							return 'L';
							break;
					}
					break;
				case 'C':
					return 'S';
					break;
				case 'A':
					switch (t->c) {
						case 'T':
						case 'C':
							return 'Y';
							break;
						case 'A':
						case 'G':
							// STOP
							return 'X';
							break;
					}
					break;
				case 'G':
					switch (t->c) {
						case 'T':
						case 'C':
							return 'C';
							break;
						case 'A':
							// STOP
							return 'X';
							break;
						case 'G':
							return 'W';
							break;
					}
					break;
			}
			break;
		case 'C':
			switch(t->b) {
				case 'T':
					return 'L';
					break;
				case 'C':
					return 'P';
					break;
				case 'A':
					switch (t->c) {
						case 'T':
						case 'C':
							return 'H';
							break;
						case 'A':
						case 'G':
							return 'Q';
							break;
					}
					break;
				case 'G':
					return 'R';
					break;
			}
			break;
		case 'A':
			switch (t->b) {
				case 'T':
					switch(t->c) {
						case 'T':
						case 'C':
						case 'A':
							return 'I';
							break;
						case 'G':
							return 'M';
					}
					break;
				case 'C':
					return 'T';
					break;
				case 'A':
					switch(t->c) {
						case 'T':
						case 'C':
							return 'N';
							break;
						case 'A':
						case 'G':
							return 'K';
							break;
					}
					break;
				case 'G':
					switch(t->c) {
						case 'T':
						case 'C':
							return 'S';
							break;
						case 'A':
						case 'G':
							return 'R';
							break;
					}
					break;
			}
			break;
		case 'G':
			switch(t->b) {
				case 'T':
					return 'V';
					break;
				case 'C':
					return 'A';
					break;
				case 'A':
					switch(t->c) {
						case 'T':
						case 'C':
							return 'D';
							break;
						case 'A':
						case 'G':
							return 'E';
							break;
					}
					break;
				case 'G':
					return 'G';
					break;
			}
			break;
	}
	return '?';
}


int
main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("usage %s filename\n", argv[0]);
		return 1;
	}

	int count = load_file(argv[1]);

	printf("Amino Acid Chain 0\n");
	for (int i = 0; i < count; i++) {
		struct codon_triplet* triplet = &kTriplets[i];
		char aminoCode = translate_amino(triplet);
		if (aminoCode == 'X') {
			printf("STOP\n");
			printf("Amino Acid Chain %d\n", i);
		} else
			printf("  %c%c%c - %s\n",  triplet->a, triplet->b, triplet->c, kAminoMatrix[decode_amino(aminoCode)].name);
	}
		
	return 0;
}
