public class Noeud
{
	public Noeud filsGauche = null, filsDroit = null;
	public Symbole symbole;
	public Noeud(Symbole s, Noeud filsGauche, Noeud filsDroit)
	{
		this.symbole = s;
		this.filsGauche = filsGauche;
		this.filsDroit = filsDroit;
	}
	public int calcule()
	{
		if(this.symbole.estOperation())
		{
			int rfg = filsGauche.calcule();
			int rfd = filsDroit.calcule();
			switch(symbole.getOperation())
			{
				case '+' : return rfg + rfd;
				case '-' : return rfg - rfd;
				case '/' : return rfg / rfd;
				case '*' : return rfg * rfd;
			}
		}
		return symbole.getNombre();
	}
}
