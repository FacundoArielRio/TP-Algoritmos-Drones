#ifndef VISUALIZADOR_H_INCLUDED
#define VISUALIZADOR_H_INCLUDED

#include "drone.h"

const char CSS_ESTILOS[] = R"(
  <style>
    body {
      font-family: 'Segoe UI', Arial, sans-serif;
      background-color: #0f172a;
      color: #f8fafc;
      margin: 15px;
    }
    h1 {
      text-align: center;
      color: #38bdf8;
      font-size: 24px;
      margin-bottom: 15px;
    }
    .layout {
      display: flex;
      justify-content: center;
      gap: 20px;
      align-items: flex-start;
    }
    .table-container {
      border: 2px solid #334155;
      border-radius: 8px;
      background-color: #1e293b;
      padding: 8px;
      overflow: auto;
      max-height: 82vh;
      max-width: 80vw;
    }
    table {
      border-collapse: collapse;
    }
    td {
      width: 14px;
      height: 14px;
      text-align: center;
      font-size: 9px;
      font-weight: bold;
      border: 1px solid #1e293b; /* Borde sutil para delimitar la grilla */
      background-color: #0f172a; /* Fondo oscuro unificado */
    }
    /* Estilos tácticos destacados por acción */
    .c-despegue { background-color: #22c55e !important; color: #ffffff !important; }
    .c-kamikaze { background-color: #ef4444 !important; color: #ffffff !important; }
    .c-granada  { background-color: #f59e0b !important; color: #ffffff !important; }
    .c-espera   { background-color: #06b6d4 !important; color: #ffffff !important; }
    .c-paso     { background-color: #3b82f6 !important; color: #ffffff !important; }

    /* Barra lateral */
    .sidebar {
      background-color: #1e293b;
      border: 1px solid #334155;
      border-radius: 8px;
      padding: 15px;
      width: 200px;
    }
    .sidebar h3 {
      color: #38bdf8;
      margin-top: 0;
      font-size: 16px;
      border-bottom: 1px solid #334155;
      padding-bottom: 8px;
    }
    .item {
      display: flex;
      align-items: center;
      margin-bottom: 10px;
      font-size: 13px;
    }
    .box {
      width: 18px;
      height: 18px;
      text-align: center;
      line-height: 18px;
      font-weight: bold;
      border-radius: 3px;
      margin-right: 10px;
      font-size: 11px;
    }
  </style>
)";

bool generarHTML(const char rutaHTML[], Orden grilla[TAM_GRILLA][TAM_GRILLA]);

#endif // VISUALIZADOR_H_INCLUDED
