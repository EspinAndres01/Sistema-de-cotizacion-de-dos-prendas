#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <tuple>
#include <map>

class Prenda {
protected:
    std::string calidad;
    float precio_unitario;
    std::string tipo_prenda;

public:
    Prenda(std::string calidad, float precio_unitario, std::string tipo_prenda) :
        calidad(calidad), precio_unitario(precio_unitario), tipo_prenda(tipo_prenda) {}

    std::string get_calidad() const {
        return calidad;
    }

    float get_precio_unitario() const {
        return precio_unitario;
    }


    std::string get_tipo_prenda() const {
        return tipo_prenda;
    }
    

};

class Tienda {
private:
    std::string nombre;
    std::string direccion;
    std::vector<Prenda> prendas;
public:
    Tienda(std::string nombre, std::string direccion) :
        nombre(nombre), direccion(direccion) {}

    std::string get_nombre() const {
        return nombre;
    }

    std::string get_direccion() const {
        return direccion;
    }

    void agregar_prenda(const Prenda& prenda) {
        prendas.push_back(prenda);
    }

    const std::vector<Prenda>& get_prendas() const {
        return prendas;
    }
};

class Cotizacion {
private:
    int id;
    std::string fecha;
    int codigo_vendedor;
    std::string prenda;
    int cantidad;
    float resultado;
    float precio_unitario;
public:
    Cotizacion(int id,std::string fecha, int codigo_vendedor, std::string prenda,float precio_unitario, int cantidad, float resultado) : 
        id(id),fecha(fecha), codigo_vendedor(codigo_vendedor), prenda(prenda),precio_unitario(precio_unitario), cantidad(cantidad), resultado(resultado) {
        
        // Obtener fecha y hora actuales
        std::time_t now = std::time(nullptr);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        
        fecha = buffer;
    }

    int get_id() const {
        return id;
    }

    std::string get_fecha() const {
        return fecha;
    }

    int get_codigo_vendedor() const {
        return codigo_vendedor;
    }

    std::string get_prenda() const {
        return prenda;
    }

    int get_cantidad() const {
        return cantidad;
    }

    float get_resultado() const {
        return resultado;
    }

    float get_precio_unitario() const{
        return precio_unitario;
    }
};

class Vendedor {
private:
    std::string nombre;
    std::string apellido;
    int codigo;
    std::vector<Cotizacion> historial;
public:
    Vendedor(std::string nombre, std::string apellido, int codigo) :
        nombre(nombre), apellido(apellido), codigo(codigo) {}

    std::string get_nombre() const {
        return nombre;
    }

    std::string get_apellido() const {
        return apellido;
    }

    int get_codigo() const {
        return codigo;
    }

    void agregar_cotizacion(const Cotizacion& cotizacion) {
        historial.push_back(cotizacion);
    }

    const std::vector<Cotizacion>& get_historial_cotizaciones() const {
        return historial;
    }
};

enum TipoPrenda{
    CAMISAS_MC_CUELLO_COMUN_STANDARD,
    CAMISAS_MC_CUELLO_COMUN_PREMIUM,
    CAMISAS_MC_CUELLO_MAO_PREMIUM,
    CAMISAS_MC_CUELLO_MAO_STANDARD,
    CAMISAS_ML_CUELLO_COMUN_STANDARD,
    CAMISAS_ML_CUELLO_COMUN_PREMIUM,
    CAMISAS_ML_CUELLO_MAO_PREMIUM,
    CAMISAS_ML_CUELLO_MAO_STANDARD,
    PANTALONES_CHUPINES_STANDARD,
    PANTALONES_CHUPINES_PREMIUM,
    PANTALONES_COMUNES_STANDARD,
    PANTALONES_COMUNES_PREMIUM,
};

class Stock {
private:
    std::map<TipoPrenda, int> stock;

public:
    Stock() {
        stock[CAMISAS_MC_CUELLO_COMUN_STANDARD] = 150;
        stock[CAMISAS_MC_CUELLO_COMUN_PREMIUM] = 150;
        stock[CAMISAS_MC_CUELLO_MAO_PREMIUM] = 100;
        stock[CAMISAS_MC_CUELLO_MAO_STANDARD] = 100;
        stock[CAMISAS_ML_CUELLO_COMUN_STANDARD] = 175;
        stock[CAMISAS_ML_CUELLO_COMUN_PREMIUM] = 175;
        stock[CAMISAS_ML_CUELLO_MAO_PREMIUM] = 75;
        stock[CAMISAS_ML_CUELLO_MAO_STANDARD] = 75;
        stock[PANTALONES_CHUPINES_STANDARD] = 750;
        stock[PANTALONES_CHUPINES_PREMIUM] = 750;
        stock[PANTALONES_COMUNES_STANDARD] = 250;
        stock[PANTALONES_COMUNES_PREMIUM] = 250;
    }

    void actualizarStock(TipoPrenda prenda, int cantidad) {
        auto it = stock.find(prenda);
        if (it == stock.end()) {
            std::cout << "La prenda especificada no existe" << std::endl;
        } else if (it->second < cantidad) {
            std::cout << "No hay suficientes unidades disponibles en stock" << std::endl;
        } else {
            it->second -= cantidad;
        }
    }

    int obtenerStock(TipoPrenda prenda) const {
        auto it = stock.find(prenda);
        if (it == stock.end()) {
            std::cout << "La prenda especificada no existe" << std::endl;
            return 0;
        } else {
            return it->second;
        }
    }
};   


class Pantalon : public Prenda {
private:
    std::string tipo;
    TipoPrenda tipo_prenda_enum;
public:
    Pantalon(std::string calidad, float precio_unitario, std::string tipo_prenda,std::string tipo,TipoPrenda tipo_prenda_enum) :
        Prenda(calidad, precio_unitario, tipo_prenda), tipo(tipo),tipo_prenda_enum(tipo_prenda_enum) {}

    std::string get_tipo() const {
        return tipo;
    }



    float calcular_precio_final_pantalon() {
        float precio_final = precio_unitario;
        
        if (tipo == "Chupin") {
            precio_final *= 0.88;
        }
        if (calidad == "Premium") {
            precio_final *= 1.3;
        }
        else if (calidad == "Standar") {
            precio_final =precio_unitario;
        }
        return precio_final;
    }
    std::string obtenerNombrePrenda() {
        switch (tipo_prenda_enum) {
            case TipoPrenda::PANTALONES_CHUPINES_STANDARD:
                return "Pantalones chupines standar";
            case TipoPrenda::PANTALONES_CHUPINES_PREMIUM:
                return "Pantalones chupines premium";
            case TipoPrenda::PANTALONES_COMUNES_PREMIUM:
                return "Pantalones comunes premium";
            case TipoPrenda::PANTALONES_COMUNES_STANDARD:
                return "Pantalones normales standard";
            default:
                return "";
        }
    }
    std::string obtener_descripcion() {
        return obtenerNombrePrenda() + " - " + tipo;
    }

    float obtener_precio_unitario()  {
        return calcular_precio_final_pantalon();
    }
};




class Camisa : public Prenda {
private:
    TipoPrenda tipo_prenda_enum;
    std::string tipo_manga;
    std::string tipo_cuello;

public:
    Camisa(std::string calidad, float precio_unitario, std::string tipo_prenda, std::string tipo_manga, std::string tipo_cuello, TipoPrenda tipo_prenda_enum) :
        Prenda(calidad, precio_unitario, tipo_prenda), tipo_manga(tipo_manga), tipo_cuello(tipo_cuello), tipo_prenda_enum(tipo_prenda_enum) {}

    std::string get_tipo_manga() const {
        return tipo_manga;
    }

    std::string get_tipo_cuello() const {
        return tipo_cuello;
    }


    float calcular_precio_final_Camisa() {
        float precio_final = precio_unitario;
        if (tipo_manga == "Manga Corta") {
            precio_final *= 0.9;
        }
        if (tipo_cuello == "Cuello Mao") {
            precio_final *= 1.03;
        }
        if (tipo_manga == "Manga Corta" && tipo_cuello == "Cuello Mao") {
            precio_final *= 0.9 * 1.03;
        }
        if (calidad == "Premium") {
            precio_final *= 1.3;
        }
        else if (calidad == "Standar") {
            precio_final = precio_unitario;
        }
        return precio_final;
    }
    std::string obtenerNombrePrenda() {
        switch (tipo_prenda_enum) {
            case TipoPrenda::CAMISAS_MC_CUELLO_COMUN_PREMIUM:
                return "Camisas manga corta cuello común premium";
            case TipoPrenda::CAMISAS_MC_CUELLO_COMUN_STANDARD:
                return "Camisas manga corta cuello común standard";
            case TipoPrenda::CAMISAS_MC_CUELLO_MAO_PREMIUM:
                return "Camisas manga corta cuello mao premium";
            case TipoPrenda::CAMISAS_MC_CUELLO_MAO_STANDARD:
                return "Camisas manga corta cuello mao standard";
            case TipoPrenda::CAMISAS_ML_CUELLO_COMUN_PREMIUM:
                return "Camisas manga larga cuello común premium";
            case TipoPrenda::CAMISAS_ML_CUELLO_COMUN_STANDARD:
                return "Camisas manga larga cuello común standard";
            case TipoPrenda::CAMISAS_ML_CUELLO_MAO_PREMIUM:
                return "Camisas manga larga cuello mao premium";
            case TipoPrenda::CAMISAS_ML_CUELLO_MAO_STANDARD:
                return "Camisas manga larga cuello mao standard";
            default:
                return "";
        }
    }

    std::string obtener_descripcion() {
        return obtenerNombrePrenda() + " - " + tipo_manga + " - " + tipo_cuello;
    }

    float obtener_precio_unitario()  {
        return calcular_precio_final_Camisa();
    }
};




void menuGeneral(Tienda tienda,Vendedor vendedor);
void menuCuello();
void menuManga();
void menuPrenda();
void menuCalidad();
void menuPantalon();
std::string fechaActual();

struct TiendayVendedor {
    Tienda tienda;
    Vendedor vendedor;
};

TiendayVendedor crearTiendayVendedor();

