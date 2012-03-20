create table CLIENT
(
	idClient number(15) PRIMARY KEY,
	nomClient varchar2(50) NOT NULL,
	prenomClient varchar2(50) NOT NULL,
	adresseClient varchar2(100) NOT NULL,
	numTelClient number(10)
);
create table VILLE
(
	idVille number(15) PRIMARY KEY,
	nomVille varchar2(50) NOT NULL UNIQUE
);
create table COMPAGNIE
(
	idCompagnie number(10) PRIMARY KEY,
	nomCompagnie varchar2(50) NOT NULL UNIQUE
);
create table ESCALE
(
	idEscale number(10) PRIMARY KEY,
	idVilleDepart number(15) NOT NULL,
	idVilleArrivee number(15) NOT NULL,
	CONSTRAINT fk_escale_villedepart FOREIGN KEY (idVilleDepart) REFERENCES	VILLE(idVille) ON DELETE CASCADE,
	CONSTRAINT fk_escale_villearrivee FOREIGN KEY (idVilleArrivee) REFERENCES VILLE(idVille) ON DELETE CASCADE
);
create table VOL
(
	idVol number(10),
	idCompagnie number(10) NOT NULL,
	dateDepart date NOT NULL,
	dateArrivee date NOT NULL,
	idVilleDepart number(15) NOT NULL,
	idVilleArrivee number(15) NOT NULL,
	nombreBillets number(4) NOT NULL,
	nombreBilletsReserves number(4) NOT NULL,
	CHECK( nombreBillets >= 0),
	PRIMARY KEY(idVol, idCompagnie),
	CONSTRAINT fk_vol_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_vol_villedepart FOREIGN KEY (idVilleDepart) REFERENCES VILLE(idVille) ON DELETE CASCADE,
	CONSTRAINT fk_vol_villearrivee FOREIGN KEY (idVilleArrivee) REFERENCES VILLE(idVille) ON DELETE CASCADE
);
create table BILLET
(
	idBillet number(15),
	idVol number(10) NOT NULL,
	idCompagnie number(10) NOT NULL,
	prix number(15) CHECK(prix > 0) NOT NULL,
	promo number(2) CHECK (promo > 0 AND promo < 100),
	etatBillet char(1) CHECK(etatBillet = 'A' OR etatBillet = 'R'),
	CONSTRAINT fk_billet_vol FOREIGN KEY (idVol) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_billet_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	PRIMARY KEY(idBillet, idVol, idCompagnie)
);
create table BILLET_CLIENT
(
	idAchat number(15) PRIMARY KEY,
	idBillet number(15) NOT NULL,
	idClient number(15) NOT NULL,
	dateAchat date NOT NULL,
	CONSTRAINT fk_billet_client_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE ,
	CONSTRAINT fk_billet_client_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE
);
create table CARTE_FIDELITE
(
	idCompagnie number(10) NOT NULL, 
	idClient number(15) NOT NULL,
	miles number(10) NOT NULL,
	CONSTRAINT fk_carte_fidelite_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_carte_fidelite_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE,
	PRIMARY KEY(idClient, idCompagnie)
);
create table RESERVATION
(
	dateReservation date NOT NULL,
	idClient number(15),
	idBillet number(15),
	CONSTRAINT fk_reservation_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE,
	CONSTRAINT fk_reservation_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE,
	PRIMARY KEY(idClient, idBillet)
);
create table VOL_ESCALE
(
	idVol number(10),
	idEscale number(10),
	CONSTRAINT fk_vol_escale_vol FOREIGN KEY (idVol) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_vol_escale_escale FOREIGN KEY (idEscale) REFERENCES ESCALE ON DELETE CASCADE,
	PRIMARY KEY(idVol, idEscale)
);

