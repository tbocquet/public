package paquet-Suite;

public abstract class Suite
{
	// premier = u0 , pas = raison
	public int premier, pas;
	public Suite(int premier, int pas)
	{
		this.premier = premier;
		this.pas = pas;
	}
	public abstract int valeurAuRangN(int n);
	public abstract int sommeAuRangN(int n);

}
