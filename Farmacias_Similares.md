# Farmacias de Similares S.A. de C.V.

## 1. Identificación de la Entidad
| Atributo | Detalle |
| :--- | :--- |
| **Razón Social** | Farmacias de Similares S.A. de C.V. |
| **RFC** | FSI970908ML5 |
| **Grupo Perteneciente** | Grupo Por Un País Mejor (GPUPM) |
| **Sede Fiscal** | Alemania 10, Col. Independencia, Benito Juárez, CDMX, C.P. 03630 |
| **Contacto Principal** | (55) 5422-4500 |
| **Atención al Cliente** | SIMITEL: 800 911 6666 |

---

## 2. Infraestructura Digital y Presencia en Web
La arquitectura está diseñada para soportar alta disponibilidad y picos de tráfico masivos, delegando la capa de entrega a servicios de nube escalables.

### A. Capa de E-commerce y Aplicación
* **Plataforma Base:** **VTEX** (SaaS de comercio electrónico).
* **Frontend:** Desarrollado sobre la librería **React**, optimizando la interactividad del lado del cliente.
* **Backend / Server-side:** Interacción con entornos **ASP.NET** y servidores **Nginx 1.26.2**.
* **Gestión de Assets:** Utilizan `farmaciassimilaresmx.vtexassets.com` a través de AWS CloudFront.

### B. Hosting y Red (Networking)
* **Proveedor de Infraestructura (Cloud):** Amazon Web Services (AWS).
* **CDN y Seguridad:** **Amazon CloudFront** (Proxy inverso para mitigación de latencia y protección).
* **Resolución de Nombres:** Amazon DNS.
* **Dominio:** Registrado en **GoDaddy** (con privacidad activada vía Domains By Proxy, LLC).
* **Nameservers Propios:**
    * `ns1.drsimi.com`
    * `ns2.drsimi.com`
    * `ns3.drsimi.com`

### Red Propia (AS28421)
* **Bloque IP:** `200.34.206.0/24` (256 direcciones IP).
* **IP Principal de Consulta:** `200.34.206.111`
* **Proveedores de Internet (Upstreams):**
    * AS8151 - UNINET (Telmex)
    * AS18734 - Operbes, S.A. de C.V. (Bestel)
* **Responsable ante LACNIC:** Roger Jimenez.
* **Contacto de Abuso:** `asanchezm@fsimilares.com`.

---

## 3. Servicios y Endpoints Específicos
| Servicio | Endpoint / Detalles |
| :--- | :--- |
| **Servidor de Correo** | `mail.farmaciasdesimilares.com` (IPs: .79, .104, .77) |
| **Facturación Electrónica** | `facturacfd.farmaciasdesimilares.com.mx:82` (Puerto no estándar) |
| **Recursos Humanos** | **SAP SuccessFactors** (`career19.sapsf.com`) |
| **Contenedores/Orquestación** | AWS EKS (Elastic Kubernetes Service) en la zona `us-east-1c` |
| **Marketing / Analítica** | Google Analytics, Google Tag Manager, Facebook Connect |

---

## 4. Estructura Organizacional y Liderazgo
* **Vicepresidencia Administrativa:** Óscar de la Sierra Arámburo.
* **Representación Legal:** Luis Francisco Martínez Guerra.
* **Estrategia de Salud:** Dra. María del Carmen Villafaña Peralta.
* **Liderazgo Ejecutivo:** Lic. Víctor Araujo Domínguez.

### Empresas del Ecosistema Logístico
1. **Laboratorios Best:** Fabricación de medicamentos genéricos.
2. **Transportes Farmacéuticos Similares:** Distribución nacional.

---

## 5. Seguridad
* **Puerto 80 (HTTP):** Abierto (Nginx).
* **Puerto 443 (HTTPS):** Abierto (TLS 1.3 activo).
* **Puerto 82:** Identificado para el sistema de facturación.
