#include <iostream>
#include <cstdio>
#include <cstring>
#include "include/visualizador.h"

using namespace std;

bool generarHTML(const char rutaHTML[], Orden grilla[TAM_GRILLA][TAM_GRILLA])
{
    FILE *f = fopen(rutaHTML, "w");
    if (f == NULL)
    {
        cout << "Error: No se pudo crear el archivo HTML en: " << rutaHTML << endl;
        return false;
    }

    fprintf(f, "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n");
    fprintf(f, "  <meta charset=\"UTF-8\">\n");
    fprintf(f, "  <title>Misión del Dron</title>\n");
    fprintf(f, "%s\n", CSS_ESTILOS);
    fprintf(f, "</head>\n<body>\n");

    fprintf(f, "  <h1>Visualización del Recorrido del Dron</h1>\n");
    fprintf(f, "  <div class=\"layout\">\n");
    fprintf(f, "    <div class=\"table-container\">\n");
    fprintf(f, "      <table>\n");

    for (int i = 0; i < TAM_GRILLA; i++)
    {
        fprintf(f, "        <tr>\n");
        for (int j = 0; j < TAM_GRILLA; j++)
        {
            Orden celda = grilla[i][j];

            if (celda.despegue)
                fprintf(f, "          <td class=\"c-despegue\" title=\"Despegue (%d;%d)\">D</td>\n", i, j);
            else if (celda.aterrizaje || celda.ataqueKamikaze)
                fprintf(f, "          <td class=\"c-kamikaze\" title=\"Fin (%d;%d)\">F</td>\n", i, j);
            else if (celda.soltarGranada1 || celda.soltarGranada2)
                fprintf(f, "          <td class=\"c-granada\" title=\"Granada (%d;%d)\">G</td>\n", i, j);
            else if (celda.espera > 0)
                fprintf(f, "          <td class=\"c-espera\" title=\"Espera %ds (%d;%d)\">E</td>\n", celda.espera, i, j);
            else if (celda.siguientex != -1 && celda.siguientey != -1)
                fprintf(f, "          <td class=\"c-paso\" title=\"Paso (%d;%d)\">•</td>\n", i, j);
            else
                fprintf(f, "          <td title=\"Vacio (%d;%d)\"></td>\n", i, j);
        }
        fprintf(f, "        </tr>\n");
    }

    fprintf(f, "      </table>\n");
    fprintf(f, "    </div>\n");

    fprintf(f, "    <div class=\"sidebar\">\n");
    fprintf(f, "      <h3>Referencias</h3>\n");
    fprintf(f, "      <div class=\"item\"><div class=\"box c-despegue\">D</div> Despegue</div>\n");
    fprintf(f, "      <div class=\"item\"><div class=\"box c-kamikaze\">F</div> Aterrizaje / Kamikaze</div>\n");
    fprintf(f, "      <div class=\"item\"><div class=\"box c-granada\">G</div> Soltar Granada</div>\n");
    fprintf(f, "      <div class=\"item\"><div class=\"box c-espera\">E</div> Tiempo de Espera</div>\n");
    fprintf(f, "      <div class=\"item\"><div class=\"box c-paso\">•</div> Movimiento de Ruta</div>\n");
    fprintf(f, "    </div>\n");
    fprintf(f, "  </div>\n");
    fprintf(f, "</body>\n</html>\n");

    fclose(f);
    cout << "\nArchivo HTML generado exitosamente en: " << rutaHTML << endl;
    return true;
}
