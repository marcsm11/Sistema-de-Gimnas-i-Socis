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
    Tarifa() : preuMensual(0.0), nomTarifa("Bàsica") {}

    Tarifa(string nom, double preu) : nomTarifa(nom), preuMensual(preu > 0 ? preu : 0.0) {}

    // Getters
    double getPreuMensual() const {
        return preuMensual;
    }

    string getNomTarifa() const {
        return nomTarifa;
    }
};

// ==========================================
// 2. CLASSE BASE: Soci (Utilitza COMPOSICIÓ)
// ==========================================
class Soci {
protected:
    // Fem els atributs 'protected' perquè la classe filla (SociVIP) hi pugui accedir
    string nom;
    int idSoci;
    Tarifa tarifa; // COMPOSICIÓ: El soci TÉ UNA Tarifa a dins

public:
    // Constructor de Soci
    Soci(string n, int id, Tarifa t)
        : nom(n), idSoci(id), tarifa(t) {
    }

    // Getters
    string getNom() const { return nom; }
    int getIdSoci() const { return idSoci; }

    // Mètode virtual per permetre el polimorfisme / redefinició en classes filles
    virtual double calcularQuota() const {
        return tarifa.getPreuMensual();
    }

    // Destructor virtual per bona praxi en herència
    virtual ~Soci() {}
};

// ==========================================
// 3. CLASSE DERIVADA: SociVIP (Utilitza HERÈNCIA)
// ==========================================
class SociVIP : public Soci { // SociVIP ÉS UN Soci
private:
    double descompteEntrenador; // p. ex. 15.0 per un 15% de descompte o un descompte en euros

public:
    // Constructor: Crida al constructor de la classe base (Soci)
    SociVIP(string n, int id, Tarifa t, double descompte)
        : Soci(n, id, t), descompteEntrenador(descompte) {
    }

    // Redefinició (override) del mètode calcularQuota()
    double calcularQuota() const override {
        double quotaBase = tarifa.getPreuMensual();
        double quotaFinal = quotaBase - descompteEntrenador;
        return quotaFinal > 0 ? quotaFinal : 0.0; // Evitem quotes negatives
    }
};

// ==========================================
// PROVA DEL PROGRAMA (main)
// ==========================================
int main() {
    // 1. Creem un parell de tarifes
    Tarifa tarifaEstandard("Estàndard", 45.0);
    Tarifa tarifaPremium("Premium", 60.0);

    // 2. Creem un Soci normal (Composició amb tarifaEstandard)
    Soci sociNormal("Marc", 101, tarifaEstandard);

    // 3. Creem un Soci VIP (Herència de Soci + Descompte de 10€)
    SociVIP sociVIP("Anna", 102, tarifaPremium, 10.0);

    // 4. Mostrem els resultats
    cout << "Soci Normal: " << sociNormal.getNom()
        << " | Quota: " << sociNormal.calcularQuota() << " EUR\n";

    cout << "Soci VIP: " << sociVIP.getNom()
        << " | Quota amb descompte: " << sociVIP.calcularQuota() << " EUR\n";

    return 0;
}