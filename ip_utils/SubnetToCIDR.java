public class SubnetToCIDR {
	private static int co(String in) {
                int c = 0;
                for (int q = 0; q < in.length(); q++) {
                        if (in.charAt(q) == '0')
                                break;
                        else
                                c++;
                }
                return c;
        }

        private static String zrpad(String s, int len) {
                while (s.length() < len) {
                        s = "0" + s;
                }
                return s;
        }

        public static void main(String[] argv)
        {
                if (argv.length != 1) {
                        System.err.println("Usage: SubnetToCIDR <netmask>" +
				"   (e.g. 255.255.255.0)");
                        System.err.println("Output: <CIDR bitcount>      " +
				"        (e.g. 24)");
                        System.exit(1);
                }
                String[] terms = argv[0].split("\\.");
                if (terms.length != 4) {
                        System.err.println("Address did not have 4 dotted " +
				"terms!");
                        System.exit(2);
                }
                String binaddr = "";
                for (int q = 0; q < terms.length; q++) {
                        try {
                                int i = Integer.parseInt(terms[q]);
                                binaddr += zrpad(Integer.toBinaryString(i), 8);
                        }
                        catch (NumberFormatException nfe) {
                                System.err.println("Not a real netmask!");
                                System.exit(3);
                        }
                }
                System.out.println(co(binaddr));
        }
}

