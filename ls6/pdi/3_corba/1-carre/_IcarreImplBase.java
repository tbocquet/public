
/**
* _IcarreImplBase.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from Icarre.idl
* vendredi 16 novembre 2012 10 h 21 CET
*/

public abstract class _IcarreImplBase extends org.omg.CORBA.portable.ObjectImpl
                implements Icarre, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors
  public _IcarreImplBase ()
  {
  }

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("carre", new java.lang.Integer (0));
  }

  public org.omg.CORBA.portable.OutputStream _invoke (String $method,
                                org.omg.CORBA.portable.InputStream in,
                                org.omg.CORBA.portable.ResponseHandler $rh)
  {
    org.omg.CORBA.portable.OutputStream out = null;
    java.lang.Integer __method = (java.lang.Integer)_methods.get ($method);
    if (__method == null)
      throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);

    switch (__method.intValue ())
    {
       case 0:  // Icarre/carre
       {
         int source = in.read_long ();
         int $result = (int)0;
         $result = this.carre (source);
         out = $rh.createReply();
         out.write_long ($result);
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:Icarre:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }


} // class _IcarreImplBase
