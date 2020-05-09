--- Delete existing data

DELETE FROM track;
DELETE FROM cd;
DELETE FROM artist;

--- Now the data inserts

--- First the artist (or group) tables

INSERT INTO artist(ID,Name) VALUES(0,'');
INSERT INTO artist(ID,Name) VALUES(1,'Pink Floyd');
INSERT INTO artist(ID,Name) VALUES(2,'Genesis');
INSERT INTO artist(ID,Name) VALUES(3,'Einaudi');
INSERT INTO artist(ID,Name) VALUES(4,'Melanie');

--- Then the cd table

INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(0,'',0'');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(1,'Dark Side of the Moon',1,'B000024D4P');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(2,'Wish You Were Here',1,'B000024D4S');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(3,'A Trick of the Tail',2,'B000024EXM');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(4,'Selling England By the Pound2',2,'B000024E9M');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(5,'I Giorni',3,'B000071WEV');
INSERT INTO cd(ID,Title,Artist_id,Catalogue) VALUES(6,'Northern Star',4,'B00004YMST');

--- populate the tracks

INSERT INTO track(CD_ID,Track_id,Title) VALUES(0,0,'');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(1,1,'Speak to me');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(1,2,'Breathe');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(2,1,'Shine on you crazy diamond');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(2,2,'Welcome to the machine');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(2,3,'Have a cigar');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(2,4,'Wish you were here');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(2,5,'Shine on you crazy diamondpt.2');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(5,1,'Melodia Africana (part1)');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(5,2,'I due fiumi');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(5,3,'In un\'altra vita');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(6,11,'Closer');
INSERT INTO track(CD_ID,Track_id,Title) VALUES(6,12,'Feel The sun');







