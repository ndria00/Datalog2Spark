package application;
import org.apache.spark.sql.Dataset;
import org.apache.spark.sql.Row;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.sql.functions.*;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
public class Main{
    public static void main(String[] args){
        SparkSession session = new SparkSession.Builder().appName("test").master("local").getOrCreate();
        session.sparkContext().setLogLevel("error");
        if(args.length == 0){
            System.out.println("No path to instance folder was given");
            System.exit(1);
        }
        String pathToInstance = args[0];
        if(pathToInstance.charAt(pathToInstance.length()-1) != '/' && pathToInstance.charAt(pathToInstance.length()-1) != '\\')
            pathToInstance = pathToInstance + '/';
        System.out.println("Opening instansce folder at: " + args[0]);
        //Compilation of rule with id 0
        Dataset<Row> b1 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "b1.csv");
        Dataset<Row> b2 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "b2.csv");
        Compiling join
        //Compilation of rule with id 1
        Dataset<Row> c1 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "c1.csv");
        Dataset<Row> c2 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "c2.csv");
        Compiling join
        //Compilation of rule with id 2
        Dataset<Row> c3 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "c3.csv");
        Dataset<Row> c4 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "c4.csv");
        Compiling join
        //Compilation of rule with id 3
        Dataset<Row> d1 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "d1.csv");
        Dataset<Row> d2 = session.read().format("csv").option("header", false).schema("term0INT, term1INT").option("sep", ";").load( + pathToInstance + "d2.csv");
        Compiling join
    }
}
