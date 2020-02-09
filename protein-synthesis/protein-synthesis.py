#!/usr/bin/env python3

import random
import numpy as np

adenine = np.array([1, 0, 0, 0])
thymine = np.array([0, 0, 0, 1])
guanine = np.array([0, 1, 0, 0])
cytosine = np.array([0, 0, 1, 0])
uracil = np.array([0, 0, 0, 0])

def create_dna_script(amount_of_bases):
    script = []
    for i in range(amount_of_bases):
        base = random.randint(0,3)
        if base == 0:
            script.append(adenine)
        elif base == 1:
            script.append(thymine)
        elif base == 2:
            script.append(guanine)
        else:
            script.append(cytosine)
    script = np.array(script)
    return script
def transcription(dna):
    m_rna = []
    for base in dna:
        if np.array_equal(base, adenine):
            m_rna.append(uracil)
        else:
            codon_base = np.array([0, 0, 0, 0])
            for i in range(base.shape[0]):
                if base[i] == 1:
                    codon_base[-i + 3] = 1
            m_rna.append(codon_base)
    m_rna = np.array(m_rna)
    return m_rna
def translation(mrna):
    trna = "" # list of anti-codon base initials
    for codon in mrna:
        if np.array_equal(codon, adenine):
            trna += 'U' # for uracil
        elif np.array_equal(codon, uracil):
            trna += 'A'
        elif np.array_equal(codon, guanine):
            trna += 'C'
        else:
            trna += 'G'
    return trna
if __name__ == "__main__":
    dna = create_dna_script(100)
    mRNA = transcription(dna)
    polymer = translation(mRNA) # end product of protein synthesis
    print(polymer)