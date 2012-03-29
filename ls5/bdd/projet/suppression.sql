-- Ce script supprime toutes les tables et toutes les contraintes

-- Suppression des FK en premier, avec les autres contraintes
ALTER TABLE CLIENT			DROP 	CONSTRAINT u_client_nom_prenom_adresse ;
ALTER TABLE CLIENT			DROP 	CONSTRAINT u_client_login;
ALTER TABLE VILLE			DROP 	CONSTRAINT u_ville_nomVille ;
ALTER TABLE ESCALE			DROP 	CONSTRAINT fk_escale_ville;
ALTER TABLE ESCALE			DROP 	CONSTRAINT fk_escale_vol ;
ALTER TABLE VOL				DROP 	CONSTRAINT fk_vol_compagnie ;
ALTER TABLE VOL				DROP 	CONSTRAINT fk_vol_villedepart ;
ALTER TABLE VOL				DROP 	CONSTRAINT fk_vol_villearrivee;
ALTER TABLE BILLET			DROP 	CONSTRAINT ck_billet_etatbillet ;
ALTER TABLE BILLET			DROP 	CONSTRAINT ck_billet_prix ;
ALTER TABLE BILLET			DROP 	CONSTRAINT fk_billet_vol_compagnie ;
ALTER TABLE BILLET_CLIENT 	DROP 	CONSTRAINT fk_billet_client_client ;
ALTER TABLE BILLET_CLIENT 	DROP 	CONSTRAINT fk_billet_client_billet ;
ALTER TABLE CARTE_FIDELITE 	DROP 	CONSTRAINT fk_carte_fidelite_compagnie ;
ALTER TABLE CARTE_FIDELITE 	DROP 	CONSTRAINT fk_carte_fidelite_client ;
ALTER TABLE RESERVATION 	DROP 	CONSTRAINT fk_reservation_client ;
ALTER TABLE RESERVATION 	DROP 	CONSTRAINT fk_reservation_billet ;

-- Suppression des PK en second
ALTER TABLE CLIENT			DROP 	CONSTRAINT pk_client ;
ALTER TABLE COMPAGNIE		DROP 	CONSTRAINT pk_compagnie ;
ALTER TABLE RESERVATION		DROP 	CONSTRAINT pk_reservation ;
ALTER TABLE BILLET_CLIENT 	DROP 	CONSTRAINT pk_billet_client ;
ALTER TABLE BILLET			DROP 	CONSTRAINT pk_billet ;
ALTER TABLE VOL				DROP 	CONSTRAINT pk_vol ;
ALTER TABLE ESCALE			DROP 	CONSTRAINT pk_escale ;
ALTER TABLE VILLE			DROP 	CONSTRAINT pk_ville ;
ALTER TABLE CARTE_FIDELITE 	DROP 	CONSTRAINT pk_carte_fidelite ;

-- Suppression des tables en dernier
DROP TABLE  CLIENT ;
DROP TABLE  VILLE ;
DROP TABLE  COMPAGNIE ;
DROP TABLE  ESCALE ;
DROP TABLE  VOL ;
DROP TABLE  BILLET ;
DROP TABLE  BILLET_CLIENT ;
DROP TABLE  CARTE_FIDELITE ;
DROP TABLE  RESERVATION ;
