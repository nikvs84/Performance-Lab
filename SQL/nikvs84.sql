-- ЭТО ЗАПРОСЫ ДЛЯ ПРОСМОТРА ТАБЛИЦ. К ЗАДАНИЮ НЕ ОТНОСЯТСЯ.
SELECT * FROM SH.CUSTOMERS;
SELECT * FROM SH.COUNTRIES;
SELECT * FROM SH.SALES;
SELECT * FROM SH.PRODUCTS;

-- 1
/*Где критерий бедности? Пусть это будет 2000*/
SELECT CUS.CUST_FIRST_NAME, CUS.CUST_LAST_NAME 
	FROM SH.CUSTOMERS CUS 
		INNER JOIN SH.COUNTRIES COU ON CUS.COUNTRY_ID = COU.COUNTRY_ID
	WHERE 
		COU.COUNTRY_NAME NOT IN ('Italy', 'Japan', 'Brazil') 
		AND CUS.CUST_GENDER = 'F'
		AND CUS.CUST_MARITAL_STATUS = 'married'
		AND CUS.CUST_CREDIT_LIMIT < 2000
;

/*Выведем топ-10 бедноты*/
SELECT C_NAME, C_LAST_NAME FROM
	(
		SELECT ROW_NUMBER() OVER(ORDER BY CUS.CUST_CREDIT_LIMIT) RATING, CUS.CUST_FIRST_NAME C_NAME, CUS.CUST_LAST_NAME C_LAST_NAME FROM SH.CUSTOMERS CUS INNER JOIN SH.COUNTRIES COU ON CUS.COUNTRY_ID = COU.COUNTRY_ID
			WHERE 
				COU.COUNTRY_NAME NOT IN ('Italy', 'Japan', 'Brazil') 
				AND CUS.CUST_GENDER = 'F'
				AND CUS.CUST_MARITAL_STATUS = 'married'
	)
	WHERE RATING < 11
;

-- 2

SELECT 'Name ' || F_NAME || ' ' || L_NAME || '; city ' || C_CITY || '; address: ' || C_ADDRESS || '; number: ' || C_PHONE || '; email: ' || C_EMAIL AS "INFO" FROM
	(
		SELECT ROW_NUMBER() OVER(ORDER BY LENGTH(CUS.CUST_STREET_ADDRESS) DESC) RATING, CUS.CUST_FIRST_NAME F_NAME, CUS.CUST_LAST_NAME L_NAME, CUS.CUST_CITY C_CITY, CUS.CUST_STREET_ADDRESS C_ADDRESS, CUS.CUST_MAIN_PHONE_NUMBER C_PHONE, CUS.CUST_EMAIL C_EMAIL FROM SH.CUSTOMERS CUS
			WHERE 
				CUS.CUST_MAIN_PHONE_NUMBER LIKE '%77'
	)
	WHERE RATING = 1
;

-- 3
WITH TEMP AS 
(
    SELECT CUS.CUST_FIRST_NAME C_NAME, CUS.CUST_LAST_NAME L_NAME, CUS.CUST_YEAR_OF_BIRTH C_YOB, PROD.PROD_CATEGORY P_CAT, PROD.PROD_LIST_PRICE P_PRICE
		FROM SH.CUSTOMERS CUS 
			INNER JOIN SH.SALES SAL ON CUS.CUST_ID = SAL.CUST_ID 
			INNER JOIN SH.PRODUCTS PROD ON SAL.PROD_ID = PROD.PROD_ID 
		WHERE PROD.PROD_CATEGORY IN ('Women', 'Girls')
) 
SELECT C_NAME, L_NAME FROM TEMP 
	WHERE P_PRICE = (SELECT MIN(P_PRICE) FROM TEMP)
    AND C_YOB > 1980
;

-- 4
SELECT * FROM SH.CUSTOMERS CUS
	WHERE CUS.CUST_GENDER = 'M'
    /*AND CUS.CUST_MARITAL_STATUS IS NULL*/
    AND NOT EXISTS 
        (
            SELECT * FROM SH.CUSTOMERS IN_CUS 
            WHERE IN_CUS.CUST_ID = CUS.CUST_ID 
            AND IN_CUS.CUST_MARITAL_STATUS IS NOT NULL
        )
    AND CUS.CUST_INCOME_LEVEL = 'D: 70,000 - 89,999'
    AND CUS.COUNTRY_ID IN 
        (
            SELECT COU.COUNTRY_ID FROM SH.COUNTRIES COU
            WHERE COU.COUNTRY_NAME IN ('Germany', 'USA')
        )
/*ORDER BY CUS.CUST_ID*/
;
/*Если не использовать EXISTS, то можно так:*/
SELECT * FROM SH.CUSTOMERS CUS
WHERE CUS.CUST_GENDER = 'M'

    AND CUS.CUST_MARITAL_STATUS IS NULL
    
    AND CUS.CUST_INCOME_LEVEL = 'D: 70,000 - 89,999'
    AND CUS.COUNTRY_ID IN 
        (
            SELECT COU.COUNTRY_ID FROM SH.COUNTRIES COU
            WHERE COU.COUNTRY_NAME IN ('Germany', 'USA')
        )
/*ORDER BY CUS.CUST_ID*/
;

-- 5
SELECT COUN.COUNTRY_NAME COUNTRY, AVG(SAL.AMOUNT_SOLD) AVG_SUMM
    FROM SH.CUSTOMERS CUS 
        INNER JOIN SH.SALES SAL ON CUS.CUST_ID = SAL.CUST_ID 
        INNER JOIN SH.PRODUCTS PROD ON SAL.PROD_ID = PROD.PROD_ID
        INNER JOIN SH.COUNTRIES COUN ON CUS.COUNTRY_ID = COUN.COUNTRY_ID
    GROUP BY COUN.COUNTRY_NAME
    ORDER BY AVG_SUMM DESC
;

-- 6
WITH DOMAINS AS
(
    SELECT DISTINCT SUBSTR(CUS.CUST_EMAIL, INSTR(CUS.CUST_EMAIL, '@') + 1 ) DOMAIN FROM SH.CUSTOMERS CUS
)

SELECT DOMAIN, COUNT(*) D_USERS
    FROM SH.CUSTOMERS CUS 
        INNER JOIN DOMAINS DOM ON CUS.CUST_EMAIL LIKE '%'|| DOM.DOMAIN 
    GROUP BY DOMAIN
    ORDER BY D_USERS DESC
;

-- 7
WITH COUN_2 AS 
(
    SELECT COUN.COUNTRY_NAME COUNTRY, COUNT(*) COUNT
        FROM SH.CUSTOMERS CUS 
        INNER JOIN SH.SALES SAL ON CUS.CUST_ID = SAL.CUST_ID 
        INNER JOIN SH.COUNTRIES COUN ON CUS.COUNTRY_ID = COUN.COUNTRY_ID
    GROUP BY COUN.COUNTRY_NAME
)

SELECT COUN.COUNTRY_NAME COUNTRY, COUNT(*)
    FROM SH.CUSTOMERS CUS 
        INNER JOIN SH.SALES SAL ON CUS.CUST_ID = SAL.CUST_ID 
        INNER JOIN SH.PRODUCTS PROD ON SAL.PROD_ID = PROD.PROD_ID
        INNER JOIN SH.COUNTRIES COUN ON CUS.COUNTRY_ID = COUN.COUNTRY_ID
    WHERE PROD.PROD_CATEGORY = 'Men'
    GROUP BY COUN.COUNTRY_NAME
    HAVING COUNT(*) > (SELECT AVG(COUNT) FROM COUN_2)  
;

-- 8
WITH STAT_CUST AS 
    (
        SELECT COU.COUNTRY_ID C_ID, 
            ROUND((SELECT COUNT(*) FROM SH.CUSTOMERS CUS WHERE CUS.COUNTRY_ID = COU.COUNTRY_ID AND CUS.CUST_GENDER = 'M' )/COUNT(*) * 100) "P_M"/*,
           ROUND((SELECT COUNT(*) FROM SH.CUSTOMERS CUS WHERE CUS.COUNTRY_ID = COU.COUNTRY_ID AND CUS.CUST_GENDER = 'F' )/COUNT(*) * 100) "P_F"*/
            FROM SH.CUSTOMERS COU
            GROUP BY COU.COUNTRY_ID
    )
SELECT COU.COUNTRY_NAME "Страна", S_C.P_M "% мужчин", (100 - S_C.P_M) "% женщин" 
    FROM STAT_CUST S_C
        INNER JOIN SH.COUNTRIES COU
            ON S_C.C_ID = COU.COUNTRY_ID
    ORDER BY COU.COUNTRY_NAME
;

-- 9
WITH STAT_SALES AS
    (
        SELECT S.TIME_ID S_DATE, S.PROD_ID S_PID, COUNT(S.PROD_ID) S_COUNT 
            FROM SH.SALES S 
            GROUP BY S.TIME_ID, S.PROD_ID
    )
SELECT P_COUNT "Макс покуп/день", P_NAME "prod_name" 
    FROM
        (
            SELECT ROW_NUMBER() OVER(ORDER BY P_COUNT DESC) P_NUM, P_NAME, P_COUNT 
                FROM 
                    (
                        SELECT PROD.PROD_NAME P_NAME, MAX(S_S.S_COUNT) P_COUNT
                            FROM STAT_SALES S_S
                                INNER JOIN SH.PRODUCTS PROD
                                    ON S_S.S_PID = PROD.PROD_ID
                           GROUP BY PROD.PROD_NAME
                    )
        )
    WHERE P_NUM < 21
;

-- 10
WITH STAT_SALES AS
    (
        SELECT S.TIME_ID S_DATE, COUNT(S.PROD_ID) S_COUNT, (SELECT PR1.PROD_CATEGORY FROM SH.PRODUCTS PR1 WHERE PR1.PROD_ID = S.PROD_ID ) P_CAT
            FROM SH.SALES S
            GROUP BY S.TIME_ID, S.PROD_ID
    )

SELECT MAX_COUNT "Макс покуп/день", P_CAT "prod_category" 
    FROM
        (
            SELECT ROW_NUMBER() OVER (ORDER BY MAX_COUNT DESC) CAT_NUM, P_CAT, MAX_COUNT 
                FROM
                    (
                        SELECT P_CAT, MAX(S_COUNT) MAX_COUNT 
                            FROM STAT_SALES
                            GROUP BY P_CAT
                    )

        )
    WHERE CAT_NUM < 21
;

-- 11
/*
Здесь есть повторяющийся подзапрос. С использованием временной таблицы (WITH xxx AS) 
или представления (CREATE VIEW) выборка выполняется быстрее.
Наверное, можно было сделать проще и правильнее, но времени мало

Например, так работает процентов на 30 быстрее:

CREATE OR REPLACE VIEW SH.USER5_TEMP AS
    (
        SELECT TRUNC(S.TIME_ID, 'MM' ) R_DATE, SUM(S.QUANTITY_SOLD ) S_SUM
            FROM SH.SALES S
            GROUP BY TRUNC(S.TIME_ID, 'MM' )
    )
;

CREATE TABLE SH.SALES_User5_Nikolai_Semenyuk AS
    (
        SELECT * 
            FROM SH.SALES S
            WHERE TRUNC(S.TIME_ID, 'MM') = 
                (
                    SELECT R_DATE
                        FROM SH.USER5_TEMP
                        WHERE S_SUM = 
                            (
                                SELECT MAX(S_SUM) FROM SH.USER5_TEMP
                            )
                )
    )
;

DROP VIEW SH.USER5_TEMP;
*/
CREATE TABLE SH.SALES_User5_Nikolai_Semenyuk AS
    (
        SELECT * 
            FROM SH.SALES S
            WHERE TRUNC(S.TIME_ID, 'MM') = 
                (
                    SELECT R_DATE
                        FROM 
                            (
                                SELECT TRUNC(S.TIME_ID, 'MM' ) R_DATE, SUM(S.QUANTITY_SOLD ) S_SUM
                                    FROM SH.SALES S
                                    GROUP BY TRUNC(S.TIME_ID, 'MM' )
                            )
                        WHERE S_SUM = 
                            (
                                SELECT MAX(S_SUM) FROM 
                                    (
                                        SELECT TRUNC(S.TIME_ID, 'MM' ) R_DATE, SUM(S.QUANTITY_SOLD ) S_SUM
                                            FROM SH.SALES S
                                            GROUP BY TRUNC(S.TIME_ID, 'MM' )
                                    )
                        
                            )
                )
    )
;

