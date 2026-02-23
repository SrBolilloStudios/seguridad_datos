Javier Cruz Uc

[Concepto de seguridad de datos](seguridad_datos.md)

---

## Índice
1. [Fundamentos de Seguridad (19 Ene)](#-19-de-enero-fundamentos-de-seguridad)
2. [Protocolos y Escaneo de Red (21 Ene)](#-21-de-enero-protocolos-y-escaneo-de-red)
3. [Amenazas, Frameworks y Perfiles (26 Ene)](#-26-de-enero-amenazas-frameworks-y-perfiles)
4. [Vulnerabilidades y Pentesting (28 Ene)](#-28-de-enero-vulnerabilidades-y-pentesting)
5. [Ingeniería Social y Criptografía (04 Feb)](#-04-de-febrero-ingeniería-social-y-criptografía)
6. [Investigación: Gestión de Riesgos y Controles](#-actividad-997-investigación-de-conceptos-críticos)

---

## 19 de Enero: Fundamentos de Seguridad

### Conceptos Base: La Triada CIA
El núcleo de la seguridad de la información se basa en tres principios fundamentales:
* **Confidencialidad:** Garantizar que solo las personas autorizadas tengan acceso a la información.
* **Integridad:** Asegurar que la información no sea alterada de forma no autorizada.
* **Disponibilidad:** Mantener los sistemas operativos y accesibles cuando se requieran.



### El Modelo AAA
Define el proceso de gestión de acceso:
* **Authentication (Autenticación):** Confirmar la identidad del usuario (¿Quién eres?).
* **Authorization (Autorización):** Determinar los permisos otorgados (¿Qué puedes hacer?).
* **Accountability (Rendición de cuentas):** Registro y auditoría de las acciones realizadas (¿Qué hiciste?).

### Capas de Red y Direccionamiento
Se analizaron las capas críticas del Modelo OSI relacionadas con la seguridad técnica:
* **Capa 4 - Transporte:** Gestión de puertos. Existen un total de $2^{16} = 65,536$ puertos disponibles para el tráfico de aplicaciones.
* **Capa 3 - Red:** Identificación lógica mediante direcciones IP para el viaje de paquetes entre redes.
* **Capa 2 - Enlace de Datos:** Comunicación directa entre dispositivos basada en la **Dirección MAC**.
    * *Estructura MAC (AA:BB:CC:DD:EE:FF):* Los primeros tres pares identifican al **Fabricante (Vendor)** y los restantes al **Objeto (OID)**.
* **Capa 1 - Física:** El nivel de hardware donde reside la identidad física grabada en la tarjeta de red.



---

## 21 de Enero: Protocolos y Escaneo de Red

### Ataques Técnicos de Red
* **Spoofing:** Técnica de ciberdelincuencia basada en la suplantación de identidad técnica (IP o MAC).
* **Poisoning (Envenenamiento):** Ataque dirigido a corromper la tabla de direcciones MAC (MAC Address Table).
* **Protocolo 802.1X:** Relacionado con el control de acceso a la red basado en la identidad y puertos físicos.

### Auditoría de Servicios (NMAP)
Se identificaron los puertos más comunes detectados en auditorías de seguridad:

| Puerto | Protocolo | Uso Común | Seguridad |
| :--- | :--- | :--- | :--- |
| **21** | FTP | Transferencia de archivos | Inseguro (texto plano) |
| **22** | SSH | Acceso remoto seguro | Seguro (encriptado) |
| **25** | SMTP | Envío de correo electrónico | Crítico para mail-relay |
| **53** | DNS | Resolución de nombres | Objetivo frecuente de DDoS |
| **80** | HTTP | Tráfico web sin cifrar | Vulnerable a sniffing |
| **110/143**| POP3/IMAP | Recepción de correos | Requieren TLS/SSL |
| **1433** | SQLS | MS SQL Server | Objetivo de Inyección SQL |
| **3306** | MYSQL | Base de datos MySQL | Exposición de datos críticos |
| **3389** | RDP | Escritorio Remoto Windows | Frecuente ataque de fuerza bruta |

---

## 26 de Enero: Amenazas, Frameworks y Perfiles

### Definiciones Críticas
* **Troubleshooting:** Proceso sistemático para encontrar la raíz de fallas técnicas.
* **Exploit:** Fragmento de software diseñado para aprovechar una vulnerabilidad específica en un sistema.
* **NVD (National Vulnerability Database):** Repositorio oficial de EE. UU. para la gestión de datos sobre vulnerabilidades.
* **Falso Positivo:** Alerta de seguridad que identifica erróneamente una actividad benigna como amenaza.
* **Falso Negativo:** El fallo más grave; cuando un sistema de seguridad no logra detectar una amenaza real.

### Frameworks de Análisis
Se utilizan marcos de trabajo para estandarizar la defensa:
1.  **STRIDE:** Modelo de Microsoft para identificar amenazas en el diseño de software.
2.  **MITRE ATT&CK:** Base de conocimiento global sobre tácticas y técnicas de adversarios reales.

### Clasificación de Hackers
Se define al hacker como alguien capaz de hacer funcionar un sistema de formas no previstas, diferenciados por su ética y motivos:
* **White Hat:** Hackers éticos que actúan por el bien común y la protección.
* **Black Hat:** Ciberdelincuentes con fines maliciosos o lucro personal.
* **Grey Hat:** Perfil ambiguo; buscan fallos sin permiso pero suelen pedir compensación para repararlos.
* **Hacktivistas:** Motivados por causas ideológicas o políticas.
* **Suicidal Hackers:** Atacantes que no temen ser capturados durante su acción.
* **Script Kiddies (Plug and Play):** Usuarios que utilizan software de ataque sin entender su funcionamiento.

---

## 28 de Enero: Vulnerabilidades y Pentesting

### Conceptos de Explotación
* **Payload:** Datos o código enviados para aprovechar una vulnerabilidad.
* **Zero Day (Día 0):** Fallo de seguridad explotado antes de que el fabricante tenga una solución o parche.
* **Flaw:** Error o falla técnica estructural en el sistema.
* **Log4j:** Biblioteca de Java famosa por una vulnerabilidad crítica de registro que comprometió millones de servidores.
* **Shodan:** Motor de búsqueda para encontrar dispositivos IoT y servidores expuestos en Internet.

### El Ciclo del Pentest (Pruebas de Penetración)
Proceso estructurado para evaluar la seguridad de un activo:
1.  **Reconnaissance:** Reconocimiento inicial del objetivo.
2.  **Footprinting:** Recolección de información técnica detallada.
3.  **Network Mapping:** Mapeo de la red para identificar servicios activos.
4.  **Gaining Access:** Explotación efectiva para entrar al sistema.
5.  **Daisy Chaining / Covering Tracks:** Acciones para mantener el acceso y borrar huellas del ataque.



### Centros de Operación
* **SOC (Security Operations Center):** Centro dedicado exclusivamente a la vigilancia y respuesta ante incidentes de ciberseguridad.
* **NOC (Network Operations Center):** Enfocado en la gestión, rendimiento y disponibilidad de la infraestructura de red.
* **SIEM:** Herramientas que centralizan el análisis de registros (logs) para detectar anomalías.

---

## 04 de Febrero: Ingeniería Social y Criptografía

### Ingeniería Social: El Eslabón más Débil
Técnicas de manipulación psicológica para explotar la vulnerabilidad humana:
* **Phishing:** Suplantación masiva de identidades corporativas para robo de datos.
* **Spear Phishing:** Ataque personalizado y altamente dirigido a un individuo específico.
* **Whaling:** Ataque de phishing dirigido a ejecutivos de alto rango (CEO, CFO).

### Criptografía Básica
* **Cifrado César:** Método de sustitución simple por desplazamiento de caracteres.
* **Hashing:** Generación de una huella digital única e irreversible de los datos.
* **Codificación:** Cambio de formato de datos (no es secreto, solo formato).
* **Password Entropy:** Medida de la fuerza y dificultad para romper una contraseña por fuerza bruta.

---
