#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#define filelocation "./datagps.txt"

void printSEOUL();
void printCHEONAN();
void printSouthKorea();
void printWorld();
void printBUS();
void printBLANK();
void noGPSdata();

int main() {
    FILE * dataFile;
    int rc; 
    time_t now;
    struct tm timestamp;
    char timebuffer[80];

    struct gps_data_t gps_data;
    if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
        printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
        return EXIT_FAILURE;
    }   
    gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

    if(fopen(filelocation, "r") == NULL){
        dataFile = fopen(filelocation, "a");
        fprintf(dataFile, "name, latitude, longitude, speed\n");
    } else dataFile = fopen(filelocation, "a");

    while (1) {
        if (gps_waiting (&gps_data, 1000000)) {
            if ((rc = gps_read(&gps_data)) == -1) {
                printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
            } else {
                if ((gps_data.status == STATUS_FIX) && 
                        (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                        !isnan(gps_data.fix.latitude) && 
                        !isnan(gps_data.fix.longitude)) {
                    
                    time(&now); 
                    timestamp = *localtime(&now);
                    strftime(timebuffer, sizeof(timebuffer), "%Y-%m-%d  %I:%M:%S%p", &timestamp);
                    if (5 < gps_data.fix.speed) printBUS(timestamp);
                    else if (37.4 < gps_data.fix.latitude <= 37.7 && 126.7 < gps_data.fix.longitude <= 127.2) printSEOUL(timestamp);
                    else if (36.6 < gps_data.fix.latitude <= 37 && 127 < gps_data.fix.longitude <= 127.5) printCHEONAN(timestamp);
                    else if (33.1 < gps_data.fix.latitude <= 38 && 125.8 < gps_data.fix.longitude <= 129) printSouthKorea(timestamp);
                    else printWorld(timestamp);
                    printf("\tTime\t\t:\t%s\n\tLatitude\t:\t%f\n\tLongitude\t:\t%f\n\tSpeed\t\t:\t%f (m/s)\n", timebuffer, gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed);
                    fprintf(dataFile, "%s, %f, %f, %f\n", timebuffer, gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed);
                    fflush(dataFile);
                } else {
                    time(&now);
                    noGPSdata(*localtime(&now));
                }
            }
        }
        sleep(1);
    }

    gps_stream(&gps_data, WATCH_DISABLE, NULL);
    gps_close (&gps_data);
    fclose(dataFile);

    return EXIT_SUCCESS;
}

void printBLANK(){
    printf("\n\n\n\n\n\n");
}

void printSEOUL(int timestamp){
    system("clear");
    printf("\n                         ajQWWWWWWWWQP             ");
    printf("\n                        jQWWWWWWWWWQWP             ");
    printf("\n               qaaaWQa  QQWWWQWQWQWWWa             ");
    printf("\n               WWWWWWQaaWWWQWWQWWWWQWQQ[           ");
    printf("\n              qWWWWWWWWQWWWWQWWWWWQWWWga           ");
    printf("\n  ap          ]WWWWWQWWWWWWQWWWWWWWWWQWP'          ");
    printf("\n aWWQa     jQmQWQQWQWWQWQWWWWWQWQWWWQWW'           ");
    printf("\n WWWWQWgj4QQWWQWWWWWWWWWWWWWQWWWWWQWWW'            ");
    printf("\nWWWWWWWWQQJ4QWWWWQWWQWQWWWWQWWQWWQWWQLjja          ");
    printf("\n?WW?WWQWWWQQgjP4QWWWWWWWQWWWWWWWQWWWQQ[yWWWWW      ");
    printf("\n     QQWWWWWWWQQJg#4QWQWWW?LaaaW?WWWPLQWWWWfw      ");
    printf("\n    ]WWWWQWQWWWWWQmmw???4aWWWWWWWWWWWQWWWW?        ");
    printf("\n    jQWWWWWWWWQWWWWWWWWWWWWWQWWWWWWQWWQWWQa        ");
    printf("\n          ]QWQWQWWWWQWQWWWQWWWWWWWQWWQWWWWWF       ");
    printf("\n           4QWWWWWWQWWWWQWWWQWQWWQWWWWWWW?'        ");
    printf("\n            4QWWWWQWWQWP']?' jQWQWWQP?/'           ");
    printf("\n            ]4W! ?l?l?l'      JQQWW?'           \n\n");
    if(timestamp % 2 == 0){
        printf("\t ____  _____ ___  _   _ _ \n");
        printf("\t/ ___|| ____/ _ \\| | | | |\n");
        printf("\t\\___ \\|  _|| | | | | | | |\n");
        printf("\t ___) | |__| |_| | |_| | |___ \n");
        printf("\t|____/|_____\\___/ \\___/|_____|\n\n");
    } else printBLANK();
}

void printCHEONAN(int timestamp){
    system("clear");
    printf("\n             qpmXXB#XXX#Lgggp        qa\n");
    printf("           aa]a ){ZXXXXXeZZ#Lp  agLgWXXXLgp\n");
    printf("          jZ&S#g#XXUXXZXXXXXXL&XXXZZX$XXZZZLp\n");
    printf("       qJ#XXXX#XXX{ZXX&mXmXXm#XX[SXXmXXXXXXXLp \n");
    printf("         PWmXXXdXXXLXXXUSSSdXXXXXSSXmSrmmXXF?\n");
    printf("         !? !X7ZXmXXXmXmXXXJsZXXmqmSq#\n");
    printf("              6B`lZXXU&XXXmSXXX#XXXXX#a\n");
    printf("              )XX lXXXXJSXXmm#ZmXXXXXXXXq\n");
    printf("                &X6 mX#AXmXXZXXXAqmXXXsXXXm\n");
    printf("                )`F lXXXXXAXXXJsXXXXXXXXXXX[\n");
    printf("                  l`' 4mSXXmAXUdZXXmXXXmXXmqf\n");
    printf("                      !XXXX$SXXXXXXXXX#XUXF7p  p\n");
    printf("                      ]XXXXXXXXXuLXXXUXXXXSGUa]UaqgBga\n");
    printf("                    qJX&X##XXXXXmmmqmSXsXXXXS&XSXXXZm\n");
    printf("                       J4SsXJXU#     4XmmF`?`lXXXLXXX[\n");
    printf("                         {ZXF`!'              4mXXX`m[\n\n");
    if(timestamp % 2 == 0){
        printf("\t  ____ _   _ _____ ___  _   _    _    _   _ \n");
        printf("\t / ___| | | | ____/ _ \\| \\ | |  / \\  | \\ | |\n");
        printf("\t| |   | |_| |  _|| | | |  \\| | / _ \\ |  \\| |\n");
        printf("\t| |___|  _  | |__| |_| | |\\  |/ ___ \\| |\\  |\n");
        printf("\t \\____|_| |_|_____\\___/|_| \\_/_/   \\_\\_| \\_|\n\n");
    } else printBLANK();
}

void printSouthKorea(int timestamp){
    system("clear");
    printf("\n                                  Jp");
    printf("\n                          gagagagWZL");
    printf("\n                        ]####Z#Z#Z##q");
    printf("\n                        J#Z#ZZ#Z#Z#Z#L");
    printf("\n                       gm#Z#Z#Z#Z#Z#Z#L");
    printf("\n                       4#Z#Z#Z#Z#Z#Z#Z#q");
    printf("\n                       ]###Z#Z#Z#Z#Z#Z#Z,");
    printf("\n                       jJ#Z#Z#ZmZ#Z#Z#Z##[");
    printf("\n                     jga/mZ#Z#Z#Z#Z#Z#Z#ZW         ##");
    printf("\n                    ]L###j##Z#Z#Z#Z#ZZ#Z#Z         ##");
    printf("\n                    )m4Z#Z#Z#Z#Z#Z#Z#Z#Z#Z");
    printf("\n                      ]X#Z#Z#Z###Z#Z#Z#Z#Z                  #");
    printf("\n                       #Z#Z##Z#UmZ#Z#Z#Z#[");
    printf("\n                      )4X#Z#Z#Z#Z#Z#Z#Z#ZFj");
    printf("\n                       ]mZ#Z##Z#Z#Z#Z#Z#ZZm");
    printf("\n                       aJZ#Z#Z##Z#Z#mZ#mZ#[");
    printf("\n                      ]ZZ#Z#Z#Z#ZZ##&#ZZ#Z'");
    printf("\n                      mm##Z#mZ#Z#Z#ZZ#Z#Z[");
    printf("\n                     ]ZZ#Z#ZZ#Z#Z#Z#Z#mZ!");
    printf("\n                    ]\\##Z#Z#Z#Z#PZ#P]  '");
    printf("\n                     j#Z#Z#Zm4g   ]F");
    printf("\n                     PJ#Zm!WL7");
    printf("\n                      4Z!')!");
    printf("\n                      ]?\n\n\n");
    printf("\n                       ga");
    printf("\n                    aZ###'");
    printf("\n                    ]!'\n\n");

    if(timestamp % 2 == 0){
        printf("\t ____              _   _       _  __ \n");
        printf("\t/ ___|  ___  _   _| |_| |__   | |/ /___  _ __ ___  __ _ \n");
        printf("\t\\___ \\ / _ \\| | | | __| '_ \\  | ' // _ \\| '__/ _ \\/ _` |\n");
        printf("\t ___) | (_) | |_| | |_| | | | | . \\ (_) | | |  __/ (_| |\n");
        printf("\t|____/ \\___/ \\__,_|\\__|_| |_| |_|\\_\\___/|_|  \\___|\\__,_|\n\n");
    } else printBLANK();
}

void printWorld(int timestamp){
    system("clear");
    printf("\nQQQQQQQQQQQQQQQ?4QQ@PEaaaw6,     qQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
    printf("\nQQQQQ!    . ' -)'?""\\)aE ]QQ' aaaQQQQQQQQQQQQP4QQQQQQQDQQQQQQQP???? ]????4@P?$QQQQQQQQQQQQQQQ");
    printf("\nQQQQQ!    . ' -)?""\\)aE ]QQ' aaaQQQQQQQQQQQQP4QQQQQQQDQQQQQQQP???? ]????4@P?$QQQQQQQQQQQQQQ");
    printf("\nQQQQQWQQf             ]QmQQQQQQQQQQQQQQQQ9Wgajk       )QQQQQQgp               )?4Qw/QQQQQQQQ");
    printf("\nQQQQQQQf          _ayWQQQQQQQQQQQQQQQQQQaf)'          ajQQQQa _,                qm?QQQQQQQQQ");
    printf("\nQQQQQQQQ[p   qpapyQQQQQQQQQQQQQQQQQQQQQQ^qagwq.a?' ?4QQQQ6,'               )]J4@'QQQQQQQQQ");
    printf("\nQQQQQQQQQyp ]Q?QQ?QQQQQQQQQQQQQQQQQQQQQQ??`  ""4P)Wg  ]QQQQQQQa,                $QQQQQQQQQQQQ");
    printf("\nQQQQQQQQQQQQaay4QQQQQQQQQQQQQQQQQQQQQQP'           \\,  ??4QQQQQQQQgp  qaa   aaj@WQQQQQQQQQQQ");
    printf("\nQQQQQQQQQQQQQWQQyQQQQQT!)??$QQQQQQQQQQ(             ?p aaQQQQQQQQQQQp]QQQQaajQQQ7QQQQQQQQQQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQ?       ?4QQQQQQQQp   ,           yWQQQQQQQQQQQQQQQQgP)WP""]QW$QQQQQQQQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQw           QQQQQQQQQQQW        aQQQQQQQQQQQQQQQQQQQQQa/(qmyWmfQ??H?QQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQQ6a,       QQQQQQQQQQQQQ6i     )WQQQQQQQQQQQQQQQQQQQQWWQQQQQPT?4W46QQQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQQQQf    =ayQQQQQQQQQQQQQf     qaP'mQQQQQQQQQQQQQQQQQQQQQQP?'     ""4QQQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQQQQf   qyQQQQQQQQQQQQQQQQp   qyW6yQQQQQQQQQQQQQQQQQQQQQQQ         qQQQQ");
    printf("\nQQQQQQQQQQQQQQQQQQQQQQQQ6  yQQQQQQQQQQQQQQQQQQQaawWQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQaaaQQQQQ'");
    printf("\nQQQQQQQQQQQQQQQQQQQQQQQQQf_QQQQQQQQQQQQQQQQQQQQQWWQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWWQQQmwQQ");
    printf("\n");
    if(timestamp % 2 == 0){
        printf("\t ___ _   _   _____ _   _ _____  __        _____  ____  _     ____\n");
        printf("\t|_ _| \\ | | |_   _| | | | ____| \\ \\      / / _ \\|  _ \\| |   |  _ \\\n");
        printf("\t | ||  \\| |   | | | |_| |  _|    \\ \\ /\\ / / | | | |_) | |   | | | |\n");
        printf("\t | || |\\  |   | | |  _  | |___    \\ V  V /| |_| |  _ <| |___| |_| |\n");
        printf("\t|___|_| \\_|   |_| |_| |_|_____|    \\_/\\_/  \\___/|_| \\_\\_____|____/\n\n");
    } else printBLANK();
}

void printBUS(int timestamp){
    system("clear");
    printf("\t\t ______________________\n");
    printf("\t\t |,----.,----.,----.,--.\\\n");
    printf("\t\t ||    ||    ||    ||   \\\\\n");
    printf("\t\t |`----'`----'|----||----\\`.\n");
    printf("\t\t [            |   -||- __|(|\n");
    printf("\t\t [  ,--.      |____||.--.  |\n");
    printf("\t\t =-(( `))-----------(( `))==\n");
    printf("\t\t    `--'             `--'\n\n");
    if(timestamp % 2 == 0){
        printf("\t ____  ___ ____ ___ _   _  ____       _   _  _____        __   /\\//\\/\n");
        printf("\t|  _ \\|_ _|  _ \\_ _| \\ | |/ ___|     | \\ | |/ _ \\ \\      / /   /\\//\\/\n");
        printf("\t| |_) || || | | | ||  \\| | |  _      |  \\| | | | \\ \\ /\\ / /\n");
        printf("\t|  _ < | || |_| | || |\\  | |_| |     | |\\  | |_| |\\ V  V /\n");
        printf("\t|_| \\_\\___|____/___|_| \\_|\\____|     |_| \\_|\\___/  \\_/\\_/ \n\n");
    } else printBLANK();
}

void noGPSdata(int timestamp){
    system("clear");
    if(timestamp % 2 == 0){
        printf("     _   _  ___     ____ ____  ____    ____    _  _____  _    \n");
        printf("    | \\ | |/ _ \\   / ___|  _ \\/ ___|  |  _ \\  / \\|_   _|/ \\  \n");
        printf("    |  \\| | | | | | |  _| |_) \\___ \\  | | | |/ _ \\ | | / _ \\  \n");
        printf("    | |\\  | |_| | | |_| |  __/ ___) | | |_| / ___ \\| |/ ___ \\ \n");
        printf("    |_| \\_|\\___/   \\____|_|   |____/  |____/_/   \\_\\_/_/   \\_\\\n");
        printf("        ___     ___    ___ _        _    ____  _     _____ \n");
        printf("       / \\ \\   / / \\  |_ _| |      / \\  | __ )| |   | ____|\n");
        printf("      / _ \\ \\ / / _ \\  | || |     / _ \\ |  _ \\| |   |  _|  \n");
        printf("     / ___ \\ V / ___ \\ | || |___ / ___ \\| |_) | |___| |___ \n");
        printf("    /_/   \\_\\_/_/   \\_\\___|_____/_/   \\_\\____/|_____|_____|\n");
    } else printBLANK();
}
