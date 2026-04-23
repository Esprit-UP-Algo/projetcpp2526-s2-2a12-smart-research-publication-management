-- =============================================================================
-- INVENTORY FIX: drop LABS_RESERVATIONS* and add USE_COUNT on PRODUCT
-- =============================================================================
-- IMPORTANT:
-- 1) This file lives in your PROJECT folder. Open it FROM HERE in SQL Developer
--    (File > Open). Do NOT put this inside the SQL Developer install folder —
--    that folder is only the program; it does not store your database tables.
-- 2) Connect in SQL Developer as the SAME user that OWNS your tables.
--    Your export uses schema HICHEM. If your owner is different, replace HICHEM
--    everywhere below (Ctrl+H).
-- 3) Run the whole script (F5 or Run Script). Then right-click "Tables" > Refresh.
-- =============================================================================

ALTER SESSION SET CURRENT_SCHEMA = HICHEM;

-- Drop any variant of the extra reservation table (ignore ORA-00942 if missing)
BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE HICHEM.LABS_RESERVATIONS CASCADE CONSTRAINTS';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -942 THEN RAISE; END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE HICHEM.LABS_RESERVATION CASCADE CONSTRAINTS';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -942 THEN RAISE; END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE HICHEM.LABS_RESERVATIOS CASCADE CONSTRAINTS';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -942 THEN RAISE; END IF;
END;
/

-- Add USE_COUNT on PRODUCT (ignore ORA-01430 if column already exists)
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE HICHEM.PRODUCT ADD (USE_COUNT NUMBER DEFAULT 0)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE != -1430 THEN RAISE; END IF;
END;
/

UPDATE HICHEM.PRODUCT
SET USE_COUNT = NVL(QT_RS, 0)
WHERE USE_COUNT IS NULL OR USE_COUNT = 0;

COMMIT;

-- Optional: verify
-- SELECT table_name FROM all_tables WHERE owner = 'HICHEM' AND table_name LIKE 'LABS_RESERV%';
-- DESC HICHEM.PRODUCT;
