-- =============================================================================
--  FIX POINTAGE DÉPART RFID
--  Exécuter dans SQL Developer (F5) connecté en tant que HICHEM
--  
--  PROBLÈME : La contrainte EMPLOYES_CHK4 bloque l'UPDATE de HEURE_DEPART
--  car elle fait heure_depart > heure_arrivee sur des VARCHAR2 et peut
--  rejeter des valeurs valides selon le contexte.
-- =============================================================================

ALTER SESSION SET CURRENT_SCHEMA = HICHEM;

-- =============================================================================
-- ÉTAPE 1 : Désactiver puis supprimer la contrainte CHK4 problématique
-- =============================================================================
-- Cette contrainte fait : CHECK (heure_depart > heure_arrivee)
-- sur des colonnes VARCHAR2. Elle bloque silencieusement l'UPDATE départ.

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE HICHEM.EMPLOYES DISABLE CONSTRAINT EMPLOYES_CHK4';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -2430 THEN NULL; END IF; -- déjà désactivée
END;
/

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE HICHEM.EMPLOYES DROP CONSTRAINT EMPLOYES_CHK4';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -2443 THEN NULL; END IF; -- n'existe pas
END;
/

-- =============================================================================
-- ÉTAPE 2 : Recréer la contrainte UNIQUEMENT sur NULL (logique correcte)
-- La contrainte ne s'applique que si HEURE_DEPART est renseigné
-- On recrée une version plus permissive qui accepte NULL (départ non pointé)
-- =============================================================================
ALTER TABLE HICHEM.EMPLOYES 
ADD CONSTRAINT EMPLOYES_CHK4 
CHECK (
    HEURE_DEPART IS NULL 
    OR HEURE_ARRIVEE IS NULL 
    OR HEURE_DEPART > HEURE_ARRIVEE
) ENABLE;

-- =============================================================================
-- ÉTAPE 3 : Vérifier que la colonne UID_CARTE existe bien
-- =============================================================================
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
-- ÉTAPE 4 : Vérification — Si tout est OK, vous verrez vos employés ici
-- =============================================================================
SELECT ID_EMPLOYE, NOM, PRENOM, UID_CARTE,
       DATE_POINTAGE, HEURE_ARRIVEE, HEURE_DEPART, STATUT_JOURNALIER
FROM HICHEM.EMPLOYES
ORDER BY ID_EMPLOYE;

-- =============================================================================
-- ÉTAPE 5 : Assigner les UIDs de cartes RFID à vos employés
-- (Remplacez 'XXXXXXXX' par les UIDs lus sur le moniteur série Arduino)
-- =============================================================================
-- UPDATE HICHEM.EMPLOYES SET UID_CARTE = 'A1B2C3D4' WHERE ID_EMPLOYE = 1;
-- UPDATE HICHEM.EMPLOYES SET UID_CARTE = 'B2C3D4E5' WHERE ID_EMPLOYE = 7;
-- UPDATE HICHEM.EMPLOYES SET UID_CARTE = 'C3D4E5F6' WHERE ID_EMPLOYE = 8;
-- COMMIT;
