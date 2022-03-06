-- Keep a log of any SQL queries you execute as you solve the mystery.

-- View Crime Scene report and link to interviews
SELECT *
    FROM crime_scene_reports AS c
  WHERE c.month = 7
    AND c.day = 28
    AND c.year = 2021
    AND c.street = "Humphrey Street";

-- Search for interviews on the same day
SELECT *
    FROM interviews AS i
  WHERE i.month = 7
    AND i.day = 28
    AND i.year = 2021;


-- Filter based on witness testiomnies
SELECT name
    FROM people AS p

  -- Cross check with license plates spotted at the bakery
  WHERE p.license_plate IN
  (
    SELECT license_plate
        FROM bakery_security_logs AS b
    WHERE hour = 10
        AND minute >= 15 AND minute <= 25
        AND activity = "exit"
  )

  -- Cross check with ATM records
  AND p.id IN
  (
      SELECT person_id
        FROM bank_accounts AS b
      JOIN atm_transactions ON atm_transactions.account_number = b.account_number
        WHERE month = 7 AND day = 28 AND year = 2021 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"
  )

  -- Outbound flights
  AND p.passport_number IN
  (
      SELECT passport_number
        FROM passengers AS pass
      WHERE flight_id IN
      (
          SELECT id
            FROM flights
          WHERE month = 7 AND day = 29 AND year = 2021 ORDER BY hour, minute ASC LIMIT 1
      )
  )

  --Query phone calls
  AND p.phone_number IN
  (
      SELECT caller
        FROM phone_calls AS ph
      WHERE duration < 60 AND month = 7 AND day = 28 AND year = 2021
  );

-- Find Accompliace
SELECT name, phone_number
    FROM people
  WHERE people.phone_number IN
  (
    SELECT receiver
      FROM phone_calls AS ph
    WHERE ph.duration <= 60
      AND ph.month = 7
      AND ph.day = 28
      AND ph.year = 2021
      AND caller = (
          SELECT phone_number FROM people WHERE name = "Bruce"
      )
  );

  -- Search for destination city
SELECT city
    FROM airports
  WHERE id IN
  (
    SELECT destination_airport_id FROM flights
    ORDER BY hour, minute DESC LIMIT 1
  );
