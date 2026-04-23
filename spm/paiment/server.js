const http = require("http");
const fs = require("fs");
const path = require("path");

const port = 3000;
const baseDir = path.join(__dirname, "public");

const mimeTypes = {
  ".html": "text/html; charset=utf-8",
  ".css": "text/css; charset=utf-8",
  ".js": "application/javascript; charset=utf-8",
  ".json": "application/json; charset=utf-8"
};

const server = http.createServer((req, res) => {
  const rawUrl = req.url || "/";
  const parsedUrl = new URL(rawUrl, `http://${req.headers.host || "localhost"}`);
  let urlPath = parsedUrl.pathname || "/";
  let forcedQuery = "";

  // Some QR scanners send an encoded query inside the pathname
  // (/index.html%3FlabName=...) or double-encoded (%253F).
  const lowerRaw = rawUrl.toLowerCase();
  let markerIndex = lowerRaw.indexOf("%3f");
  let markerLength = 3;
  if (markerIndex === -1) {
    markerIndex = lowerRaw.indexOf("%253f");
    markerLength = 5;
  }
  if (markerIndex !== -1) {
    const rawPathOnly = rawUrl.slice(0, markerIndex);
    const rawQueryOnly = rawUrl.slice(markerIndex + markerLength);
    urlPath = rawPathOnly.split("?")[0] || "/index.html";
    forcedQuery = rawQueryOnly.replace(/^[/?&]+/, "");
  }

  try {
    urlPath = decodeURIComponent(urlPath);
  } catch (_) {
    // Keep original value when decoding fails.
  }

  if (urlPath === "/") {
    urlPath = "/index.html";
  } else if (urlPath.endsWith("/")) {
    urlPath = urlPath.slice(0, -1);
  }

  if (urlPath === "/index.html") {
    // Keep explicit mapping for QR links like /index.html/?...
    urlPath = "/index.html";
  }

  if (forcedQuery) {
    const location = `/?${forcedQuery}`;
    res.writeHead(302, { Location: location });
    res.end();
    return;
  }

  const safePath = path.normalize(urlPath).replace(/^(\.\.[/\\])+/, "");
  const filePath = path.join(baseDir, safePath);

  if (!filePath.startsWith(baseDir)) {
    res.writeHead(403, { "Content-Type": "text/plain; charset=utf-8" });
    res.end("Acces refuse");
    return;
  }

  fs.readFile(filePath, (err, data) => {
    if (err) {
      // Fallback to index for URLs that should open the payment page.
      const fallbackPath = path.join(baseDir, "index.html");
      fs.readFile(fallbackPath, (fallbackErr, fallbackData) => {
        if (fallbackErr) {
          res.writeHead(404, { "Content-Type": "text/plain; charset=utf-8" });
          res.end("Page non trouvee");
          return;
        }
        res.writeHead(200, { "Content-Type": "text/html; charset=utf-8" });
        res.end(fallbackData);
      });
      return;
    }

    const ext = path.extname(filePath).toLowerCase();
    res.writeHead(200, { "Content-Type": mimeTypes[ext] || "application/octet-stream" });
    res.end(data);
  });
});

server.listen(port, () => {
  console.log(`Site de paiement disponible sur http://localhost:${port}`);
});
