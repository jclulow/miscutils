/*
 * Copyright (c) 2010, Joshua M. Clulow. All rights reserved.
 *
 * This file is distributable under the BSD license.
 *    (see ../BSD_LICENSE)
 */

import java.util.Random;

public class RandomPasswords
{
	public static void main(String[] argv)
	{
		int num = 0, len = 0;
		try
		{
			num = Integer.parseInt(argv[0]);
			len = Integer.parseInt(argv[1]);
		}
		catch (Exception e)
		{
			System.err.println("Usage: rndpass <num> <len>");
			System.err.println("        num - number of passwords to generate");
			System.err.println("        len - length of each password");
			System.exit(1);
		}
		for (int q = 0; q < num; q++)
			System.out.println(generatePassword(len));
	}

	public static String generatePassword(int len)
	{
		String password = "";
		Random r = new Random();

		while (password.length() < len)
		{
			int p = r.nextInt(26 * 2 + 10 + 4); // A-Z, a-z, 0-9, $, %, #, .

			if (p >= 0 && p <= 25)
				password += (char)(p -  0 + 'A');
			else if (p >= 26 && p <= 51)
				password += (char)(p - 26 + 'a');
			else if (p >= 52 && p < 61)
				password += (char)(p - 52 + '0');
			else
			{
				switch (p)
				{
					case 62: password += '$'; break;
					case 63: password += '%'; break;
					case 64: password += '#'; break;
					case 65: password += '.'; break;
				}
			}
		}

		return password;
	}
}

