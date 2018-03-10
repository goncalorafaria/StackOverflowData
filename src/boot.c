//#include "interface.h"
#include <libxml/parser.h>

#include <stdio.h> // temporario
#include <string.h>
#include <ctype.h>
#include "Community.h"
//#include <Bloco.h>
#include <glib.h>


/**
 *  Main structure.
 * 
 * 
 * PostTypeId =1 pergunta;
 * 
 * PostTypeId = 2 resposta;
 * */
#define getAtr(hold,n,str) hold = xmlGetProp(n, (const xmlChar*)str)

#define convert_to_lowercase(p,str) for( (p)=(str) ; *(p)!='\0'; (p)++) *(p) = tolower(*(p))
typedef void (*parse_function) (TAD_community , const xmlNode*);

// Métodos publicos.
//TAD_community init();
//TAD_community clean(TAD_community com);
//TAD_community load(TAD_community com, char* dump_path)

// Métodos privados.
//static void parsePost( TAD_community com, xmlNode * node);
static void parseUser( TAD_community com, const xmlNode * node);
static void parser ( TAD_community com , char* dump_path, char* file_name , parse_function f  );
static void parsePost ( TAD_community com , const xmlNode* node );
static void parseHistory ( TAD_community com, const xmlNode* node);
//

// recebe uma avl tree e retira de la as datas , para um su-array defenido no glib
// estou a assumir que recebo uma AVL;

TAD_community load(TAD_community com, char* dump_path){

    parser(com, dump_path, "Users", parseUser);
    printf("USER::%d \n",userSet_size(com));
    parser(com, dump_path, "Posts", parsePost);
    printf("USER::%d \n",postSet_size(com));
    parser(com, dump_path, "PostHistory", parseHistory);
    
    /*
    ///////////////////////////////////////////////////////////////////
    
    sprintf(tmpstr,"%s/Posts.xml",dump_path);
    doc = xmlReadFile(tmpstr, NULL, 0);

    if( !doc )
        perror("Could not parse the XML file\n");
    
    root_element = xmlDocGetRootElement(doc);

    parsePost(com,root_element);
    printf("USER::%d \n",postSet_size(com));
    
    g_free(tmpstr);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    // x.............................................................
    */
    return com;
}

static void parser ( TAD_community com , char* dump_path, char* file_name , parse_function f ){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    xmlNode *node = NULL;
    char* p;
    
    char* docname = g_malloc( sizeof(char)* ( strlen(dump_path) + strlen(file_name) + 6) ); 
    ////////////////////////////////////////////7
    sprintf(docname,"%s/%s.xml",dump_path,file_name);

    //printf("%s\n",tmpstr);
    doc = xmlParseFile(docname);

    if( !doc )
        perror("Erro no parse do documento XML.\n");
    
    root_element = xmlDocGetRootElement(doc);

    if ( !root_element ) {
        perror("Documento vazio.\n");
        xmlFreeDoc(doc);
        return;
    }
    node = root_element;
    strcpy(docname,file_name);
    convert_to_lowercase(p,docname);

    if (xmlStrcmp(node->name, (const xmlChar *) docname) ) {
        perror("Documento do tipo errado.\n");
        xmlFreeDoc(doc);
        return;
    }
    node = node->xmlChildrenNode;
    while (node != NULL) {
        if ((!xmlStrcmp(node->name, (const xmlChar *)"row"))){
            //perror("->alivde\n");
            f(com , node);
            //printf("%d -> size \n ",userSet_size(com) );
        }
        node = node->next;
    }

    g_free(docname);
    xmlFreeDoc(doc);

    xmlCleanupParser();
    xmlMemoryDump();
    return;
}

static void parsePost ( TAD_community com , const xmlNode* node ){

    xmlChar * hold;
    char buffer[100];
    int dia, mes, ano ;
    unsigned int *ident;
    Post x = NULL;
    //unsigned long childCount = xmlChildElementCount(node),i;
 
            //printf("%c%s\n",'-', node->name);
            //printf("%d\n",++e);
    x = (Post)createPost();

    ident = g_malloc ( sizeof( unsigned int ) );

            // GET POST ID <LONG> getatr( hold , n , str )
    getAtr(hold,node,"Id");
    *ident = (unsigned int) atoi((const char*) hold );
    xmlFree(hold);

    setP_id(x, *ident );

            // GET POST DATE
    getAtr(hold,node,"CreationDate");
    sscanf( (const char*)hold,"%d-%d-%d%s",&ano,&mes,&dia,buffer);
    xmlFree(hold);
    setP_date(x, dia,mes,ano);

            // GET POST TYPE
    getAtr(hold,node,"PostTypeId");
    setP_type ( x , (unsigned char) atoi((const char*) hold ) );
    xmlFree(hold);

    if( getP_type(x) == 2 ){// ans
        getAtr(hold,node,"ParentId");
        setP_parentId( x ,(unsigned int) atoi((const char*) hold ) );
        xmlFree(hold);
    }
    // ADD SCORE.
    getAtr(hold,node,"Score");
    setP_score(x ,(unsigned int) atoi((const char*) hold ));
    //printf("%s\n",(char*)hold);
    xmlFree(hold);

    // GET OWNER REF

    // GET POST TITLE
    getAtr(hold,node,"Title");
    if(hold){
        setP_name(x, (unsigned char*)hold );
        xmlFree(hold);
    }

    postTree_insert(com, getP_date_point(x) , x );
    postSet_insert(com , ident, x );

}

static void parseUser ( TAD_community com , const xmlNode* node ){

    xmlChar * hold=NULL;
    Util x = NULL;
    unsigned long *ident;
    //unsigned long childCount = xmlChildElementCount(node),i;
    //printf("erros\n");
    x = (Util)createUtil();
    ident = g_malloc ( sizeof( unsigned long ));

            // get user id
    getAtr(hold,node,"Id");
    *ident = (unsigned long) atol((const char*) hold );
    //printf("%d \n",(int)*ident);
    xmlFree(hold);
            
            // GET UTIL BIO
    getAtr(hold,node,"AboutMe");
    
    if(hold ){
        setU_bio(x, (unsigned char*)hold );
        //printf("%s \n",(char*)hold);
        xmlFree(hold);
    }

            // get Display name
    getAtr(hold,node,"DisplayName");
    setU_name(x, (unsigned char*)hold );
    xmlFree(hold);

    userSet_insert( com, ident, x );
    return;
}

static void parseHistory ( TAD_community com, const xmlNode* node){

    xmlChar * hold=NULL;
    Util x = NULL;
    Post y = NULL;
    unsigned long userId;
    unsigned int postId;

    getAtr(hold,node,"UserId");
    userId = (unsigned long) atol((const char*) hold );
    xmlFree(hold);

    getAtr(hold,node,"PostId");
    postId = (unsigned int) atoi((const char*) hold );
    xmlFree(hold);

    x = userSet_lookup(com, userId);
    if ( !x ) return;
    y = postSet_lookup(com, postId);
    if ( !y ) return;

    if( getP_type(y) == 1 ){
        inc_Q(x);
    }

    if( getP_type(y) == 2 ){
        inc_A(x);
    }

    setP_fund(y, userId);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    bind_toBacia(x,y);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  

    return;
}
