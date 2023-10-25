#clear table
DELETE FROM mobannouncer_ids;

#insert world rares
INSERT INTO mobannouncer_ids (entry, description)
SELECT entry, name
FROM creature_template
WHERE rank IN ('4','2') AND NOT lootid = 0 AND creature_template.entry NOT IN ('596','599','1720','3586','3652','3672','3872','4425','4438','4842','5400','5708','5912','6228','6488','6489','6490','7354','8923','9024','9041','9042','9217','9218','9219','9596','9718','9736','10080','10081','10082','10263','10376','10393','10509','10558','10809','10820','10899','11467','11688','12237','16179','16180','16181');

#insert world bosses
INSERT INTO mobannouncer_ids (entry, description)
SELECT entry, name
FROM creature_template
WHERE entry IN ('12397','14887', '14888', '14889', '14890');
