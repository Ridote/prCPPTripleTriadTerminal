// overloading class constructors
#include <iostream>
#include <string>
using namespace std;


class punto{
    int x;
    int y;

public:
    punto(){
        x = 0;
        y = 0;
    }
    punto(int x, int y){
        this->x = x;
        this->y = y;
    }

    int operator==(const punto& p){
        return (p.x == this->x) && (p.y == this->y);
    }
    int operator!=(const punto& p){
        return !(*this == p);
    }

    friend ostream &operator<<( ostream &output, const punto &p )
    {
        output << "(" << p.x << ", " << p.y << ")";
        return output;
    }

};

template <class T>
class lista{

    T* elem;
    lista* siguiente;
    lista* anterior;

    public:
        lista(){
            elem = nullptr;
            siguiente = nullptr;
            anterior = nullptr;
        }

        lista(lista* anteriorp, T* elemento){
            this->anterior = anteriorp;
            siguiente = nullptr;
            this -> elem = new T;
            *(this->elem) = *elemento;
        }

        void anadir(T* elemento){
            if(this->elem != nullptr){
                lista* ultimo = this;
                while(ultimo -> siguiente != nullptr){
                    ultimo = ultimo->siguiente;
                }
                ultimo->siguiente = new lista(ultimo, elemento);
            }else{
                this->elem = new T;
                *(this->elem) = *elemento;
            }
        }

        T get(int pos){
            lista* iterador = this;
            int i = 0;
            while(i < pos && iterador->siguiente != nullptr){
                iterador = iterador -> siguiente;
                i++;
            }
            if(i == pos){
                return *(iterador -> elem);
            }
        }

        void eliminar(int pos){
            int i = 0;
            lista* elemento = this;
            while(i < pos && elemento->siguiente != nullptr){
                elemento = elemento->siguiente;
                i++;
            }
            if(elemento != nullptr){
                if(elemento->anterior != nullptr){
                    if(elemento->siguiente != nullptr){
                        elemento->anterior->siguiente = elemento->siguiente;
                        elemento->siguiente->anterior = elemento->anterior;
                        delete elemento->elem;
                        delete elemento;
                    }else{
                        elemento->anterior->siguiente = nullptr;
                        delete elemento->elem;
                        delete elemento;
                    }
                }else{
                    if(this->siguiente != nullptr){
                        *this->elem = *this->siguiente->elem;
                        lista* sigAux = this->siguiente;
                        this->siguiente = this->siguiente->siguiente;
                        delete sigAux->elem;
                        delete sigAux;
                    }else{
                        delete this->elem;
                        this->elem = nullptr;
                        this->siguiente = nullptr;
                    }
                }
            }
        }

        int buscar(T* elemento){
            lista* aux = this;
            int i = 0;

            if(this->elem != nullptr){
                while(aux!=nullptr && *aux->elem != *elemento){
                    i++;
                    aux = aux -> siguiente;
                }
                if(aux!=nullptr && *aux->elem == *elemento){
                    return i;
                }
            }

            return -1;
        }

        void recorrer(){
            lista* puntero = this;
            while(puntero != nullptr){
                cout << *(puntero->elem) << endl;
                puntero = puntero->siguiente;
            }
        }



};

template <class T>
class conjunto {
    lista<T>* aLista;

    public:

        conjunto(){
            aLista = new lista<T>;
        }
        int anadir(T* elemento){

            if(aLista->buscar(elemento) == -1){
                aLista->anadir(elemento);
                return 1;
            }
            return 0;
        }

        int eliminar(T* elemento){
            int pos = aLista->buscar(elemento);
            if(pos == -1)
            {
                return -1;
            }
            aLista->eliminar(pos);
            return 1;
        }

        int contiene(T* elemento){
            return aLista->buscar(elemento) != -1;
        }

        void recorrer(){
            aLista->recorrer();
        }
};

void pruebaLista(){
    lista<int> mylista;
    int s = 0;
    mylista.anadir(&s);
    s = 1;
    mylista.anadir(&s);
    s = 2;
    mylista.anadir(&s);
    s = 3;
    mylista.anadir(&s);
    s = 4;
    mylista.anadir(&s);
    mylista.recorrer();


    cout << endl << "El elemento " << s << " esta en la posicion " << mylista.buscar(&s) << endl;

    cout << "\n\nBorremos ahora algun elemento, por ejemplo el 0, el 4 y el 2" << endl;
    mylista.eliminar(4);
    mylista.eliminar(2);
    mylista.eliminar(0);

    mylista.recorrer();
}


