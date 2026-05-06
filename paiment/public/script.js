const form = document.getElementById("paymentForm");
const labNameInput = document.getElementById("labName");
const responsableInput = document.getElementById("responsable");
const phoneInput = document.getElementById("phone");
const montantTotalInput = document.getElementById("montantTotal");
const montantPayeInput = document.getElementById("montantPaye");
const resteInput = document.getElementById("reste");
const cardNumberInput = document.getElementById("cardNumber");
const expiryInput = document.getElementById("expiry");
const result = document.getElementById("result");

function prefillFromQueryParams() {
  const params = new URLSearchParams(window.location.search);
  labNameInput.value = params.get("labName") || "";
  responsableInput.value = params.get("responsable") || "";
  phoneInput.value = params.get("phone") || "";
  montantTotalInput.value = params.get("montantTotal") || "";
  montantPayeInput.value = params.get("montantPaye") || "";
  const reste = params.get("reste");
  if (reste) {
    resteInput.value = Number(reste).toFixed(2);
  } else {
    calculateReste();
  }
}

function sanitizeCardNumber(value) {
  const numbersOnly = value.replace(/\D/g, "").slice(0, 16);
  return numbersOnly.replace(/(\d{4})(?=\d)/g, "$1 ");
}

function calculateReste() {
  const total = parseFloat(montantTotalInput.value) || 0;
  const paye = parseFloat(montantPayeInput.value) || 0;
  const reste = Math.max(total - paye, 0);
  resteInput.value = reste.toFixed(2);
}

montantTotalInput.addEventListener("input", calculateReste);
montantPayeInput.addEventListener("input", calculateReste);

cardNumberInput.addEventListener("input", () => {
  cardNumberInput.value = sanitizeCardNumber(cardNumberInput.value);
});

expiryInput.addEventListener("input", () => {
  let raw = expiryInput.value.replace(/\D/g, "").slice(0, 4);
  if (raw.length >= 3) {
    raw = `${raw.slice(0, 2)}/${raw.slice(2)}`;
  }
  expiryInput.value = raw;
});

form.addEventListener("submit", (event) => {
  event.preventDefault();
  calculateReste();

  const cardDigits = cardNumberInput.value.replace(/\s/g, "");
  if (cardDigits.length !== 16) {
    result.textContent = "Numero de carte invalide. Entrez 16 chiffres.";
    result.style.color = "#dc2626";
    return;
  }

  if (!/^\d{2}\/\d{2}$/.test(expiryInput.value)) {
    result.textContent = "Date d'expiration invalide. Format attendu MM/AA.";
    result.style.color = "#dc2626";
    return;
  }

  result.textContent = "Paiement enregistre avec succes.";
  result.style.color = "#16a34a";
});

prefillFromQueryParams();
