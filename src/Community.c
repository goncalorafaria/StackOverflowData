#include <glib.h>
#include "Community.h"
#include <date.h>
#include "bArray.h"

#include <stdio.h>

typedef struct TCD_community
{
    GHashTable *userById;

    //GHashTable *userByName;
    bArray PostArray;
    GHashTable *post;

} * TAD_community;

/*
*/

int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data)
{

    // user data será sempre null;
    Date x = (Date)a, y = (Date)b;

    if (get_year(x) > get_year(y))
        return 1;
    else if (get_year(x) < get_year(y))
        return -1;
    //-----------------------------------------
    if (get_month(x) > get_month(y))
        return 1;
    else if (get_month(x) < get_month(y))
        return -1;
    //-----------------------------------------
    if (get_day(x) > get_day(y))
        return 1;
    else if (get_day(x) < get_day(y))
        return -1;

    return 0;
}

static int post_src(void *a, void *b, void *garb)
{ // Post, date.
    Post x = (Post)a;

    return (-1) * date_compare(getP_date_point(x), (Date)b, NULL);
}
int post_ord(const void *a, const void *b)
{

    Post an = *(Post *)a;
    Post bn = *(Post *)b;

    return date_compare(getP_date_point(an), getP_date_point(bn), NULL);
}

void gen_free_date(void *d)
{
    free_date((Date)d);
}

TAD_community init(void)
{

    TAD_community x = g_malloc(sizeof(struct TCD_community));

    x->userById = g_hash_table_new_full(g_int64_hash, g_int64_equal, NULL, destroyUtil);
    //x->userByName = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    x->post = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, destroyPost);

    x->PostArray = NULL;
    return x;
}

TAD_community clean(TAD_community com)
{
    g_hash_table_destroy(com->userById);

    //if( com->userByName)
    //  g_hash_table_destroy(com->userByName);

    g_hash_table_destroy(com->post);

    if (com->PostArray)
        destroy_A(com->PostArray);

    g_free(com);

    return NULL;
}
/*

TAD_community terminate_UbyName( TAD_community com ){
    g_hash_table_destroy(com->userByName);
    com->userByName = NULL;
    return com;
}
Util userSet_name_lookup(TAD_community com, unsigned char *name)
{
    return (Util)g_hash_table_lookup(com->userByName, name);
}
TAD_community userSet_insert_name(TAD_community com, unsigned char *key, Util x)
{
    g_hash_table_insert(com->userByName, (void *)key, (void *)x);
    return com;
}

*/

int reverseCompare(void *a, void *b, void *fun)
{

    Fcompare the_func = (Fcompare)fun;
    return (-1) * the_func(a, b, NULL);
}

TAD_community turnOn_array(TAD_community com, unsigned long n)
{
    com->PostArray = init_A(n, NULL);
    return com;
}
TAD_community insert_array(TAD_community com, Post x)
{
    com->PostArray = add_to_A(com->PostArray, (void *)x);
    return com;
}

TAD_community finalize_array(TAD_community com)
{
    com->PostArray = sort_A(com->PostArray, post_ord);
    return com;
}

HEAP array_Priority_Queue(TAD_community com, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{
    return Generalized_Priority_Queue(com->PostArray, Qsize, q_cmp, filter, user_data);
}

HEAP arraySeg_Priority_Queue(TAD_community com, Date begin, Date end, unsigned long Qsize, Fcompare q_cmp, int (*filter)(void *, void *), void *user_data)
{
    return from_to_Priority_Queue(com->PostArray, begin, end, Qsize, q_cmp, post_src, filter, user_data);
}

static void print(void *x, void *y)
{

    //Post a = (Post)x;
    //Date d = getP_date_point(a);

    Date d = x;
    printf(" %d-%d-%d \n", get_day(d), get_month(d), get_year(d));
}

void *arraySeg_transversal(TAD_community com, Date begin, Date end, void (*functor)(void *, void *), void *user_data)
{
    return for_each_from_to(com->PostArray, begin, end, functor, post_src, user_data);
}

void *arrayRev_transversal(TAD_community com, int (*functor)(void *, void *), void *user_data)
{
    return for_each_rev(com->PostArray, functor, user_data);
}


void *show_date(TAD_community com)
{
    for_each(com->PostArray, print, NULL);
    return NULL;
}

// USER HASHTABLE;
TAD_community userSet_insert_id(TAD_community com, unsigned long *key, Util x)
{

    g_hash_table_insert(com->userById, (void *)key, (void *)x);
    return com;
}

void *userSet_id_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{
    //g_hash_table_foreach(com->userById, f, x);
    
    GHashTableIter iter;
    void *key, *value;

    g_hash_table_iter_init(&iter, com->userById);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        f(key, value, x);
    }

    return x;
}

Util userSet_id_lookup(TAD_community com, unsigned long num)
{
    return (Util)g_hash_table_lookup(com->userById, &num);
}

unsigned int userSet_size(TAD_community com)
{
    return g_hash_table_size(com->userById);
}

// POST HASHTABLE
TAD_community postSet_insert(TAD_community com, unsigned int *key, Post x)
{
    g_hash_table_insert(com->post, (void *)key, (void *)x);
    return com;
}

Post postSet_lookup(TAD_community com, unsigned int num)
{
    return (Post)g_hash_table_lookup(com->post, &num);
}

void *postSet_transversal(TAD_community com, void (*f)(void *, void *, void *), void *x)
{   
    g_hash_table_foreach(com->post, f, x);
    
    
    GHashTableIter iter;
    void *key, *value;

    g_hash_table_iter_init(&iter, com->post);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        f(key, value, x);
    }
    
    return x;
}

unsigned int postSet_size(TAD_community com)
{
    return g_hash_table_size(com->post);
}
