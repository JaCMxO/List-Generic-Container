/**
 * Conternedor List
 * Company: ITESO
 * Engineer: Jaime Alberto Camacho Ortiz
 */ 
#include <stdlib.h>
#include "Type.h"
#include "List.h"

struct strNode{
	Type value;
	struct strNode *next;
	struct strNode *prior;
};
typedef struct strNode *Node;

struct strList{
	Node first;
	Node last;
	unsigned int size;
};

Node create_node(Type value){
	Node new = (Node)malloc(sizeof(struct strNode));
	new->next = NULL;
	new->prior = NULL;
	new->value = value;
	return new;
}

//Crear un ejemplar List con memoria dinámica y asigna NULL, NULL y 0 a sus elementos
List list_create(){
	List new = (List)malloc(sizeof(struct strList));
	new->first = NULL;
	new->last = NULL;
	new->size = 0;
	return new;
}

//Verificar si la lista está vacía
boolean list_isEmpty(List l){
	if(l){
		return (l->size) ? False:True;
	}
	return Error;
}

//Extrae el tamaño de la lista
unsigned int list_size(List l){
	if(list_isEmpty(l) != Error){
		return l->size;
	}
	return 0;
}

//Agrega un elemento al final de la lista e incrementa el tamaño en uno
void list_add(List l, Type value){
	if(list_isEmpty(l) != Error){
		Node new = create_node(value);
		if(list_isEmpty(l)){
			l->first = new;
		}else{
			//implementado por el profesor
			l->last->next = new;
			new->prior = l->last;
			
		}
		l->last = new;
		l->size++;
	}
}

//Devuelve el elemento en la posición index
Type list_get(List l, unsigned int index){
	if(list_isEmpty(l) != Error){
		// la lista si existe
		Node current = NULL;
		unsigned int i=0;
		if((index>=0) && (index<l->size)){
			//el valor de index es válido
			current = l->first;		//Colocamos el cursor al inicio de la lista
			while(i<index){
				current = current->next;
				i++;
			}
			//Ya llegamos a la posición que nos interesa
			return current->value;
		}
	}
	return NULL;
}

//Reemplaza el elemento en la posición index por el valor recibido
boolean list_set(List l, Type value,  unsigned int index){
	if(list_isEmpty(l) != Error){
		// la lista si existe
		Node current = NULL;
		unsigned int i=0;
		if((index>=0) && (index<l->size)){
			//el valor de index es válido
			current = l->first;		//Colocamos el cursor al inicio de la lista
			while(i<index){
				current = current->next;
				i++;
			}
			//Ya llegamos a la posición que nos interesa
			Type temp;
			temp = current->value;
			current->value = value;
			free(temp);
		}
	}
	return Error;
}

//Elimina y devuelve el elemento de la posición index y decrementa el tamaño en uno
Type list_remove(List l, unsigned int index){
	Node current = NULL;
	unsigned int i = 0;
	unsigned int s = l->size;
	if(list_isEmpty(l) != Error){
		//La lista existe
		if((index >= 0) && (index<s)){		//desplazarse hasta la posición deseada
			current = l->first;
			while(i<index){
				current = current->next;
				i++;
			}
		}
		if(l->last == l->first){		//si solo existe un elemento en la lista
			Type temp_value = NULL;
			temp_value = current->value;
			l->first = NULL;
			l->last = NULL;
			free(current);
			return temp_value;
		}else{
			if(index == 0){		//si se quiere eliminar el primer nodo
				Type temp_value = NULL;
				temp_value = current->value;
				l->first = current->next;
				l->first->prior = NULL;
				l->size--;
				free(current);
				return temp_value;
			}else{
				if(index == (s-1)){		//si se quiere eliminar el último nodo
					Type temp_value = NULL;
					temp_value = current->value;
					l->last = current->prior;
					l->last->next = NULL;
					l->size--;
					free(current);
					return temp_value;
				}else{//si se quiere eliminar un nodo que se encuentra a media lista
					Type temp_value = current->value;
					current->prior->next = current->next;
					current->next->prior = current->prior;
					l->size--;
					free(current);
					return temp_value;
				}
			}
		}
	}
	return NULL;
}

//Inserta un nuevo elemento en la posición index e incrementa el tamaño en uno
void list_insert(List l, Type value, unsigned int index){
	Node current = NULL;	//Crear un nodo para guardar temporalmente a el dato que se va a mover
	Node new = create_node(value);	//crear el nodo nuevo que se va a insertar
	if(list_isEmpty(l) != Error){		//verificar que la lista existe
		unsigned int i = 0;
		current = l->first;
		if((index >= 0) && (index < l->size)){//validar que el indice sea correcto
			//desplazarse hasta la posición indicada
			while(i < index){
				current = current->next;
				i++;
			}
		}
		if(list_isEmpty(l) == True){		//verificar si la lista está vacía
			list_add(l, value);
		}else{
			if(index == 0){
				//insertar el nuevo dato al inicio de la lista
				current->prior = new;
				new->next = current;
				l->first = new;
				l->size++;
			}else{
				new->prior = current->prior;
				current->prior->next = new;
				new->next = current;
				current->prior = new;
				l->size++;
			}
		}
	}
}

//Elimina todos los elemetos de la lista y a la lista
void list_destroy(List l){
	for(unsigned int i=0; i<l->size; i++){
		list_remove(l, i);
	}
	free(l);
}