#ifndef __AUTRES_FONCTIONS_H__
#define __AUTRES_FONCTIONS_H__

#define NB_DIVISEUR 285

// Récupérer l'adresse du premier bit à 1
int getFirstBitToOne(CodeWord_t * cw);
void deplacementBits(CodeWord_t * cw, int nb);
void coder(CodeWord_t *cw);
void division(CodeWord_t *x);

#endif

