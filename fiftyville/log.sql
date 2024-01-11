-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query crime_scene_reports table for events that happened the day the duck robbery happened

SELECT *
FROM crime_scene_reports
WHERE crime_scene_reports.year = 2021
AND crime_scene_reports.month = 7
AND crime_scene_reports.day = 28;

-- Query interviews table for the day the robbery happened

SELECT *
FROM interviews
WHERE interviews.year = 2021
AND interviews.month = 7
AND interviews.day = 28;

-- Query bakery_security_logs for footage after the robbery

SELECT *
FROM bakery_security_logs
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28;

-- Query for ATM transactions before the time and the robbery and get names
SELECT bank_accounts.account_number, people.name
FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw";

-- QUERY for ATM transactions before the time of the robber and people who made a phone call after the robbery

SELECT bank_accounts.account_number,
        people.name,
        phone_calls.caller,
        phone_calls.duration,
        phone_calls.receiver
FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw"
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;


-- Narrow search to people who took a flight the next day

-- QUERY for ATM transactions the day and location of the robbery
SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.atm_location = "Humphrey Lane";

----- Query ATM Transactions and phone calls the day of the robbery
SELECT people.name,
        phone_calls.caller,
        receiver_name.name,
        phone_calls.receiver,
        phone_calls.duration,
        atm_transactions.transaction_type,
        atm_transactions.amount
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN people AS receiver_name ON phone_calls.receiver = receiver_name.phone_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.atm_location = "Leggett Street"
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 61;

-- Query phone calls the day of the robbery

SELECT people.name,
        receiver.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;



-- Query ATM Transactions, phone calls and license plate the day of the robbery

SELECT people.name,
        phone_calls.duration,
        bakery_security_logs.hour,
        bakery_security_logs.minute,
        bakery_security_logs.activity
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.atm_location = "Leggett Street"
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 61
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28;


-- QUERY bakery_security_logs the day of the robbery and license plate owner

SELECT people.name,
        people.license_plate,
        bakery_security_logs.activity,
        bakery_security_logs.hour,
        bakery_security_logs.minute
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.activity = "exit"
AND bakery_security_logs.hour > 9
AND bakery_security_logs.hour < 11;



-- Query for flight times on the 2021 JULY 29 flights departing from Fiftyville

SELECT flights.id,
        origin_airports.full_name AS origin_full_name,
        origin_airports.city AS origin_city,
        flights.destination_airport_id,
        destination_airports.full_name AS destination_full_name,
        flights.hour,
        flights.minute,
        destination_airports.city
FROM flights
JOIN airports AS origin_airports ON flights.origin_airport_id = origin_airports.id
JOIN airports AS destination_airports ON flights.destination_airport_id = destination_airports.id
WHERE year = 2021
AND month = 7
AND day = 29
ORDER BY hour;



-- Query list of people flying on flight id 36 on July 29 2021

SELECT people.name,
        flights.hour,
        flights.minute,
        flights.id
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
ORDER BY hour;



-- Query ATM Transactions, phone calls and license plate the day of the robbery and flight the next day

SELECT people.name,
        phone_calls.duration,
        bakery_security_logs.hour,
        bakery_security_logs.minute,
        bakery_security_logs.activity,
        flights.hour,
        flights.id,
        receiver.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.atm_location = "Leggett Street"
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 61
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29;


