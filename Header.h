#ifndef HEADERS_H
#define HEADERS_H

#include <cstdint>

// La commande prama pack permet de condenser les structures
// Elle ordonne on compilateur de ne pas ajouter de bits lors de la compilation
#pragma pack(push, 1)
struct TP2FichierEntente
{
    uint16_t file_type{ 0x6969 }; // Toujours 0x4D42 qui représente BM
    uint32_t file_size{ 0 }; // Taille du fichier en octets (bytes)
    uint32_t decallageDonner{ 0 }; // Décalage 
    uint32_t laby_noHeader_size{ 0 }; // Taille du labyrainthe sans le Headers
    uint16_t laby_case_number{ 0 }; // Nombre de case du labyrainthe
    uint16_t laby_case_startNumber{ 0 }; // Case de début du labyrainthe
    uint16_t laby_case_endNumber{ 0 }; // Case de fin du labyrainthe
};

struct TP2SolutionEntete
{
    uint32_t number_case_travel{ 0 }; // Nombre de case voyager
    uint32_t data_decalage_sinceStart{ 0 }; // Décalage des donner depuis le début
};

struct TP2LienCase
{
    uint16_t case_origine{ 0 }; // Case d'origine
    uint16_t case_destination{ 0 }; // Case de fin
};

struct TP2EtapeChemin 
{
    uint16_t numero_case{ 0 }; // Numero de case
};

#pragma pack(pop)

#endif
