package Default;

public class Run {
    private static ParseFile fileParser = new ParseFile();

    public static void main(String[] args) {
        try {
            if (args.length == 0) {
                fileParser.parseFile("TestFile.txt");
            } else {
                fileParser.parseFile(args[0]);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
