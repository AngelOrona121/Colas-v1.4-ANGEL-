/*
 *  +=============== Presentación ===============+
 *
 *  Enunciado del problema:
 *  Una Cola (Queue) es una estructura de datos en donde el primero en entrar
 *  es el primero en salir. Para nuestro caso, haremos el problema un poco
 *  mas complejo añadiéndole lo que se conoce como prioridad. En los casos en que
 *  una Cola tiene prioridad se considera esta al momento de insertar un nuevo
 *  nodo a la estructura. La Cola tiene la siguiente forma para los nodos:
 *
 *  struct Queue {
 *    int dato;
 *    Queue *next;
 *  };
 *
 *  Autores (ID - Nombre):
 *  1115395 - Diego Ramirez
 *  1113891 - Alan Arturo Sosa Del Villar
 *  1115419 - Tomás Alberto Méndez Rosario
 *  1114790 - Gabriel Antonio Alba Natera
 *  1114042 - Jean Carlo Ramirez Cabrera
 *  1113744 - José Otniel Paulino Frías
 *  1114290 - Angel Antonio Orona Pimentel
 *  1115915 - Melvin Brahim Molina Contreras
 *
 *  Fecha en la que se desarrollo el programa (dd/mm/aa):
 *  18/08/2023
 */

 /* Implementación de librerías */
#include <iostream>
#include <string>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

/* Estructura de dato para simular el nodo de una Cola (Queue) */
struct Queue
{
    int dato;    // Almacena un valor entero.
    int priori;
    Queue* next; // Puntero a otro objeto Queue, permite enlazar objetos Queue en una lista.
};

/* Funciones complementarias */
/// @brief Imprime en consola un mensaje con estilo.
/// @note El mensaje se imprimirá sin saltos de lineas, a menos que se le especifique en el string pasado por parámetro.
/// @param msg Mensaje que se imprimirá en consola.
/// @param styleCode El código de estilo a aplicar al mensaje.
void imprimirConEstilo(string msg, int styleCode)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Cambiar el color del texto
    SetConsoleTextAttribute(hConsole, styleCode);
#endif

    cout << msg; // Imprimir mensaje

    // Restaurar el color original del texto
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
}

/// @brief Verificar si un número es un dígito o no.
/// @param d La entrada a verificar.
/// @return true si el número es un dígito, false si no lo es.
bool esDigito(string d)
{
    // Si hay mas de 2 caracteres en d deja de ser un dígito
    if (d.length() > 1)
        return false;

    // Se recorre el string para verificar si todos sus caracteres son dígitos
    for (char c : d)
        if (!isdigit(c))
            return false;

    return true;
}

/// @brief Verificar si un número es un entero o no.
/// @param num La entrada a verificar.
/// @return true si el número es un entero, false si no lo es.
bool esEntero(string num)
{
    // Se verifica el tamaño del numero para saber si no sobrepasa el rango de un int
    if (num.length() > 11)
        return false;

    // Se recorre el string para verificar si todos sus caracteres son dígitos y si tiene un '-' al inicio lo ignora
    for (int i = 0; i < num.length(); i++)
    {
        if (i == 0 && num[i] == '-')
            continue;

        if (!isdigit(num[i]))
            return false;
    }

    return true;
}

void imprimirQueue(Queue*& first) //Metodo para imprimir el estado de la cola, empezando desde el primero hasta el ultimo.
{
    Queue* Temp = first;
    int conteo = 1;
    while (Temp != NULL) //Mientras el puntero que recorre la cola sea distinto de nulo. 
    {

        //Se muestra cada informacion respecto a su posicion.

        cout << "\n\t" << conteo << ". Dato alojado:" << Temp->dato << endl;

        if (Temp->next != NULL) //Aqui para que el puntero que recorre avance en uno en uno.
        {
            Temp = Temp->next;
            conteo++;
        }
        else
        { //En el momento en que ya no sea distinto de NULL, se acaba. 
            break;
        }
    }
}

/// @brief Simula la operación enqueue en una cola.
/// @param first Referencia del primer nodo de la cola.
/// @param last  Referencia del ultimo nodo de la cola.
/// @param valor Valor a ingresar como un nodo en la cola.
/// @param prioridad Prioridad del valor que se ingresara a la cola.
void enqueue(Queue*& first, Queue*& last, int valor, int prioridad)
{
    Queue* nuevo_nodo = new Queue(); // Crear un nuevo nodo para el elemento a encolar.
    nuevo_nodo->dato = valor;        // Asignar el valor al miembro "dato" del nuevo nodo.
    nuevo_nodo->priori = prioridad;   // Asignar la prioridad al miembro "priori" del nuevo nodo.
    nuevo_nodo->next = NULL;       // Inicializar el puntero "next" del nuevo nodo.

    if (first == NULL)
    {                     // Si la cola está vacía...
        first = nuevo_nodo; // El nuevo nodo se convierte en el primero.
        last = nuevo_nodo;  // El nuevo nodo también es el último ya que es el único.
    }
    else
    { // Si ya hay elementos en la cola...
        if (prioridad < first->priori || prioridad == 0)
        {
            // Si la prioridad del nuevo nodo es menor que la prioridad del primer nodo actual...
            nuevo_nodo->next = first; // El siguiente nodo del nuevo nodo apunta al primer nodo actual.
            first = nuevo_nodo;       // El nuevo nodo se convierte en el primer nodo.
        }
        else
        {
            Queue* temp = first; // Nodo temporal para recorrer la cola.
            while (temp->next != NULL && temp->next->priori <= prioridad-1)

#pragma region MyRegion
                /*
               temp->next != NULL:

               Esto verifica si el nodo temporal (temp) no ha llegado al final de la cola.
               Si temp->next es NULL, significa que no hay más nodos después y, por lo tanto, hemos llegado al final de la cola.

               temp->next->priori <= prioridad-1:

               Esto verifica si la prioridad del siguiente nodo
               (temp->next->priori) es menor o igual a prioridad-1. Aquí, prioridad-1 se usa
               para asegurarse de que el nuevo nodo se inserte antes de los nodos con la misma prioridad.
               Restar 1 a prioridad permite que el nuevo nodo con la misma prioridad se
               inserte delante de los nodos existentes con esa prioridad.
               */

#pragma endregion

            {
                temp = temp->next; // Avanzar al siguiente nodo mientras la prioridad sea menor o igual.
            }

            nuevo_nodo->next = temp->next; // El siguiente nodo del nuevo nodo apunta al siguiente nodo del nodo temporal.
            temp->next = nuevo_nodo;       // El siguiente nodo del nodo temporal apunta al nuevo nodo.

            if (temp == last)  // Si se inserta al final, actualizamos "last".
            {
                last = nuevo_nodo;
            }
        }
    }


    imprimirConEstilo("\n=> Operación enqueue realizada: ", FOREGROUND_BLUE);
    cout << "se ha agregado el número " << valor << " a la cola..." << endl;
}

/// @brief Simula la operación dequeue en una cola.
/// @param first Referencia del primer elemento de la cola.
/// @param last Referencia del ultimo elemento de la cola.
int dequeue(Queue*& first, Queue*& last)
{
    Queue* temp = first; // Se crea un nodo temporal
    int d = temp->dato;  // Se guarda el valor del nodo temporal

    // Si la cola solo tiene un elemento...
    if (first == last)
    {
        first = NULL;
        last = NULL;
    }
    else // Si hay más de un elemento en la cola...
    {
        first = first->next; // Asigna el siguiente nodo como el primer elemento en la cola
    }

    delete temp; // Libera la memoria del nodo eliminado

    imprimirConEstilo("\n=> Operación dequeue realizada: ", FOREGROUND_BLUE);
    cout << "se ha eliminado el número " << d << " de la cola..." << endl;

    return d;
}

int main()
{
    Queue* first = NULL;                      // Puntero al principio de la cola.
    Queue* last = NULL;                       // Puntero al final de la cola.
    int valor, prioridad;                     // Opción almacena la opción del usuario, valor almacena el valor a agregar a la cola.
    string entrada, opcion, cadena_prioridad; // Entrada almacena la entrada del usuario como una cadena de texto.

    // Imprimir el titulo del programa utilizando un Raw String
    imprimirConEstilo(
        R"(
+==================================================+
|                                                  |
|                 Colas (Queues)                   |
|                                                  |
+==================================================+
  )",
        FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    while (true)
    {
        // Menu del programa
        imprimirConEstilo("\n\nA continuación, elija una de las siguientes opciones:\n", FOREGROUND_GREEN);
        cout << "\t1. Realizar Enqueue (agregar un elemento a la cola)" << endl;
        cout << "\t2. Realizar Dequeue (sacar un elemento de la cola)" << endl;
        cout << "\t3. Desplegar (realizar multiples dequeues hasta vaciar la cola)" << endl;
        cout << "\t4. Imprimir (Mostrar el estado actual de la cola)" << endl;

        imprimirConEstilo("\tPresione cualquier otro dígito para terminar el programa...\n\n", FOREGROUND_RED | FOREGROUND_INTENSITY);

        // Recibir y validar la opción elegida del usuario
        imprimirConEstilo("-> ", FOREGROUND_BLUE);
        cin >> opcion;

        while (!esDigito(opcion))
        {
            imprimirConEstilo("\n¡Opción invalida! Debe ingresar un algún dígito, intente de nuevo: ", FOREGROUND_RED);
            cin >> opcion;
        }

        // Transformar la opción en un entero y en base a esta tomar una decisión
        switch (stoi(opcion))
        {
        case 1:
            while (true)
            {
                try
                {
                    imprimirConEstilo("\n\nEscriba el elemento que quiere agregar a la cola: ", FOREGROUND_GREEN);
                    cin >> entrada;

                    imprimirConEstilo("\nEscriba la prioridad del elemento: ", FOREGROUND_GREEN);
                    cin >> cadena_prioridad;

                    if (esEntero(entrada) && esEntero(cadena_prioridad) && stoi(cadena_prioridad) >= 0)
                    {
                        valor = stoi(entrada);
                        prioridad = stoi(cadena_prioridad);
                        enqueue(first, last, valor, prioridad);

                        break;
                    }
                    else
                    {
                        imprimirConEstilo("\n¡Entrada invalida! Debes ingresar un número entero valido dentro del rango.\n", FOREGROUND_RED | FOREGROUND_INTENSITY);
                    }
                }
                catch (const out_of_range&)
                {
                    imprimirConEstilo("\n¡Número fuera del rango válido para int!\n", FOREGROUND_RED | FOREGROUND_INTENSITY);
                }
            }
            break;

        case 2:
            if (first != NULL) // Si la cola no esta vacía se saca el ultimo valor que entro
            {
                dequeue(first, last);
            }
            else
            {
                imprimirConEstilo("\n(Empty Queue)", FOREGROUND_BLUE);
                cout << " la cola esta vacía..." << endl;
            }
            break;

        case 3: // Mientras la cola no este vacía se van sacando los nodos hasta llegar a NULL
            while (first != NULL)
            {
                dequeue(first, last);
            }

            imprimirConEstilo("\n(Empty Queue)", FOREGROUND_BLUE);
            cout << " la cola ha sido vaciada..." << endl;
            break;

        case 4:
            imprimirConEstilo("\nEstado de la Cola:\n", FOREGROUND_BLUE);
            imprimirQueue(first);
            break;
        default:
            imprimirConEstilo("\n\nSaliendo del programa...", FOREGROUND_BLUE);
            return 0;
        }
    }

    return 0;
}