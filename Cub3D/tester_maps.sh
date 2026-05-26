#!/bin/bash

# Colores para la terminal
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

EXECUTABLE="./cub3d"
MAP_DIR="map"

# Verificar si el ejecutable existe, si no, compilar
if [ ! -f "$EXECUTABLE" ]; then
	echo -e "${YELLOW}Ejecutable no encontrado. Compilando el proyecto...${NC}"
	make
	if [ $? -ne 0 ]; then
		echo -e "${RED}Error: La compilación falló.${NC}"
		exit 1
	fi
fi

# Verificar si la carpeta de mapas existe
if [ ! -d "$MAP_DIR" ]; then
	echo -e "${RED}Error: La carpeta '$MAP_DIR' no existe.${NC}"
	exit 1
fi

echo "=================================================="
echo "      INICIANDO TESTER DE MAPAS PARA CUB3D        "
echo "=================================================="
echo "Nota: Si un mapa es correcto, la ventana se abrirá."
echo "Por favor, ciérrala manualmente para continuar el test."
echo "=================================================="
echo ""

# Contador de resultados
total=0
passed_errors=0
passed_success=0
crashes=0

# Bucle sobre todos los archivos de la carpeta map
for map_file in "$MAP_DIR"/*; do
	# Evitar procesar directorios por si acaso
	[ -e "$map_file" ] || continue
	[ -f "$map_file" ] || continue

	total=$((total + 1))
	echo -e "${YELLOW}[Test $total] Probando:${NC} $map_file"
	
	# Ejecutar cub3d con el mapa actual de forma normal
	# Redirigimos stderr a un archivo temporal para analizarlo si es necesario
	$EXECUTABLE "$map_file" 2> /tmp/cub3d_err.log
	status=$?

	# Analizar el código de salida (exit status)
	if [ $status -eq 0 ]; then
		# El programa terminó con EXIT_SUCCESS (el usuario cerró la ventana)
		echo -e "${GREEN}  -> [OK] El mapa se cargó correctamente y abrió la ventana.${NC}"
		passed_success=$((passed_success + 1))
	elif [ $status -eq 1 ]; then
		# El programa terminó con EXIT_FAILURE (Error controlado en el parseo)
		echo -e "${GREEN}  -> [CONTROLADO] Error de parseo gestionado con éxito.${NC}"
		if [ -s /tmp/cub3d_err.log ]; then
			echo -n "     Mensaje impreso: "
			cat /tmp/cub3d_err.log
		fi
		passed_errors=$((passed_errors + 1))
	else
		# Cualquier otro código suele indicar un SegFault o un parón por AddressSanitizer
		echo -e "${RED}  -> [CRASH/ASAN] ¡ALERTA! El programa falló de forma no controlada (Código: $status).${NC}"
		if [ -s /tmp/cub3d_err.log ]; then
			cat /tmp/cub3d_err.log
		fi
		crashes=$((crashes + 1))
	fi
	echo "--------------------------------------------------"
done

# Limpieza del log temporal
rm -f /tmp/cub3d_err.log

# Resumen de las pruebas
echo ""
echo "=================================================="
echo "               RESUMEN DE PRUEBAS                 "
echo "=================================================="
echo -e "Total de mapas evaluados: $total"
echo -e "${GREEN}Mapas válidos completados: $passed_success${NC}"
echo -e "${GREEN}Errores de parseo controlados: $passed_errors${NC}"
if [ $crashes -gt 0 ]; then
	echo -e "${RED}Crashes / Errores críticos detectados: $crashes${NC}"
	echo -e "${RED}Revisa los mapas que han dado error no controlado para evitar fugas o SegFaults.${NC}"
else
	echo -e "${GREEN}¡Felicidades! Ningún mapa causó un crash inesperado.${NC}"
fi
echo "=================================================="