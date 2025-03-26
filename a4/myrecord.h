#ifndef MYRECORD_H
#define MYRECORD_H

#include <stdio.h>

/* 
 * Structure to hold a person's name and score.
 * The name is stored in an array of 21 characters (up to 20 characters plus a null terminator).
 */
typedef struct {
    char name[21];
    float score;
} RECORD;

/*
 * Structure to hold basic statistics computed from the record data.
 */
typedef struct {
    int count;
    float mean;
    float stddev;   /* standard deviation */
    float median;
} STATS;

/*
 * Structure to hold a letter grade.
 * The letter grade is stored as a string of up to 2 letters plus a null terminator.
 */
typedef struct {
    char letter_grade[3];
} GRADE;

/*
 * Convert a percentage grade to a letter grade defined by percentage ranges.
 *
 * @param score - percentage grade.
 * @return - letter grade wrapped in a GRADE structure.
 */
GRADE grade(float score);

/*
 * Import record data from the input file and store each record’s name and score
 * in the RECORD array passed by dataset. The file is assumed to have comma-separated
 * values (CSV) for each record.
 *
 * @param fp - FILE pointer to the input file.
 * @param dataset - array of RECORD to store record data.
 * @return - the number of records imported.
 */
int import_data(FILE *fp, RECORD *dataset); 

/*
 * Process the record data by computing the average, standard deviation,
 * and median of the score values. Returns a STATS structure with the results.
 *
 * @param dataset - input record data array.
 * @param count - number of records in the dataset array.
 * @return - computed statistics as a STATS structure.
 */
STATS process_data(RECORD *dataset, int count);

/*
 * Prepare and write a report (including statistics and letter grades)
 * to the output file. The records in the report are sorted in decreasing order of score.
 *
 * @param fp - FILE pointer to the output file.
 * @param dataset - array of RECORD data.
 * @param stats - the computed statistics.
 * @return - returns 1 if successful; 0 if there are no records (count < 1).
 */
int report_data(FILE *fp, RECORD *dataset, STATS stats);

#endif /* MYRECORD_H */
