#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <list>
using namespace std;

class Jugador;
//##################################################################################################################################
//# ENUMS ##########################################################################################################################
//##################################################################################################################################
enum Regla {rSuma, rIgual, rElemental};
enum Elemento{eNoElemental, eFuego, eAgua, eRayo, eTierra};
enum Colores{cError, cAcierto, cFuego, cAgua, cRayo, cTierra, cMarco};
enum Lados{lArriba, lAbajo, lIzquierda, lDerecha};

class Color{
    int const COLORES[7][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

    public:
        COLORREF getColor(Colores c){
            return RGB(COLORES[c][0],COLORES[c][1],COLORES[c][2]);
        }
};

class Punto{
    int x;
    int y;

    public:
        Punto(){
            x = 0;
            y = 0;
        }
        Punto(int x, int y){
            this->x = x;
            this->y = y;
        }

        int operator==(const Punto& p){
            return (p.x == this->x) && (p.y == this->y);
        }
        int operator!=(const Punto& p){
            return !(*this == p);
        }

        friend ostream &operator<<( ostream &output, const Punto &p )
        {
            output << "(" << p.x << ", " << p.y << ")";
            return output;
        }
};

class Lado{
    public:
        static const Punto* lados[4];
        Lado(){
        }

        const Punto* getLado(Lados lado){
            return lados[lado];
        }
};
const Punto* Lado::lados[4] = {new Punto(1,0),new Punto(-1,0),new Punto(0,-1),new Punto(0,1)};



//##################################################################################################################################
//# CLASS CARTA ####################################################################################################################
//##################################################################################################################################
class Carta{
    private:
        int top;
        int bottom;
        int right;
        int left;
        int identificadorJugador;
        Jugador* jugador;
    public:
        Carta(int top, int bottom, int right, int left, Jugador* jugador);
        int getTop();
        int getBottom();
        int getRight();
        int getLeft();
        Jugador* getJugador();
        void setJugador(Jugador* jugador);

        friend ostream &operator<<( ostream &output, const Carta &c );

};
class Mano{
    private:
        list<Carta> cartas;
        list<Carta> jugadas;
        Jugador* jugador;
    public:
        Mano(Jugador* jugador, int cantidadCartas);
        Carta getCarta(int pos);
        Carta getCartaJugada(int pos);
        void anadirCarta(Carta* carta);
        bool jugarCarta(unsigned int pos);
        friend ostream &operator<<( ostream &output, const Mano &m );
};
class Jugador{
    private:
        int identificador;
        Mano* mano;
    public:
        Jugador(int identificador, int numeroCartas);
        Mano* getMano();
        int getIdentificador();
        void anadirCarta(Carta* carta);
        Carta getCarta(int pos);
        bool jugarCarta(int pos);
        friend ostream &operator<<( ostream &output, const Jugador &j );
};


Carta::Carta(int top, int bottom, int right, int left, Jugador* jugador){
    this->top = top;
    this->bottom = bottom;
    this->right = right;
    this->left = left;
    this->jugador = jugador;
}

int Carta::getTop(){
    return top;
}

int Carta::getBottom(){
    return bottom;
}

int Carta::getRight(){
    return right;
}

int Carta::getLeft(){
    return left;
}

Jugador* Carta::getJugador(){
    return jugador;
}

void Carta::setJugador(Jugador* jugador){
    this->jugador = jugador;
}

ostream &operator<<( ostream &output, const Carta &c )
{
    output << "(T: " << c.top << ", B: " << c.bottom << ", R: " << c.right << ", L: " << c.left << ", J: ";
    if(c.jugador != nullptr){
         output << c.jugador->getIdentificador();
    }else{
        output << 0;
    }
    output << ")";
    return output;
}


//##################################################################################################################################
//# CLASS MANO #####################################################################################################################
//##################################################################################################################################


Mano::Mano(Jugador* jugador, int cantidadCartas){
    this->jugador = jugador;

    //Insertamos cartas aleatorias en la mano
    for(int i = 0; i < cantidadCartas; i++){
        cartas.push_back(Carta(rand()%(9) + 1,rand()%(9) + 1,rand()%(9) + 1,rand()%(9) + 1,jugador));
    }
}

void Mano::anadirCarta(Carta* carta){
    this->cartas.push_back(*carta);
}


Carta Mano::getCarta(int pos){
    list<Carta> l = cartas; // look, no pointers!
    auto puntero = l.begin();

    std::advance(puntero, pos);

    return *puntero;
}

Carta Mano::getCartaJugada(int pos){
    list<Carta> l = jugadas; // look, no pointers!
    auto puntero = l.begin();

    std::advance(puntero, pos);

    return *puntero;
}

bool Mano::jugarCarta(unsigned int pos){
    if(pos >= cartas.size()){
        return false;
    }
    this->jugadas.push_back(getCarta(pos));
    auto puntero = cartas.begin();
    std::advance(puntero,pos);
    this->cartas.erase(puntero);
    return true;
}

ostream &operator<<( ostream &output, const Mano &m )
{
    output << "\tEn Mano:" << endl;
    list<Carta> puntero = m.cartas;
    list<Carta>::iterator it = puntero.begin();
    for(unsigned int i = 0; i < m.cartas.size();i++){
        output << "\t\t" << (*it) << endl;
        std::advance(it,1);

    }
    output << "\n\tJugadas: " << endl;

    puntero = m.jugadas;
    it = puntero.begin();
    for(unsigned int i = 0; i < m.jugadas.size();i++){
        output << "\t\t" << (*it) << endl;
        std::advance(it,1);

    }

    return output;
}

//##################################################################################################################################
//# CLASS JUGADOR ##################################################################################################################
//##################################################################################################################################


Jugador::Jugador(int identificador, int numeroCartas){
    this->identificador = identificador;
    this->mano = new Mano(this, numeroCartas);
}
Mano* Jugador::getMano(){
    return this->mano;
}

int Jugador::getIdentificador(){
    return identificador;
}

void Jugador::anadirCarta(Carta* carta)
{
    this->mano->anadirCarta(carta);
}

Carta Jugador::getCarta(int pos){
    return this->mano->getCarta(pos);
}
bool Jugador::jugarCarta(int pos){
    return this->mano->jugarCarta(pos);
}

ostream &operator<<( ostream &output, const Jugador &j ){
    output << "Jugador " << j.identificador << endl << *j.mano;
    return output;
}


//##################################################################################################################################
//# CLASS TABLERO ##################################################################################################################
//##################################################################################################################################
class Tablero{
    Carta* celdas[36];
    int tamanoTablero;
    public:
        Tablero(int tamTablero){
            for(int i = 0; i < tamTablero; i++){
                for(int j = 0; j < tamTablero; j++){
                    celdas[i * tamTablero + j] = new Carta(0,0,0,0,nullptr);
                }
            }
            this->tamanoTablero = tamTablero;
        }

        int getTamano(){
            return tamanoTablero;
        }

        bool libre(int fila, int col){
			return celdas[fila*tamanoTablero + col]->getJugador() == nullptr;
        }

        bool volteable(Carta* cartaAtacante, int fila, int col)
        {
            return !libre(fila,col) && (cartaAtacante->getJugador() != celdas[fila*tamanoTablero + col]->getJugador());
        }


        bool posicionValida(int fila, int col){
            return ((fila < tamanoTablero) && (fila >= 0) && (col < tamanoTablero) && (col >= 0));
        }

        bool setCarta(Jugador* jugador, int posCarta, int fila, int col){
            if(libre(fila,col)){
                Carta carta = jugador->getCarta(posCarta);
                if(jugador->jugarCarta(posCarta)){
                    *celdas[fila*tamanoTablero+col] = carta;
                    return true;
                }
            }
            return false;
        }

        Carta* getCarta(int fila, int col){
            if(posicionValida(fila,col)){
                return celdas[fila*tamanoTablero + col];
            }
            return nullptr;
        }
        void voltear(Carta* carta, int fila, int col, bool cadena){
            if(posicionValida(fila,col) and volteable(carta, fila, col)){
                celdas[fila*tamanoTablero + col]->setJugador(carta->getJugador());
                if(cadena){
                    voltear(carta, fila,col,cadena);
                    voltear(carta, fila-1,col,cadena);
                    voltear(carta, fila,col+1,cadena);
                    voltear(carta, fila,col-1,cadena);
                }
            }
        }

        void atacar(Carta* cartaAtacante, Lados ladoOrigenAtacante, int fila, int col){
            if(posicionValida(fila,col)){
                Carta* cartaAtacada = celdas[fila*tamanoTablero + col];
                int ataque;
                int defensa;
                if(volteable(cartaAtacante,fila,col)){
                    if(ladoOrigenAtacante == Lados::lArriba){
                        ataque = cartaAtacante->getBottom();
                        defensa = cartaAtacada->getTop();
                    }else if(ladoOrigenAtacante == Lados::lAbajo){
                        ataque = cartaAtacante->getTop();
                        defensa = cartaAtacada->getBottom();
                    }else if(ladoOrigenAtacante == Lados::lIzquierda){
                        ataque = cartaAtacante->getRight();
                        defensa = cartaAtacada->getLeft();
                    }else if(ladoOrigenAtacante == Lados::lDerecha){
                        ataque = cartaAtacante->getLeft();
                        defensa = cartaAtacada->getRight();
                    }else{
                        cout << "ERROR FATALISIMO, EN EL FLIP ENVIAS UN LADO QUE NO EXISTE JEJE ANORMAL" << endl;
                    }
                    if(ataque > defensa){
                        voltear(cartaAtacante,fila,col,0);
                    }
                }
            }
        }

        friend ostream &operator<<( ostream &output, const Tablero &t )
        {
            output << "\t";
            for(int i = 0; i < t.tamanoTablero; i++)
            {
                output << i << "\t\t\t\t";
            }

            output << endl;

            for(int i = 0; i < t.tamanoTablero; i++)
            {
                output << i << "\t";

                for(int j = 0; j < t.tamanoTablero; j++){
                    output << *(t.celdas[i*t.tamanoTablero + j]) << ",\t";
                }
                output << endl;
            }
            return output;
        }
};


//##################################################################################################################################
//# CLASS JUEGO ####################################################################################################################
//##################################################################################################################################

class Juego{
	//#turno <- turno del jugador que viene ahora
	//#turnos <- numero de turnos hasta el momento
    int tamanoTablero;
    int numJugadores;
    Jugador* jugadores[10];
    Tablero* tablero;
    int turnos;
    int turno;

    public:
        Juego(int numJugadores, int tamanoTablero){
            int numCartas = tamanoTablero*tamanoTablero / numJugadores;
            if(numCartas*numJugadores < (tamanoTablero*tamanoTablero)){
                numCartas += 1;
            }
            for(int i = 0; i < numJugadores; i++){
                jugadores[i] = new Jugador(i+1, numCartas);
            }
            this->tamanoTablero = tamanoTablero;
            this->numJugadores = numJugadores;
            this->tablero = new Tablero(tamanoTablero);
            this->turnos = 0;
            this->turno = 0;


        }
        int getTurno(){
            return this->turno;
        }

        bool iteracion(int posCarta, int fila, int col){
            Carta* cartaAtacante;
            bool posicionValida = tablero->posicionValida(fila, col);

            if(posicionValida){
                if(this->tablero->setCarta(jugadores[turno], posCarta, fila,col)){
                    cartaAtacante = tablero->getCarta(fila, col);
                    tablero->atacar(cartaAtacante, Lados::lArriba, fila+1, col);
                    tablero->atacar(cartaAtacante, Lados::lAbajo, fila-1, col);
                    tablero->atacar(cartaAtacante, Lados::lIzquierda, fila, col+1);
                    tablero->atacar(cartaAtacante, Lados::lDerecha, fila, col-1);
                    turno += 1;
                    turnos += 1;
                    if(turno >= numJugadores){
                        turno = 0;
                    }
                    return true;
                }
            }
            return false;
        }


        bool finalizado(){
            return turnos == (tamanoTablero*tamanoTablero);
        }

        int getGanador(){
            int ganador[numJugadores];
            int ret;
            int sol;
            for(int i = 0; i < numJugadores; i++)
            {
                ganador[i] = 0;
            }
            for(int fila = 0; fila < tamanoTablero; fila++)
            {
                for(int col = 0; col < tamanoTablero; col++)
                {
                    ganador[tablero->getCarta(fila,col)->getJugador()->getIdentificador() - 1]++;
                }
            }
            sol = 0;
            ret = ganador[0];
            for(int i = 1; i < numJugadores; i++)
            {
                if(ret < ganador[i])
                {
                    ret = ganador[i];
                    sol = i;
                }
            }
            return sol+1;
        }

        friend ostream &operator<<( ostream &output, const Juego &j)
        {
            output << endl << endl <<"********************************** Turno " << j.turnos << " **********************************" << endl;
            for(int i = 0; i < j.numJugadores; i++)
            {
                output << *j.jugadores[i] << endl;
            }
            output << *j.tablero << endl;
            output << "Turno del jugador " << j.turno+1 << endl;
            return output;
        }
};
//##################################################################################################################################
//# AUXILIAR FUNCTIONS AND METHODS #################################################################################################
//##################################################################################################################################

Carta randomCarta(Jugador* jugador, int minimo,int maximo){
	return Carta(rand()%maximo+minimo,rand()%maximo+minimo,rand()%maximo+minimo,rand()%maximo+minimo,jugador);
}

//##################################################################################################################################
//# MAIN ###########################################################################################################################
//##################################################################################################################################
int tripleTriad(){
    int numJug;
    int tamTablero;
    int numCarta;
    int fila, col;
    cout << "Introduce el numero de jugadores (max. 6, min. 2)" << endl;
    cin >> numJug;
    cin.clear();
    fflush(stdin);

    while((numJug > 6) || (numJug < 2)){
        cout << "Introduce el numero de jugadores (max. 6, min. 2)" << endl;
        cin >> numJug;
        cin.clear();
        fflush(stdin);
    }

    cout << "Introduce el ancho del tablero (max. 5, min. 3)" << endl;
    cin >> tamTablero;
    cin.clear();
    fflush(stdin);


    while((tamTablero > 5) || (tamTablero < 3)){
        cout << "Introduce el ancho del tablero (max. 5, min. 3)" << endl;
        cin >> tamTablero;
        cin.clear();
        fflush(stdin);
    }


    Juego juego = Juego(int(numJug),int(tamTablero));

    while(juego.finalizado() == false){
        cout << juego << endl;
        cout << "Introduzca la carta que va a utilizar" << endl;
        cin >> numCarta;
        cin.clear();
        fflush(stdin);


        cout << "Introduzca la posicion, fila y columna separadas por enter" << endl;
        cin >> fila;
        cin.clear();
        fflush(stdin);
        cin >> col;
        cin.clear();
        fflush(stdin);

        juego.iteracion(numCarta, fila, col);
    }
    cout << endl << endl << juego << endl << endl;
    cout << endl << endl << "JUEGO FINALIZADO" << endl << endl;
    if(juego.getGanador() != 0){
        cout << endl << endl << "HA GANADO EL JUGADOR " << juego.getGanador() << endl << endl;
    }else{
        cout << endl << endl << "EMPATE" << endl << endl;
    }

    return 0;
}
