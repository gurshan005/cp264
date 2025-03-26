#include <math.h>
#include "myrecord_bst.h"

/*
 * add_record:
 *   Inserts the new record into the BST (using bst_insert)
 *   and updates the statistics using Welford’s online algorithm.
 */
void add_record(BSTDS *ds, RECORD record) {
    /* Insert record into the BST */
    bst_insert(&ds->root, record);
    
    ds->count++;
    if (ds->count == 1) {
        ds->mean = record.score;
        ds->M2 = 0.0;
        ds->stddev = 0.0;
    } else {
        float delta = record.score - ds->mean;
        ds->mean += delta / ds->count;
        ds->M2 += delta * (record.score - ds->mean);
        ds->stddev = sqrt(ds->M2 / ds->count);
    }
}

/*
 * remove_record:
 *   Searches for a node with data.name matching 'name' (using bst_search),
 *   removes it from the BST (using bst_delete),
 *   and updates the statistics using the inverse of the online algorithm.
 */
void remove_record(BSTDS *ds, char *name) {
    if (ds->count <= 0)
        return;
    
    /* Find the node to be removed */
    BSTNODE *node = bst_search(ds->root, name);
    if (node == NULL)
        return;  /* Not found */
    
    float x = node->data.score;
    
    /* Remove the node from the BST */
    bst_delete(&ds->root, name);
    
    if (ds->count == 1) {
        /* Removing the only element resets all statistics */
        ds->count = 0;
        ds->mean = 0.0;
        ds->M2 = 0.0;
        ds->stddev = 0.0;
    } else {
        int old_count = ds->count;
        float old_mean = ds->mean;
        ds->count--;  /* New count */
        float new_mean = (old_count * old_mean - x) / ds->count;
        ds->M2 -= (x - old_mean) * (x - new_mean);
        ds->mean = new_mean;
        if (ds->count > 1)
            ds->stddev = sqrt(ds->M2 / ds->count);

        else
            ds->stddev = 0.0;
    }
}

/*
 * bstds_clean:
 *   Cleans the BSTDS by cleaning the underlying BST (using bst_clean)
 *   and resets the statistical fields.
 */
void bstds_clean(BSTDS *ds) {
    bst_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0.0;
    ds->stddev = 0.0;
    ds->M2 = 0.0;
}
