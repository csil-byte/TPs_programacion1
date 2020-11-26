#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc (sizeof(LinkedList));

    if (this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	int len = ll_len(this);
	Node* auxNode=NULL;
	if(this!=NULL && nodeIndex>-1 && len>nodeIndex)
	{
		auxNode = this->pFirstNode;
		for(i=0;i<nodeIndex;i++)
		{
			auxNode = auxNode->pNextNode;
		}
	}
	return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	Node* newNode;
	Node* prevNode;

    int returnAux = -1;

    if (this != NULL && nodeIndex > - 1)
    {
    	newNode = (Node*)malloc(sizeof(newNode));
    	if (newNode != NULL)
    	{
    		newNode->pElement = pElement;
    	if (nodeIndex == 0)
    	{
    		newNode->pNextNode = this->pFirstNode;
    		this->pFirstNode = newNode;
    	}
    	else
    	{
    		prevNode = getNode(this, nodeIndex-1);
    		newNode->pNextNode = prevNode->pNextNode;
    		prevNode->pNextNode = newNode;
    	}
    	this->size++;
    	returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len (this);

    if (this != NULL && len > -1)
    {
    	addNode (this,len,pElement);
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Retorna un puntero al elemento que se encuentra en el índice especificado.
 * Verificando que el puntero this sea distinto de NULL y que index sea positivo e
 * inferior al tamaño del array.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;
    int len = ll_len (this);

    if (this != NULL && index > -1 && index < len)
    {
    	pNode = getNode(this, index);
    	return pNode->pElement;
    }

    return returnAux;
}


/** \brief Inserta un elemento en el LinkedList, en el índice especificado.
 * Verificando que el puntero this sea distinto de NULL y que index sea positivo
 *  e inferior al tamaño del array.
 *  Si la verificación falla la función retorna (-1) y si tiene éxito (0).
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int len = ll_len (this);
    Node* pNode;

    if (this != NULL && index > -1 && len > -1 && index <= len )
    {
    	pNode = getNode(this, index);
    	if (pNode != NULL)
    	{
    		pNode->pElement = pElement;
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina un elemento del LinkedList, en el índice especificado. Verificando
 * que el puntero this sea distinto de NULL y que index sea positivo e inferior al tamaño del array
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len = ll_len (this);
    Node* pNode;
    Node* removeNode;
    Node* prevNode;

        if (this != NULL && index > -1 && len > -1 && index <= len )
        {
        	pNode = getNode(this, index);

        	if (pNode != NULL)
        	{
        		if ( len == 1)
        		{
        			//free(pNode->pElement);
        			free(pNode);
        			this->pFirstNode = NULL;
        			this->size= 0;
        			returnAux = 0;
        		}
        		else if (index == 0 && len>1)
        		{
        			removeNode = getNode(this, index);
        			this->pFirstNode = removeNode->pNextNode;
        			//free(pNode->pElement);
        			free(pNode);
        			this->size--;
        			returnAux = 0;
        		}
        		else
        		{
        			prevNode = getNode (this, index-1);
        			prevNode->pNextNode = pNode->pNextNode;
        			free(pNode);
        			this->size--;
        		}
        	}
        }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len = ll_len(this);

    if (this != NULL && len > -1)
    {
    	for (int i; i< len ; i++)
    	{
    		ll_remove(this,i);

    	}
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if (this != NULL)
    {
    	free(this);
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNode;

        if (this != NULL && len > -1)
        {
        	for (int i= 0; i< len ; i++)
        	{
        		pNode = getNode(this, i);

        		if (pNode != NULL && pNode->pElement == pElement)
        		{
        			returnAux = i;
        		}
        	}
        }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if (this != NULL)
    {
    	if (this->pFirstNode == NULL)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if (this != NULL && len > -1 && index > -1 && index <= len)
    {
    	addNode(this, index, pElement);
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;
	void* bufferElement = NULL;
    int len = ll_len (this);
    Node* pNode;
    Node* removeNode;
    Node* prevNode;


        if (this != NULL && index > -1 && len > -1 && index <= len )
        {
        	pNode = getNode(this, index);

        	if (pNode != NULL)
        	{
        		bufferElement = pNode->pElement;

        		if ( len == 1)
        		{
        			this->pFirstNode = NULL;
        			this->size= 0;
        			returnAux = bufferElement;
        			free(pNode);
        		}
        		else if (index == 0 && len>1)
        		{
        			removeNode = getNode(this, index);
        			this->pFirstNode = removeNode->pNextNode;
        			this->size--;
        			returnAux = bufferElement;
        			free(pNode);
        		}
        		else
        		{
        			prevNode = getNode (this, index-1);
        			prevNode->pNextNode = pNode->pNextNode;
        			this->size--;
        			returnAux = bufferElement;
        			free(pNode);
        		}
        	}
        }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	int len = ll_len(this);
	void* bufferElement = NULL;

	if ( this != NULL && len > -1)
	{
		returnAux = 0;
		for (int i= 0; i< len ; i++)
		{
			bufferElement = ll_get(this, i);
			if (bufferElement == pElement)
			{
				returnAux = 1;
				break;
			}
		}
	}
	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int lenList2;
    void* elementsList2 = NULL;

    if (this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	lenList2 = ll_len(this2);
    	if (lenList2 > -1)
    	{
    		for (int i = 0; i < lenList2 ; i++)
    		{
    			elementsList2 = ll_get(this2, i);
    			if (!ll_contains(this, elementsList2) )
    			{
    				returnAux = 0;
    				break;
    			}
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len = ll_len(this);
    void* thisElements= NULL;

    if(this!= NULL && from >= 0 && len > 0 && to <=len && from<= to)
    {
    	cloneArray = ll_newLinkedList();
    	for (int i = from; i <= to; i++)
    	{
    		thisElements = ll_get(this, i);
    		ll_add(cloneArray, thisElements);
    	}
    }

    return cloneArray;
}


/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
	LinkedList* cloneArray = NULL;

	    if(this!=NULL)
	    {
	        cloneArray=ll_subList(this,0,ll_len(this));
	    }
	    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
	int flagSwap;
	int i;
	int len = ll_len(this);
	int nuevoLimite;
	void* bufferElement;
	if(this != NULL && pFunc != NULL && len > 0 && (order == 1 || order == 0))
	{
		nuevoLimite = len - 1;
		do
		{
			flagSwap=0;
			for(i=0; i<len-1;i++)
			{
				if(order == 1 && (pFunc(ll_get(this, i),ll_get(this, i+1)) > 0))
				{
					flagSwap=1;
					bufferElement = ll_get(this, i);
					ll_set(this, i, ll_get(this, i+1));
					ll_set(this, i+1, bufferElement);
				}
				else if(order == 0 &&(pFunc(ll_get(this, i),ll_get(this, i+1)) < 0) )
				{
					flagSwap=1;
					bufferElement = ll_get(this, i);
					ll_set(this, i, ll_get(this, i+1));
					ll_set(this, i+1, bufferElement);
				}
			}
			nuevoLimite--;
		}
		while(flagSwap);
		returnAux = 0;
	}
    return returnAux;
}

int ll_map (LinkedList* this, int (*pFunc)(void*))
{
	int output = -1;
	int len = ll_len(this);
	void* pElemento;

	if (this!= NULL)
	{
		for (int i = 0; i < len ; i++)
		{
			pElemento = ll_get(this, i);
			pFunc (pElemento);
		}
		output = 0;
	}
return output;
}

int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux = -1;
	int len = ll_len(this);

	if (this != NULL && pFunc != NULL && len > 0)
	{
		for (int i= 0; i<= len; i++)
		{
			if(pFunc(ll_get(this, i)) == 1)
			{
				ll_remove(this, i);
			}
		}
	}
	return returnAux;
}

