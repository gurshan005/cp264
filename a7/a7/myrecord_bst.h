#ifndef MYRECORD_BST_H
#define MYRECORD_BST_H

#include "bst.h"  // This header must define BSTNODE and RECORD

/*
 * Define structure type BSTDS.
 * It contains a pointer to the BST root and statistics for record data.
 * Statistics include count, mean, and standard deviation (stddev).
 * An auxiliary field M2 is added to support online variance calculation.
 */
typedef struct {
    BSTNODE *root;
    int count;
    float mean;
    float stddev;
    float M2;  /* Auxiliary field for online variance calculation */
} BSTDS;

/* 
 * Add a record into the BSTDS and update its statistics 
 * using an incremental (online) algorithm.
 * @param ds     - pointer to the BSTDS.
 * @param record - RECORD data to be added.
 */
void add_record(BSTDS *ds, RECORD record);

/* 
 * Delete a node from the BSTDS with data.name matching the given name 
 * and update the statistics using an incremental algorithm.
 * @param ds   - pointer to the BSTDS.
 * @param name - node data.name to be removed.
 */
void remove_record(BSTDS *ds, char *name);

/* 
 * Clean the BSTDS (free the underlying BST) and reset count, mean, and stddev.
 * @param ds - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *ds);

#endif // MYRECORD_BST_H
