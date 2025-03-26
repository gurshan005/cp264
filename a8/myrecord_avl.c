#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "myrecord_avl.h"

/*---------------------------------------------------------------------
 * Helper function: recursively traverse the source AVL tree and insert
 * each record into the destination tree.
 */
static void avl_merge_rec(AVLNODE *src, AVLNODE **dest) {
    if (src == NULL)
        return;
    avl_merge_rec(src->left, dest);
    avl_insert(dest, src->data); // Insert a copy of the record.
    avl_merge_rec(src->right, dest);
}

/* Merge source AVL tree into destination AVL tree.
 * The source tree remains unchanged.
 */
void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source) {
    if (rootp_source == NULL || *rootp_source == NULL)
        return;
    avl_merge_rec(*rootp_source, rootp_dest);
}

/*---------------------------------------------------------------------
 * Helper function: recursively aggregate the count, sum, and sum of squares
 * of the score values stored in the AVL tree.
 */
static void avlds_aggregate(AVLNODE *root, int *count, float *sum, float *sumsq) {
    if (root == NULL)
        return;
    avlds_aggregate(root->left, count, sum, sumsq);
    (*count)++;
    *sum += root->data.score;
    *sumsq += root->data.score * root->data.score;
    avlds_aggregate(root->right, count, sum, sumsq);
}

/*---------------------------------------------------------------------
 * Merge source AVLDS into destination AVLDS.
 * The underlying AVL trees are merged (by inserting copies from source
 * into destination), and then the stats (count, mean, stddev) are updated
 * using an aggregation algorithm. The source AVLDS is cleaned after merging.
 */
void avlds_merge(AVLDS *dest, AVLDS *source) {
    if (dest == NULL || source == NULL)
        return;
    if (source->root == NULL)
        return; // Nothing to merge

    if (dest->root == NULL) {
        /* If destination is empty, simply transfer the source tree and stats. */
        dest->root = source->root;
        dest->count = source->count;
        dest->mean = source->mean;
        dest->stddev = source->stddev;
    } else {
        /* Merge source tree into destination tree. */
        avl_merge(&(dest->root), &(source->root));

        /* Recompute the aggregated stats by traversing the merged tree. */
        int count = 0;
        float sum = 0.0, sumsq = 0.0;
        avlds_aggregate(dest->root, &count, &sum, &sumsq);
        float new_mean = (count > 0) ? (sum / count) : 0.0;
        float variance = (count > 0) ? (sumsq / count) - (new_mean * new_mean) : 0.0;
        if (variance < 0) variance = 0;
        dest->count = count;
        dest->mean = new_mean;
        dest->stddev = sqrt(variance);
    }

    /* Clean the source AVLDS */
    avl_clean(&(source->root));
    source->count = 0;
    source->mean = 0.0;
    source->stddev = 0.0;
}

/*---------------------------------------------------------------------
 * Clean the AVLDS: free the underlying AVL tree and reset count, mean, stddev.
 */
void avlds_clean(AVLDS *ds) {
    if (ds == NULL)
        return;
    avl_clean(&(ds->root));
    ds->count = 0;
    ds->mean = 0.0;
    ds->stddev = 0.0;
}

/*---------------------------------------------------------------------
 * Add a record to the AVLDS.
 * The record is inserted into the AVL tree and the aggregated stats are
 * updated incrementally.
 */
void add_record(AVLDS *ds, RECORD data) {
    if (ds == NULL)
        return;
    /* Insert the record into the underlying AVL tree. */
    avl_insert(&(ds->root), data);

    /* Update aggregated stats incrementally.
     * Let current count = n, mean = m, variance = s^2.
     * With new record x, new count = n+1 and:
     *    new_mean = (n*m + x) / (n+1)
     *    new_variance = [n*(s^2 + (m - new_mean)^2) + (x - new_mean)^2] / (n+1)
     */
    int n = ds->count;
    float m = ds->mean;
    float s2 = ds->stddev * ds->stddev; // current variance
    int new_n = n + 1;
    float new_mean = (n * m + data.score) / new_n;
    float new_var = 0.0;
    if (new_n > 1) {
        new_var = (n * (s2 + (m - new_mean) * (m - new_mean)) + (data.score - new_mean) * (data.score - new_mean)) / new_n;
    }
    ds->count = new_n;
    ds->mean = new_mean;
    ds->stddev = sqrt(new_var);
}

/*---------------------------------------------------------------------
 * Remove a record by name from the AVLDS.
 * After removal from the underlying AVL tree, the stats are recomputed by
 * aggregating the remaining nodes.
 */
void remove_record(AVLDS *ds, char *name) {
    if (ds == NULL || ds->root == NULL)
        return;
    /* Search for the record by name; if not found, nothing to remove. */
    AVLNODE *node = avl_search(ds->root, name);
    if (node == NULL)
        return;

    /* Remove the record from the AVL tree. */
    avl_delete(&(ds->root), name);
    ds->count--;  // Decrement count

    if (ds->count <= 0) {
        ds->mean = 0.0;
        ds->stddev = 0.0;
        return;
    }
    /* Recompute stats by traversing the AVL tree. */
    int count = 0;
    float sum = 0.0, sumsq = 0.0;
    avlds_aggregate(ds->root, &count, &sum, &sumsq);
    float new_mean = sum / count;
    float variance = (count > 0) ? (sumsq / count) - (new_mean * new_mean) : 0.0;
    if (variance < 0)
        variance = 0;
    ds->mean = new_mean;
    ds->stddev = sqrt(variance);
}