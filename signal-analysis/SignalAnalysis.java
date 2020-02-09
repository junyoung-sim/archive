// the signal analysis (segmentation) algorithm module

package SignalAnalysis;

import java.io.*;
import java.nio.Buffer;
import java.util.*;

public class SignalAnalysis {
	int minimum_segmentation_range = 3;
	int default_segmentation_range = 10;
	int maximum_segmentation_range = 25;
	String path;
	int segmentation_range = -1;

    public SignalAnalysis() {}

	// constructor of the class requires following arguments
	// data-file path, segmentation range, amount of databits to import from the data file
	public void sess_run(String data_path, int range) throws IOException {
		this.path = data_path;
		this.segmentation_range = default_segmentation_range;
		File f = new File(path);

		// verify if the specified segmentation range is valid in range
		if(range < this.minimum_segmentation_range || range > this.maximum_segmentation_range) {
			System.out.println("WARNING: Specified segmentation range is out of range... Reverting default segmentation range");
			this.segmentation_range = this.default_segmentation_range;
		} else {}

		// verify if the specified datafile is a valid path
		// if specified datafile path is invalid, terminate the program
		if(f.exists() == false) {
			System.out.println("ERROR: Specified datafile path does not exist... Terminating program!");
		} else {
			// run the segmentation algorithm
			try {
                signal_segmentation_algorithm();
			} catch(IOException e) {
				System.out.println("FATAL: IOException occurred while executing algorithm");
			}
		}
	}

	public void signal_segmentation_algorithm() throws IOException {
		// runs the actual segmentation algorithm on the input data,
		// overwrite the file with the segmentated data
        List<Integer> raw = new ArrayList<Integer>();
        List<Integer> seg = new ArrayList<Integer>();
        File f = new File(this.path);
        Scanner sc = new Scanner(f);

        while(sc.hasNextLine()) {
            String current_line = sc.nextLine();
            String words[] = current_line.split(",");
            for(String str: words) {
                try {
                    int data_point = Integer.parseInt(str);
                    raw.add(data_point);
                } catch (NumberFormatException nfe) {}
            }
        }

        Integer [] raw_signal = new Integer[raw.size()];
        raw_signal = raw.toArray(raw_signal);

		// run the signal segmentation algorithm
		// that detects two data points with the highest alteration value
        int idx1 = -1, idx2 = -1;
		int maximum_alteration = -10000;
		for(int r = 0; r < raw.size() - segmentation_range; r++) {
			for(int i = r; i < r + segmentation_range; i++) {
				if(i + 1 >= r + segmentation_range) {}
				else {
					int signal_alteration = Math.abs(raw_signal[i] - raw_signal[i + 1]);

					if(signal_alteration > maximum_alteration) {
						idx1 = i; idx2 = i + 1;
					} else {}
				}
			}

			// copy the selected two points of the datafile to the segmentated List
            seg.add(raw_signal[idx1]);
            seg.add(raw_signal[idx2]);
        }

        Integer [] segmentated_arr = new Integer[seg.size()];
        segmentated_arr = seg.toArray(segmentated_arr);

        PrintStream ps = new PrintStream("output.txt");
        for(int i = 0 ; i < seg.size(); i++) {
            ps.print(String.valueOf(segmentated_arr[i]) + ",");
        }
	}
}
