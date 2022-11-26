-- Keep a log of any SQL queries you execute as you solve the mystery.

-- browsing throught the crime reports to find the relevant crime scene involving the CS50 duck:
select * from crime_scene_reports where crime_scene_reports.description like '%CS50%duck%';

-- Theft happened at 10.15 am.
-- the report id = 295 mentions 3 witnesses and their interviews. All mentioned the bakery.
-- time to find the witnesses and see their statements on 28/07/2021 mentioning the bakery:
select * from interviews where interviews.year = 2021 and interviews.month = 7 and interviews.day = 28 and interviews.transcript like "%bakery%";

    -- interview id = 161 from Ruth:
    -- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
    -- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

        -- FOLLOW UP:
        -- access bakery security logs to see licence plates that left bakery within 10 minutes of the theft:
        select bakery_security_logs.license_plate
        from bakery_security_logs
        where bakery_security_logs.year = 2021
        and bakery_security_logs.month = 7
        and bakery_security_logs.day = 28
        and bakery_security_logs.hour = 10
        and bakery_security_logs.minute >= 15
        and bakery_security_logs.minute <= 25
        and bakery_security_logs.activity = 'exit';

        -- This query returns 8 plates, which can be linked to people as follows:
        select * from people
        where license_plate in
        (
            select bakery_security_logs.license_plate
            from bakery_security_logs
            where bakery_security_logs.year = 2021
            and bakery_security_logs.month = 7
            and bakery_security_logs.day = 28
            and bakery_security_logs.hour = 10
            and bakery_security_logs.minute >= 15
            and bakery_security_logs.minute <= 25
            and bakery_security_logs.activity = 'exit'
        );

--          +--------+---------+----------------+-----------------+---------------+
--          |   id   |  name   |  phone_number  | passport_number | license_plate |
--          +--------+---------+----------------+-----------------+---------------+
--          | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
--          | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
--          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
--          | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
--          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--          | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
--          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--          +--------+---------+----------------+-----------------+---------------+


    -- interview id = 162 from Eugene:
    -- I don't know the thief's name, but it was someone I recognized.
    -- Earlier this morning, before I arrived at Emma's bakery, I was walking
    -- by the ATM on Leggett Street and saw the thief there withdrawing some money.

        -- FOLLOW UP:
        -- Eugene saw the thief withdraw some money on Leggett Street in the morning
        -- let's look at the relevant transactions:
        select * from atm_transactions
        where atm_transactions.year = 2021
        and atm_transactions.month = 7
        and atm_transactions.day = 28
        and atm_transactions.transaction_type = 'withdraw'
        and atm_transactions.atm_location = 'Leggett Street';

        -- next, we can link the accounts to people:
        select * from people
        join bank_accounts on bank_accounts.person_id = people.id
        where bank_accounts.account_number in
        (
            select atm_transactions.account_number from atm_transactions
            where atm_transactions.year = 2021
            and atm_transactions.month = 7
            and atm_transactions.day = 28
            and atm_transactions.transaction_type = 'withdraw'
            and atm_transactions.atm_location = 'Leggett Street'
        );

--          +--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          |   id   |  name   |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
--          +--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
--          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
--          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       | 458378    | 2012          |
--          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       | 395717    | 2014          |
--          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
--          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
--          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
--          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       | 438727    | 2018          |
--          +--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+

        -- we can now narrow the list of subjects by linking people with vehicles which left the bakery:
        select * from people
        join bank_accounts on bank_accounts.person_id = people.id
        where bank_accounts.account_number in
        (
            select atm_transactions.account_number from atm_transactions
            where atm_transactions.year = 2021
            and atm_transactions.month = 7
            and atm_transactions.day = 28
            and atm_transactions.transaction_type = 'withdraw'
            and atm_transactions.atm_location = 'Leggett Street'
        )
        and people.license_plate in
        (
            select bakery_security_logs.license_plate
            from bakery_security_logs
            where bakery_security_logs.year = 2021
            and bakery_security_logs.month = 7
            and bakery_security_logs.day = 28
            and bakery_security_logs.hour = 10
            and bakery_security_logs.minute >= 15
            and bakery_security_logs.minute <= 25
            and bakery_security_logs.activity = 'exit'
        );

--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          |   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
--          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
--          | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
--          | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+



    -- interview id = 163 from Raymond:
    -- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
    -- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    -- The thief then asked the person on the other end of the phone to purchase the flight ticket.

        -- FOLLOW UP:
        -- Raymond saw the thief talk to someone for less than one minute as they were leaving the bakery.
        -- let's find calls made in that time frame that lasted less than one minute.
        select * from phone_calls
        where phone_calls.year = 2021
        and phone_calls.month = 7
        and phone_calls.day = 28
        and phone_calls.duration < 60;

--          +-----+----------------+----------------+------+-------+-----+----------+
--          | id  |     caller     |    receiver    | year | month | day | duration |
--          +-----+----------------+----------------+------+-------+-----+----------+
--          | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
--          | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
--          | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
--          | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
--          | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
--          | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
--          | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
--          | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
--          | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
--          +-----+----------------+----------------+------+-------+-----+----------+

        -- next, let's link it to our suspects and see if any of them made any of these calls:
        select * from people
        join bank_accounts on bank_accounts.person_id = people.id
        where bank_accounts.account_number in
        (
            select atm_transactions.account_number from atm_transactions
            where atm_transactions.year = 2021
            and atm_transactions.month = 7
            and atm_transactions.day = 28
            and atm_transactions.transaction_type = 'withdraw'
            and atm_transactions.atm_location = 'Leggett Street'
        )
        and people.license_plate in
        (
            select bakery_security_logs.license_plate
            from bakery_security_logs
            where bakery_security_logs.year = 2021
            and bakery_security_logs.month = 7
            and bakery_security_logs.day = 28
            and bakery_security_logs.hour = 10
            and bakery_security_logs.minute >= 15
            and bakery_security_logs.minute <= 25
            and bakery_security_logs.activity = 'exit'
        )
        and people.phone_number in
        (
            select phone_calls.caller from phone_calls
            where phone_calls.year = 2021
            and phone_calls.month = 7
            and phone_calls.day = 28
            and phone_calls.duration < 60
        );

--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          |   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
--          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+

        -- also, the thief is flying out of Fiftyville tomorrow, so lets check what flights are there:
        -- Fiftyville airport id = 8
        select * from flights
        where flights.origin_airport_id in
        (
            select airports.id from airports
            where airports.city like "%Fiftyville%"
        )
        and flights.year = 2021
        and flights.month = 7
        and flights.day = 29;

--          +----+-------------------+------------------------+------+-------+-----+------+--------+
--          | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--          +----+-------------------+------------------------+------+-------+-----+------+--------+
--          | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
--          | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
--          | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
--          | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
--          | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
--          +----+-------------------+------------------------+------+-------+-----+------+--------+


        -- haing the flights, lets get passengers' passport numbers of all the flights after the theft:
        select * from passengers
        where passengers.flight_id in
        (
            select flights.id from flights
            where flights.origin_airport_id in
            (
                select airports.id from airports
                where airports.city like "%Fiftyville%"
            )
            and flights.year = 2021
            and flights.month = 7
            and flights.day = 29
        );


--          +-----------+-----------------+------+
--          | flight_id | passport_number | seat |
--          +-----------+-----------------+------+
--          | 18        | 2835165196      | 9C   |
--          | 18        | 6131360461      | 2C   |
--          | 18        | 3231999695      | 3C   |
--          | 18        | 3592750733      | 4C   |
--          | 18        | 2626335085      | 5D   |
--          | 18        | 6117294637      | 6B   |
--          | 18        | 2996517496      | 7A   |
--          | 18        | 3915621712      | 8D   |
--          | 23        | 4149859587      | 7D   |
--          | 23        | 9183348466      | 8A   |
--          | 23        | 7378796210      | 9B   |
--          | 23        | 7874488539      | 2C   |
--          | 23        | 4195341387      | 3A   |
--          | 23        | 6263461050      | 4A   |
--          | 23        | 3231999695      | 5A   |
--          | 23        | 7951366683      | 6B   |
--          | 36        | 7214083635      | 2A   |
--          | 36        | 1695452385      | 3B   |
--          | 36        | 5773159633      | 4A   |
--          | 36        | 1540955065      | 5C   |
--          | 36        | 8294398571      | 6C   |
--          | 36        | 1988161715      | 6D   |
--          | 36        | 9878712108      | 7A   |
--          | 36        | 8496433585      | 7B   |
--          | 43        | 7597790505      | 7B   |
--          | 43        | 6128131458      | 8A   |
--          | 43        | 6264773605      | 9A   |
--          | 43        | 3642612721      | 2C   |
--          | 43        | 4356447308      | 3B   |
--          | 43        | 7441135547      | 4A   |
--          | 53        | 7894166154      | 9B   |
--          | 53        | 6034823042      | 2C   |
--          | 53        | 4408372428      | 3D   |
--          | 53        | 2312901747      | 4D   |
--          | 53        | 1151340634      | 5A   |
--          | 53        | 8174538026      | 6D   |
--          | 53        | 1050247273      | 7A   |
--          | 53        | 7834357192      | 8C   |
--          +-----------+-----------------+------+


        -- having the passport numbers, let's check if our suspects are on any of these flights:
        select * from people
        join bank_accounts on bank_accounts.person_id = people.id
        where bank_accounts.account_number in
        (
            select atm_transactions.account_number from atm_transactions
            where atm_transactions.year = 2021
            and atm_transactions.month = 7
            and atm_transactions.day = 28
            and atm_transactions.transaction_type = 'withdraw'
            and atm_transactions.atm_location = 'Leggett Street'
        )
        and people.license_plate in
        (
            select bakery_security_logs.license_plate
            from bakery_security_logs
            where bakery_security_logs.year = 2021
            and bakery_security_logs.month = 7
            and bakery_security_logs.day = 28
            and bakery_security_logs.hour = 10
            and bakery_security_logs.minute >= 15
            and bakery_security_logs.minute <= 25
            and bakery_security_logs.activity = 'exit'
        )
        and people.phone_number in
        (
            select phone_calls.caller from phone_calls
            where phone_calls.year = 2021
            and phone_calls.month = 7
            and phone_calls.day = 28
            and phone_calls.duration < 60
        )
        and people.passport_number in
        (
            select passengers.passport_number from passengers
            where passengers.flight_id in
            (
                select flights.id from flights
                where flights.origin_airport_id in
                (
                    select airports.id from airports
                    where airports.city like "%Fiftyville%"
                )
                and flights.year = 2021
                and flights.month = 7
                and flights.day = 29
            )
        );

--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          |   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
--          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+

        -- as expected, both were on the planes the next day... but the thief took the earliest flight so:
        select * from people
        join bank_accounts on bank_accounts.person_id = people.id
        where bank_accounts.account_number in
        (
            select atm_transactions.account_number from atm_transactions
            where atm_transactions.year = 2021
            and atm_transactions.month = 7
            and atm_transactions.day = 28
            and atm_transactions.transaction_type = 'withdraw'
            and atm_transactions.atm_location = 'Leggett Street'
        )
        and people.license_plate in
        (
            select bakery_security_logs.license_plate
            from bakery_security_logs
            where bakery_security_logs.year = 2021
            and bakery_security_logs.month = 7
            and bakery_security_logs.day = 28
            and bakery_security_logs.hour = 10
            and bakery_security_logs.minute >= 15
            and bakery_security_logs.minute <= 25
            and bakery_security_logs.activity = 'exit'
        )
        and people.phone_number in
        (
            select phone_calls.caller from phone_calls
            where phone_calls.year = 2021
            and phone_calls.month = 7
            and phone_calls.day = 28
            and phone_calls.duration < 60
        )
        and people.passport_number in
        (
            select passengers.passport_number from passengers
            where passengers.flight_id in
            (
                select flights.id from flights
                where flights.origin_airport_id in
                (
                    select airports.id from airports
                    where airports.city like "%Fiftyville%"
                )
                and flights.year = 2021
                and flights.month = 7
                and flights.day = 29
                order by flights.hour asc, minute asc
                limit 1
            )
        );

--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          |   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
--          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
--          +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+

        -- Bruce is the thief!

    -- WHO IS THE ACCOMPLICE?
    -- it is the person that Bruce called after the crime:
    select * from people
    where people.phone_number in -- getting the acomplice by their phone number
    (
        select phone_calls.receiver from phone_calls
        where phone_calls.year = 2021
        and phone_calls.month = 7
        and phone_calls.day = 28
        and phone_calls.duration < 60
        and phone_calls.caller in -- caller is Bruce
        (
            select people.phone_number from people
            join bank_accounts on bank_accounts.person_id = people.id
            where bank_accounts.account_number in
            (
                select atm_transactions.account_number from atm_transactions
                where atm_transactions.year = 2021
                and atm_transactions.month = 7
                and atm_transactions.day = 28
                and atm_transactions.transaction_type = 'withdraw'
                and atm_transactions.atm_location = 'Leggett Street'
            )
            and people.license_plate in
            (
                select bakery_security_logs.license_plate
                from bakery_security_logs
                where bakery_security_logs.year = 2021
                and bakery_security_logs.month = 7
                and bakery_security_logs.day = 28
                and bakery_security_logs.hour = 10
                and bakery_security_logs.minute >= 15
                and bakery_security_logs.minute <= 25
                and bakery_security_logs.activity = 'exit'
            )
            and people.phone_number in
            (
                select phone_calls.caller from phone_calls
                where phone_calls.year = 2021
                and phone_calls.month = 7
                and phone_calls.day = 28
                and phone_calls.duration < 60
            )
            and people.passport_number in
            (
                select passengers.passport_number from passengers
                where passengers.flight_id in
                (
                    select flights.id from flights
                    where flights.origin_airport_id in
                    (
                        select airports.id from airports
                        where airports.city like "%Fiftyville%"
                    )
                    and flights.year = 2021
                    and flights.month = 7
                    and flights.day = 29
                    order by flights.hour asc, minute asc
                    limit 1
                )
            )
        )
    );

--          +--------+-------+----------------+-----------------+---------------+
--          |   id   | name  |  phone_number  | passport_number | license_plate |
--          +--------+-------+----------------+-----------------+---------------+
--          | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
--          +--------+-------+----------------+-----------------+---------------+

    -- the accomplice was Robin!

    -- WHERE IS BRUCE?
    select * from airports
    where airports.id in
    (
        select flights.destination_airport_id from flights
        where flights.origin_airport_id in
        (
            select airports.id from airports
            where airports.city like "%Fiftyville%"
        )
        and flights.year = 2021
        and flights.month = 7
        and flights.day = 29
        order by flights.hour asc, minute asc
        limit 1
    );

--          +----+--------------+-------------------+---------------+
--          | id | abbreviation |     full_name     |     city      |
--          +----+--------------+-------------------+---------------+
--          | 4  | LGA          | LaGuardia Airport | New York City |
--          +----+--------------+-------------------+---------------+

    -- Bruce escaped to NYC!

--
