// main module for executing the signal analysis (segmentation) algorithm

import java.io.*;
import java.util.*;
import SignalAnalysis.SignalAnalysis;

public class main {
	public static void main(String args[]) throws IOException {
		Scanner scan = new Scanner(System.in);
		
		System.out.print("Insert full path to data file: ");
		String path = scan.nextLine();

		SignalAnalysis algorithm = new SignalAnalysis();
		
		try {
			algorithm.sess_run(path, 10);
		} catch(IOException e) {
			System.out.println("ERROR: Algorithm threw IOException!");
		}
	}
}
