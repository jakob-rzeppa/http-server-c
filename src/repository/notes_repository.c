
#include "notes_repository.h"

/**
 * File structure:
 * id;content-size;content
 * example: 5;12;example note
 */

struct note
{
    int id;
    char *content;
};

int get_notes(int id)
{
    return SUCCESSFUL;
}

int create_note(char *content)
{
    FILE *file;

    // --- FIND THE ID ---
    file = fopen(DATABASE_PATH, "r" /* read mode */);
    if (file == NULL)
    {
        log_error("create_note failed: could not open file: %s", strerror(errno));
        return FAILED;
    }

    char *line_buffer = (char *)malloc(sizeof(char) * DATABASE_LINE_BUFFER_SIZE);

    int highest_id = 0;
    while (fgets(line_buffer, DATABASE_LINE_BUFFER_SIZE - 1, file) != NULL)
    {
        // atoi will stop reading at the first non-numeric character (';')
        int current_id = atoi(line_buffer);

        // Only write the line if it's not the one we want to delete
        if (current_id > highest_id)
        {
            highest_id = current_id;
        }
    }

    free(line_buffer);
    fclose(file);
    file = NULL;

    // --- ASSEMBLE THE LINE ---
    int content_size = strlen(content);
    int line_size = 3 /* seperators */ + 10 /* id size */ + 10 /* content_size size */ + content_size + 1 /* esc char */;
    char *line = (char *)malloc(sizeof(char) * (line_size));

    int snprintf_res = snprintf(line, line_size, "%d;%d;%s\n", highest_id + 1, content_size, content);
    if (snprintf_res < 0 || snprintf_res >= line_size)
    {
        log_error("create_note failed: content buffer overflow");
        free(line);
        return FAILED;
    }

    // --- APPEND THE LINE ---
    file = fopen(DATABASE_PATH, "a" /* append mode */);
    if (file == NULL)
    {
        log_error("create_note failed: could not open file: %s", strerror(errno));
        free(line);
        return FAILED;
    }

    fprintf(file, line);

    fclose(file);
    file = NULL;

    free(line);
    return SUCCESSFUL;
}

int update_note(int id, char *content)
{
    // --- ASSEMBLE THE LINE ---
    int content_size = strlen(content);
    int line_size = 3 /* seperators */ + 10 /* id size */ + 10 /* content_size size */ + content_size + 1 /* esc char */;
    char *line = (char *)malloc(sizeof(char) * (line_size));

    int snprintf_res = snprintf(line, line_size, "%d;%d;%s\n", id, content_size, content);
    if (snprintf_res < 0 || snprintf_res >= line_size)
    {
        log_error("create_note failed: content buffer overflow");
        free(line);
        return FAILED;
    }

    FILE *file;
    FILE *temp;

    bool update_has_happened = false;

    // --- STORE A COPY OF THE FILE WITH THE UPDATED LINE ---
    file = fopen(DATABASE_PATH, "r" /* read mode */);
    if (file == NULL)
    {
        log_error("update_note failed: could not open file: %s", strerror(errno));
        free(line);
        return FAILED;
    }

    temp = fopen("update_notes.tmp", "w" /* write mode */);
    if (temp == NULL)
    {
        log_error("update_note failed: could not open temp file: %s", strerror(errno));
        free(line);
        fclose(file);
        return FAILED;
    }

    char *file_line_buffer = (char *)malloc(sizeof(char) * DATABASE_LINE_BUFFER_SIZE);

    while (fgets(file_line_buffer, DATABASE_LINE_BUFFER_SIZE - 1, file) != NULL)
    {
        // atoi will stop reading at the first non-numeric character (';')
        int current_id = atoi(file_line_buffer);

        if (current_id == id)
        {
            fprintf(temp, line);
            update_has_happened = true;
        }
        else
        {
            fprintf(temp, file_line_buffer);
        }
    }

    free(file_line_buffer);
    fclose(temp);
    temp = NULL;
    fclose(file);
    file = NULL;

    if (!update_has_happened)
    {
        log_error("update_note failed: id not found");
        remove("update_notes.tmp");
        free(line);
        return FAILED;
    }

    // --- WRITE THE COPY TO THE FILE ---
    temp = fopen("update_notes.tmp", "r" /* read mode */);
    if (temp == NULL)
    {
        log_error("update_note failed: could not open temp file: %s", strerror(errno));
        free(line);
        return FAILED;
    }

    file = fopen(DATABASE_PATH, "w" /* write mode */);
    if (file == NULL)
    {
        log_error("update_note failed: could not open file: %s", strerror(errno));
        fclose(temp);
        free(line);
        return FAILED;
    }

    char *temp_line_buffer = (char *)malloc(sizeof(char) * DATABASE_LINE_BUFFER_SIZE);

    while (fgets(temp_line_buffer, DATABASE_LINE_BUFFER_SIZE - 1, temp) != NULL)
    {
        fprintf(file, temp_line_buffer);
    }

    free(line);
    free(temp_line_buffer);
    fclose(file);
    file = NULL;
    fclose(temp);
    temp = NULL;

    // --- DELETE TEMP FILE ---
    remove("update_notes.tmp");

    return SUCCESSFUL;
}

int delete_note(int id)
{
    FILE *file;
    FILE *temp;

    // --- STORE A COPY OF THE FILE WITHOUT THE LINE ---
    file = fopen(DATABASE_PATH, "r" /* read mode */);
    if (file == NULL)
    {
        log_error("delete_note failed: could not open file: %s", strerror(errno));
        return FAILED;
    }

    temp = fopen("delete_notes.tmp", "w" /* write mode */);
    if (temp == NULL)
    {
        log_error("delete_note failed: could not open temp file: %s", strerror(errno));
        fclose(file);
        return FAILED;
    }

    char *file_line_buffer = (char *)malloc(sizeof(char) * DATABASE_LINE_BUFFER_SIZE);

    while (fgets(file_line_buffer, DATABASE_LINE_BUFFER_SIZE - 1, file) != NULL)
    {
        // atoi will stop reading at the first non-numeric character (';')
        int current_id = atoi(file_line_buffer);

        // Only write the line if it's not the one we want to delete
        if (current_id != id)
        {
            fprintf(temp, file_line_buffer);
        }
    }

    free(file_line_buffer);
    fclose(temp);
    temp = NULL;
    fclose(file);
    file = NULL;

    // --- WRITE THE COPY TO THE FILE ---
    temp = fopen("delete_notes.tmp", "r" /* read mode */);
    if (temp == NULL)
    {
        log_error("delete_note failed: could not open temp file: %s", strerror(errno));
        return FAILED;
    }

    file = fopen(DATABASE_PATH, "w" /* write mode */);
    if (file == NULL)
    {
        log_error("delete_note failed: could not open file: %s", strerror(errno));
        fclose(temp);
        return FAILED;
    }

    char *temp_line_buffer = (char *)malloc(sizeof(char) * DATABASE_LINE_BUFFER_SIZE);

    while (fgets(temp_line_buffer, DATABASE_LINE_BUFFER_SIZE - 1, temp) != NULL)
    {
        fprintf(file, temp_line_buffer);
    }

    free(temp_line_buffer);
    fclose(file);
    file = NULL;
    fclose(temp);
    temp = NULL;

    // --- DELETE TEMP FILE ---
    remove("delete_notes.tmp");

    return SUCCESSFUL;
}