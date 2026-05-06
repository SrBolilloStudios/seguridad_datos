# Farmacias de Similares S.A. de C.V.

---

## Identificación Legal

| Campo | Valor |
|---|---|
| **Razón Social** | Farmacias de Similares S.A. de C.V. |
| **RFC** | FSI970908ML5 |
| **Corporativo** | Grupo Por Un País Mejor |
| **Domicilio Fiscal** | Alemania 10, Col. Independencia, Benito Juárez, CDMX, C.P. 03630 |

---

## Estructura Organizacional

| Entidad | Funcionalidad Principal | Domicilio | Teléfono |
|---|---|---|---|
| Farmacias de Similares S.A. de C.V. | Sede Fiscal y Ejecutiva | Alemania 10, Col. Independencia, Benito Juárez, CDMX, C.P. 03630 | (0155) 5422-4500 |
| Grupo Por Un País Mejor | Corporativo / Fundaciones | Alemania 10, Col. Independencia, Benito Juárez, CDMX, C.P. 03630 | +52 55 5539 9171 |
| SIMITEL (Atención al Cliente) | Interacción Minorista (B2C) | Operación Descentralizada | 800 911 6666 |

### Personas Clave

- **Óscar de la Sierra Arámburo** — Vicepresidente Administrativo
- **Luis Francisco Martínez Guerra** — Representante Legal y Apoderado
- **Dra. María del Carmen Villafaña Peralta** — Vicepresidenta de Salud; responsable de asegurar que las estrategias comerciales se alineen con criterios sanitarios
- **Lic. Víctor Araujo Domínguez** — Área jurídica / representación legal

### Subsidiarias y Unidades de Negocio

- **Laboratorios Best** — Fabricación de medicamentos genéricos
- **Transportes Farmacéuticos Similares** — Logística y distribución para más de 10,000 puntos de venta a nivel nacional

---

## Infraestructura de Red

### Direccionamiento IP y ASN

| Parámetro | Valor |
|---|---|
| **IP Principal** | `200.34.206.111` |
| **Rango propio** | `200.34.206.0/24` (256 direcciones IP públicas) |
| **IPs adicionales** | `200.34.206.79`, `200.34.206.104`, `200.34.206.77` |
| **ASN** | AS28421 |

### Conectividad (Upstreams)

| ASN | Proveedor |
|---|---|
| AS8151 | UNINET (Telmex) |
| AS18734 | Operbes, S.A. de C.V. (Bestel) |

### Registro en LACNIC

| Campo | Valor |
|---|---|
| **Responsable** | Roger Jimenez |
| **Contacto** | asanchezm@fsimilares.com |
| **Teléfono** | +52 5554220157 |

### Puertos y Servicios Expuestos

| Puerto | Estado | Servicio |
|---|---|---|
| `80/tcp` | Abierto | HTTP — **nginx 1.26.2** |
| `443/tcp` | Abierto | HTTPS — **nginx 1.26.2** + TLS 1.3 |
| `82/tcp` | Abierto | Sistema CFD / Facturación Electrónica (`facturacfd.farmaciasdesimilares.com.mx:82`) |

---

## DNS y Dominios

### Registrador y Privacidad

| Campo | Valor |
|---|---|
| **Registrador** | GoDaddy |
| **Privacidad WHOIS** | Domains By Proxy, LLC (privacidad activa — datos del titular ocultos) |

### Nameservers Propios

```
ns1.drsimi.com
ns2.drsimi.com
ns3.drsimi.com
```

> El sufijo `drsimi` hace referencia a la mascota corporativa **Dr. Simi**.

### Subdominios y Hosts Relevantes

| Host | Función |
|---|---|
| `mail.farmaciasdesimilares.com` | Servidor de correo propio (MX prioridad 10) |
| `facturacfd.farmaciasdesimilares.com.mx:82` | Sistema de facturación electrónica CFD (puerto no estándar) |
| `farmaciassimilaresmx.vtexassets.com` | CDN de assets estáticos (AWS CloudFront, región Reino Unido) |
| `career19.sapsf.com` | Portal de RRHH — SAP SuccessFactors |
| `portalfranq.com.mx` | Probable portal del programa de franquicias (alojado en el bloque /24) |

### Dominios Alojados

Según IPinfo.io, el bloque `200.34.206.0/24` aloja al menos **77 dominios**.

---

## Plataforma E-commerce y Stack Tecnológico

### E-commerce

| Capa | Tecnología |
|---|---|
| **Plataforma** | VTEX |
| **CDN / Proxy inverso** | Amazon CloudFront (AWS) |
| **DNS** | Amazon Route 53 |
| **Contenedor backend** | AWS EKS — nodo `prod-dj-iostore-eks-use1c-r3n` (us-east-1c) |

### Componentes VTEX (versiones detectadas)

```
vtex.render-runtime     @ 8.136.2
vtex.styleguide         @ 9.146.16
vtex.login              @ 2.70.0
vtex.minicart           @ 2.68.0
```

### Backend / Servidor

| Tecnología | Detalle |
|---|---|
| **Servidor web** | nginx 1.26.2 |
| **Framework servidor** | ASP.NET |
| **TLS** | TLS 1.3 |

### Frontend

| Tecnología | Rol |
|---|---|
| **JavaScript** | Lenguaje principal del cliente |
| **React** | Librería de interfaces de usuario |

### Analytics y Marketing

| Herramienta | Propósito |
|---|---|
| Google Analytics | Métricas de tráfico y conversión |
| Google Tag Manager | Gestión de etiquetas y eventos |
| Facebook Connect | Integración social / login |

### Recursos Humanos

| Sistema | URL / Detalle |
|---|---|
| SAP SuccessFactors | `career19.sapsf.com` — portal de candidatos y gestión de talento |

---

## Notas de Reconocimiento

- La empresa opera su propio bloque de IPs (`/24`), DNS (`drsimi.com`) y servidor de correo, indicando una infraestructura on-premise complementaria a la nube.
- El nodo EKS `us-east-1c` sugiere que la carga de e-commerce se procesa principalmente en la región **US East (N. Virginia)** de AWS.
- El puerto 82 expuesto para facturación CFD es un servicio legado de facturación electrónica según la normativa del SAT México.
- La privacidad WHOIS vía Domains By Proxy oculta los datos del registrante público del dominio principal.
