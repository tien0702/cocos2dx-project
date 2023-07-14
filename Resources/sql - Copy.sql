PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS Ability (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, level INTEGER NOT NULL DEFAULT (0), unlock_level INTEGER DEFAULT (0) NOT NULL, equip_location TEXT REFERENCES AbilityEquipLocation (name), power_id INTEGER REFERENCES Power (id), name TEXT UNIQUE NOT NULL, description TEXT, icon_path TEXT NOT NULL, state_alloweds TEXT NOT NULL DEFAULT (1));
INSERT INTO Ability (id, level, unlock_level, equip_location, power_id, name, description, icon_path, state_alloweds) VALUES (1, 1, 1, 'DashLocation', 1, 'Dash', 'Dash', 'dash-ability', '1,2');
INSERT INTO Ability (id, level, unlock_level, equip_location, power_id, name, description, icon_path, state_alloweds) VALUES (2, 1, 1, 'NormalATK', 1, 'Normal Attack', 'Normal Attack', 'normal-atk-ability', '1,2');
INSERT INTO Ability (id, level, unlock_level, equip_location, power_id, name, description, icon_path, state_alloweds) VALUES (3, 1, 1, 'UltimateLocation', 6, 'Serpent Screw', 'Serpent Screw', 'serpent-screw', '1,2');

CREATE TABLE IF NOT EXISTS AbilityEquipLocation (name TEXT PRIMARY KEY NOT NULL);
INSERT INTO AbilityEquipLocation (name) VALUES ('DashLocation');
INSERT INTO AbilityEquipLocation (name) VALUES ('TalenLocation');
INSERT INTO AbilityEquipLocation (name) VALUES ('UltimateLocation');
INSERT INTO AbilityEquipLocation (name) VALUES ('NormalATK');

CREATE TABLE IF NOT EXISTS AbilityStat (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, stat_name TEXT REFERENCES Stat (name) NOT NULL, ability_name TEXT REFERENCES Ability (name) NOT NULL, value INTEGER NOT NULL DEFAULT (0));
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (1, 'Movement Speed', 'Dash', 700);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (2, 'Time Hold', 'Dash', 750);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (3, 'Power Rate', 'Dash', 500);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (4, 'Casting Time', 'Dash', 600);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (5, 'Stack', 'Dash', 3);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (6, 'Cooldown', 'Dash', 2000);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (7, 'Tick Frequency', 'Dash', 500);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (8, 'Boot Time', 'Serpent Screw', 500);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (9, 'Casting Time', 'Serpent Screw', 1000);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (10, 'Cooldown', 'Serpent Screw', 15000);
INSERT INTO AbilityStat (id, stat_name, ability_name, value) VALUES (11, 'Tick Frequency', 'Serpent Screw', 200);

CREATE TABLE IF NOT EXISTS Bonus (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, stat_name TEXT REFERENCES Stat (name) NOT NULL, modifi_type_name REFERENCES StatModificationType (name) NOT NULL, effect_type TEXT NOT NULL, duration INTEGER NOT NULL DEFAULT (0), start_time INTEGER NOT NULL DEFAULT (0), value INTEGER NOT NULL DEFAULT (0));
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1000, 'Attack', 'Percentage', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1001, 'Attack Speed', 'Percentage', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1002, 'Crit Rate', 'BaseValue', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1003, 'Crit Damage', 'BaseValue', ' ', 0, 0, 40000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1004, 'Movement Speed', 'Percentage', ' ', 0, 0, 15000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1005, 'Health Point', 'Percentage', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1006, 'Defense', 'Percentage', ' ', 0, 0, 31000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (1007, 'Health Point Recovery', 'BaseValue', ' ', 0, 0, 40);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2000, 'Attack', 'Percentage', ' ', 15, 0, 200);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2001, 'Crit Rate', 'BaseValue', ' ', 15, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2002, 'Crit Damage', 'BaseValue', ' ', 15, 0, 40000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2003, 'Movement Speed', 'Percentage', ' ', 15, 0, 10000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2004, 'Health Point', 'Percentage', ' ', 15, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2005, 'Current Hp', 'BaseValue', ' ', 0, 0, 300);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2006, 'Current Mana', 'BaseValue', ' ', 0, 0, 300);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2007, 'Current Mana', 'BaseValue', ' ', 0, 0, 300);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2008, 'Current Mana', 'BaseValue', ' ', 0, 0, 300);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (2009, 'Current Mana', 'BaseValue', ' ', 0, 0, 300);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3000, 'Attack', 'Percentage', ' ', 0, 0, 1000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3001, 'Defense', 'Percentage', ' ', 0, 0, 10000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3002, 'Health Point', 'Percentage', ' ', 0, 0, 15000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3003, 'Mana Recovery', 'BaseValue', ' ', 0, 0, 15);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3004, 'Attack Speed', 'Percentage', ' ', 0, 0, 10000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3005, 'Movement Speed', 'Percentage', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3006, 'Cryo Damage Bonus', 'Percentage', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3007, 'Physical Damage Bonus', 'Percentage', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3008, 'Attack', 'Percentage', ' ', 0, 0, 15000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3009, 'Defense', 'Percentage', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3010, 'Health Point', 'Percentage', ' ', 0, 0, 10000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3011, 'Mana', 'Percentage', ' ', 0, 0, 10000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3012, 'Attack Speed', 'Percentage', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3013, 'Movement Speed', 'Percentage', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3014, 'Crit Rate', 'BaseValue', ' ', 0, 0, 20000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3015, 'Crit Damage', 'BaseValue', ' ', 0, 0, 40000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3016, 'Crit Rate', 'BaseValue', ' ', 0, 0, 15000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3017, 'Crit Damage', 'BaseValue', ' ', 0, 0, 30000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3018, 'Attack Speed', 'Percentage', ' ', 0, 0, 25000);
INSERT INTO Bonus (id, stat_name, modifi_type_name, effect_type, duration, start_time, value) VALUES (3019, 'Crit Damage', 'Percentage', ' ', 0, 0, 900000);

CREATE TABLE IF NOT EXISTS BonusDeck (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, bonuses_id TEXT NOT NULL);
INSERT INTO BonusDeck (id, bonuses_id) VALUES (1, '3000,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,3013,3014,3015,3016,3017,3018,3019');

CREATE TABLE IF NOT EXISTS Chapter (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, name TEXT NOT NULL UNIQUE, reward_id NOT NULL REFERENCES Reward (id), state INTEGER NOT NULL DEFAULT (0));
INSERT INTO Chapter (id, name, reward_id, state) VALUES (1, 'Jura', 1, 0);
INSERT INTO Chapter (id, name, reward_id, state) VALUES (2, 'Plateau', 2, 0);

CREATE TABLE IF NOT EXISTS ChapterMap (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, "index" INTEGER NOT NULL DEFAULT (0), chapter_name TEXT REFERENCES Chapter (name) NOT NULL, tile_map_name TEXT NOT NULL DEFAULT map0, is_cleared INTEGER DEFAULT (0) NOT NULL, bonus_deck_id INTEGER NOT NULL DEFAULT (0) REFERENCES BonusDeck (id), reward_id INTEGER REFERENCES Reward (id), reward_on_completed TEXT, enemy_wave_json TEXT);
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (1, 1, 'Jura', 'map1', 0, 1, 1, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Blood Buburst","Level":71}]},{"Enemies":[{"EnemyName":"Blood Buburst","Level":65}]},{"Enemies":[{"EnemyName":"Blood Buburst","Level":69}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (2, 2, 'Jura', 'map2', 0, 1, 2, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Fire Pig","Level":27},{"EnemyName":"Big Fire Pig","Level":23},{"EnemyName":"Big Fire Pig","Level":18},{"EnemyName":"Big Gentleman Pig","Level":15},{"EnemyName":"Werewolf","Level":19},{"EnemyName":"Big Fire Pig","Level":27}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":18},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Gentleman Pig","Level":17},{"EnemyName":"Werewolf","Level":10},{"EnemyName":"Werewolf","Level":13},{"EnemyName":"Big Gentleman Pig","Level":19},{"EnemyName":"Big Fire Pig","Level":15},{"EnemyName":"Big Fire Pig","Level":15}]},{"Enemies":[{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":16},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Werewolf","Level":21},{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":27},{"EnemyName":"Werewolf","Level":23}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (3, 3, 'Jura', 'map3', 0, 1, 3, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Iron Pig","Level":34},{"EnemyName":"Iron Pig","Level":35},{"EnemyName":"Golem","Level":34},{"EnemyName":"Iron Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":34}]},{"Enemies":[{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Iron Pig","Level":38},{"EnemyName":"Golem","Level":30},{"EnemyName":"Iron Pig","Level":30},{"EnemyName":"Golem","Level":37},{"EnemyName":"Iron Pig","Level":31},{"EnemyName":"Big Gentleman Pig","Level":39},{"EnemyName":"Big Gentleman Pig","Level":34},{"EnemyName":"Golem","Level":34}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Golem","Level":36},{"EnemyName":"Golem","Level":39},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":38}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (4, 4, 'Jura', 'map4', 0, 1, 5, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Fire Pig","Level":27},{"EnemyName":"Big Fire Pig","Level":23},{"EnemyName":"Big Fire Pig","Level":18},{"EnemyName":"Big Gentleman Pig","Level":15},{"EnemyName":"Werewolf","Level":19},{"EnemyName":"Big Fire Pig","Level":27}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":18},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Gentleman Pig","Level":17},{"EnemyName":"Werewolf","Level":10},{"EnemyName":"Werewolf","Level":13},{"EnemyName":"Big Gentleman Pig","Level":19},{"EnemyName":"Big Fire Pig","Level":15},{"EnemyName":"Big Fire Pig","Level":15}]},{"Enemies":[{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":16},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Werewolf","Level":21},{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":27},{"EnemyName":"Werewolf","Level":23}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (5, 5, 'Jura', 'map5', 0, 1, 6, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Iron Pig","Level":34},{"EnemyName":"Iron Pig","Level":35},{"EnemyName":"Golem","Level":34},{"EnemyName":"Iron Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":34}]},{"Enemies":[{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Iron Pig","Level":38},{"EnemyName":"Golem","Level":30},{"EnemyName":"Iron Pig","Level":30},{"EnemyName":"Golem","Level":37},{"EnemyName":"Iron Pig","Level":31},{"EnemyName":"Big Gentleman Pig","Level":39},{"EnemyName":"Big Gentleman Pig","Level":34},{"EnemyName":"Golem","Level":34}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Golem","Level":36},{"EnemyName":"Golem","Level":39},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":38}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (6, 6, 'Jura', 'mapboss1', 0, 1, 6, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Demon","Level":69},{"EnemyName":"Demon","Level":74},{"EnemyName":"Golem","Level":77},{"EnemyName":"Golem","Level":62},{"EnemyName":"Demon","Level":62},{"EnemyName":"Golem","Level":72},{"EnemyName":"Werewolf","Level":72},{"EnemyName":"Golem","Level":74}]},{"Enemies":[{"EnemyName":"Demon","Level":72},{"EnemyName":"Demon","Level":78},{"EnemyName":"Golem","Level":79},{"EnemyName":"Demon","Level":65},{"EnemyName":"Golem","Level":64},{"EnemyName":"Werewolf","Level":69},{"EnemyName":"Demon","Level":63}]},{"Enemies":[{"EnemyName":"Demon","Level":73},{"EnemyName":"Golem","Level":61},{"EnemyName":"Golem","Level":62},{"EnemyName":"Golem","Level":65},{"EnemyName":"Werewolf","Level":69},{"EnemyName":"Demon","Level":73}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (7, 1, 'Jura', 'plateau1', 0, 1, 1, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Fire Pig","Level":27},{"EnemyName":"Big Fire Pig","Level":23},{"EnemyName":"Big Fire Pig","Level":18},{"EnemyName":"Big Gentleman Pig","Level":15},{"EnemyName":"Werewolf","Level":19},{"EnemyName":"Big Fire Pig","Level":27}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":18},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Gentleman Pig","Level":17},{"EnemyName":"Werewolf","Level":10},{"EnemyName":"Werewolf","Level":13},{"EnemyName":"Big Gentleman Pig","Level":19},{"EnemyName":"Big Fire Pig","Level":15},{"EnemyName":"Big Fire Pig","Level":15}]},{"Enemies":[{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":16},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Werewolf","Level":21},{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":27},{"EnemyName":"Werewolf","Level":23}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (8, 2, 'Jura', 'plateau2', 0, 1, 2, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Iron Pig","Level":34},{"EnemyName":"Iron Pig","Level":35},{"EnemyName":"Golem","Level":34},{"EnemyName":"Iron Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":34}]},{"Enemies":[{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Iron Pig","Level":38},{"EnemyName":"Golem","Level":30},{"EnemyName":"Iron Pig","Level":30},{"EnemyName":"Golem","Level":37},{"EnemyName":"Iron Pig","Level":31},{"EnemyName":"Big Gentleman Pig","Level":39},{"EnemyName":"Big Gentleman Pig","Level":34},{"EnemyName":"Golem","Level":34}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Golem","Level":36},{"EnemyName":"Golem","Level":39},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":38}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (9, 3, 'Jura', 'plateau3', 0, 1, 3, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Fire Pig","Level":27},{"EnemyName":"Big Fire Pig","Level":23},{"EnemyName":"Big Fire Pig","Level":18},{"EnemyName":"Big Gentleman Pig","Level":15},{"EnemyName":"Werewolf","Level":19},{"EnemyName":"Big Fire Pig","Level":27}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":18},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Big Gentleman Pig","Level":17},{"EnemyName":"Werewolf","Level":10},{"EnemyName":"Werewolf","Level":13},{"EnemyName":"Big Gentleman Pig","Level":19},{"EnemyName":"Big Fire Pig","Level":15},{"EnemyName":"Big Fire Pig","Level":15}]},{"Enemies":[{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":16},{"EnemyName":"Werewolf","Level":12},{"EnemyName":"Werewolf","Level":21},{"EnemyName":"Big Fire Pig","Level":19},{"EnemyName":"Big Gentleman Pig","Level":27},{"EnemyName":"Werewolf","Level":23}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (10, 4, 'Plateau', 'plateau4', 0, 1, 5, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Iron Pig","Level":34},{"EnemyName":"Iron Pig","Level":35},{"EnemyName":"Golem","Level":34},{"EnemyName":"Iron Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":34}]},{"Enemies":[{"EnemyName":"Iron Pig","Level":33},{"EnemyName":"Iron Pig","Level":38},{"EnemyName":"Golem","Level":30},{"EnemyName":"Iron Pig","Level":30},{"EnemyName":"Golem","Level":37},{"EnemyName":"Iron Pig","Level":31},{"EnemyName":"Big Gentleman Pig","Level":39},{"EnemyName":"Big Gentleman Pig","Level":34},{"EnemyName":"Golem","Level":34}]},{"Enemies":[{"EnemyName":"Big Gentleman Pig","Level":30},{"EnemyName":"Golem","Level":36},{"EnemyName":"Golem","Level":39},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":32},{"EnemyName":"Big Gentleman Pig","Level":38}]}]');
INSERT INTO ChapterMap (id, "index", chapter_name, tile_map_name, is_cleared, bonus_deck_id, reward_id, reward_on_completed, enemy_wave_json) VALUES (11, 5, 'Plateau', 'plateau5', 0, 1, 6, '[{"Name":"Gold","Amount":300},{"Name":"Ruby","Amount":5}]', '[{"Enemies":[{"EnemyName":"Demon","Level":69},{"EnemyName":"Demon","Level":74},{"EnemyName":"Golem","Level":77},{"EnemyName":"Golem","Level":62},{"EnemyName":"Demon","Level":62},{"EnemyName":"Golem","Level":72},{"EnemyName":"Werewolf","Level":72},{"EnemyName":"Golem","Level":74}]},{"Enemies":[{"EnemyName":"Demon","Level":72},{"EnemyName":"Demon","Level":78},{"EnemyName":"Golem","Level":79},{"EnemyName":"Demon","Level":65},{"EnemyName":"Golem","Level":64},{"EnemyName":"Werewolf","Level":69},{"EnemyName":"Demon","Level":63}]},{"Enemies":[{"EnemyName":"Demon","Level":73},{"EnemyName":"Golem","Level":61},{"EnemyName":"Golem","Level":62},{"EnemyName":"Golem","Level":65},{"EnemyName":"Werewolf","Level":69},{"EnemyName":"Demon","Level":73}]}]');

CREATE TABLE IF NOT EXISTS Coin (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, name TEXT UNIQUE NOT NULL, quantity INTEGER NOT NULL DEFAULT (0), icon_path TEXT);
INSERT INTO Coin (id, name, quantity, icon_path) VALUES (0, 'Gold', 200, 'gold.png');
INSERT INTO Coin (id, name, quantity, icon_path) VALUES (1, 'Ruby', 200, 'ruby.png');

CREATE TABLE IF NOT EXISTS ConsumableItem (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, consumable_item_template INTEGER REFERENCES ConsumableItemTemplate (id) NOT NULL, quantity INTEGER NOT NULL DEFAULT (0));
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (8, 8, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (9, 9, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (10, 10, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (11, 11, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (12, 12, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (13, 13, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (14, 14, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (15, 15, 100);
INSERT INTO ConsumableItem (id, consumable_item_template, quantity) VALUES (16, 16, 100);

CREATE TABLE IF NOT EXISTS ConsumableItemTemplate (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, item_base_name TEXT REFERENCES ItemBase (name) NOT NULL UNIQUE, bonus_id INTEGER NOT NULL REFERENCES Bonus (id), consumable_type TEXT NOT NULL DEFAULT Food REFERENCES ConsumableItemType (name));
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (8, 'HP Potion', 2005, 'Potion');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (9, 'MP Potion', 2006, 'Potion');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (10, 'DragonMeat', 2004, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (11, 'CreatureMeat', 2001, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (12, 'Bread For Animal', 2005, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (13, 'CookedFish', 2006, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (14, 'SteveJOB?', 2005, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (15, 'CaoBangWine', 2003, 'Food');
INSERT INTO ConsumableItemTemplate (id, item_base_name, bonus_id, consumable_type) VALUES (16, 'NemchuaThanhHoa', 2002, 'Food');

CREATE TABLE IF NOT EXISTS ConsumableItemType (name TEXT PRIMARY KEY UNIQUE NOT NULL);
INSERT INTO ConsumableItemType (name) VALUES ('Food');
INSERT INTO ConsumableItemType (name) VALUES ('Potion');

CREATE TABLE IF NOT EXISTS ElementType (name TEXT NOT NULL UNIQUE PRIMARY KEY);
INSERT INTO ElementType (name) VALUES ('Physical');
INSERT INTO ElementType (name) VALUES ('Pyro');
INSERT INTO ElementType (name) VALUES ('Cryo');
INSERT INTO ElementType (name) VALUES ('Lighning');

CREATE TABLE IF NOT EXISTS Entity (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, entity_type_id INT NOT NULL, name TEXT NOT NULL UNIQUE, exps INT NOT NULL, weight INT NOT NULL, portraitFileName TEXT NOT NULL, spriteFileName TEXT NOT NULL, size TEXT NOT NULL DEFAULT (0), states TEXT NOT NULL DEFAULT spawn, FOREIGN KEY (entity_type_id) REFERENCES EntityType (id));
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (1, 1, 'Luna', 0, 50, 'CloseNormal.png', 'luna', '70,150', 'spawn');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (2, 3, 'Blood Buburst', 0, 5, '', 'blood-buburst', '50,50', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (3, 3, 'Blobulord', 0, 10, '', 'blobulord', '110,110', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (4, 3, 'Werewolf', 0, 5, '', 'werewolf', '70,70', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (5, 3, 'Big Fire Pig', 0, 10, ' ', 'big-fire-pig', '90,80', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (6, 3, 'Big Gentleman Pig', 0, 33, ' ', 'big-gentleman-pig', '90,80', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (7, 3, 'Iron Pig', 0, 22, ' ', 'iron-pig', '60,60', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (8, 3, 'Demon', 0, 44, ' ', 'demon', '70,120', 'spawn,idle,move,chasing,attack,take-hit,die');
INSERT INTO Entity (id, entity_type_id, name, exps, weight, portraitFileName, spriteFileName, size, states) VALUES (9, 3, 'Golem', 0, 100, ' ', 'golem', '70,120', 'spawn,idle,move,chasing,attack,take-hit,die');

CREATE TABLE IF NOT EXISTS EntityStat (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, entity_name TEXT REFERENCES Entity (name) NOT NULL, stat_name TEXT REFERENCES Stat (name) NOT NULL, value INTEGER NOT NULL DEFAULT (0), growth_value INTEGER NOT NULL DEFAULT (0));
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (1, 'Luna', 'Attack', 160, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (2, 'Luna', 'Defense', 100, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (3, 'Luna', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (4, 'Luna', 'Mana', 1500, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (5, 'Luna', 'Attack Speed', 2000, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (6, 'Luna', 'Movement Speed', 300, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (7, 'Luna', 'Crit Rate', 30000, 100);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (8, 'Luna', 'Crit Damage', 50000, 300);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (9, 'Luna', 'Health Point Recovery', 30, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (10, 'Luna', 'Mana Recovery', 20, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (11, 'Luna', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (12, 'Luna', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (13, 'Luna', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (14, 'Luna', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (15, 'Luna', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (16, 'Luna', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (17, 'Luna', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (18, 'Luna', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (19, 'Luna', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (20, 'Luna', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (21, 'Luna', 'Current Hp', 3000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (22, 'Luna', 'Current Mana', 1500, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (23, 'Blood Buburst', 'Attack', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (24, 'Blood Buburst', 'Defense', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (25, 'Blood Buburst', 'Health Point', 3000, 100);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (26, 'Blood Buburst', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (27, 'Blood Buburst', 'Attack Speed', 1200, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (28, 'Blood Buburst', 'Movement Speed', 100, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (29, 'Blood Buburst', 'Crit Rate', 50, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (30, 'Blood Buburst', 'Crit Damage', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (31, 'Blood Buburst', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (32, 'Blood Buburst', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (33, 'Blood Buburst', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (34, 'Blood Buburst', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (35, 'Blood Buburst', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (36, 'Blood Buburst', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (37, 'Blood Buburst', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (38, 'Blood Buburst', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (39, 'Blood Buburst', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (40, 'Blood Buburst', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (41, 'Blood Buburst', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (42, 'Blood Buburst', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (43, 'Blood Buburst', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (44, 'Blood Buburst', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (45, 'Blood Buburst', 'Range Find', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (46, 'Blood Buburst', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (47, 'Blood Buburst', 'Range Attack', 70, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (48, 'Blood Buburst', 'Run Speed', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (49, 'Blobulord', 'Attack', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (50, 'Blobulord', 'Defense', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (51, 'Blobulord', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (52, 'Blobulord', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (53, 'Blobulord', 'Attack Speed', 2000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (54, 'Blobulord', 'Movement Speed', 70, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (55, 'Blobulord', 'Crit Rate', 50, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (56, 'Blobulord', 'Crit Damage', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (57, 'Blobulord', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (58, 'Blobulord', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (59, 'Blobulord', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (60, 'Blobulord', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (61, 'Blobulord', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (62, 'Blobulord', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (63, 'Blobulord', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (64, 'Blobulord', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (65, 'Blobulord', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (66, 'Blobulord', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (67, 'Blobulord', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (68, 'Blobulord', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (69, 'Blobulord', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (70, 'Blobulord', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (71, 'Blobulord', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (72, 'Blobulord', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (73, 'Blobulord', 'Range Attack', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (74, 'Blobulord', 'Run Speed', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (75, 'Werewolf', 'Attack', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (76, 'Werewolf', 'Defense', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (77, 'Werewolf', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (78, 'Werewolf', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (79, 'Werewolf', 'Attack Speed', 1500, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (80, 'Werewolf', 'Movement Speed', 70, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (81, 'Werewolf', 'Crit Rate', 50, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (82, 'Werewolf', 'Crit Damage', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (83, 'Werewolf', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (84, 'Werewolf', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (85, 'Werewolf', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (86, 'Werewolf', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (87, 'Werewolf', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (88, 'Werewolf', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (89, 'Werewolf', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (90, 'Werewolf', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (91, 'Werewolf', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (92, 'Werewolf', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (93, 'Werewolf', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (94, 'Werewolf', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (95, 'Werewolf', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (96, 'Werewolf', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (97, 'Werewolf', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (98, 'Werewolf', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (99, 'Werewolf', 'Range Attack', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (100, 'Werewolf', 'Run Speed', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (101, 'Big Fire Pig', 'Attack', 120, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (102, 'Big Fire Pig', 'Defense', 80, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (103, 'Big Fire Pig', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (104, 'Big Fire Pig', 'Mana', 40, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (105, 'Big Fire Pig', 'Attack Speed', 1300, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (106, 'Big Fire Pig', 'Movement Speed', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (107, 'Big Fire Pig', 'Crit Rate', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (108, 'Big Fire Pig', 'Crit Damage', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (109, 'Big Fire Pig', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (110, 'Big Fire Pig', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (111, 'Big Fire Pig', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (112, 'Big Fire Pig', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (113, 'Big Fire Pig', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (114, 'Big Fire Pig', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (115, 'Big Fire Pig', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (116, 'Big Fire Pig', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (117, 'Big Fire Pig', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (118, 'Big Fire Pig', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (119, 'Big Fire Pig', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (120, 'Big Fire Pig', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (121, 'Big Fire Pig', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (122, 'Big Fire Pig', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (123, 'Big Fire Pig', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (124, 'Big Fire Pig', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (125, 'Big Fire Pig', 'Range Attack', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (126, 'Big Fire Pig', 'Run Speed', 300, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (127, 'Big Gentleman Pig', 'Attack', 120, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (128, 'Big Gentleman Pig', 'Defense', 80, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (129, 'Big Gentleman Pig', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (130, 'Big Gentleman Pig', 'Mana', 40, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (131, 'Big Gentleman Pig', 'Attack Speed', 1300, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (132, 'Big Gentleman Pig', 'Movement Speed', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (133, 'Big Gentleman Pig', 'Crit Rate', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (134, 'Big Gentleman Pig', 'Crit Damage', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (135, 'Big Gentleman Pig', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (136, 'Big Gentleman Pig', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (137, 'Big Gentleman Pig', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (138, 'Big Gentleman Pig', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (139, 'Big Gentleman Pig', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (140, 'Big Gentleman Pig', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (141, 'Big Gentleman Pig', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (142, 'Big Gentleman Pig', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (143, 'Big Gentleman Pig', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (144, 'Big Gentleman Pig', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (145, 'Big Gentleman Pig', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (146, 'Big Gentleman Pig', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (147, 'Big Gentleman Pig', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (148, 'Big Gentleman Pig', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (149, 'Big Gentleman Pig', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (150, 'Big Gentleman Pig', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (151, 'Big Gentleman Pig', 'Range Attack', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (152, 'Big Gentleman Pig', 'Run Speed', 300, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (153, 'Iron Pig', 'Attack', 80, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (154, 'Iron Pig', 'Defense', 150, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (155, 'Iron Pig', 'Health Point', 4000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (156, 'Iron Pig', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (157, 'Iron Pig', 'Attack Speed', 1000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (158, 'Iron Pig', 'Movement Speed', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (159, 'Iron Pig', 'Crit Rate', 50, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (160, 'Iron Pig', 'Crit Damage', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (161, 'Iron Pig', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (162, 'Iron Pig', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (163, 'Iron Pig', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (164, 'Iron Pig', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (165, 'Iron Pig', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (166, 'Iron Pig', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (167, 'Iron Pig', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (168, 'Iron Pig', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (169, 'Iron Pig', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (170, 'Iron Pig', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (171, 'Iron Pig', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (172, 'Iron Pig', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (173, 'Iron Pig', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (174, 'Iron Pig', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (175, 'Iron Pig', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (176, 'Iron Pig', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (177, 'Iron Pig', 'Range Attack', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (178, 'Iron Pig', 'Run Speed', 300, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (179, 'Demon', 'Attack', 500, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (180, 'Demon', 'Defense', 200, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (181, 'Demon', 'Health Point', 5000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (182, 'Demon', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (183, 'Demon', 'Attack Speed', 2000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (184, 'Demon', 'Movement Speed', 70, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (185, 'Demon', 'Crit Rate', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (186, 'Demon', 'Crit Damage', 900000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (187, 'Demon', 'Health Point Recovery', 500, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (188, 'Demon', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (189, 'Demon', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (190, 'Demon', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (191, 'Demon', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (192, 'Demon', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (193, 'Demon', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (194, 'Demon', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (195, 'Demon', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (196, 'Demon', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (197, 'Demon', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (198, 'Demon', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (199, 'Demon', 'Current Hp', 5000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (200, 'Demon', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (201, 'Demon', 'Range Find', 350, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (202, 'Demon', 'Break Time', 70, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (203, 'Demon', 'Range Attack', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (204, 'Demon', 'Run Speed', 300, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (205, 'Golem', 'Attack', 100, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (206, 'Golem', 'Defense', 200, 5);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (207, 'Golem', 'Health Point', 3000, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (208, 'Golem', 'Mana', 50, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (209, 'Golem', 'Attack Speed', 1200, 10);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (210, 'Golem', 'Movement Speed', 70, 1);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (211, 'Golem', 'Crit Rate', 50, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (212, 'Golem', 'Crit Damage', 200, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (213, 'Golem', 'Health Point Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (214, 'Golem', 'Mana Recovery', 10, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (215, 'Golem', 'Cooldown Reduction', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (216, 'Golem', 'Skill Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (217, 'Golem', 'Physical Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (218, 'Golem', 'Physical Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (219, 'Golem', 'Pyro Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (220, 'Golem', 'Pyro Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (221, 'Golem', 'Cryo Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (222, 'Golem', 'Cryo Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (223, 'Golem', 'Lightning Damage Bonus', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (224, 'Golem', 'Lightning Resistance', 0, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (225, 'Golem', 'Current Hp', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (226, 'Golem', 'Current Mana', 1000, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (227, 'Golem', 'Range Find', 250, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (228, 'Golem', 'Break Time', 150, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (229, 'Golem', 'Range Attack', 100, 0);
INSERT INTO EntityStat (id, entity_name, stat_name, value, growth_value) VALUES (230, 'Golem', 'Run Speed', 300, 0);

CREATE TABLE IF NOT EXISTS EntityType (































    id           INT  PRIMARY KEY































                      UNIQUE































                      NOT NULL,































    name         TEXT NOT NULL































);
INSERT INTO EntityType (id, name) VALUES (1, 'Character');
INSERT INTO EntityType (id, name) VALUES (2, 'NPC');
INSERT INTO EntityType (id, name) VALUES (3, 'Enemy');

CREATE TABLE IF NOT EXISTS EquipableLocation (name TEXT PRIMARY KEY NOT NULL);
INSERT INTO EquipableLocation (name) VALUES ('Weapon');
INSERT INTO EquipableLocation (name) VALUES ('RuneTop');
INSERT INTO EquipableLocation (name) VALUES ('RuneMiddle');
INSERT INTO EquipableLocation (name) VALUES ('RuneBottom');
INSERT INTO EquipableLocation (name) VALUES ('Non');

CREATE TABLE IF NOT EXISTS ItemBase (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, item_type_id INT NOT NULL, equipable_locaion TEXT NOT NULL DEFAULT Weapon REFERENCES EquipableLocation (name), quality TEXT NOT NULL REFERENCES ItemQuality (name), name TEXT NOT NULL UNIQUE, weight REAL NOT NULL DEFAULT 0, description TEXT NOT NULL, prices TEXT NOT NULL DEFAULT (0), icon_path TEXT NOT NULL, FOREIGN KEY (item_type_id) REFERENCES ItemType (id));
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (9, 2, 'RuneTop', 'Rare', 'Brave Heart 1', 1.0, 'Brave Heart', '100,3', 'r1');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (10, 2, 'RuneMiddle', 'Rare', 'Brave Heart 2', 1.0, 'Brave Heart', '100,3', 'r2');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (11, 2, 'RuneBottom', 'Rare', 'Brave Heart 3', 1.0, 'Brave Heart', '100,3', 'r3');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (12, 2, 'RuneTop', 'Legendary', 'Brave Heart 4', 1.0, 'Brave Heart', '100,3', 'r1');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (13, 2, 'RuneMiddle', 'Legendary', 'Brave Heart 5', 1.0, 'Brave Heart', '100,3', 'r2');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (14, 2, 'RuneBottom', 'Legendary', 'Brave Heart 6', 1.0, 'Brave Heart', '100,3', 'r3');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (15, 2, 'RuneTop', 'Normal', 'Brave Heart 7', 1.0, 'Brave Heart', '100,3', 'r1');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (16, 2, 'RuneMiddle', 'Normal', 'Brave Heart 8', 1.0, 'Brave Heart', '100,3', 'r2');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (17, 2, 'RuneBottom', 'Normal', 'Brave Heart 9', 1.0, 'Brave Heart', '100,3', 'r3');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (25, 1, 'Weapon', 'Legendary', 'Tomb of Blizzard', 2.0, 'From the North of the World', '1234,200', 'FrozenTomb');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (26, 1, 'Weapon', 'Rare', 'Tomb of Hell', 3.0, 'The UnderWorld', '1000,50', 'HellTomb');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (27, 1, 'Weapon', 'Normal', 'Tomb of Forest', 2.0, 'Mysterious Jungle', '500,30', 'JungleTomb');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (28, 3, 'Non', 'Normal', 'HP Potion', 1.0, 'Restore 300 HP', '300,5', 'HealingPotion');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (29, 3, 'Non', 'Normal', 'MP Potion', 1.0, 'Restore 300 MP', '300,5', 'ManaPotion');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (30, 3, 'Non', 'Legendary', 'DragonMeat', 2.0, 'EpicBacon+Milk', '2500,15', 'Icon2');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (31, 3, 'Non', 'Rare', 'CreatureMeat', 2.0, 'Meat?', '2000,15', 'Icon1');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (32, 3, 'Non', 'Rare', 'Bread For Animal', 2.0, 'DogFOOD?', '1500', 'Icon3');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (33, 3, 'Non', 'Normal', 'CookedFish', 2.0, 'Cao b?ng FISH', '1000,15', 'Icon4');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (34, 3, 'Non', 'Normal', 'SteveJOB?', 2.0, 'Appl3?', '999,599', 'Icon5');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (35, 1, 'Weapon', 'Legendary', 'DeathNote', 1.0, 'DeathNOTE', '3000,6', 'Deathnote');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (36, 3, 'Non', 'Legendary', 'CaoBangWine', 1.0, 'FromCaoBang', '999,5', 'RCB');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (37, 3, 'Non', 'Legendary', 'NemchuaThanhHoa', 1.0, 'NemThanhHoa', '999,5', 'Nemchua');
INSERT INTO ItemBase (id, item_type_id, equipable_locaion, quality, name, weight, description, prices, icon_path) VALUES (38, 1, 'Weapon', 'Rare', 'ThunderBolt', 2.0, 'DarkThunder', '1500,15', 'ThunderBolt');

CREATE TABLE IF NOT EXISTS ItemQuality (name TEXT PRIMARY KEY UNIQUE NOT NULL);
INSERT INTO ItemQuality (name) VALUES ('Normal');
INSERT INTO ItemQuality (name) VALUES ('Rare');
INSERT INTO ItemQuality (name) VALUES ('Legendary');

CREATE TABLE IF NOT EXISTS ItemType (































    id   INT  PRIMARY KEY































    NOT NULL,































    name TEXT NOT NULL































);
INSERT INTO ItemType (id, name) VALUES (1, 'Weapon');
INSERT INTO ItemType (id, name) VALUES (2, 'Rune');
INSERT INTO ItemType (id, name) VALUES (3, 'Consumable');
INSERT INTO ItemType (id, name) VALUES (4, 'Collectable');

CREATE TABLE IF NOT EXISTS ObjectStat (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, stat_name TEXT REFERENCES Stat (name) NOT NULL, value INTEGER NOT NULL DEFAULT (0));
INSERT INTO ObjectStat (id, stat_name, value) VALUES (1, 'Casting Time', 1500);
INSERT INTO ObjectStat (id, stat_name, value) VALUES (2, 'Range', 300);
INSERT INTO ObjectStat (id, stat_name, value) VALUES (3, 'Cooldown', 7000);
INSERT INTO ObjectStat (id, stat_name, value) VALUES (4, 'Casting Time', 1500);
INSERT INTO ObjectStat (id, stat_name, value) VALUES (5, 'AreaRadius', 100);
INSERT INTO ObjectStat (id, stat_name, value) VALUES (6, 'Boot Time', 500);

CREATE TABLE IF NOT EXISTS PassiveSkill (































    id           INTEGER PRIMARY KEY AUTOINCREMENT































                         UNIQUE,































    name         TEXT    NOT NULL,































    level        INTEGER NOT NULL,































    cooldown     REAL    NOT NULL,































    success_rate REAL    NOT NULL































                         DEFAULT 1,































    mana_needed  INTEGER NOT NULL































                         DEFAULT 0,































    description  TEXT    NOT NULL,































    condition    TEXT    NOT NULL































);
INSERT INTO PassiveSkill (id, name, level, cooldown, success_rate, mana_needed, description, condition) VALUES (1, 'Skill', 1, 3.0, 0.7, 5, 'abc..', '1');

CREATE TABLE IF NOT EXISTS Player (item_base_id INT REFERENCES ItemBase (id) NOT NULL) STRICT;

CREATE TABLE IF NOT EXISTS Power (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, value REAL NOT NULL, value_number INT NOT NULL, element_type_name TEXT NOT NULL REFERENCES ElementType (name), FOREIGN KEY (element_type_name) REFERENCES ElementType);
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (1, 1500.0, 243, 'Physical');
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (2, 2500.0, 243, 'Pyro');
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (3, 5230.0, 588, 'Cryo');
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (4, 2000.0, 243, 'Lighning');
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (5, 3000.0, 243, 'Lighning');
INSERT INTO Power (id, value, value_number, element_type_name) VALUES (6, 3000.0, 0, 'Cryo');

CREATE TABLE IF NOT EXISTS Projectile (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, projectile_range REAL NOT NULL, speed REAL NOT NULL, ani_file_name TEXT NOT NULL, des_ani_name TEXT NOT NULL, radius REAL NOT NULL DEFAULT (1));
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (1, 400.0, 500.0, '01', 'explosion-1', 20.0);
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (2, 600.0, 300.0, '01', 'explosion-1', 20.0);
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (3, 300.0, 250.0, '02', 'explosion-1', 20.0);
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (4, 400.0, 700.0, '01', 'explosion-1', 20.0);
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (5, 500.0, 500.0, 'Nam', 'explosion-1', 20.0);
INSERT INTO Projectile (id, projectile_range, speed, ani_file_name, des_ani_name, radius) VALUES (6, 500.0, 800.0, 'thunder-bolt', 'explosion-1', 20.0);

CREATE TABLE IF NOT EXISTS Reward (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, exp_reward INTEGER NOT NULL DEFAULT (0), info_coin TEXT NOT NULL, info_items TEXT NOT NULL);
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (1, 500, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (2, 44, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (3, 22, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (4, 33, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (5, 44, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (6, 55, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');
INSERT INTO Reward (id, exp_reward, info_coin, info_items) VALUES (7, 33, '[{"Name":"Gold","Amount":3000},{"Name":"Ruby","Amount":50}]', '[{"Name":"HP Potion","Amount":2},{"Name":"MP Potion","Amount":3},{"Name":"DragonMeat","Amount":2},{"Name":"CaoBangWine","Amount":1},{"Name":"NemchuaThanhHoa","Amount":3}]');

CREATE TABLE IF NOT EXISTS Skill (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL DEFAULT (0), skill_template_name TEXT REFERENCES SkillTemplate (name), level INTEGER NOT NULL DEFAULT (0), equipped INTEGER NOT NULL DEFAULT (0));
INSERT INTO Skill (id, skill_template_name, level, equipped) VALUES (1, 'Explosion', 1, 0);
INSERT INTO Skill (id, skill_template_name, level, equipped) VALUES (2, 'Water Ball', 1, 1);
INSERT INTO Skill (id, skill_template_name, level, equipped) VALUES (3, 'Explosion Wind', 1, 1);

CREATE TABLE IF NOT EXISTS SkillStat (id INTEGER PRIMARY KEY AUTOINCREMENT, skill_name TEXT REFERENCES SkillTemplate (name), stat_name TEXT REFERENCES Stat (name), _value INTEGER NOT NULL DEFAULT (0));
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (1, 'Explosion', 'Range', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (2, 'Explosion', 'Cooldown', 3000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (3, 'Explosion', 'Casting Time', 1000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (4, 'Explosion', 'AoE Radius', 60);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (5, 'Explosion', 'Boot Time', 500);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (6, 'Blast Hammer', 'Range', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (7, 'Blast Hammer', 'Cooldown', 3000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (8, 'Blast Hammer', 'Casting Time', 1000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (9, 'Blast Hammer', 'AoE Radius', 60);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (10, 'Blast Hammer', 'Boot Time', 500);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (11, 'Serpent Screw', 'Range', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (12, 'Serpent Screw', 'Cooldown', 3000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (13, 'Serpent Screw', 'Casting Time', 1000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (14, 'Serpent Screw', 'AoE Radius', 60);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (15, 'Serpent Screw', 'Boot Time', 1200);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (16, 'Explosion', 'Mana Cost', 20);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (17, 'Blast Hammer', 'Mana Cost', 20);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (18, 'Serpent Screw', 'Mana Cost', 20);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (19, 'Explosion Wind', 'Range', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (20, 'Explosion Wind', 'Cooldown', 3000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (21, 'Explosion Wind', 'Casting Time', 2000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (22, 'Explosion Wind', 'AoE Radius', 100);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (23, 'Explosion Wind', 'Boot Time', 1200);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (24, 'Explosion Wind', 'Mana Cost', 100);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (25, 'Water Ball', 'Action Range', 360);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (26, 'Water Ball', 'Range', 60);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (27, 'Water Ball', 'Boot Time', 100);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (28, 'Water Ball', 'Mana Cost', 60);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (29, 'Water Ball', 'Cooldown', 2000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (30, 'Water Ball', 'AoE Width', 40);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (31, 'Water Ball', 'AoE Height', 40);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (32, 'Water Ball', 'AoE Radius', 130);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (33, 'Water Ball', 'Maximum Projectile Range', 360);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (34, 'Water Ball', 'Movement Speed', 700);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (35, 'Explosion Wind', 'AoE Radius', 100);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (36, 'Shark', 'Range', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (37, 'Shark', 'Cooldown', 3000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (38, 'Shark', 'Casting Time', 2000);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (39, 'Shark', 'AreaRadius', 100);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (40, 'Shark', 'Boot Time', 300);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (41, 'Shark', 'Mana Cost', 20);
INSERT INTO SkillStat (id, skill_name, stat_name, _value) VALUES (42, 'Shark', 'AoE Radius', 160);

CREATE TABLE IF NOT EXISTS SkillTemplate (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, name TEXT UNIQUE NOT NULL DEFAULT defaultSkill, description TEXT, icon_name TEXT, effect_name TEXT, input_id INTEGER, targeting_type INTEGER, activation_type INTEGER NOT NULL DEFAULT (0), power_id INTEGER REFERENCES Power (id));
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (1, 'Explosion', 'Explosion', 'explosion', 'explosion', 3, 2, 0, 1);
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (2, 'Blast Hammer', 'blast-hammer', 'blast-hammer', 'blast-hammer', 3, 2, 0, 1);
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (4, 'Serpent Screw', 'serpent-screw', 'serpent-screw', 'serpent-screw', 3, 2, 0, 1);
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (5, 'Explosion Wind', 'explosion-wind', 'explosion-wind', 'explosion-wind', 2, 2, 0, 1);
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (6, 'Water Ball', 'water-ball', 'water-ball', 'water-ball', 3, 1, 1, 3);
INSERT INTO SkillTemplate (id, name, description, icon_name, effect_name, input_id, targeting_type, activation_type, power_id) VALUES (7, 'Shark', 'shark', 'shark', 'shark', 2, 2, 0, 4);

CREATE TABLE IF NOT EXISTS Stat (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, type INT NOT NULL DEFAULT 0, name TEXT NOT NULL UNIQUE, abbreviation TEXT NOT NULL, value_type TEXT REFERENCES ValueType (name) NOT NULL DEFAULT OnlyNumber, description TEXT NOT NULL);
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (1, 0, 'Attack', 'ATK', 'BothTypesNumbers', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (2, 0, 'Defense', 'DEF', 'BothTypesNumbers', '2');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (3, 0, 'Health Point', 'HP', 'BothTypesNumbers', '3');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (4, 0, 'Mana', 'MP', 'BothTypesNumbers', '4');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (5, 0, 'Attack Speed', 'ATK Speed', 'BothTypesNumbers', '5');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (6, 1, 'Movement Speed', 'Move Speed', 'BothTypesNumbers', '6');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (7, 1, 'Crit Rate', 'Crit Rate', 'OnlyPercent', '7');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (8, 1, 'Crit Damage', 'Crit DMG', 'OnlyPercent', '8');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (9, 1, 'Health Point Recovery', 'HP Recovery', 'OnlyNumber', '9');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (10, 1, 'Mana Recovery', 'MP Recovery', 'OnlyNumber', '10');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (11, 1, 'Cooldown Reduction', 'CD Reduction', 'OnlyPercent', '11');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (12, 1, 'Skill Damage Bonus', 'Skill DMG Bonus', 'OnlyPercent', '12');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (13, 2, 'Physical Damage Bonus', 'Physical DMG Bonus', 'OnlyPercent', '13');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (14, 2, 'Physical Resistance', 'Physical RES', 'OnlyPercent', '14');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (15, 2, 'Pyro Damage Bonus', 'Pyro DMG Bonus', 'OnlyPercent', '15');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (16, 2, 'Pyro Resistance', 'Pyro RES', 'OnlyPercent', '16');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (17, 2, 'Cryo Damage Bonus', 'Cryo DMG Bonus', 'OnlyPercent', '17');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (18, 2, 'Cryo Resistance', 'Cryo RES', 'OnlyPercent', '18');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (19, 2, 'Lightning Damage Bonus', 'Lightning DMG Bonus', 'OnlyPercent', '19');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (20, 2, 'Lightning Resistance', 'Lightning RES', 'OnlyPercent', '20');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (21, 1, 'Current Hp', 'Current HP', 'OnlyNumber', '21');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (22, 1, 'Current Mana', 'Current Mana', 'OnlyNumber', '22');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (23, 1, 'Range Find', 'Range Find', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (24, 1, 'Break Time', 'Break Time', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (25, 1, 'Range Attack', 'Range Attack', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (26, 1, 'Time Recheck ', 'Time Recheck', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (27, 1, 'Casting Time', 'CastingTime', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (28, 1, 'Cooldown', 'Cooldown', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (29, 1, 'Range', 'Range', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (30, 1, 'Time Hold', 'Time Hold', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (31, 1, 'Power Rate', 'Power Rate', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (32, 1, 'Stack', 'Stack', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (33, 1, 'Run Speed', 'Run Speed', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (34, 1, 'Tick Frequency', 'Tick Frequency', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (35, 1, 'Success Rate', 'Success Rate', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (36, 1, 'Area Range', 'Area Range', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (37, 1, 'Action Range', 'Action Range', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (38, 1, 'Boot Time', 'Boot Time', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (39, 1, 'AreaRadius', 'AreaRadius', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (40, 1, 'Mana Cost', 'Mana Cost', 'OnlyNumber', '1');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (41, 1, 'AoE Width', 'AoE Width', 'OnlyNumber', 'AoE Width');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (42, 1, 'AoE Height', 'AoE Height', 'OnlyNumber', 'AoE Height');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (43, 1, 'AoE Radius', 'AoE Radius', 'OnlyNumber', 'AoE Radius');
INSERT INTO Stat (id, type, name, abbreviation, value_type, description) VALUES (44, 1, 'Maximum Projectile Range', 'Maximum Projectile Range', 'OnlyNumber', 'Maximum Projectile Range');

CREATE TABLE IF NOT EXISTS StatModificationType (name PRIMARY KEY UNIQUE NOT NULL);
INSERT INTO StatModificationType (name) VALUES ('Percentage');
INSERT INTO StatModificationType (name) VALUES ('Numeric');
INSERT INTO StatModificationType (name) VALUES ('Absolute');
INSERT INTO StatModificationType (name) VALUES ('BaseValue');

CREATE TABLE IF NOT EXISTS ValueType (name TEXT PRIMARY KEY UNIQUE NOT NULL);
INSERT INTO ValueType (name) VALUES ('BothTypesNumbers');
INSERT INTO ValueType (name) VALUES ('OnlyPercent');
INSERT INTO ValueType (name) VALUES ('OnlyNumber');

CREATE TABLE IF NOT EXISTS Weapon (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, weapon_template_id INTEGER REFERENCES WeaponTemplate (id) NOT NULL, level INTEGER DEFAULT (1) NOT NULL, locked BLOB NOT NULL DEFAULT (false), equipped BLOB DEFAULT (0) NOT NULL, exps INTEGER NOT NULL DEFAULT (0));
INSERT INTO Weapon (id, weapon_template_id, level, locked, equipped, exps) VALUES (9, 9, 20, 0, 0, 35);
INSERT INTO Weapon (id, weapon_template_id, level, locked, equipped, exps) VALUES (10, 10, 15, 0, 0, 35);
INSERT INTO Weapon (id, weapon_template_id, level, locked, equipped, exps) VALUES (11, 11, 10, 1, 0, 35);
INSERT INTO Weapon (id, weapon_template_id, level, locked, equipped, exps) VALUES (12, 12, 999, 0, 0, 35);
INSERT INTO Weapon (id, weapon_template_id, level, locked, equipped, exps) VALUES (13, 13, 15, 1, 1, 35);

CREATE TABLE IF NOT EXISTS WeaponTemplate (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, item_base_name TEXT REFERENCES ItemBase (name) NOT NULL, projectile_id INT NOT NULL, passive_skill_id INTEGER NOT NULL REFERENCES PassiveSkill (id) ON DELETE SET NULL ON UPDATE SET DEFAULT DEFAULT (1), bonus_id INT NOT NULL REFERENCES Bonus (id), atk_bns INT NOT NULL DEFAULT 0, weap_range REAL NOT NULL, type INT NOT NULL DEFAULT 0, state_alloweds TEXT NOT NULL DEFAULT '1', FOREIGN KEY (bonus_id) REFERENCES Bonus (id), FOREIGN KEY (projectile_id) REFERENCES Projectile (id), FOREIGN KEY (passive_skill_id) REFERENCES PassiveSkill (id));
INSERT INTO WeaponTemplate (id, item_base_name, projectile_id, passive_skill_id, bonus_id, atk_bns, weap_range, type, state_alloweds) VALUES (9, 'Tomb of Blizzard', 5, 1, 1000, 125, 300.0, 0, '1');
INSERT INTO WeaponTemplate (id, item_base_name, projectile_id, passive_skill_id, bonus_id, atk_bns, weap_range, type, state_alloweds) VALUES (10, 'Tomb of Hell', 2, 1, 1001, 90, 275.0, 0, '1');
INSERT INTO WeaponTemplate (id, item_base_name, projectile_id, passive_skill_id, bonus_id, atk_bns, weap_range, type, state_alloweds) VALUES (11, 'Tomb of Forest', 2, 1, 1002, 60, 250.0, 0, '1');
INSERT INTO WeaponTemplate (id, item_base_name, projectile_id, passive_skill_id, bonus_id, atk_bns, weap_range, type, state_alloweds) VALUES (12, 'DeathNote', 2, 1, 1003, 9999, 350.0, 0, '1');
INSERT INTO WeaponTemplate (id, item_base_name, projectile_id, passive_skill_id, bonus_id, atk_bns, weap_range, type, state_alloweds) VALUES (13, 'ThunderBolt', 6, 1, 1004, 48, 375.0, 0, '1');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
