-- =============================================================================
--  ARDUINO RFID - POINTAGE LABO
--  Exécuter dans SQL Developer (F5)  —  Connecté en tant que HICHEM
--
--  Seul ajout nécessaire : une colonne UID_CARTE dans EMPLOYES.
--  Aucune nouvelle table créée.
-- =============================================================================

ALTER SESSION SET CURRENT_SCHEMA = HICHEM;

-- Ajouter la colonne UID_CARTE dans EMPLOYES
-- (stocke l'UID hexadécimal de la carte RFID de l'employé)
BEGIN
    EXECUTE IMMEDIATE
        'ALTER TABLE HICHEM.EMPLOYES ADD (UID_CARTE VARCHAR2(20))';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -1430 THEN RAISE; END IF; -- -1430 = colonne déjà existante
END;
/

COMMIT;

-- =============================================================================
--  Après avoir trouvé l'UID avec le moniteur série Arduino, assigner les cartes
-- =============================================================================
-- UPDATE HICHEM.EMPLOYES SET UID_CARTE = 'A1B2C3D4' WHERE ID_EMPLOYE = 1;
-- UPDATE HICHEM.EMPLOYES SET UID_CARTE = 'B2C3D4E5' WHERE ID_EMPLOYE = 2;
-- COMMIT;

-- Vérification
-- SELECT ID_EMPLOYE, NOM, PRENOM, UID_CARTE FROM HICHEM.EMPLOYES;
