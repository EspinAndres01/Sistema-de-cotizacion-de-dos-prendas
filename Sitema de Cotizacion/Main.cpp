#include <iostream>
#include <string>
#include <vector>
#include "Constructor.h"
#include <chrono>
#include <ctime>
#include <tuple>


using namespace std;


void menuCuello(){
    
    cout << "PASO 2.b: La camisa a cotizar, ¿Es Cuello Mao?" << endl;
    cout << "1) Si" << endl;
    cout << "2) No" << endl;
    cout <<"********************************************"<< endl;
    cout << "Presiona 3 para regresar al menu principal"<< endl;
    cout <<"********************************************"<< endl;
}

void menuManga(){
    
    cout << "PASO 2.a: La camisa a cotizar, ¿Es Manga corta?" << endl;
    cout << "1) Si" << endl;
    cout << "2) No" << endl;
    cout <<"********************************************"<< endl;
    cout << "Presiona 3 para regresar al menu principal"<< endl;
    cout <<"********************************************"<< endl;

}

void menuPrenda(){
    
    cout << "Seleccione una prenda:" << endl;
    cout << "1) Camisa" << endl;
    cout << "2) Pantalon" << endl;
    cout <<"********************************************"<< endl;
    cout << "Presiona 3 para regresar al menu principal"<< endl;
    cout <<"********************************************"<< endl;
}

void menuCalidad(){
    system("cls");
    cout << "Seleccione la calidad de la prenda" << endl;
    cout << "1) Standard" << endl;
    cout << "2) Premium" << endl;
    cout <<"********************************************"<< endl;
    cout << "Presiona 3 para regresar al menu principal"<< endl;
    cout <<"********************************************"<< endl;
}

string fechaActual(){
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    string fecha = ctime(&now_c);
    return fecha;
}

TiendayVendedor crearTiendayVendedor(){
    // Crear objeto Tienda y vendedor
    Tienda tienda("TIENDA CAMISA Y PANTALONES", "Calle Ejemplo 123");
    Vendedor vendedor("Juan"," Perez",12345);
    return {tienda,vendedor};
}

void menuGeneral(Tienda tienda,Vendedor vendedor){
    
    system("cls");
    // Mostrar información general
    cout << "----------------------------------" << endl;
    cout << "COTIZADOR EXPRESS - MENU PRINCIPAL" << endl;
    cout << "----------------------------------" << endl;
    
    cout << tienda.get_nombre() << " | " << tienda.get_direccion() << endl;
    cout << "VENDEDOR: " + vendedor.get_nombre() << " " << vendedor.get_apellido() << " | " << "ID: " + to_string(vendedor.get_codigo()) << endl;
    cout << "----------------------------------" << endl;
    cout << "*************** MENU ************" << endl;
    cout << "SELECCIONE UNA OPCION:" << endl;
    cout << "1) Historial de Cotizaciones" << endl;
    cout << "2) Realizar Cotizacion" << endl;
    cout << "3) Salir" << endl;
    

}

void menuPantalon(){
    cout << "El pantalon a cotizar, ¿Es chupin?:" << endl;
    cout << "1) Si" << endl;
    cout << "2) No" << endl;
    cout <<"********************************************"<< endl;
    cout << "Presiona 3 para regresar al menu principal"<< endl;
    cout <<"********************************************"<< endl;
}



int solicitarCantidadCotizar(const Stock& stock, TipoPrenda tipo_prenda) {
    system("cls");
    int stock_disponible = stock.obtenerStock(tipo_prenda);
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "EXISTE " << stock_disponible << " CANTIDAD DE UNIDADES EN STOCK DE LA PRENDA SELECCIONADA" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Ingrese la cantidad de unidades a cotizar" << endl;
    int cantidad_unidades;
    cin >> cantidad_unidades;

    // Verificar que la cantidad de unidades a cotizar no exceda la cantidad de unidades disponibles en el stock
    while (cantidad_unidades > stock_disponible) {
        cout << "La cantidad de unidades ingresada excede el stock disponible. Ingrese una cantidad menor o igual a " << stock_disponible << endl;
        cin >> cantidad_unidades;
    }

    return cantidad_unidades;
}


void realizarCotizacionCamisa(Stock& stock, Vendedor& vendedor, TipoPrenda tipo_prenda, Camisa& camisa) {
    
    // Obtener el nombre de la prenda correspondiente al tipo de prenda
    std::string nombre_prenda = camisa.obtenerNombrePrenda();

    // Solicitar cantidad de unidades a cotizar
    int cantidad_unidades = solicitarCantidadCotizar(stock, tipo_prenda);

    // Verificar que la cantidad de unidades a cotizar no exceda la cantidad de unidades disponibles en el stock
    int cantidad_disponible = stock.obtenerStock(tipo_prenda);
    if (cantidad_unidades <= cantidad_disponible) {
        // Se actualiza el stock correspondiente en la clase Stock
        stock.actualizarStock(tipo_prenda, cantidad_unidades);

        // Calcular resultado
        float resultado = camisa.calcular_precio_final_Camisa() * cantidad_unidades;

        // Agregar cotización al historial del vendedor
        int id = vendedor.get_historial_cotizaciones().size() + 1;
        int codigo_vendedor = vendedor.get_codigo();
        std::string fecha = fechaActual();
        Cotizacion cotizacion(id, fecha, codigo_vendedor, camisa.obtener_descripcion(), camisa.obtener_precio_unitario(), cantidad_unidades, resultado);
        vendedor.agregar_cotizacion(cotizacion);
        system("cls");
        // Mostrar resultado al usuario
        cout << ""<<endl;
        cout << "----------------------------------------"<<endl;
        cout << "           COTIZADOR EXPRESS            "<<endl;
        cout << "----------------------------------------"<<endl;
        cout << "Cotizacion realizada con exito:" << endl;
        cout << "Prenda: " << nombre_prenda << endl;
        cout << "Cantidad: " << cantidad_unidades << endl;
        cout << "Precio unitario sin descuento o aumento: $"<<camisa.get_precio_unitario()<<endl;
        cout << "Precio unitario con descuento o aumento: $" << camisa.obtener_precio_unitario() << endl;
        cout << "Total: " << resultado << endl;
        cout <<"********************************************"<< endl;
        cout << "Presiona 3 para regresar al menu principal"<< endl;
        cout <<"********************************************"<< endl;
    } else {
        cout << "No hay suficientes unidades disponibles en el stock." << endl;
        cout << "Cantidad disponible: " << cantidad_disponible << endl;
    }
}


void realizarCotizacionPantalon(Stock& stock, Vendedor& vendedor, TipoPrenda tipo_prenda, Pantalon& pantalon) {
    
    // Obtener el nombre de la prenda correspondiente al tipo de prenda
    std::string nombre_prenda = pantalon.obtenerNombrePrenda();

    // Solicitar cantidad de unidades a cotizar
    int cantidad_unidades = solicitarCantidadCotizar(stock, tipo_prenda);

    // Verificar que la cantidad de unidades a cotizar no exceda la cantidad de unidades disponibles en el stock
    int cantidad_disponible = stock.obtenerStock(tipo_prenda);
    if (cantidad_unidades <= cantidad_disponible) {
        // Se actualiza el stock correspondiente en la clase Stock
        stock.actualizarStock(tipo_prenda, cantidad_unidades);

        // Calcular resultado
        float resultado = pantalon.calcular_precio_final_pantalon() * cantidad_unidades;

        // Agregar cotización al historial del vendedor
        int id = vendedor.get_historial_cotizaciones().size() + 1;
        int codigo_vendedor = vendedor.get_codigo();
        std::string fecha = fechaActual();
        Cotizacion cotizacion(id, fecha, codigo_vendedor, pantalon.obtener_descripcion(), pantalon.obtener_precio_unitario(), cantidad_unidades, resultado);
        vendedor.agregar_cotizacion(cotizacion);
        system("cls");
        // Mostrar resultado al usuario
        cout << "----------------------------------------"<<endl;
        cout << "           COTIZADOR EXPRESS            "<<endl;
        cout << "----------------------------------------"<<endl;
        cout << "Cotización realizada con éxito:" << endl;
        cout << "Prenda: " << nombre_prenda << endl;
        cout << "Cantidad: " << cantidad_unidades << endl;
        cout << "Precio unitario sin descuento o aumento: $"<<pantalon.get_precio_unitario()<<endl;
        cout << "Precio unitario con descuento o aumento: $" << pantalon.obtener_precio_unitario() << endl;
        cout << "Total: " << resultado << endl;
        cout <<"********************************************"<< endl;
        cout << "Presiona 3 para regresar al menu principal"<< endl;
        cout <<"********************************************"<< endl;
    } else {
        cout << "No hay suficientes unidades disponibles en el stock." << endl;
        cout << "Cantidad disponible: " << cantidad_disponible << endl;
    }
}




int main() {
    //Obtengo los objetos creados
    auto tiendayvendedor = crearTiendayVendedor();
    Tienda tienda = tiendayvendedor.tienda;
    Vendedor vendedor = tiendayvendedor.vendedor;
    
    // Mostrar opciones
    int opcion;
    do {

        menuGeneral(tienda,vendedor);
        if(cin >> opcion){
            if(opcion != 1 && opcion !=2 && opcion !=3){
                cout<<"La opcion ingresada no es validad, por favor seleccione una opccion validad."<<endl;

            }else{

                switch (opcion) {
            
                //Historial
                
                case 1: {
                    system("cls");
                    // Obtener historial de cotizaciones del vendedor
                    const vector<Cotizacion>& historial_cotizaciones = vendedor.get_historial_cotizaciones();

                    // Imprimir historial de cotizaciones
                    if (historial_cotizaciones.empty()) {
                        cout <<"********************************************"<< endl;
                        cout << "No hay cotizaciones registradas para este vendedor" << endl;
                        cout <<"********************************************"<< endl;
                        cout << "Presiona 3 para regresar al menu principal"<< endl;
                        cout <<"********************************************"<< endl;
                    } else {
                        cout << ""<<endl;
                        cout << "----------------------------------------"<<endl;
                        cout << "           COTIZADOR EXPRESS            "<<endl;
                        cout << "----------------------------------------"<<endl;
                        cout << "Historial de cotizaciones:" << endl;
                        for (const Cotizacion& cotizacion : historial_cotizaciones) {
                            cout << "ID: " << cotizacion.get_id() << endl;
                            cout << "Fecha: " << cotizacion.get_fecha() << endl;
                            cout << "Prenda: " << cotizacion.get_prenda() << endl;
                            cout << "Precio Unitario con descuento o aumento: $" << cotizacion.get_precio_unitario() << endl;
                            cout << "Cantidad: " << cotizacion.get_cantidad() << endl;
                            cout << "Resultado: $" << cotizacion.get_resultado() << endl << endl;
                        }
                    }

                    cout <<"********************************************"<< endl;
                    cout << "Presiona 3 para regresar al menu principal"<< endl;
                    cout <<"********************************************"<< endl;
                    system("PAUSE");
                    break;
                }
                //Cotizacion
                case 2: {
                    system("cls");
                    // Realizar cotización
                    int opcion_prenda;
                    menuPrenda();
                    cin >> opcion_prenda;

                    switch (opcion_prenda) {
                        //camisa
                        case 1:{
                            system("cls");
                            int opcion_manga_corta;
                            menuManga();
                            cin >> opcion_manga_corta;
                            switch (opcion_manga_corta) {
                                //Manga corta
                                case 1:{
                                    system("cls");
                                    // Lógica para camisa manga corta
                                    int cuello_mao;
                                    menuCuello();
                                    cin>> cuello_mao;
                                    
                                    switch(cuello_mao){
                                        //Cuello mao
                                        case 1:{
                                            system("cls");
                                            int calidad_prendas;
                                            menuCalidad();
                                            cin>> calidad_prendas;
                                            switch (calidad_prendas){
                                                
                                                //Camisa manga corta cuello Mao standar
                                                case 1:{
                                                    
                                                    system("cls");
                                                    Stock stock;                                                
                                                    float precio_unitario;
                                                    cout <<"********************************************"<< endl;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cout <<"********************************************"<< endl<<endl;
                                                    cin >> precio_unitario;
                                                    
                                                    Camisa camisa("Standar", precio_unitario, "Camisa", "Manga Corta", "Cuello Mao",CAMISAS_MC_CUELLO_MAO_STANDARD);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_MC_CUELLO_MAO_STANDARD,camisa);
                                                    system("PAUSE");
                                    
                                                
                                                    break;
                                                }
                                                // Camisa manga corta cuello Mango Premium
                                                case 2:{
                                                    system("cls");
                                                    Stock stock;
                                                            

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Premium",precio_unitario,"Camisa","Manga Corta","Cuello Mao",CAMISAS_MC_CUELLO_MAO_PREMIUM);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_MC_CUELLO_MAO_PREMIUM,camisa);
                                                    system("PAUSE");

                                                    break;
                                                }                                                                                                                 
                                                case 3:{
                                                    system("cls");
                                                    if(calidad_prendas==3){
                                                        return main();
                                                    }
                                                    break;
                                                }
                                            }
                                            break;       
                                        }
                                        // Cuello normal
                                        case 2:{
                                            system("cls");
                                            int calidad_prendas;
                                            menuCalidad();
                                            cin>> calidad_prendas;
                                            switch (calidad_prendas){
                                                //Camisa manga corta cuello normal standar
                                                case 1:{
                                                    system("cls");
                                                    Stock stock;
                                                    

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Standar",precio_unitario,"Camisa","Manga Corta","Cuello Normal",CAMISAS_MC_CUELLO_COMUN_STANDARD);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_MC_CUELLO_COMUN_STANDARD,camisa);
                                                    system("PAUSE");        
                                                    
                                                    break;
                                                }
                                                // Camisa manga corta cuello normal Premium
                                                case 2:{
                                                    system("cls");
                                                    
                                                    Stock stock;
                                                    
                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Premium",precio_unitario,"Camisa","Manga Corta","Cuello Normal",CAMISAS_MC_CUELLO_COMUN_PREMIUM);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_MC_CUELLO_COMUN_PREMIUM,camisa);
                                                    system("PAUSE");
                                                    
                                                    break;

                                                    
                                                }                                                                                                                 
                                                //salir
                                                case 3:{
                                                    system("cls");
                                                    if(calidad_prendas==3){
                                                        return main();
                                                    }
                                                    break;
                                                }
                                            }
                                            break;       
                                        }                                    
                                        //Salir
                                        case 3:{
                                            system("cls");
                                            if(cuello_mao==3){
                                                return main();
                                            }
                                            break;
                                        }    
                                    }
                                break;  
                                } 
                                //Manga Larga
                                case 2:{
                                system("cls");
                                    // Lógica para camisa manga larga 
                                    int cuello_mao;
                                    menuCuello();
                                    cin>> cuello_mao;
                                    switch(cuello_mao){
                                        //Camisa manga larga Cuello Mao
                                        case 1:{
                                            system("cls");
                                            int calidad_prendas;
                                            menuCalidad();
                                            cin>> calidad_prendas;
                                            switch (calidad_prendas){
                                                //Camisa manga larga cuello Mao Standar
                                                case 1:{
                                                    system("cls");
                                                    Stock stock;
                                                    

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Standar",precio_unitario,"Camisa","Manga Larga","Cuello Mao",CAMISAS_ML_CUELLO_MAO_STANDARD);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_ML_CUELLO_MAO_STANDARD,camisa);
                                                    system("PAUSE");
                                                    break;
                                                }
                                                //Camisa manga larga cuello Mao Premium
                                                case 2:{
                                                    system("cls");
                                                    Stock stock;
                                                    

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Premium",precio_unitario,"Camisa","Manga Larga","Cuello Mao",CAMISAS_ML_CUELLO_MAO_PREMIUM);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_ML_CUELLO_MAO_PREMIUM,camisa);                                                
                                                    system("PAUSE");
                                                    break;
                                                }                                            
                                                case 3:{
                                                    system("cls");
                                                    if(calidad_prendas==3){
                                                        return main();
                                                    }
                                                    break;
                                                }
                                            }

                                            break;        
                                        }
                                        //Camisa manga larga Cuello Normal
                                        case 2:{
                                            system("cls");
                                            int calidad_prendas;
                                            menuCalidad();
                                            cin>> calidad_prendas;
                                            switch (calidad_prendas){
                                                //Camisa manga larga cuello noraml Standar
                                                case 1:{
                                                    system("cls");
                                                    Stock stock;
                                                    

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Standar",precio_unitario,"Camisa","Manga Larga","Cuello Normal",CAMISAS_ML_CUELLO_COMUN_STANDARD);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_ML_CUELLO_COMUN_STANDARD,camisa);
                                                    system("PAUSE");
                                                    break;
                                                }
                                                //Camisa manga larga cuello normal Premium
                                                case 2:{
                                                    system("cls");
                                                    Stock stock;
                                                

                                                    float precio_unitario;
                                                    cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                                    cin >> precio_unitario;
                                                    Camisa camisa("Premium",precio_unitario,"Camisa","Manga Larga","Cuello Normal",CAMISAS_ML_CUELLO_COMUN_PREMIUM);
                                                    realizarCotizacionCamisa(stock, vendedor, TipoPrenda::CAMISAS_ML_CUELLO_COMUN_PREMIUM,camisa);
                                                    system("PAUSE");
                                                    break;
                                                }                                            
                                                
                                                                                                                                                                

                                            }

                                            break;        
                                        }                                       
                                        //Salir
                                        case 3:{
                                            system("cls");
                                            if(cuello_mao==3){
                                                return main();
                                            }
                                            break;
                                        }
                                    }
                                    break;
                                    
                                }                             
                                //Salir
                                case 3:{
                                    system("cls");
                                    if(opcion_manga_corta==3){
                                        return main();
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        //pantalon
                        case 2:{
                            system("cls");
                            int pantalon_chupin;
                            menuPantalon();
                            cin>> pantalon_chupin;
                            switch (pantalon_chupin){
                                //Pantalon chupin
                                case 1:{
                                    system("cls");
                                    int calidad_prendas;
                                    menuCalidad();
                                    cin>> calidad_prendas;
                                    switch (calidad_prendas){
                                        case 1:{
                                            system("cls");
                                            //PANTALON CHUPIN STANDAR
                                            Stock stock;
                                            float precio_unitario;
                                            cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                            cin >> precio_unitario;
                                            Pantalon pantalon("Standar",precio_unitario,"Pantalon","Chupin",PANTALONES_CHUPINES_STANDARD);
                                            realizarCotizacionPantalon(stock, vendedor, TipoPrenda::PANTALONES_CHUPINES_STANDARD,pantalon);
                                            system("PAUSE");
                                            break;
                                        }
                                        case 2:{
                                            system("cls");
                                            //PANTALON CHUPIN PREMIUM
                                            Stock stock;
                                            float precio_unitario;
                                            cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                            cin >> precio_unitario;
                                            Pantalon pantalon("Premium",precio_unitario,"Pantalon","Chupin",PANTALONES_CHUPINES_PREMIUM);
                                            realizarCotizacionPantalon(stock, vendedor, TipoPrenda::PANTALONES_CHUPINES_PREMIUM,pantalon);
                                            system("PAUSE");
                                            break;
                                        }
                                        case 3:{
                                            //salir
                                            system("cls");
                                            if(calidad_prendas==3){
                                                return main();
                                            }
                                            break;
                                        }
                                    }

                                    break;
                                }
                                //Pantalon normal
                                case 2:{
                                    system("cls");
                                    int calidad_prendas;
                                    menuCalidad();
                                    cin>> calidad_prendas;
                                    switch (calidad_prendas){
                                        case 1:{ 
                                            system("cls");                                     
                                            //PANTALON NORMAL STANDAR
                                            Stock stock;
                                            float precio_unitario;
                                            cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                            cin >> precio_unitario;
                                            Pantalon pantalon("Standar",precio_unitario,"Pantalon","Normal",PANTALONES_COMUNES_STANDARD);
                                            realizarCotizacionPantalon(stock, vendedor, TipoPrenda::PANTALONES_COMUNES_STANDARD,pantalon);
                                            system("PAUSE");
                                            break;
                                        }
                                        case 2:{
                                            system("cls");
                                            //PANTALON NORMAL PREMIUM
                                            Stock stock;
                                            float precio_unitario;
                                            cout << "Ingrese el precio unitario de la prenda a cotizar" << endl;
                                            cin >> precio_unitario;
                                            Pantalon pantalon("Premium",precio_unitario,"Pantalon","Normal",PANTALONES_COMUNES_PREMIUM);
                                            realizarCotizacionPantalon(stock, vendedor, TipoPrenda::PANTALONES_COMUNES_PREMIUM,pantalon);
                                            system("PAUSE");
                                            break;
                                        }
                                        case 3:{
                                            //salir
                                            system("cls");
                                            if(calidad_prendas==3){
                                                return main();
                                            }
                                            break;
                                        }
                                    }

                                    break;
                                }
                                //Salir
                                case 3:{
                                    //salir
                                    system("cls");
                                    if(pantalon_chupin==3){
                                        return main();
                                    }
                                    break;
                                }

                            }

                            break;
                        }
                        //salir
                        case 3:{
                            system("cls");
                            if(opcion_prenda==3){
                            break;
                            }                                           
                        }                 
                    }
                    break;    
                }        
                //Salir
                case 3: {
                    system("cls");  
                    if(opcion==3){
                        cout<<"Saliendo del programa..."<<endl;
                    }
                    break;
                    
                }
                default:{
                    cout<<"Opcion invalidad, intente de nuevo"<<endl;
                    break;
                }  
            }             
            }
        }
        else{
            cout << "La entrada no es valida, por favor ingrese un numero entero." << endl;
            cin.clear(); // Limpiar el flag de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
        }

        
        
        

        

        
    }while (opcion != 3);
    cout<<"\n\n Gracias por usar el programa.\n\n"<<endl;
    return 0;
    
}
