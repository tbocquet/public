-- TOUJOURS METTRE DES SIMPLES COTES
-- PAS DE COMMENTAIRE SUR UNE LIGNE AVEC UNE INSTRUCTION

INSERT INTO CLIENT VALUES(1, 'moi', 'prenomdemoi', 'adresse', 1050305010); 
INSERT INTO CLIENT VALUES(2, 'moi2', 'prenomdemoi2', 'adresse2', 1050305010); 
INSERT INTO CLIENT VALUES(3, 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 

INSERT INTO COMPAGNIE VALUES(1, 'bla1');
INSERT INTO COMPAGNIE VALUES(2, 'bla2');
INSERT INTO COMPAGNIE VALUES(3, 'bla3');
INSERT INTO COMPAGNIE VALUES(4, 'bla4');
INSERT INTO COMPAGNIE VALUES(5, 'bla5');
INSERT INTO COMPAGNIE VALUES(6, 'bla6');


INSERT INTO VILLE VALUES(1, 'PARIS');
INSERT INTO VILLE VALUES(2, 'LARIS');
INSERT INTO VILLE VALUES(3, 'SARIS');

INSERT INTO ESCALE VALUES(1, 1, 2);
INSERT INTO ESCALE VALUES(2, 1, 3);
INSERT INTO ESCALE VALUES(3, 2, 3);

INSERT INTO VOL VALUES(1, 1, 1, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/03/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), 10, 0);
INSERT INTO VOL VALUES(2, 1, 2, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/03/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), 10, 0);
INSERT INTO VOL VALUES(3, 1, 3, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/03/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), 10, 0);

INSERT INTO CARTE_FIDELITE VALUES(1, 1, 900);
INSERT INTO CARTE_FIDELITE VALUES(2, 1, 950);

-- BILLET idBillet idVol, idCompagnie, prix, promo, etatBillet
INSERT INTO BILLET VALUES(1, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(2, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(3, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(4, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(5, 1, 1, 1000, 0, 'A');
INSERT INTO BILLET VALUES(6, 1, 1, 1000, 0, 'A');
INSERT INTO BILLET VALUES(7, 1, 1, 1000, 0, 'R');
INSERT INTO BILLET VALUES(8, 1, 1, 1000, 0, 'R');

-- BILLET_CLIENT idAchat, idBillet, idClient, dateAchat
INSERT INTO BILLET_CLIENT VALUES(1, 1, 1, DEFAULT);

-- erreur volontaire
-- INSERT INTO CLIENT VALUES(3, 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 
-- INSERT INTO ESCALE VALUES(4, 3, 3);

