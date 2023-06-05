// Programming Challenge description

/*
 * Given 
 * - A list of foriegn exchange rates
 * - A selected currency
 * - A target currency
 * Your goal is to caculate the max amount of the target currency
 * to 1 unit of the select currency through the FX transactions. Assume
 * all the transactions are free and done immediately. If you cannot finish
 * the exchange, return -1.0.
 *
 * Test1
 *
 * Input
 * USD,CAD,1.3;USD,GBP,0.71;USD,JPY,109;GBP,JPY,155
 * USD
 * JPY
 *
 * Expected Output
 * 110.05
 *
 * Test2
 *
 * Input
 * USD,GBP,0.7;USD,JPY,109;GBP,JPY,155;CAD,CNY,5.27;CAI,KRW,921,
 * USD
 * CNY
 *
 * Expected Output
 * -1.0
 *
 */

import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        InputStreamReader r = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(r);
        String conversion_rate = in.readLine();
        String conversion[] = conversion_rate.split(";");
        String currency1 = in.readLine();
        String currency2 = in.readLine();

        if(currency1.equals(currency2)){
            System.out.println(0);
            return;
        }
        Queue<String> queue = new LinkedList<>();
        ArrayList<String> visited = new ArrayList<>();
        for(String temp : conversion){
            String conversion_one[] = temp.split(",");
            if(conversion_one[0].equals(currency1)){
                queue.add(conversion_one[1]);
                queue.add(conversion_one[2]);
            }
            else if(conversion_one[1].equals(currency1)){
                double d = Double.parseDouble(conversion_one[2]);
                d=1/d;
                d=Math.round(d*100.0)/100.0;
                queue.add(conversion_one[0]);
                queue.add(d+"");
            }
        }
        visited.add(currency1);
        double max=-1.0;
        while(!queue.isEmpty()){
            String currency = queue.poll();
            double rate = Double.parseDouble(queue.poll());

            if(currency.equals(currency2)){
                if(rate>max) max=rate;
            }
            else{
                for(String temp : conversion){
                    String conversion_one[] = temp.split(",");
                    if(conversion_one[0].equals(currency) && !visited.contains(currency)){
                        double d = Double.parseDouble(conversion_one[2]);
                        d=d*rate;
                        d=Math.round(d*100.0)/100.0;
                        queue.add(conversion_one[1]);
                        queue.add(d+"");
                    }
                    else if(conversion_one[1].equals(currency) && !visited.contains(currency)){
                        double d = Double.parseDouble(conversion_one[2]);
                        d=1/d;
                        d=d*rate;
                        d=Math.round(d*100.0)/100.0;
                        queue.add(conversion_rate[0]);
                        queue.add(d+"");
                    }
                }
                visited.add(currency);
            }
        }
        System.out.println(max);
    }
}