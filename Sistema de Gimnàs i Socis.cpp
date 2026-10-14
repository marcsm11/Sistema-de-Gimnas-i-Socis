#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CLASSE DE SUPORT: Tarifa
// ==========================================
class Tarifa {
private:
    double preuMensual;
    string nomTarifa;

public:
    // Constructors
    Tarifa();
    Tarifa(string nom, double preu);

    // Getters
    double getPreuMensual() const;
    string getNomTarifa() const;
};

// ==========================================
// 2. CLASSE BASE: Soci (Utilitza COMPOSICIÓ)
// ==========================================
class Soci {
protected:
    // Atributs protegits per permetre l'accés a la classe derivada
    string nom;
    unsigned int idSoci; // Tipus sense signe (>= 0)
    Tarifa tarifa;       // COMPOSICIÓ: El soci TÉ UNA Tarifa a dins

public:
    // Constructor i Destructor
    Soci(string n, unsigned int id, Tarifa t);
    virtual ~Soci();

    // Getters
    string getNom() const;
    unsigned int getIdSoci() const;

    // Mètode virtual per permetre polimorfisme
    virtual double calcularQuota() const;
};

// ==========================================
// 3. CLASSE DERIVADA: SociVIP (Utilitza HERÈNCIA)
// ==========================================
class SociVIP : public Soci { // SociVIP ÉS UN Soci
private:
    double descompteEntrenador;

public:
    // Constructor
    SociVIP(string n, unsigned int id, Tarifa t, double descompte);

    // Redefinició (override) del mètode
    double calcularQuota() const override;
};