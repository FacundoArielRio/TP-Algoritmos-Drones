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
        cout << "[!] Error: No se pudo crear el archivo HTML en: " << rutaHTML << endl;
        return false;
    }

    int minX = TAM_GRILLA, maxX = 0, minY = TAM_GRILLA, maxY = 0;
    bool hayRecorrido = false;

    for (int i = 0; i < TAM_GRILLA; i++) {
        for (int j = 0; j < TAM_GRILLA; j++) {
            if (grilla[i][j].despegue || grilla[i][j].aterrizaje ||
                grilla[i][j].soltarGranada1 || grilla[i][j].soltarGranada2 ||
                grilla[i][j].ataqueKamikaze || grilla[i][j].espera > 0) {
                hayRecorrido = true;
                if (i < minX) minX = i;
                if (i > maxX) maxX = i;
                if (j < minY) minY = j;
                if (j > maxY) maxY = j;
            }
        }
    }

    if (!hayRecorrido) { minX = 0; maxX = 20; minY = 0; maxY = 20; }

    fprintf(f, "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n");
    fprintf(f, "  <meta charset=\"UTF-8\">\n");
    fprintf(f, "  <title>Misión del Dron</title>\n");
    fprintf(f, "  <style>\n");
    fprintf(f, "    body { font-family: 'Segoe UI', Arial, sans-serif; background-color: #0f172a; color: #f8fafc; margin: 20px; }\n");
    fprintf(f, "    h1 { text-align: center; color: #38bdf8; font-size: 26px; margin-bottom: 15px; }\n");
    fprintf(f, "    .controls { text-align: center; margin-bottom: 20px; }\n");
    fprintf(f, "    .btn-zoom { background-color: #0284c7; color: white; border: none; padding: 10px 20px; font-size: 14px; font-weight: bold; border-radius: 6px; cursor: pointer; transition: background 0.3s; }\n");
    fprintf(f, "    .btn-zoom:hover { background-color: #0369a1; }\n");
    fprintf(f, "    .layout { display: flex; justify-content: center; gap: 20px; align-items: flex-start; }\n");
    fprintf(f, "    .table-container { max-width: 75vw; max-height: 75vh; overflow: auto; border: 2px solid #334155; border-radius: 8px; background-color: #1e293b; padding: 10px; }\n");
    fprintf(f, "    table { border-collapse: collapse; transition: transform 0.4s ease; transform-origin: top left; }\n");
    fprintf(f, "    td { width: 14px; height: 14px; text-align: center; font-size: 10px; border: 1px solid #334155; color: #475569; }\n");

    fprintf(f, "    .c-despegue { background-color: #22c55e; color: #ffffff; font-weight: bold; } /* Verde */\n");
    fprintf(f, "    .c-kamikaze { background-color: #ef4444; color: #ffffff; font-weight: bold; } /* Rojo */\n");
    fprintf(f, "    .c-granada { background-color: #f59e0b; color: #ffffff; font-weight: bold; } /* Naranja */\n");
    fprintf(f, "    .c-espera { background-color: #06b6d4; color: #ffffff; font-weight: bold; } /* Cyan */\n");
    fprintf(f, "    .c-paso { background-color: #3b82f6; color: #ffffff; } /* Azul */\n");

    fprintf(f, "    .sidebar { background-color: #1e293b; border: 1px solid #334155; border-radius: 8px; padding: 15px; width: 220px; }\n");
    fprintf(f, "    .sidebar h3 { color: #38bdf8; margin-top: 0; font-size: 16px; border-bottom: 1px solid #334155; padding-bottom: 8px; }\n");
    fprintf(f, "    .item { display: flex; align-items: center; margin-bottom: 10px; font-size: 13px; }\n");
    fprintf(f, "    .box { width: 18px; height: 18px; text-align: center; line-height: 18px; font-weight: bold; border-radius: 3px; margin-right: 10px; font-size: 11px; }\n");
    fprintf(f, "  </style>\n</head>\n<body>\n");

    fprintf(f, "  <h1>Visualización del Recorrido del Dron</h1>\n");
    fprintf(f, "  <div class=\"controls\">\n");
    fprintf(f, "    <button class=\"btn-zoom\" onclick=\"hacerZoom()\">🔍 Zoom al Recorrido</button>\n");
    fprintf(f, "  </div>\n");

    fprintf(f, "  <div class=\"layout\">\n");
    fprintf(f, "    <div class=\"table-container\" id=\"contenedor\">\n");
    fprintf(f, "      <table id=\"grilla\">\n");

    for (int i = 0; i < TAM_GRILLA; i++)
    {
        fprintf(f, "        <tr>\n");
        for (int j = 0; j < TAM_GRILLA; j++)
        {
            Orden celda = grilla[i][j];

            if (celda.despegue)
                fprintf(f, "          <td class=\"c-despegue\" id=\"celda-%d-%d\" title=\"Despegue (%d;%d)\">D</td>\n", i, j, i, j);
            else if (celda.aterrizaje || celda.ataqueKamikaze)
                fprintf(f, "          <td class=\"c-kamikaze\" id=\"celda-%d-%d\" title=\"Fin (%d;%d)\">F</td>\n", i, j, i, j);
            else if (celda.soltarGranada1 || celda.soltarGranada2)
                fprintf(f, "          <td class=\"c-granada\" id=\"celda-%d-%d\" title=\"Granada (%d;%d)\">G</td>\n", i, j, i, j);
            else if (celda.espera > 0)
                fprintf(f, "          <td class=\"c-espera\" id=\"celda-%d-%d\" title=\"Espera %ds (%d;%d)\">E</td>\n", celda.espera, i, j, i, j);
            else if (celda.siguientex != 0 || celda.siguientey != 0)
                fprintf(f, "          <td class=\"c-paso\" id=\"celda-%d-%d\" title=\"Paso (%d;%d)\">•</td>\n", i, j, i, j);
            else
                fprintf(f, "          <td>.</td>\n");
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

    fprintf(f, "  <script>\n");
    fprintf(f, "    let zoomed = false;\n");
    fprintf(f, "    function hacerZoom() {\n");
    fprintf(f, "      const tabla = document.getElementById('grilla');\n");
    fprintf(f, "      const objetivo = document.getElementById('celda-%d-%d');\n", minX, minY);
    fprintf(f, "      if (!zoomed) {\n");
    fprintf(f, "        tabla.style.transform = 'scale(2.5)';\n");
    fprintf(f, "        if (objetivo) { objetivo.scrollIntoView({ behavior: 'smooth', block: 'center', inline: 'center' }); }\n");
    fprintf(f, "        zoomed = true;\n");
    fprintf(f, "      } else {\n");
    fprintf(f, "        tabla.style.transform = 'scale(1)';\n");
    fprintf(f, "        zoomed = false;\n");
    fprintf(f, "      }\n");
    fprintf(f, "    }\n");
    fprintf(f, "  </script>\n");
    fprintf(f, "</body>\n</html>\n");

    fclose(f);
    cout << "[OK] Archivo HTML con Zoom generado exitosamente en: " << rutaHTML << endl;
    return true;
}
