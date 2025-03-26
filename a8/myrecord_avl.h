#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H

#include "avl.h"
#include <math.h>

/* This structure holds the root pointer of an AVL tree data structure,
 * along with count, mean and standard deviation (stddev) of the data.score
 * values stored in the AVL tree.
 */
typedef struct {
    AVLNODE *root;
    int count;
    float mean;
    float stddev;
} AVLDS;

/* Merge source AVL tree into destination AVL tree.
 * No change is made to the source tree.
 *
 * @param rootp_dest   - pointer to pointer of root of destination tree.
 * @param rootp_source - pointer to pointer of root of source tree.
 */
void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source);

/* Merge source AVLDS into destination AVLDS.
 * The aggregation algorithm is used to compute the updated stats.
 * The source AVLDS can be cleaned (reset) after the merge.
 *
 * @param dest   - pointer to the destination AVLDS.
 * @param source - pointer to the source AVLDS.
 */
void avlds_merge(AVLDS *dest, AVLDS *source);

/* Clean the AVLDS: clean the underlying AVL tree and set count=0, mean=0, stddev=0.
 *
 * @param ds - pointer to the AVLDS.
 */
void avlds_clean(AVLDS *ds);

/* Add a record (data) into the AVLDS.
 * The record is inserted into the AVL tree and the aggregated stats are updated.
 *
 * @param ds   - pointer to the AVLDS.
 * @param data - record data to add.
 */
void add_record(AVLDS *ds, RECORD data);

/* Remove a record (by name) from the AVLDS.
 * The record is removed from the AVL tree and the aggregated stats are recomputed.
 *
 * @param ds   - pointer to the AVLDS.
 * @param name - key (record name) to remove.
 */
void remove_record(AVLDS *ds, char *name);

#endif // MYRECORD_AVL_H
