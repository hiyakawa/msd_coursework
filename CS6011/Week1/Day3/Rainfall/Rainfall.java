import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class RainfallStatistics {
    private int month_;
    private int year_;
    private double rainfall_;

    private int getMonth() {return month_;}
    private double getRainfall() {return rainfall_;}

    public RainfallStatistics() {
        month_ = -1;
        year_ = -1;
        rainfall_ = -1.0;
    }

    public static void parseFile(String file_name) {
        try {
            Scanner fileReader = new Scanner(new FileInputStream(file_name));
            // split the text by spaces and new lines
            fileReader.useDelimiter("\\s+");
            // create an array of RainfallStatistics to store the data
            ArrayList<RainfallStatistics> rainfallData = new ArrayList<>();
            // create an object to record the data
            RainfallStatistics cur_data = new RainfallStatistics();
            int counter = 0;
            String cur_word;

            while (fileReader.hasNext()) {
                cur_word = fileReader.next();
                if (counter % 3 == 1) {
                    cur_data.month_ = convertMonth(cur_word);
                }
                else if (counter % 3 == 2) {
                    cur_data.year_ = Integer.parseInt(cur_word);
                }
                // we don't want to read in the 0th word which is the city!
                else if (counter != 0) {
                    cur_data.rainfall_ = Double.parseDouble(cur_word);
                    // push the current object back into the array
                    rainfallData.add(cur_data);
                    // allocate a new space for the current object
                    cur_data = new RainfallStatistics();
                }
                counter++;
            }

            // calculate the average rainfall amount for all the data points
            double sum_rainfall = 0.0;
            for (int i = 0; i < rainfallData.size(); i++) {
                sum_rainfall += rainfallData.get(i).rainfall_;
            }
            double avg_rainfall = sum_rainfall / rainfallData.size();

            // use Map to group the data by months and calculate mean values
            Map<Integer, DoubleSummaryStatistics> classify =
                    rainfallData.stream().collect(
                            Collectors.groupingBy(RainfallStatistics::getMonth,
                            Collectors.summarizingDouble(RainfallStatistics::getRainfall)));

            String months[] = new String[]
                    {"January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December"};

            // write to the result text file
            PrintWriter pw = new PrintWriter(new FileOutputStream("rainfall_results.txt"));
            pw.write("The overall average rainfall amount is "
                    + roundTwo(avg_rainfall) + " inches.\n");

            for (int i = 0; i < 12; i++) {
                pw.write("The average rainfall amount for " + months[i] + " is " +
                        roundTwo(classify.get(i + 1).getAverage()) + " inches.\n");
            }
            pw.close();
        }
        // throw exceptions if the file does not exist
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    // convert month in English to integers
    private static int convertMonth(String str_month) {
        int int_month = switch (str_month) {
            case "January" -> 1;
            case "February" -> 2;
            case "March" -> 3;
            case "April" -> 4;
            case "May" -> 5;
            case "June" -> 6;
            case "July" -> 7;
            case "August" -> 8;
            case "September" -> 9;
            case "October" -> 10;
            case "November" -> 11;
            case "December" -> 12;
            default -> -1;
        };
        return int_month;
    }

    // round doubles to two digits
    private static String roundTwo(double num) {
        String result = String.format("%.2f", num);
        return result;
    }
}

public class Main {
    public static void main(String[] args) {
        String file_name = "rainfall_data.txt";
        RainfallStatistics.parseFile(file_name);
    }
}