#include <stdio.h>//se añaden las librerias necesarias para que el programa funcione
#include <stdlib.h>
#include <string.h>

typedef struct Node {//se declara el struct del nodo para la lista simple
    void *data;//esta variable lleva la informacion
    struct Node *next;//esta variable permite avanzar al siguiente nodo
} Node;

typedef struct {//se declara el struct de la lista
    Node *head;//esta variable apunta al primer nodo de la lista
    Node *tail;//esta variables apunta al ultimo nodo de la lista
    Node *current;//esta variable apunta al nodo actual de la lista
} List;

List *list_create() //funcion que crea una nueva lista
{
    List *lista=(List*) malloc(sizeof(List));//se usa memoria para determinar el tamaño
    lista->head=NULL;//todas las variables se inicializan en NULL
    lista->tail=NULL;
    lista->current=NULL;
    return lista;//se retorna la lista
}

void list_pushBack(List *lista,void *data) //funcion que añade un nuevo nodo al final de la lista
{
    Node *nodo=(Node*)malloc(sizeof(Node));//se usa memoria dinamica para determinar el tamaño del nuevo nodo
    nodo->data=data;//se asigna la informacion a la data
    nodo->next=NULL;//se asigna que el siguiente nodo es NULL
    if(lista->tail==NULL)//si el tail de la lista es NULL, significa que la lista esta vacia
    {
        lista->head=nodo;//la cabeza y la cola de la lista son el nuevo nodo
        lista->tail=nodo;
    } 
    else//si la lista tiene cola, se añade el nuevo nodo al final, este volviendose la nueva cola
    {
        lista->tail->next=nodo;
        lista->tail=nodo;
    }
}

void *list_first(List *lista) //funcion que devuelve la informacion del primer nodo de la lista
{
    if(lista==NULL || lista->head==NULL) //si la lista esta vacia, se devuelve NULL
    {
        return NULL;
    }
    lista->current=lista->head;//se declara que el current es la cabeza de la lista
    return lista->current->data;//se retorna la informacion
}

void *list_next(List *lista) //funcion que devuelve la informacion del nodo siguiente al current
{
    if(lista==NULL || lista->current==NULL || lista->current->next==NULL) //si la lista esta vacia o el siguiente al current es NULL, se retorna NULL
    {
        return NULL;
    }
    lista->current=lista->current->next;//el current pasa a ser el siguente
    return lista->current->data;//se retorna la informacion del nuevo current
}

void list_destroy(List *list) //funcion que libera la lista y sus nodos
{
    Node *curr=list->head;//nodo current que empieza en la cabeza de la lista
    while(curr!=NULL) //mientras el nodo sea distinto de NULL, el bucle continua
    {
        Node *tmp=curr;//se crea un temporal que es igual al current
        curr=curr->next;//current avanza al siguiente nodo
        free(tmp);//se libera la memoria del nodo tmp
    }
    free(list);//una vez liberados todos los nodos, se libera la lista
}

typedef struct TreeNode {//se declara el struct de los nodos del arbol binario
    char *key;//se declara la llave
    void *value;//el value contiene toda la informacion
    struct TreeNode *left;//variable que permite ir al hijo izquierdo
    struct TreeNode *right;//variable que permite ir al hijo derecho
    int height;//variable que registra la altura del nodo
} TreeNode;

typedef struct {//se declara el struct del arbol
    TreeNode *root;//nodo que apunta a la raiz del arbol
} Map;

int height(TreeNode *nodo) //funcion que retorna la altura de un nodo
{
    if(nodo==NULL)//si el nodo es NULL, se retorna 0
    {
        return 0;
    }
    return nodo->height;//sino se retorna la altura
}

int Max(int a,int b) //funcion que retorna la altura mas alta, compara la altura del subarbol derecho y el izquierdo
{
    if(a>b)//si a es mayor que b, se retorna a
    {
        return a;
    }
    return b;//si b es mayor, se retorna este
}

TreeNode *createNode(char *key,void *value) //funcion que crea un nuevo nodo para el arbol
{
    TreeNode *nodo=(TreeNode*)malloc(sizeof(TreeNode));//se usa memoria dinamica para determinar el tamaño del nuevo nodo
    nodo->key=strdup(key);//se duplica la llave original en la llave del nodo
    nodo->value=value;//se traspasa la informacion al nodo
    nodo->left=NULL;//se declara que el nuevo nodo no conecta con ningun otro
    nodo->right=NULL;
    nodo->height=1;//se declara que su altura es 1
    return nodo;//se retorna el nuevo nodo
}

TreeNode *rotateRight(TreeNode *y) //funcion que permite rotar un conjunto de nodos hacia la derecha
{
    TreeNode *x=y->left;//se declara un nodo x que es el nodo izquierdo de y
    TreeNode *T2=x->right;//se declara un nodo T2 que es el nodo derecho de x
    x->right=y;//y se vuelve el nodo derecho de x
    y->left=T2;//T2 se vuelve el nodo izquierdo de y
    y->height=Max(height(y->left),height(y->right))+1;//se calcula la nueva altura del nodo y
    x->height=Max(height(x->left),height(x->right))+1;//se calcula la nueva altura del nodo x
    return x;//se retorna el nodo x
}

TreeNode *rotateLeft(TreeNode *x) //funcion que permite rotar un conjunto de nodos hacia la derecha, sigue casi la misma logica que la funcion anterior pero se alternan los nodos
{
    TreeNode *y=x->right;
    TreeNode *T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=Max(height(x->left),height(x->right))+1;
    y->height=Max(height(y->left),height(y->right))+1;
    return y;
}

int getBalance(TreeNode *nodo) //funcion que devuelve el balance de un nodo
{
    if(nodo==NULL)//si el nodo es NULL, retorna NULL
    {
        return 0;
    }
    return height(nodo->left)-height(nodo->right);//sino, retorna la resta de las alturas del subarbol izquierdo menos el derecho
}

TreeNode *insertNode(TreeNode *nodo,char *key,void *value) //funcion que inserta un nuevo nodo en el arbol, ademas usa el metodo de autobalance AVL
{
    if(nodo==NULL)//si el nodo es NULL, simplemente se crea un nuevo nodo
    {
        return createNode(key,value);
    }
    int cmp=strcmp(key,nodo->key);//se compara la llave del nodo actual con la llave del nuevo nodo
    if(cmp<0)//si es menor a cero, se vuelve a llamar la funcion con el nodo a la izquierda del nodo original
    {
        nodo->left=insertNode(nodo->left,key,value);
    }
    else 
    {
        if(cmp>0)//si es mayor a 0, se se vuelve a llamar la funcion con el nodo a la derecha del nodo original
        {
            nodo->right=insertNode(nodo->right,key,value);
        }
        else//si las llaves son iguales, se retorna el nodo original, ya que no pueden haber llaves repetidas
        {
            return nodo;
        }
    }   
    nodo->height=1+Max(height(nodo->left),height(nodo->right));//se calcula la nueva altura del nodo original
    int balance=getBalance(nodo);//se calcula el balance del nodo original
    if(balance>1 && strcmp(key,nodo->left->key)<0)//si el balance es mayor a 1 y la llave del nuevo es menor al original, se rota a la derecha
    {
        return rotateRight(nodo);
    }
    if(balance<-1 && strcmp(key,nodo->right->key)>0)//si el balance es menor a -1 y la llave del nuevo es mayor a al original, se rota a la izquierda 
    {
        return rotateLeft(nodo);
    }
    if(balance>1 && strcmp(key,nodo->left->key)>0) //si el balance es mayor a 1 y la llave del nuevo es mayor al original, se rota el nodo izquierdo del nodo original y luego el nodo original se rota a la derecha
    {
        nodo->left=rotateLeft(nodo->left);
        return rotateRight(nodo);
    }
    if(balance<-1 && strcmp(key,nodo->right->key)<0) //si el balance es menor a -1 y la llave del nuevo es menor al original, se rota el nodo derecho del nodo original y luego el nodo original se rota a la izquierda
    {
        nodo->right=rotateRight(nodo->right);
        return rotateLeft(nodo);
    }
    return nodo;//se retorna el nodo
}

Map *map_create() //funcion que crea el arbol binario
{
    Map *mapa=(Map*)malloc(sizeof(Map));//se usa memoria dinamica para determinar el tamaño del arbol
    mapa->root=NULL;//se declara la raiz como NULL
    return mapa;//se retorna el mapa
}

void map_insert(Map *map,char *key,void *value) //funcion que inserta un nuevo nodo al arbol
{
    map->root=insertNode(map->root,key,value);//se llama a la funcion insertNode comenzando desde la raiz del arbol
}

void *map_search(Map *map,char *key) //funcion que permite buscar un nodo en el arbol
{
    TreeNode *curr=map->root;//se crea el nodo current que empieza en la raiz del arbol
    while(curr!=NULL) 
    {
        int cmp=strcmp(key,curr->key);//se comparan las llaves del nodo actual con la llave que se busca 
        if(cmp==0)//si son iguales, se retorna la informacion del nodo actual
        {
            return curr->value;
        }
        else 
        {
            if(cmp<0)//si la llave es menor al del nodo, se avanza al nodo izquierdo
            {
                curr=curr->left;
            }
            else//si la llave es mayor al del nodo, se avanza al nodo derecho
            {
                curr=curr->right;
            }
        }
    }
    return NULL;//si no se encuentra, se retorna NULL
}

void destroyTree(TreeNode *nodo,void (*freeValue)(void*)) //funcion que libera los nodos del arbol, la funcion freeValue es una funcion que libera la memoria de la variable value dentro de los nodos
{
    if(nodo==NULL)//si el nodo es NULL, se retorna NULLo
    {
        return;
    }
    destroyTree(nodo->left,freeValue);//se vuelve a llamar la funcion con el nodo izquierdo del original
    destroyTree(nodo->right,freeValue);//lo mismo pero con el derecho
    if(freeValue!=NULL)//si freevalue es distinto de NULL(osea que se contenga informacion de una pelicula), se libera la informacion del value del nodo
    {
        freeValue(nodo->value);
    }
    free(nodo->key);//se libera la llave del nodo
    free(nodo);//se libera el nodo
}

void map_destroy(Map *map, void (*freeValue)(void*)) //funcion para liberar el arbol
{
    destroyTree(map->root, freeValue);//se llama a la funcion destroyTree, esta inicializa con la raiz del arbol
    free(map);//una vez liberado todos los nodos, se libera el arbol
}

typedef struct{//se declara el struct de las peliculas que se ingresen
    char id[20];//variable que recibe la id de la pelicula
    char titulo[200];//variable que recibe el titulo de la pelicula
    char director[200];//variable que recibe los directores
    char genero[100];//recibe los generos
    int anio;//recibe el año
    float rating;//recibe el rating
} Pelicula;

void insertar_en_mapa_lista(Map *map,char *key,Pelicula *p) //funcion que permite insertar una nueva lista de peliculas en un arbol
{
    List *lista=map_search(map,key);//se busca la llave en el arbol
    if(lista==NULL) //si no existe un lista asociada a esa llave, se crea una nueva lista y se inserta dentro del arbol como un nuevo nodo
    {
        lista=list_create();
        map_insert(map,key,lista);
    }
    list_pushBack(lista, p);//se inserta la informacion de la pelicula al final de la lista
}

void imprimir_pelicula(Pelicula *p) //funcion que imprime toda la informacion de una pelicula
{
    printf("ID: %s | Titulo: %s | Director: %s | Genero: %s | Anio: %d | Rating: %.1f\n", p->id,p->titulo,p->director,p->genero,p->anio,p->rating);
    printf("----------------------\n");
}

void limpiarPantalla()//esta funcion limpia la pantalla de todo lo que haya sido impreso, esto para evitar una acumulacion de texto en pantalla
{
  #ifdef _WIN32//en caso que el sistema operativo sea windows se usa este comando
    system("cls");
  #else//en caso que el sistema operativo sea otro(linux,macOS,etc.) se usa este comando
    system("clear");
  #endif//se termina la funcion
}

void mostrarMenuPrincipal() //funcion que imprime el menu principal del programa
{
  limpiarPantalla();//se limpia la pantalla
  puts("======================");//se imprimen las opciones y lo demas
  puts("     StreamFinder");
  puts("======================");
  puts("1) Cargar Peliculas");
  puts("2) Buscar por genero");
  puts("3) Buscar por director");
  puts("4) Buscar por decada");
  puts("5) Busqueda avanzada(genero y decada)");
  puts("6) Gestionar mi Watchlist");
  puts("7) Salir");
}

void presioneTeclaParaContinuar()//funcion que al terminar con la funcion de la opcion escogida, pide presioner una tecla para seguir al siguiente bucle o terminar con el bucle en caso de salir
{
  printf("\nPresione ENTER para continuar...");
  int c;//variable que registra el valor de ENTER
  while((c=getchar())!='\n' && c!=EOF);//"\n" es un salto de linea y EOF es un valor(generalmente -1) que indica que no hay mas datos por leer, asi que mientras que c sea distintos a estos dos, el bucle continuara
  getchar();//comando que obtiene el valor ASCII de un caracter y espera que el usuario presione ENTER
}

void cargar_peliculas(Map *PelisPorId, Map *PelisPorGenero, Map *PelisPorDirector, Map *PelisPorDecada)//funcion que recibe un archivo CSV, analiza si cumple un formato preestablecido e ingresa la informacion en distintos mapas
{
    char nombreArchivo[256];//variable que recibe el nombre del archivo
    printf("Ingrese el nombre/ruta del archivo CSV: ");
    scanf(" %[^\n]",nombreArchivo);//se escanea el nombre ingresado
    FILE *archivo=fopen(nombreArchivo,"r");//se abre el archivo
    if(archivo==NULL)//si el archivo es NULL, se imprime lo siguiente y se retorna
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char linea[4096];//variable que recibe una linea de texto
    if(fgets(linea,sizeof(linea),archivo)==NULL)//si fgets no recibe ningun texto en la primera linea, significa que el archivo esta vacio, se retorna NULL y se cierra el archivo
    {
        printf("El archivo esta vacio!\n");
        fclose(archivo);
        return;
    }
    char encabezados[30][256];//variable que recibe los encabezados de cada columna del archivo
    int i=0;//variables que permiten explorar el archivo
    int j=0;
    int k=0;
    int dentroComillas=0;//variable que analiza si se hay texto dentro de comillas
    while(linea[i]!='\0')//mientras la linea sea distinto a caracter nulo, el bucle continua
    {
        if(linea[i]=='"')//si la linea esta entre comillas, se declara que la variable dentroComillas es distinto de 0
        {
            dentroComillas = !dentroComillas;
        }
        else
        {
            if(linea[i]==',' && !dentroComillas)//si la linea es una coma y esta dentro de comillas
            {
                encabezados[j][k]='\0';//el cabezado (j,k) es un caracter nulo
                j++;//j aumenta en 1
                k=0;//k vuelve a ser 0
            }
            else//sino se verifica lo siguiente
            {
                if(linea[i]!='\n' && linea[i]!='\r')//si la linea es distinto a salto de linea y a retorno de carro
                {
                    encabezados[j][k++]=linea[i];//el encabezado(j,k+1) es igual a la linea i
                }
            }
        }
        i++;//a i se le suma 1
    }
    encabezados[j][k]='\0';//el encabezado (j,k) es igual a caracter nulo
    int totalColumnas=j+1;//variable que cuenta el total de columnas, siendo j+1
    int indiceID=-1;//se crean variables en -1 que sirven para verificar si el archivo cuenta con los parametros necesarios para crear los mapas
    int indiceTitulo=-1;
    int indiceDirector=-1;
    int indiceGenero=-1;
    int indiceAnio=-1;
    int indiceRating=-1;
    for(i=0;i<totalColumnas;i++)//mientras la variable i sea menor al total de colmumnas, el bucle continua
    {
        if(strcmp(encabezados[i],"Const")==0)//si el encabezado i es igual al ID de la pelicula, la variable cambia de valor
        {
            indiceID=i;
        }
        else 
        {
            if(strcmp(encabezados[i],"Title")==0)//se hace lo mismo con cada variable
            {
                indiceTitulo=i;
            }
            else 
            {
                if(strcmp(encabezados[i],"Directors")==0)
                {
                    indiceDirector=i;
                }
                else 
                {
                    if(strcmp(encabezados[i],"Genres")==0)
                    {
                        indiceGenero=i;
                    }
                    else 
                    {
                        if(strcmp(encabezados[i],"Year")==0)
                        {
                            indiceAnio=i;
                        }
                        else 
                        {
                            if(strcmp(encabezados[i],"IMDb Rating")==0)
                            {
                                indiceRating=i;
                            }
                        }
                    }
                }
            }
        }
    }
    if(indiceID==-1 || indiceTitulo==-1 || indiceDirector==-1 || indiceGenero==-1 || indiceAnio==-1 || indiceRating==-1)//si alguna variable termina con un -1, significa que el archivo no cumple con los parametro requeridos
    {
        printf("El archivo no tiene la estructura correcta!\n");
        fclose(archivo);
        return;
    }
    int peliculasCargadas=0;//contador que cuenta cuantas peliculas se cargaron
    while(fgets(linea,sizeof(linea),archivo))//mientras haya texto, el bucle continua
    {
        char campos[30][512];//lo mismo que se hizo cuando se buscaban los parametros
        i = 0;
        j = 0;
        k = 0;
        dentroComillas = 0;
        while(linea[i]!='\0')
        {
            if(linea[i]=='"')
            {
                dentroComillas = !dentroComillas;
            }
            else 
            {
                if(linea[i]==',' && !dentroComillas)
                {
                    campos[j][k]='\0';
                    j++;
                    k=0;
                }
                else 
                {
                    if(linea[i]!='\n' && linea[i]!='\r')
                    {
                        campos[j][k++]=linea[i];
                    }
                }
            }
            i++;
        }
        campos[j][k] = '\0';
        if(strlen(campos[indiceID])==0 || strlen(campos[indiceTitulo])==0)//si la longitud de ambos campos es 0, se continua con el siguiente ciclo
        {
            continue;
        }
        Pelicula *peli=(Pelicula*)malloc(sizeof(Pelicula));//se crea un nuevo struct para pelicula usando memoria dinamica
        strcpy(peli->id,campos[indiceID]);//se copia toda la informacion respectiva a las distintas variables del struct
        strcpy(peli->titulo,campos[indiceTitulo]);
        strcpy(peli->director,campos[indiceDirector]);
        strcpy(peli->genero,campos[indiceGenero]);
        peli->anio=atoi(campos[indiceAnio]);
        peli->rating=atof(campos[indiceRating]);
        map_insert(PelisPorId,peli->id,peli);//se inserta la informacion en el arbol PelisPorId
        char generos[512];//variable que recibe el nombre de los generos de pelis
        strcpy(generos,peli->genero);//se copia el/los genero/s
        char *tokenGenero=strtok(generos,",");//se crea/n una/s variable/s que recibe/n cada uno de los generos de la pelicula actual, estas separadas por una coma
        while(tokenGenero!=NULL)//mientras hayan tokens, se continua
        {
            while(*tokenGenero==' ')//mientras el token sea un espacio vacio, se avanza en el token
            {  
                tokenGenero++;
            }
            insertar_en_mapa_lista(PelisPorGenero,tokenGenero,peli);//se inserta la informacion en el arbol PelisPorGenero
            tokenGenero=strtok(NULL,",");//se elimia el token actual y se pasa al siguiente
        }
        insertar_en_mapa_lista(PelisPorDirector,peli->director,peli);//se inserta la informacion en el arbol PelisPorDirector
        char decada[20];//variable para el año
        sprintf(decada,"%d",(peli->anio/10)*10);//se cambia el ultimo digito del año para ver a que decada pertenece
        insertar_en_mapa_lista(PelisPorDecada,decada,peli);//se inserta la informacion en el arbol PelisPorDecada
        peliculasCargadas++;//el contador aumenta en 1
    }
    fclose(archivo);//una vez teerminado se cierra el archivo y se imprime que se cargo correctamente y el total de pelis cargadas
    printf("Catalogo cargado correctamente.\n");
    printf("Peliculas cargadas: %d\n",peliculasCargadas);
}

void buscar_por_genero(Map *PelisPorGenero)//funcion para buscar peliculas por genero
{
    char genero[100];//variable que recibe el genero deseado
    printf("Ingrese genero: ");
    scanf(" %[^\n]",genero);//escanea el genero ingresado
    List *lista = map_search(PelisPorGenero,genero);//revisa si existe el genero dentro del arbol PelisPorGenero
    if(lista==NULL) //si la lista es NULL, significa que no hay peliculas de este genero y se retorna
    {
        printf("No hay peliculas de este genero\n");
        return;
    }
    Pelicula *peli=list_first(lista);//se busca el primer nodo de la lista de peliculas del genero deseado
    while(peli!=NULL)//mientras peli sea distinto de NULL, se continua
    {
        imprimir_pelicula(peli);//se imprime la informacion de la peli
        peli=list_next(lista);//se avanza al siguiente nodo
    }
}

void buscar_por_director(Map *PelisPorDirector)//funcion para buscar pelis por director
{
    char director[100];//variable que recibe el nombre del director deseado
    printf("Ingrese director: ");
    scanf(" %[^\n]", director);
    List *lista=map_search(PelisPorDirector,director);//se revisa si existe el director dentro del arbol PelisPorDirector
    if(lista==NULL) //si la lista es NULL, significa que no hay peliculas de ese director y se retorna
    {
        printf("No hay peliculas de este director\n");
        return;
    }
    Pelicula *peli=list_first(lista);//se busca el primer nodo de la lista de pelis de ese director
    while(peli!=NULL)
    {
        imprimir_pelicula(peli);//se imprime la informacion de la peli
        peli=list_next(lista);//se avanza al siguiente nodo
    }
}

void buscar_por_decada(Map *PelisPorDecada)//funcion para buscar por decada
{
    int anio;//variable que recibe el año deseado
    printf("Ingrese anio: ");
    scanf("%d",&anio);
    char key[10];//variable que se usa para pasar el año ingresado a string
    sprintf(key,"%d",(anio/10)*10);//se pasa el año a string y se convierte el ultimo digito en un 0
    List *lista=map_search(PelisPorDecada,key);//revisa si hay una lista de pelis de esa decada
    if(lista==NULL)//si la lista es NULL, no hay pelis de esa decada y se retorna 
    {
        printf("No hay peliculas de esta decada\n");
        return;
    }
    Pelicula *peli=list_first(lista);//se busca el primer nodo de la lista
    while(peli!=NULL) 
    {
        imprimir_pelicula(peli);//se imprime la informacion
        peli=list_next(lista);//se avanza al siguiente nodo
    }
}

void busqueda_avanzada(Map *PelisPorGenero)//funcion para buscar pelis por su genero y año
{
    char genero[100];//variable que recibe el genero deseado
    int anio;//variable que recibe el año deseado
    printf("Genero: ");
    scanf(" %[^\n]",genero);
    printf("Anio: ");
    scanf("%d",&anio);
    List *lista=map_search(PelisPorGenero,genero);//revisa si existe el genero en el arbol PelisPorGenero
    if(lista==NULL)//si la lista es NULL, no existe
    {
        printf("No hay peliculas de este genero y decada\n");
        return;
    }
    Pelicula *peli=list_first(lista);//se busca el primer nodo de la lista
    int cantPelis=0;//contador que analiza cuantas pelis de la decada deseada hay
    while(peli!=NULL) 
    {
        if((peli->anio/10)*10==(anio/10)*10)//se cambian los ultimos digitos de las decadas por 0 y se comparan, si son iguales, se imprime la informacion de esa peli y el contador aumenta en 1
        {
            imprimir_pelicula(peli);
            cantPelis++;
        }
        peli=list_next(lista);//se avanza al siguiente nodo
    }
    if(cantPelis==0)//si el contador es 0, significa que no hay peliculas de esa decada
    {
        printf("No hay peliculas de este genero y decada\n");
    }
    return;
}

void agregar_pelicula(List *watchlist,Map *PelisPorId)//funcion para agregar peliculas a la watchlist
{
    char id[20];//variable que recibe el id de la pelicula deseada
    printf("Ingrese ID: ");
    scanf(" %[^\n]",id);
    Pelicula *peli=map_search(PelisPorId,id);//revisa si existe la id en el arbol PelisPorId
    if(peli==NULL) //si la lista es NULL, no existe
    {
        printf("Esta pelicula no existe!\n");
        return;
    }
    Pelicula *aux=list_first(watchlist);//se busca el primer nodo de la watchlist
    while(aux!=NULL) 
    {
        if((strcmp(peli->id,aux->id)==0) && (strcmp(aux->id,peli->id)==0))//se comparan el id de la pelicula deseada con el del nodo actual, si son iguales, significa que la pelicula ya esta en la watchlist
        {
            printf("Esta pelicula ya esta en la watchlist!\n");
            return;
        }
        aux=list_next(watchlist);//se avanza al siguiente nodo
    }
    list_pushBack(watchlist,peli);//si la pelicula no esta en la watchlist, se crea un nuevo nodo al final de la lista
    printf("Pelicula agregada correctamente!\n");
}

void eliminar_pelicula(List *watchlist)//funcion para eliminar peliculas de la watchlist
{
    char id[20];//variable que recibe la id de la peli deseada
    printf("Ingrese ID de la pelicula a eliminar: ");
    scanf(" %[^\n]",id);
    Node *actual=watchlist->head;//nodo actual que comienza en la cabeza de la lista
    Node *anterior=NULL;//nodo que recibe el valor del nodo anterior al nodo a eliminar, si existe un anterior
    while(actual!=NULL)
    {
        Pelicula *peli=(Pelicula*)actual->data;//se ingresa a la informacion del nodo actual
        if(strcmp(peli->id,id)==0)//se comparan las id, si son iguales, significa que la pelicula existe en la lista y procede a eliminarse
        {
            if(anterior==NULL)//si anterior es NULL, significa que el nodo a eliminar es la cabeza, asi que la cabeza pasa a ser el nodo siguiente
            {
                watchlist->head=actual->next;
            }
            else//sino, el siguiente del actual pasa a ser el siguiente del anterior al actual
            {
                anterior->next=actual->next;
            }
            if(actual==watchlist->tail)//si el actual es la cola de la lista, el anterior pasa a ser la cola
            {
                watchlist->tail=anterior;
            }
            free(actual);//se libera el actual
            printf("Pelicula eliminada correctamente\n");
            return;
        }
        anterior=actual;//si las id no son iguales, anterior toma el valor de actual
        actual=actual->next;//y actual pasa al siguiente de la lista
    }
    printf("La pelicula no esta en la watchlist!\n");//si la id no coincide con ninguna de la lista, significa que la id no existe dentro de la watchlist
}

void mostrar_watchlist(List *watchlist)//funcion que imprime todas las peliculas en la watchlits
{
    Pelicula *peli=list_first(watchlist);//se busca el primer nodo de la watchlist
    if(peli==NULL)//si la lista es NULL, no hay peliculas en la watchlist
    {
        printf("No hay peliculas en la watchlist!\n");
    }
    while(peli!=NULL) //se imprime la informacion de todas las peliculas en la watchlist
    {
        imprimir_pelicula(peli);
        peli=list_next(watchlist);
    }
}

void gestionar_mi_watchlist(Map *map,List *watchlist)//funcion para gestionar la watchlist
{
    char opcion;//variable que recibe la opcion deseada
    do
    {
        limpiarPantalla();//limpia la pantalla
        printf("===========================\n");//se imprime el menu de la gestion de watchlist
        printf("  Gestion de mi Watchlist\n");
        printf("===========================\n");
        printf("(1) Agregar Pelicula\n");
        printf("(2) Eliminar Pelicula\n");
        printf("(3) Mostrar Watchlist\n");
        printf("(4) Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%c",&opcion);
        switch(opcion)//se revisa la opcion ingresada
        {
        case '1'://si la opcion es 1, se llama a la funcion agregar_pelicula, que recibe la lista de watchlist y el arbol PelisPorId
            agregar_pelicula(watchlist,map);
            break;
        case '2'://si la opcion es 2, se llama a la funcion eliminar_pelicula, que recibe la watchlist
            eliminar_pelicula(watchlist);
            break;
        case '3'://si la opcion es 3, se llama a la funcion mostrar_watchlist, que recibe la watchlist
            mostrar_watchlist(watchlist);
            break;
        case '4'://si la opcion es 4, se cierra la gestion de watchlist y se vuelve al menu principal
            printf("Saliendo de la Gestion . . .\n");
            break;
        default://si se ingresa un numero que no sea valido(numero menor a 1 y mayor a 4) o algo que no sea un numero, se imprime lo siguiente
            printf("Ingresa una opcion valida!");
            break;
        }
        presioneTeclaParaContinuar();//se pide presionar ENTER para continuar con el proceso
    }while(opcion!='4');//si la opcion es 4 el bucle se cierra
    return;
}

int main() {//la funcion principal del programa
    char opcion; // Variable para almacenar una opcion ingresada por el usuario
    Map *PelisPorId=map_create();//se crea un arbol para almacenar peliculas por su Id
    Map *PelisPorGenero=map_create();//se crea un arbol para almacenar peliculas por su genero
    Map *PelisPorDirector=map_create();//se crea un arbol para almacenar peliculas por su director
    Map *PelisPorDecada=map_create();//se crea un arbol para almacenar peliculas por su decada
    List *watchlist=list_create();//se crea una lista para la watchlist
    do {
        mostrarMenuPrincipal();//muestra la informacion del menu principal
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);
        switch (opcion)//se analiza la opcion ingresada por el usuario
        {
        case '1'://si la opcion es 1, se llama a la funcion cargar_peliculas, que recibe los cuatro arboles y carga la informacion de un archivo CSV
            cargar_peliculas(PelisPorId,PelisPorGenero,PelisPorDirector,PelisPorDecada);
            break;
        case '2'://si la opcion es 2, se llama a la funcion buscar_por_genero, que recibe el arbol PelisPorGenero
            buscar_por_genero(PelisPorGenero);
            break;
        case '3'://si la opcion es 3, se llama a la funcion buscar_por_director, que recibe el arbol PelisPorDirector
            buscar_por_director(PelisPorDirector);
            break;
        case '4'://si la opcion es 4, se llama a la funcion buscar_por_decada, que recibe el arbol PelisPorDecada
            buscar_por_decada(PelisPorDecada);
            break;
        case '5'://si la opcion es 5, se llama a la funcion busqueda_avanzada, que recibe el arbol PelisPorGenero
            busqueda_avanzada(PelisPorGenero);
            break;
        case '6'://si la opcion es 6, se llama a la funcion gestionar_mi_watchlist, que recibe el arbol PelisPorId y la lista watchlist
            gestionar_mi_watchlist(PelisPorId,watchlist);
            break;
        case '7'://si la opcion es 7, se cierra el programa
            printf("Saliendo de StreamFinder . . .\n");
            break;
        default://si se ingresa un numero que no sea valido(numero menor a 1 y mayor a 7) o algo que no sea un numero, se imprime lo siguiente
            printf("Ingresa una opcion valida!");
            break;
        }
        presioneTeclaParaContinuar();//se pide presionar ENTER para continuar con el bucle o cerrarlo en caso que se salga de este
    } while (opcion != '7');//si la opcion es 7 el bucle se cierra
    map_destroy(PelisPorGenero,(void*)list_destroy);//se llama a la funcion map_destroy y se libera toda la memoria del arbol PelisPorGenero
    map_destroy(PelisPorDirector,(void*)list_destroy);//se llama a la funcion map_destroy y se libera toda la memoria del arbol PelisPorDirector
    map_destroy(PelisPorDecada,(void*)list_destroy);//se llama a la funcion map_destroy y se libera toda la memoria del arbol PelisPorDecada
    map_destroy(PelisPorId,free);//se llama a la funcion map_destroy y se libera toda la memoria del arbol PelisPorId
    list_destroy(watchlist);//se llama a la funcion list_destroy y se libera la memoria de la lista watchlist
    return 0;//se retorna 0 y cierra el programa
}