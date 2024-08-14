#include <iostream>
#include <cstring>
#include <conio.h>

using namespace std;

struct Usuario{
    char name[50];
    char username[50];
    int dni;
    char loginCode[50];
    int balance;
};

struct Transaccion{
    char name[50];
    int id;
    int monto;
    bool ingreso;
    int fecha; //ddmmaaaa
};

int menu();
void listarCantidadIngresoEgreso(char t[50]);
void seleccionarUsuario(char t[50]);
bool validarCliente(char username[50]);
void listarTransacciones(char t[50]);

int main(){
    int opcion;
    //Transaccion t = {"",0, 0, true, 0};
    char t[50];

    do{
        opcion = menu();

        switch(opcion){
            case 1:
                seleccionarUsuario(t);
                listarTransacciones(t);
                break;
            case 2:
                seleccionarUsuario(t);
                listarCantidadIngresoEgreso(t);
                break;
            default:
                cout<<"Valor incorrecto";
                break;
        }
    }while(opcion!=5);

    return 0;
}

void listarCantidadIngresoEgreso(char t[50]){
        Transaccion idValidation;

        const char* nombreArchivo = "transacciones.dat";
    
        FILE * archivo = fopen(nombreArchivo, "rb");
        if (archivo == NULL) {
            cout<<"Error al abrir el archivo"<< endl;
            fclose(archivo);
        }
        else{
            fseek(archivo, 0, SEEK_SET);
            while(fread(&idValidation, sizeof(Transaccion), 1, archivo) == 1){
                if(strcasecmp(idValidation.name, t) == 0){
                    cout<<endl <<" El id de la transacción es: "<< idValidation.id<< endl;
                    if(idValidation.ingreso){
                        cout<<" El monto ingresado fue de: "<< idValidation.monto<< endl;
                    }
                    else{
                        cout<<" El monto extraido fue de: "<< idValidation.monto<< endl;
                    }
                    cout<<" La fecha en que se realizo la transaccion: "<< idValidation.fecha<< endl;
                }
            }
            fclose(archivo);
        }
        cout<<endl<<endl;
    }

void seleccionarUsuario(char t[50]){
    int flag = 0;
    do{
        if (flag == 1){
            cout<<"El usuario no existe."<< endl;
        }
        cout << "Ingrese el Usuario: ";
        cin>>t;
        cout<<endl; 

        flag = 1; 
    }while(!validarCliente(t));
}
void listarTransacciones(char t[50]){ // Terminar función preguntar al profe dudas.
        Transaccion idValidation;
        Transaccion listado[5];
        int contador = 0;
        int flag = 0;

        const char* nombreArchivo = "transacciones.dat";
    
        FILE * archivo = fopen(nombreArchivo, "rb");
        if (archivo == NULL) {
            cout<<"Error al abrir el archivo"<< endl;
            fclose(archivo);
        }
        else{
            fseek(archivo, 0, SEEK_SET);
            while(fread(&idValidation, sizeof(Transaccion), 1, archivo) == 1){
               /*  cout<<endl<<"El username es: "<< idValidation.name<< endl;
                cout<<endl <<" El id de la transacción es: "<< idValidation.id<< endl;
                if(idValidation.ingreso){
                    cout<<" El monto ingresado fue de: "<< idValidation.monto<< endl;
                }
                else{
                    cout<<" El monto extraido fue de: "<< idValidation.monto<< endl;
                }
                cout<<" La fecha en que se realizo la transaccion: "<< idValidation.fecha<< endl;  */
                if(strcasecmp(idValidation.name, t) == 0){

                    if(contador < 5){
                        listado[contador] = idValidation;
                        contador++;
                    }
                    else{
                        contador = 0;
                        listado[contador] = idValidation;
                        flag = 1;
                    }

                    if(flag == 1){
                        flag = 0;
                        for(int i = 0; i<5 ; i++){
                            cout<<listado[i].id<<endl;
                        }
                    }
                
                    
                }
            }
            fclose(archivo);
        }
        cout<<"Presione cualquier letra para volver al menu.";
        cout<<endl<<endl;
    }

bool validarCliente(char username[50]) {
    bool ingresoValido = false;
    Usuario user;
    FILE* archivo = fopen("archivo.dat", "rb");
    if (archivo != NULL) {
        while (fread(&user, sizeof(Usuario), 1, archivo) == 1) {
            if (strcasecmp(user.username, username) == 0) {
                ingresoValido = true;
                break;
            }
        }
        fclose(archivo);
    }
    return ingresoValido;
}

int menu(){
    int opcion = 0;
    cout<<"     1. Listar transacciones de un cliente por fecha(De a 5)"<< endl;
    cout<<"     2. Listar la cantidad de ingresos y egresos por mes de un cliente"<< endl;
    cout<<"     3. Listar transacciones"<<endl;
    cout<<"     4. Eliminar transaccion"<<endl;
    cout<<"     5. Salir"<<endl;
    cout << "Seleccione una opción: ";
    cin>>opcion;

    return opcion;
}