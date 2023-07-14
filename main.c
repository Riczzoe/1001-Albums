#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define _MAX_LEN_ 200
#define _MAX_ALBUM_ 980
#define _DATA_FILE_ "data.txt"
#define _ALBUM_FILE_ "1001-albums.txt"
#define _LOG_FILE_ "log.txt"

typedef struct {
    char lastDate[_MAX_LEN_];
    int numOfAlbumAlready;
    int isRandom;
} Data;

char albumInfo[_MAX_LEN_];
int newInfo = 0;

/* function declaration */
void getLastData(Data* data);
void checkAndUpdate(Data* data);
void getAlbumInfo(Data* data, char* albumInfo);
void finshListenAllAlbum(Data* data);
void randomAlbum(Data* data);
void writeData(Data* data);
void printData(char* albumInfo);

int main() {
    Data data = { "", 0, 0 };
    getLastData(&data);
    checkAndUpdate(&data);
    getAlbumInfo(&data, albumInfo);
    printData(albumInfo);
    writeData(&data);
}

/**
 * - getLastData
 *   get last date and numOfAlbumAlready from data.txt
 */
void getLastData(Data* data) {
    FILE *dataFile = fopen(_DATA_FILE_, "a+");
    if (dataFile == NULL) {
        printf("Error: cannot open file %s\n", _DATA_FILE_);
        exit(1);
    }

    fscanf(dataFile, "%s %d %d", data->lastDate, &data->numOfAlbumAlready, &data->isRandom);
    fclose(dataFile);
}

/**
 * - checkAndUpdate
 *   check if the date is the same as last date
 *   if not, update the date and numOfAlbumAlready
 *   and make newInfo = 1
 *
 *   check if the user want to listen randomly
 *   if yes, random a number between 1 and 980
 */
void checkAndUpdate(Data* data) {
    time_t now = time(NULL);
    struct tm* tmInfo = localtime(&now);
    char currentDate[_MAX_LEN_];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", tmInfo);

    if (strcmp(currentDate, data->lastDate) != 0) {
        if (data->isRandom)
            randomAlbum(data);
        else
            data->numOfAlbumAlready++;

        if (data->numOfAlbumAlready > _MAX_ALBUM_)
            finshListenAllAlbum(data);
        strcpy(data->lastDate, currentDate);

        newInfo = 1;
    }
}

/**
 * - getAlbumInfo
 *   get album info from 1001-albums.txt
 */
void getAlbumInfo(Data* data, char* albumInfo) {
    FILE* albumFile = fopen(_ALBUM_FILE_, "r+");
    if (albumFile == NULL) {
        printf("Error: cannot open file %s\n", _ALBUM_FILE_);
        exit(1);
    }

    int i;
    for (i = 0; i < data->numOfAlbumAlready; i++) {
        if (fgets(albumInfo, _MAX_LEN_, albumFile) == NULL) {
            printf("Error: cannot read file %s\n", _ALBUM_FILE_);
            fclose(albumFile);
            exit(1);
        }
    }
    
    fclose(albumFile);
    if (i != data->numOfAlbumAlready) {
        printf("Error: cannot find album %d\n", data->numOfAlbumAlready);
        exit(1);
    }
}


void finshListenAllAlbum(Data* data) {
    printf("Congratulation! You have listened all albums you need to listen before you die!\n");
    printf("You cam chose to listen randomly or in the same way as before.\n");
    printf("Randomly? (y/n): ");
    char answer[_MAX_LEN_];
    scanf("%s", answer);
    getchar();

    data->isRandom = (tolower(answer[0]) == 'y') ? 1 : 0;

    if (data->isRandom)
        randomAlbum(data);
    else 
        data->numOfAlbumAlready = 1;

    printf("Enjoy your music!\n");
}

/**
 * - randomAlbum
 *   random a number between 1 and 980
 */
void randomAlbum(Data* data) {
    srand(time(NULL));
    data->numOfAlbumAlready = rand() % 980;
}

/**
 * - writeData
 *   write data to data.txt and log.txt
 */
void writeData(Data* data) {
    FILE *dataFile = fopen(_DATA_FILE_, "wb");
    if (dataFile == NULL) {
        printf("Error: cannot open file %s\n", _DATA_FILE_);
        exit(1);
    }
    fprintf(dataFile, "%s %d %d", data->lastDate, data->numOfAlbumAlready, data->isRandom);
    fclose(dataFile);

    if (!newInfo)
        return;

    FILE* logFile = fopen(_LOG_FILE_, "a");
    if (logFile == NULL) {
        printf("Error: cannot open file %s\n", _LOG_FILE_);
        exit(1);
    }

    fprintf(logFile, "%s:\t %s", data->lastDate, albumInfo);
    fclose(logFile);
}


/**
 * - printData
 *   print album info
 */
void printData(char* albumInfo) {
    printf("Today's album is:\t");
    printf("%s", albumInfo);
    printf("Enjoy your music!\n");
}
