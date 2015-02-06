package ds;

public abstract class Bouncer {
	public abstract boolean CanAccess(String macAddress);
	public abstract boolean Detects(String macAddress);
	public abstract String WhoIs(String macAddress);
}
