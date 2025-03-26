#include "myrecord.h"
#include "mysort.h"   /* Make sure mysort.h (and its implementation) is in your project */
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/* 
 * Convert a percentage score into a letter grade.
 */
GRADE grade(float score) {
    GRADE g;
    if (score >= 90.0 && score <= 100.0) {
        strcpy(g.letter_grade, "A+");
    } else if (score >= 85.0) {   /* [85, 90) */
        strcpy(g.letter_grade, "A");
    } else if (score >= 80.0) {   /* [80, 85) */
        strcpy(g.letter_grade, "A-");
    } else if (score >= 77.0) {   /* [77, 80) */
        strcpy(g.letter_grade, "B+");
    } else if (score >= 73.0) {   /* [73, 77) */
        strcpy(g.letter_grade, "B");
    } else if (score >= 70.0) {   /* [70, 73) */
        strcpy(g.letter_grade, "B-");
    } else if (score >= 67.0) {   /* [67, 70) */
        strcpy(g.letter_grade, "C+");
    } else if (score >= 63.0) {   /* [63, 67) */
        strcpy(g.letter_grade, "C");
    } else if (score >= 60.0) {   /* [60, 63) */
        strcpy(g.letter_grade, "C-");
    } else if (score >= 57.0) {   /* [57, 60) */
        strcpy(g.letter_grade, "D+");
    } else if (score >= 53.0) {   /* [53, 57) */
        strcpy(g.letter_grade, "D");
    } else if (score >= 50.0) {   /* [50, 53) */
        strcpy(g.letter_grade, "D-");
    } else {                    /* [0, 50) */
        strcpy(g.letter_grade, "F");
    }
    return g;
}

/*
 * Import data from a CSV file. Each line should be in the form:
 *    name,score
 * For example:
 *    John Doe,75.5
 *
 * The function uses fgets to read each line, then uses strtok() to tokenize by comma.
 */
int import_data(FILE *fp, RECORD *dataset) {
    if (fp == NULL || dataset == NULL)
        return 0;
    
    char line[256];
    int count = 0;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        /* Remove any newline characters */
        line[strcspn(line, "\r\n")] = '\0';
        
        /* Get the first token (name) */
        char *token = strtok(line, ",");
        if (token == NULL)
            continue;
        /* Copy the name (up to 20 characters) */
        strncpy(dataset[count].name, token, 20);
        dataset[count].name[20] = '\0';  /* Ensure null termination */
        
        /* Get the second token (score) */
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        dataset[count].score = atof(token);
        
        count++;
    }
    
    return count;
}

/*
 * Comparison function for sorting RECORD pointers in ascending order (by score).
 * This function is used by the generic sort routine (my_sort) in process_data.
 */
static int compare_record_asc(void *p1, void *p2) {
    RECORD *r1 = *(RECORD **)p1;
    RECORD *r2 = *(RECORD **)p2;
    
    if (r1->score < r2->score)
        return -1;
    else if (r1->score > r2->score)
        return 1;
    else
        return 0;
}

/*
 * Process the record data: compute the count, mean, standard deviation, and median.
 * The median is computed by sorting a copy (via an array of pointers) of the dataset.
 */
STATS process_data(RECORD *dataset, int count) {
    STATS stats;
    stats.count = count;
    
    if (count <= 0) {
        stats.mean = stats.stddev = stats.median = 0;
        return stats;
    }
    
    /* Compute mean */
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += dataset[i].score;
    }
    stats.mean = sum / count;
    
    /* Compute standard deviation */
    float sum_sq_diff = 0;
    for (int i = 0; i < count; i++) {
        float diff = dataset[i].score - stats.mean;
        sum_sq_diff += diff * diff;
    }
    stats.stddev = sqrt(sum_sq_diff / count);
    
    /* To compute median, sort an array of pointers to records in ascending order */
    RECORD **records_ptr = (RECORD **)malloc(count * sizeof(RECORD *));
    if (records_ptr == NULL) {
        stats.median = 0;
        return stats;
    }
    for (int i = 0; i < count; i++) {
        records_ptr[i] = &dataset[i];
    }
    
    /* Use the generic sort function (e.g., quick sort) to sort the pointers in ascending order */
    my_sort((void **)records_ptr, 0, count - 1, compare_record_asc);
    
    if (count % 2 == 1) {
        /* Odd number: median is the middle score */
        stats.median = records_ptr[count / 2]->score;
    } else {
        /* Even number: median is the average of the two middle scores */
        stats.median = (records_ptr[(count / 2) - 1]->score + records_ptr[count / 2]->score) / 2.0;
    }
    
    free(records_ptr);
    
    return stats;
}

/*
 * Comparison function for sorting RECORD pointers in descending order (by score).
 * This is used in report_data so that records are printed from highest to lowest score.
 */
static int compare_record_desc(void *p1, void *p2) {
    RECORD *r1 = *(RECORD **)p1;
    RECORD *r2 = *(RECORD **)p2;
    
    if (r1->score > r2->score)
        return -1;
    else if (r1->score < r2->score)
        return 1;
    else
        return 0;
}

/*
 * Prepare and write the report to the output file.
 * The report includes the computed statistics and a list of records (sorted in descending order)
 * with their corresponding letter grades.
 */
int report_data(FILE *fp, RECORD *dataset, STATS stats) {
    if (fp == NULL || dataset == NULL || stats.count < 1)
        return 0;
    
    int count = stats.count;
    
    /* Create an array of pointers to records for sorting in descending order */
    RECORD **records_ptr = (RECORD **)malloc(count * sizeof(RECORD *));
    if (records_ptr == NULL)
        return 0;
    for (int i = 0; i < count; i++) {
        records_ptr[i] = &dataset[i];
    }
    
    /* Sort the pointers in descending order by score */
    my_sort((void **)records_ptr, 0, count - 1, compare_record_desc);
    
    /* Write the statistics header */
    fprintf(fp, "Record Count: %d\n", stats.count);
    fprintf(fp, "Mean: %.2f\n", stats.mean);
    fprintf(fp, "Standard Deviation: %.2f\n", stats.stddev);
    fprintf(fp, "Median: %.2f\n", stats.median);
    fprintf(fp, "\nRecords (sorted in decreasing order of scores):\n");
    fprintf(fp, "-----------------------------------------------\n");
    fprintf(fp, "%-20s %-7s %-3s\n", "Name", "Score", "Grade");
    fprintf(fp, "-----------------------------------------------\n");
    
    /* Write each record with its letter grade */
    for (int i = 0; i < count; i++) {
        GRADE g = grade(records_ptr[i]->score);
        fprintf(fp, "%-20s %-7.2f %-3s\n", records_ptr[i]->name, records_ptr[i]->score, g.letter_grade);
    }
    
    free(records_ptr);
    return 1;
}
