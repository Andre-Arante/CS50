SELECT DISTINCT(name) FROM people
JOIN stars ON stars.person_id = people.id
WHERE movie_id IN
-- Search for people with the same movie_id as Kevin Bacon
(
    -- Find Kevin Bacon's movies
    SELECT movie_id FROM stars
    WHERE person_id IN
    (
        SELECT id FROM people WHERE name == "Kevin Bacon"
    )
) AND name != "Kevin Bacon";