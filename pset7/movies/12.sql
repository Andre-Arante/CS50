SELECT title FROM movies WHERE id IN
-- Compare movie id with movie ids of Johnny Depp and Helena Bonham Carter
(
    SELECT movie_id FROM stars
    WHERE person_id IN (SELECT id FROM people WHERE name == "Helena Bonham Carter")
    INTERSECT
    SELECT movie_id FROM stars
    WHERE person_id IN (SELECT id FROM people WHERE name == "Johnny Depp")
);