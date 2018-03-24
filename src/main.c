#include <date.h>
#include <stdio.h>
#include "interface.h"
#include <glib.h>
#include "Community.h"
#include "stdlib.h"

//tmp
#include "bArray.h"
#include "heap.h"
#include <time.h>

int main(int argc, char*argv[] )
{
    clock_t t1, t2;
    double time_spent = 0;
    TAD_community com;

    if( argc < 2 ){
        printf("--------------------------------------------------------\n");
        printf("\tIndica o path quando invocas o programa\n");
        printf("--------------------------------------------------------\n");
        exit(-1);
    }  
    
    t1 = clock();
    com = init();
    com = load(com, argv[1] );
    clean(com);
    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("time: %f",(float)time_spent );
    
    return(1);
}

/*
int main(int argc, char*argv[] )
{
    clock_t t1, t2;
    USER q5;
    Util usq2;
    Post q6p, q7p, q9p;
    STR_pair q1;
    LONG_pair q3;
    LONG_list q2, q9;
    long *l;
    LONG_list q6, q7;
    Date begin = createDate(16, 1, 2011), end = createDate(3, 3, 2016);
    //int i, *the_test_tmp;
    int n;
    //int *bg, *ed;
    Date pdate;

    //bArray the_test;
    //int **envoy;
    //HEAP the_fst_beap,Pq;
    TAD_community com;
    int i;
    double time_spent = 0;
    //double sum;
    //10.084375
    //10.430469
    if( argc < 2 ){
        printf("--------------------------------------------------------\n");
        printf("\tIndica o path quando invocas o programa\n");
        printf("--------------------------------------------------------\n");
        exit(-1);
    }  

    t1 = clock();
    com = init();
    com = load(com, argv[1] );

    t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("\n.. Loading Terminaterd .. \nload -> time. :: %f \n", (float)(time_spent));

    printf("______________________\n");
    printf("|->Q1\n\n");
    q1 = info_from_post(com, 30334);
    if (q1)
    {
        printf("Publication name :: \t %s\n", get_fst_str(q1));
        printf("Publicant name :: \t %s\n", get_snd_str(q1));
        free_str_pair(q1);
    }
    else
        printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q2\n\n");
    n = 40;
    q2 = top_most_active(com, n);
    for (i = 0; i < n; i++)
    {
        printf(">> %d ", (int)get_list(q2, i));
        usq2 = userSet_id_lookup(com, get_list(q2, i));
        printf(" \t %d \n", getU_A(usq2) + getU_Q(usq2));
    }
    free_list(q2);

    printf("______________________\n");
    printf("|->Q3\n\n");

    q3 = total_posts(com, begin, end);

    printf("from :: 16 - 01 - 2011\n");
    printf("to   :: 03 - 03 - 2013\n");

    printf("Number of Questions ::\t %ld \n", get_fst_long(q3));
    printf("Number of Answers   ::\t %ld \n", get_snd_long(q3));
    free_long_pair(q3);

    printf("______________________\n");
    printf("|->Q5\n\n");
    q5 = get_user_info(com, 16575);
    if (q5)
    {
        printf("Short user bio :: \n%s \n", get_bio(q5));
        printf("Last 10 posts  :: \n");

        l = get_10_latest_posts(q5);

        for (i = 0; i < 10; i++)
        {
            if (l[i])
            {
                printf(" POST %d :: %ld   ", i + 1, l[i]);
                q6p = postSet_lookup(com, l[i]);

                pdate = getP_date_point(q6p);
                printf(" - %d - %d - %d - \n", get_day(pdate), get_month(pdate), get_year(pdate));
            }
            else
                printf(" Can't find that post bro\n");
        }
        g_free(l);
        free_user(q5);
    }
    else
        printf(" Nao existe colega! \n");

    printf("______________________\n");
    printf("|->Q6\n\n");

    n = 50;
    q6 = most_voted_answers(com, n, begin, end);

    for (i = 0; i < n; i++)
    {

        if ((unsigned int)get_list(q6, i))
        {
            printf(">> %d   ", (int)get_list(q6, i));
            q6p = postSet_lookup(com, (unsigned int)get_list(q6, i));
            printf("\t < %d > \n", getP_score(q6p));
        }
        else
            printf(" Can't find that post bro\n");
    }

    g_free(q6);

    printf("______________________\n");
    printf("|->Q7\n\n");
    n = 10;
    q7 = most_answered_questions(com, n, begin, end);
    for (i = 0; i < n; i++)
    {

        if ((unsigned int)get_list(q7, i))
        {
            printf(">> %d   ", (int)get_list(q7, i));
            q7p = postSet_lookup(com, (unsigned int)get_list(q7, i));
            printf("\t < %d > \n", getP_ansCount(q7p));
        }
        else
            printf(" Can't find that post bro\n");
    }
    g_free(q7);

    printf("______________________\n");
    printf("|->Q9\n\n");
    n = 10;
    q9 = both_participated(com, 15811, 449, n);
    if (q9)
    {
        for (i = 0; i < n; i++)
        {

            if ((unsigned int)get_list(q9, i))
            {
                printf(">> %d   ", (int)get_list(q9, i));
                q9p = postSet_lookup(com, (unsigned int)get_list(q9, i));

                pdate = getP_date_point(q9p);
                printf("\t - %d - %d - %d - \n", get_day(pdate), get_month(pdate), get_year(pdate));
            }
            else
                printf(" Can't find that post bro\n");
        }
    }
    g_free(q9);
    clean(com);
    return 1;
}
*/

/**
 *
 * 
 * 
 * 
 *  
  */